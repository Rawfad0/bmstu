baudot_code = {
    'A': 0b00011, 'B': 0b11001, 'C': 0b01110, 'D': 0b01001,
    'E': 0b00001, 'F': 0b01101, 'G': 0b11010, 'H': 0b10100,
    'I': 0b00110, 'J': 0b01011, 'K': 0b01111, 'L': 0b10010,
    'M': 0b11100, 'N': 0b01100, 'O': 0b11000, 'P': 0b10110,
    'Q': 0b10111, 'R': 0b01010, 'S': 0b00101, 'T': 0b10000,
    'U': 0b00111, 'V': 0b11110, 'W': 0b10011, 'X': 0b11101,
    'Y': 0b10101, 'Z': 0b10001,
    ' ': 0b00100,
    '+': 0b11111,
    '-': 0b11011,
    '*': 0b01000,
    '/': 0b00010,
    '.': 0b00000
}

baudot_reverse = {
    '00011': 'A', '11001': 'B', '01110': 'C', '01001': 'D',
    '00001': 'E', '01101': 'F', '11010': 'G', '10100': 'H',
    '00110': 'I', '01011': 'J', '01111': 'K', '10010': 'L',
    '11100': 'M', '01100': 'N', '11000': 'O', '10110': 'P',
    '10111': 'Q', '01010': 'R', '00101': 'S', '10000': 'T',
    '00111': 'U', '11110': 'V', '10011': 'W', '11101': 'X',
    '10101': 'Y', '10001': 'Z',
    '00100': ' ',
    '11111': '+',
    '11011': '-',
    '01000': '*',
    '00010': '/',
    '00000': '.'
}


def code_msg(msg, keys):
    if len(msg) % 6 != 0:
        msg += ' '*(6 - len(msg) % 6)
    coded_msg = ''
    for i in range((len(msg) - 1) // 6 + 1):
        block = msg[i*6:(i+1)*6]
        coded_msg += code_block(block, keys)
    return coded_msg


def code_block(msg, keys):
    bit_msg = ''
    for ch in msg:
        bit_msg += f"{baudot_code[ch]:05b}"

    first, second = bit_msg[:15], bit_msg[15:]
    for key in keys:
        first = first[key:] + first[:key]
        first, second = second, f"{int(first, 2) ^ int(second, 2):015b}"
    coded = first + second

    new_msg = ''
    for i in range(len(coded) // 5):
        new_msg += baudot_reverse[coded[i*5:(i+1)*5]]

    return new_msg


def decode_msg(msg, keys):
    if len(msg) % 6 != 0:
        msg += ' '*(6 - len(msg) % 6)
    decoded_msg = ''
    for i in range((len(msg) - 1) // 6 + 1):
        block = msg[i * 6:(i + 1) * 6]
        decoded_msg += decode_block(block, keys)
    return decoded_msg


def decode_block(msg, keys):
    bit_msg = ''
    for ch in msg:
        bit_msg += f"{baudot_code[ch]:05b}"

    first, second = bit_msg[:15], bit_msg[15:]
    for key in keys:
        first, second = f"{int(first, 2) ^ int(second, 2):015b}", first
        first = first[-key:] + first[:-key]
    coded = first + second

    new_msg = ''
    for i in range(len(coded) // 5):
        new_msg += baudot_reverse[coded[i * 5:(i + 1) * 5]]

    return new_msg


if __name__ == "__main__":
    # msg = "AVADAK"
    # msg = "EDAVRA"
    # coded = code_msg(msg, [1, 2])
    # print(coded)

    # msg = "MOSSTR"
    # decoded = decode_msg(msg, [2, 1])
    # print(decoded)

    coded = code_msg("EDAVRAABC", [1, 2, 3])
    print(coded)
    print(decode_msg(coded, [3, 2, 1]))
