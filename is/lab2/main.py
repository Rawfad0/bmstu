import random


def generate_key(n=1024):
    reg_length = 57
    p_func = int((2**57 + 2**7) / 2)
    gamma = ''
    reg_random = random.choices(['0', '1'], k=reg_length)
    register_str = ''.join(reg_random)
    with open("key.txt", 'w') as f:
        f.write(register_str)
    for i in range(n):
        register = int(register_str, 2)
        # print("register:", register)
        # print("p_func:", p_func)
        callback = register ^ p_func
        # print("callback:", callback)
        # print("bit register:  ", register_str)
        # print("bit p_func:  ", bin(p_func))
        # print("bit_callback:", bin(callback))
        gamma += register_str[-1]
        register_str = str(str(bin(callback))[2:].count('1') % 2) + register_str[:-1]
    return gamma


if __name__ == "__main__":
    c = input("in/out:")
    if c == "in":
        with open("in.txt", 'r') as f:
            msg = f.read()
            bin_text = ''
            for ch in msg:
                bin_text += bin(ord(ch))[2:]
        gamma = generate_key(len(bin_text))
        # gamma = generate_key()
        with open("gamma.txt", 'w') as f:
            f.write(gamma)
        print("           ", msg)
        print("source txt:", bin_text)
        print("Gamma:     ", gamma)
        coded = int(bin_text, 2) ^ int(gamma, 2)
        with open("out.txt", 'w') as f:
            f.write(bin(coded)[2:])
        print("txt->coded:", bin(coded)[2:])
    elif c == "out":
        with open("out.txt", 'r') as f:
            coded = f.read()
        with open("gamma.txt", 'r') as f:
            gamma = f.read()
        print("coded:     ", coded)
        decoded = int(coded, 2) ^ int(gamma, 2)
        decoded = bin(decoded)[2:]
        print("decoded_bin", decoded)
        msg = ''
        for i in range(len(decoded)//7):
            msg += chr(int(decoded[7*i:7*(i + 1)], 2))
        print("decoded:   ", msg)
    else:
        quit()
