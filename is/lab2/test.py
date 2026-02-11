from lab2.main import generate_key
from serial_test import serial_test
from poker_test import poker_test
from correlation_test import correlation_test


def generate_key_positive_tests(n=1024):
    result = False
    key = None
    iter = 0
    while not result:
        key = generate_key(n)
        serial_result = serial_test(key)
        poker_result = poker_test(key)
        correlation_result = correlation_test(key)
        result = serial_result[-1] * poker_result[-1] * correlation_result[-1]
        iter += 1
    print(f"Ключ проходящий тесты найден за итераций: {iter}")
    return key


if __name__ == "__main__":
    with open("in.txt", 'r') as f:
        msg = f.read()
        bin_text = ''
        for ch in msg:
            bin_text += bin(ord(ch))[2:]
    gamma = generate_key_positive_tests(len(bin_text))
    with open("gamma.txt", 'w') as f:
        f.write(gamma)
    print("           ", msg)
    print("source txt:", bin_text)
    print("Gamma:     ", gamma)
    coded = int(bin_text, 2) ^ int(gamma, 2)
    coded_msg = bin(coded)[2:]
    with open("out.txt", 'w') as f:
        f.write(coded_msg)
    print("txt->coded:", "0"*(len(gamma) - len(coded_msg)) + coded_msg)

    print(f"source message serial test: {serial_test(bin_text)[-1]}")
    print(f"source message poker  test: {poker_test(bin_text)[-1]}")
    print(f"source message correl test: {correlation_test(bin_text)[-1]}")
    print(f"coded  message serial test: {serial_test(coded_msg)[-1]}")
    print(f"coded  message poker  test: {poker_test(coded_msg)[-1]}")
    print(f"coded  message correl test: {correlation_test(coded_msg)[-1]}")
