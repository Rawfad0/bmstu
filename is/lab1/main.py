import random

ru_alphabet = "абвгдеёжзийклмнопрстуфхцчшщьъыэюя"

input_filename = input()
with open(input_filename, 'r') as f:
    msg = f.read()
print("Input msg:", msg)

filename = ''.join(input_filename.split('_')[:-1])
if "_in" in input_filename:
    key = random.sample(list(ru_alphabet), 33)
    with open(f"{filename}_key.txt", 'w') as f:
        f.write(''.join(key))
    print("    ", ru_alphabet)
    print("Key: ", *key, sep='')
    new_msg = ''
    for i in range(len(msg)):
        ch = msg[i]
        if ch.isalpha():
            chi = ru_alphabet.find(ch)
            new_msg += key[chi]
        else:
            new_msg += ch
    with open(f"{filename}_out.txt", 'w') as f:
        f.write(new_msg)
    print("New:", new_msg)
elif "_out" in input_filename:
    with open(f"{filename}_key.txt", 'r') as f:
        key = f.read()
    new_msg = ''
    for i in range(len(msg)):
        ch = msg[i]
        if ch.isalpha():
            chi = key.find(ch)
            new_msg += ru_alphabet[chi]
        else:
            new_msg += ch
    with open(f"{filename}_in.txt", 'w') as f:
        f.write(new_msg)
    print("Decoded: ", new_msg)
else:
    quit()

