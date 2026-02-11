from lab3.main import code_msg, baudot_code, baudot_reverse
from lab2.serial_test import serial_test
from lab2.poker_test import poker_test
from lab2.correlation_test import correlation_test

msg = "AVADAKEDAVRA ABC ABC ABC"

if __name__ == "__main__":
    coded_msg = code_msg(msg, [1, 2, 3, 2, 3])
    # coded_msg = code_msg(msg, [1, 2, 3, 4, 1, 2, 3])
    # coded_msg = code_msg(msg, [1, 3, 2, 4, 7, 9, 6])
    print("src msg:  ", msg)
    print("coded msg:", coded_msg)

    bit_msg1 = ''
    for ch in msg:
        bit_msg1 += f"{baudot_code[ch]:05b}"
    print("bit src msg:  ", bit_msg1)

    bit_msg2 = ''
    for ch in coded_msg:
        bit_msg2 += f"{baudot_code[ch]:05b}"
    print("bit coded msg:", bit_msg2)

    print(f"coded message SERIAL (a=0.1)(k=4) : {serial_test(bit_msg2)[-1]}")
    print(f"coded message POKER  (a=0.1)(df=6): {poker_test(bit_msg2)[-1]}")
    print(f"coded message CORREL (a=0.5)(k=9) : {correlation_test(bit_msg2)[-1]}")
