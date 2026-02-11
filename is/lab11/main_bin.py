import heapq
import os
import pickle


class HuffmanCodingBinary:
    def __init__(self, path):
        self.path = path
        self.heap = []
        self.codes = {}
        self.reverse_mapping = {}

    class HeapNode:
        def __init__(self, byte, freq):
            self.byte = byte
            self.freq = freq
            self.left = None
            self.right = None

        def __lt__(self, other):
            return self.freq < other.freq

        def __eq__(self, other):
            if other is None or not isinstance(other, HuffmanCodingBinary.HeapNode):
                return False
            return self.freq == other.freq

    def make_frequency_dict(self, data):
        frequency = {}
        for b in data:
            frequency[b] = frequency.get(b, 0) + 1
        return frequency

    def make_heap(self, frequency):
        for byte, freq in frequency.items():
            heapq.heappush(self.heap, self.HeapNode(byte, freq))

    def merge_nodes(self):
        while len(self.heap) > 1:
            node1 = heapq.heappop(self.heap)
            node2 = heapq.heappop(self.heap)

            merged = self.HeapNode(None, node1.freq + node2.freq)
            merged.left = node1
            merged.right = node2

            heapq.heappush(self.heap, merged)

    def make_codes_helper(self, root, current_code):
        if root is None:
            return
        if root.byte is not None:
            self.codes[root.byte] = current_code
            self.reverse_mapping[current_code] = root.byte
            return
        self.make_codes_helper(root.left, current_code + "0")
        self.make_codes_helper(root.right, current_code + "1")

    def make_codes(self):
        if not self.heap:
            return
        root = heapq.heappop(self.heap)
        self.make_codes_helper(root, "")

    def get_encoded_data(self, data):
        return "".join(self.codes[b] for b in data)

    def pad_encoded_data(self, encoded_data):
        extra_padding = 8 - len(encoded_data) % 8
        if extra_padding == 8:
            extra_padding = 0
        padded_info = "{0:08b}".format(extra_padding)
        encoded_data += "0" * extra_padding
        return padded_info + encoded_data

    def get_byte_array(self, padded_encoded_data):
        if len(padded_encoded_data) % 8 != 0:
            raise ValueError("Encoded data not padded properly")
        return bytearray(int(padded_encoded_data[i:i+8], 2) for i in range(0, len(padded_encoded_data), 8))

    def compress(self):
        filename, _ = os.path.splitext(self.path)
        output_path = filename + ".azj"

        with open(self.path, 'rb') as file:
            data = file.read()

        frequency = self.make_frequency_dict(data)
        self.make_heap(frequency)
        self.merge_nodes()
        self.make_codes()

        encoded_data = self.get_encoded_data(data)
        padded_encoded_data = self.pad_encoded_data(encoded_data)
        byte_array = self.get_byte_array(padded_encoded_data)

        with open(output_path, 'wb') as output:
            pickle.dump({'codes': self.codes, 'data': byte_array}, output)

        print(f"Compressed: {self.path} into {output_path}")
        return output_path

    def remove_padding(self, padded_encoded_data):
        padded_info = padded_encoded_data[:8]
        extra_padding = int(padded_info, 2)
        padded_encoded_data = padded_encoded_data[8:]
        return padded_encoded_data[:-extra_padding] if extra_padding > 0 else padded_encoded_data

    def decode_data(self, encoded_data):
        current_code = ""
        decoded_bytes = bytearray()
        for bit in encoded_data:
            current_code += bit
            if current_code in self.reverse_mapping:
                decoded_bytes.append(self.reverse_mapping[current_code])
                current_code = ""
        return decoded_bytes

    def decompress(self, input_path, file_type):
        filename, _ = os.path.splitext(input_path)
        output_path = f"{filename}_decompressed.{file_type}"

        with open(input_path, 'rb') as file:
            obj = pickle.load(file)
            self.codes = obj['codes']
            self.reverse_mapping = {v: k for k, v in self.codes.items()}
            byte_data = obj['data']

        bit_string = "".join(f"{byte:08b}" for byte in byte_data)
        encoded_data = self.remove_padding(bit_string)
        decompressed_data = self.decode_data(encoded_data)

        with open(output_path, 'wb') as output:
            output.write(decompressed_data)

        print(f"Decompressed: {self.path} into {output_path}")
        return output_path


def compression_ratio(original_file, compressed_file):
    original_size = os.path.getsize(original_file)
    compressed_size = os.path.getsize(compressed_file)

    if original_size == 0:
        raise ValueError("Исходный файл пустой")

    ratio = compressed_size / original_size
    # percent_reduction = (1 - ratio) * 100

    return ratio    # percent_reduction


if __name__ == "__main__":
    path = "1pdf.pdf"
    h = HuffmanCodingBinary(path)
    compressed = h.compress()
    path = "2docx.docx"
    h = HuffmanCodingBinary(path)
    compressed = h.compress()
    path = "3txt.txt"
    h = HuffmanCodingBinary(path)
    compressed = h.compress()
    path = "4png.png"
    h = HuffmanCodingBinary(path)
    compressed = h.compress()
    h.decompress(compressed, 'png')
    path = "5txt.txt"
    h = HuffmanCodingBinary(path)
    compressed = h.compress()
    print(compression_ratio("1pdf.pdf", "1pdf.azj"))
    print(compression_ratio("2docx.docx", "2docx.azj"))
    print(compression_ratio("3txt.txt", "3txt.azj"))
    print(compression_ratio("4png.png", "4png.azj"))
    print(compression_ratio("5txt.txt", "5txt.azj"))
