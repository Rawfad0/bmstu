import os
import struct


class LZWBinarayCompressor:
    def __init__(self, max_table_size=4096):
        self.max_table_size = max_table_size  # Максимальный размер словаря (12 бит) 4096

    def compress_file(self, input_path):
        filename, _ = os.path.splitext(input_path)
        output_path = filename + ".lzw"

        with open(input_path, "rb") as f:
            data = f.read()  # читаем бинарно

        compressed = self.compress(data)

        with open(output_path, "wb") as f:
            for code in compressed:
                f.write(struct.pack(">H", code))  # big-endian unsigned short

        print(f"Compressed: {input_path} -> {output_path}")
        return output_path

    def decompress_file(self, input_path):
        filename, _ = os.path.splitext(input_path)
        output_path = filename + "_decompressed"

        compressed = []
        with open(input_path, "rb") as f:
            while byte := f.read(2):
                compressed.append(struct.unpack(">H", byte)[0])

        decompressed = self.decompress(compressed)

        with open(output_path, "wb") as f:
            f.write(decompressed)

        print(f"Decompressed: {input_path} -> {output_path}")
        return output_path

    def compress(self, data: bytes) -> list[int]:
        dictionary = {bytes([i]): i for i in range(256)}
        dict_size = 256

        w = b""
        result = []
        for c in data:
            wc = w + bytes([c])
            if wc in dictionary:
                w = wc
            else:
                result.append(dictionary[w])
                if dict_size < self.max_table_size:
                    dictionary[wc] = dict_size
                    dict_size += 1
                w = bytes([c])
        if w:
            result.append(dictionary[w])

        return result

    def decompress(self, compressed: list[int]) -> bytes:
        dictionary = {i: bytes([i]) for i in range(256)}
        dict_size = 256

        w = bytes([compressed.pop(0)])
        result = [w]

        for k in compressed:
            if k in dictionary:
                entry = dictionary[k]
            elif k == dict_size:
                entry = w + w[:1]
            else:
                raise ValueError(f"Bad compressed k: {k}")

            result.append(entry)

            if dict_size < self.max_table_size:
                dictionary[dict_size] = w + entry[:1]
                dict_size += 1

            w = entry

        return b"".join(result)


def compression_ratio(original_file, compressed_file):
    original_size = os.path.getsize(original_file)
    compressed_size = os.path.getsize(compressed_file)

    if original_size == 0:
        raise ValueError("Исходный файл пустой")

    ratio = compressed_size / original_size
    # percent_reduction = (1 - ratio) * 100

    return ratio    # percent_reduction


if __name__ == "__main__":
    compressor = LZWBinarayCompressor()
    compressed_file = compressor.compress_file("1pdf.pdf")
    print(compression_ratio("1pdf.pdf", "1pdf.lzw"))
    compressed_file = compressor.compress_file("2docx.docx")
    print(compression_ratio("2docx.docx", "2docx.lzw"))
    compressed_file = compressor.compress_file("3txt.txt")
    print(compression_ratio("3txt.txt", "3txt.lzw"))
    compressed_file = compressor.compress_file("4png.png")
    print(compression_ratio("4png.png", "4png.lzw"))
    compressed_file = compressor.compress_file("5txt.txt")
    print(compression_ratio("5txt.txt", "5txt.lzw"))
    compressed_file = compressor.compress_file("6png.png")
    print(compression_ratio("6png.png", "6png.lzw"))

    # decompressed_file = compressor.decompress_file(compressed_file)
