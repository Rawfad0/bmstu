from time import time
from lab5.aes import encrypt, text_to_block
from lab5.aes_opt import encrypt2
from lab2.serial_test import serial_test
from lab2.poker_test import poker_test
from lab2.correlation_test import correlation_test
import random

msg = "ABCabc 123 abc45 aoje24fie4n _)2foi242s24e n3se24ion[231EDO EJF]AOPDEEA]CEOEFJ]OPM]r om]on"
# msg = "hello hello"

if __name__ == "__main__":
    tbb = time()
    # random.seed(12345)
    random.seed(321)
    # key = [i for i in range(1, 17)]
    key = random.choices([i for i in range(1, 17)], k=16)
    print(key)
    block = text_to_block(msg)
    tb = time()
    coded_msg = encrypt(block, key)     # 0.133 ms
    te = time()
    print("TIME", te - tb)
    print("src msg:  ", msg)
    print("coded msg:", coded_msg)

    bit_msg2 = ''
    for ch in coded_msg:
        bit_msg2 += f"{ch:08b}"
    print("bit coded msg:", bit_msg2)

    print(f"coded message SERIAL (a=0.1)(k=4) : {serial_test(bit_msg2)[-1]}")
    print(f"coded message POKER  (a=0.1)(df=6): {poker_test(bit_msg2)[-1]}")
    print(f"coded message CORREL (a=0.5)(k=9) : {correlation_test(bit_msg2)[-1]}")
