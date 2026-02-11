import time

from bin_rotors import *


def bin2int(b):
    return int(b, 2)


def int2bin(i):
    res = str(bin(i % 2**8))[2:]
    res = "0"*(8 - len(res)) + res
    return res


def process_rotor(ch, shift, rotor):
    step1 = int2bin(bin2int(ch) + shift)
    step2 = rotor[step1]
    step3 = int2bin(bin2int(step2) - shift)
    return step3


def enigma_code_ch(ch, n, shifts, forwards, backwards):
    for i in range(n):
        ch = process_rotor(ch, shifts[i], forwards[i])
    ch = reflector[ch]
    for i in range(n - 1, -1, -1):
        ch = process_rotor(ch, shifts[i], backwards[i])
    return ch


def enigma_code(msg, n, shifts, periods, forwards, backwards):
    coded = []
    shifts = list(map(bin2int, shifts))
    for i in range(len(msg)):
        ch = msg[i]
        for j in range(n):
            if periods[j] != 0 and (i + 1) % periods[j] == 0:
                shifts[j] = (shifts[j] + 1) % 2**8
        coded_ch = enigma_code_ch(ch, n, shifts, forwards, backwards)
        coded.append(coded_ch)
    return coded


def load_file(file_name: str) -> list[str]:
    res: list[str] = []
    with open(file_name, "rb") as file:
        data = file.read()
        for num in data:
            b_num = bin(num)
            b_num = b_num[2:]
            b_num = "0" * (8 - len(b_num)) + b_num
            res.append(b_num)
    return res


def save_file(file_name: str, data: list[str]) -> None:
    with open(file_name, "wb") as file:
        for bit_str in data:
            num = int(bit_str, 2)
            file.write(bytes([num]))


if __name__ == "__main__":
    data = load_file("crypt.jpg")
    tb = time.time()
    res: list[str] = enigma_code(
        data,
        3,
        ["10101010", "01010101", "11101111"],
        [1, 0, 0],
        [rotor_1_forward, rotor_2_forward, rotor_3_forward],
        [rotor_1_backward, rotor_2_backward, rotor_3_backward]
    )
    te = time.time()
    print(te - tb)
    save_file("out.jpg", res)
