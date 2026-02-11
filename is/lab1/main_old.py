ru_alphabet = "абвгдеёжзийклмнопрстуфхцчшщьъыэюя"


def generate_table_file(filename, key):
    table = []
    with open(f'{filename}_table.txt', 'w') as f:
        for i in range(len(key)):
            ch = key[i]
            chi = ru_alphabet.find(ch)
            line = ru_alphabet[chi:] + ru_alphabet[:chi]
            table.append(line)
            f.write(line + '\n')
    return table


input_filename = input()
if len(input_filename) < 7:
    quit()

# abc_in.txt
filename = input_filename[:-7]
keyfile = filename + '_key.txt'
with open(input_filename, 'r') as f, open(keyfile, 'r') as k:
    message = f.read()
    key = k.read()

print("Message: ", message)
print("Key:     ", key)
if "_in" in input_filename:
    table = generate_table_file(filename, key)
    print(table)
    new_msg = ''
    for i in range(len(message)):
        ch = message[i]
        if ch.isalpha():
            chi = ru_alphabet.find(ch)
            new_msg += table[i % len(key)][chi]
        else:
            new_msg += ch
    print("Out msg: ", new_msg)
    with open(f"{filename}_out.txt", 'w') as f:
        f.write(new_msg)
elif "_out" in filename:
    print("")
else:
    quit()