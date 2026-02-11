reflector = {
    'A': 'Y',
    'B': 'R',
    'C': 'U',
    'D': 'H',
    'E': 'Q',
    'F': 'S',
    'G': 'L',
    'H': 'D',
    'I': 'P',
    'J': 'X',
    'K': 'N',
    'L': 'G',
    'M': 'O',
    'N': 'K',
    'O': 'M',
    'P': 'I',
    'Q': 'E',
    'R': 'B',
    'S': 'F',
    'T': 'Z',
    'U': 'C',
    'V': 'W',
    'W': 'V',
    'X': 'J',
    'Y': 'A',
    'Z': 'T'
}

rotor_3_forward = {
    'A': 'B',
    'B': 'D',
    'C': 'F',
    'D': 'H',
    'E': 'J',
    'F': 'L',
    'G': 'C',
    'H': 'P',
    'I': 'R',
    'J': 'T',
    'K': 'X',
    'L': 'V',
    'M': 'Z',
    'N': 'N',
    'O': 'Y',
    'P': 'E',
    'Q': 'I',
    'R': 'W',
    'S': 'G',
    'T': 'A',
    'U': 'K',
    'V': 'M',
    'W': 'U',
    'X': 'S',
    'Y': 'Q',
    'Z': 'O'
}

rotor_3_backward = {v: k for k, v in rotor_3_forward.items()}

rotor_2_forward = {
    'A': 'A',
    'B': 'J',
    'C': 'D',
    'D': 'K',
    'E': 'S',
    'F': 'I',
    'G': 'R',
    'H': 'U',
    'I': 'X',
    'J': 'B',
    'K': 'L',
    'L': 'H',
    'M': 'W',
    'N': 'T',
    'O': 'M',
    'P': 'C',
    'Q': 'Q',
    'R': 'G',
    'S': 'Z',
    'T': 'N',
    'U': 'P',
    'V': 'Y',
    'W': 'F',
    'X': 'V',
    'Y': 'O',
    'Z': 'E'
}

rotor_2_backward = {v: k for k, v in rotor_2_forward.items()}

rotor_1_forward = {
    'A': 'E',
    'B': 'K',
    'C': 'M',
    'D': 'F',
    'E': 'L',
    'F': 'G',
    'G': 'D',
    'H': 'Q',
    'I': 'V',
    'J': 'Z',
    'K': 'N',
    'L': 'T',
    'M': 'O',
    'N': 'W',
    'O': 'Y',
    'P': 'H',
    'Q': 'X',
    'R': 'U',
    'S': 'S',
    'T': 'P',
    'U': 'A',
    'V': 'I',
    'W': 'B',
    'X': 'R',
    'Y': 'C',
    'Z': 'J'
}

rotor_1_backward = {v: k for k, v in rotor_1_forward.items()}


def ch2int(ch):
    return ord(ch) - ord('A')


def int2ch(i):
    return chr(i % 26 + ord('A'))


def process_rotor(ch, shift, rotor):
    step1 = int2ch(ch2int(ch) + shift)
    step2 = rotor[step1]
    step3 = int2ch(ch2int(step2) - shift)
    return step3


def enigma_code_ch(ch, n, shifts, forwards, backwards):
    for i in range(n):
        ch = process_rotor(ch, shifts[i], forwards[i])
    ch = reflector[ch]
    for i in range(n - 1, -1, -1):
        ch = process_rotor(ch, shifts[i], backwards[i])
    return ch


def enigma_code(msg, n, shifts, periods, forwards, backwards):
    coded = ''
    shifts = list(map(ch2int, shifts))
    print(msg, shifts)
    for i in range(len(msg)):
        ch = msg[i]
        for j in range(n):
            if periods[j] != 0 and (i + 1) % periods[j] == 0:
                shifts[j] = (shifts[j] + 1) % 26
        coded_ch = enigma_code_ch(ch, n, shifts, forwards, backwards)
        coded += coded_ch
    return coded


coded_msg = enigma_code(
    'ABC',
    3,
    ['Q', 'V', 'C'],
    [1, 0, 0],
    [rotor_1_forward, rotor_2_forward, rotor_3_forward],
    [rotor_1_backward, rotor_2_backward, rotor_3_backward]
)
print("CODED MESSAGE:", coded_msg)
decoded_msg = enigma_code(
    coded_msg,
    3,
    ['Q', 'V', 'C'],
    [1, 0, 0],
    [rotor_1_forward, rotor_2_forward, rotor_3_forward],
    [rotor_1_backward, rotor_2_backward, rotor_3_backward]
)
print("DECODED MESSAGE:", decoded_msg)
