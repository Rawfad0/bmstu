class DES:
    # Начальная перестановка (IP)
    IP = [
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    ]

    # Конечная перестановка (IP^-1)
    FP = [
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    ]

    # Перестановка расширения (E)
    E = [
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
    ]

    # P-блок перестановка
    P = [
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25
    ]

    # S-блоки
    S_BOX = [
        # S1
        [
            [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7],
            [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
            [4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0],
            [15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]
        ],
        # S2
        [
            [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10],
            [3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5],
            [0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15],
            [13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9]
        ],
        # S3
        [
            [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8],
            [13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1],
            [13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7],
            [1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]
        ],
        # S4
        [
            [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15],
            [13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9],
            [10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4],
            [3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]
        ],
        # S5
        [
            [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9],
            [14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6],
            [4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14],
            [11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]
        ],
        # S6
        [
            [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11],
            [10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8],
            [9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6],
            [4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]
        ],
        # S7
        [
            [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1],
            [13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6],
            [1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2],
            [6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]
        ],
        # S8
        [
            [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7],
            [1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2],
            [7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8],
            [2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]
        ]
    ]

    # PC2 - перестановка сжатия для ключа (56 бит -> 48 бит)
    PC2 = [
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    ]

    # Сдвиги для ключей
    SHIFTS = [1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1]

    def __init__(self, key):
        """Инициализация с 56-битным ключом (7 символов)"""
        if len(key) != 7:
            raise ValueError("Ключ должен быть ровно 7 символов (56 бит)")
        self.key = key
        self.subkeys = self.generate_subkeys()

    def string_to_bit_array(self, text):
        """Преобразование строки в битовый массив"""
        array = []
        for char in text:
            binval = bin(ord(char))[2:].zfill(8)
            array.extend([int(x) for x in list(binval)])
        return array

    def bit_array_to_string(self, array):
        """Преобразование битового массива в строку"""
        res = []
        for i in range(0, len(array), 8):
            if i + 8 > len(array):
                break
            byte = array[i:i + 8]
            char_code = int(''.join(str(bit) for bit in byte), 2)
            res.append(chr(char_code))
        return ''.join(res)

    def permute(self, block, table):
        """Выполнение перестановки согласно таблице"""
        # Проверяем длину блока
        max_index = max(table)
        if len(block) < max_index:
            raise ValueError(f"Блок слишком короткий: {len(block)} бит, требуется минимум {max_index} бит")

        return [block[x - 1] for x in table]

    def left_shift(self, block, n):
        """Циклический сдвиг влево"""
        return block[n:] + block[:n]

    def generate_subkeys(self):
        """Генерация 16 подключей из 56-битного ключа"""
        # Преобразуем 7-символьный ключ в 56 бит
        key_bits = self.string_to_bit_array(self.key)
        # Разделение на левую и правую части по 28 бит
        left = key_bits[:28]
        right = key_bits[28:]
        # Генерация 16 подключей
        subkeys = []
        for i in range(16):
            # Сдвиг влево
            left = self.left_shift(left, self.SHIFTS[i])
            right = self.left_shift(right, self.SHIFTS[i])
            # Объединение и применение PC2
            combined = left + right
            subkey = self.permute(combined, self.PC2)
            subkeys.append(subkey)
            # print(f"Подключ {i + 1}: {subkey}")
        return subkeys

    def xor(self, a, b):
        """Побитовое XOR"""
        return [x ^ y for x, y in zip(a, b)]

    def f_function(self, right, subkey):
        """Функция f для одного раунда"""
        # Расширение до 48 бит
        expanded = self.permute(right, self.E)

        # XOR с подключом
        xored = self.xor(expanded, subkey)

        # S-блоки
        sbox_output = []
        for i in range(8):
            # Берем 6 бит для каждого S-блока
            block = xored[i * 6:(i + 1) * 6]
            row = (block[0] << 1) + block[5]  # Первый и последний биты
            col = (block[1] << 3) + (block[2] << 2) + (block[3] << 1) + block[4]  # Средние 4 бита
            value = self.S_BOX[i][row][col]

            # Преобразование в 4 бита
            bin_value = bin(value)[2:].zfill(4)
            sbox_output.extend([int(bit) for bit in bin_value])

        # P-перестановка
        return self.permute(sbox_output, self.P)

    def encrypt_block(self, block):
        """Шифрование одного блока по схеме Фейстеля"""
        # print(f"Шифрование блока: {len(block)} бит")
        # Начальная перестановка
        block = self.permute(block, self.IP)
        # Разделение на левую и правую части
        left = block[:32]
        right = block[32:]
        # print(f"После IP: L={len(left)} бит, R={len(right)} бит")
        # 16 раундов Фейстеля (последний без замены)
        for i in range(16):
            # Смеситель: left = left XOR f(right, key)
            new_left = self.xor(left, self.f_function(right, self.subkeys[i]))
            # Замена (кроме последнего раунда)
            if i != 15:
                left = right
                right = new_left
            else:
                left = new_left
                # right остается без изменений в последнем раунде
            # print(f"Раунд {i + 1}: L={len(left)} бит, R={len(right)} бит")

        # Финальное объединение
        combined = left + right

        # Конечная перестановка
        return self.permute(combined, self.FP)

    def decrypt_block(self, block):
        """Дешифрование одного блока"""
        # print(f"Дешифрование блока: {len(block)} бит")

        # Начальная перестановка
        block = self.permute(block, self.IP)

        # Разделение на левую и правую части
        left = block[:32]
        right = block[32:]

        # 16 раундов Фейстеля с ключами в обратном порядке
        for i in range(15, -1, -1):
            # Смеситель: left = left XOR f(right, key)
            new_left = self.xor(left, self.f_function(right, self.subkeys[i]))

            # Замена (кроме первого раунда при дешифровании)
            if i != 0:
                left = right
                right = new_left
            else:
                left = new_left
                # right остается без изменений в первом раунде

        # Финальное объединение
        combined = left + right

        # Конечная перестановка
        return self.permute(combined, self.FP)

    def pad_text(self, text):
        """Дополнение текста до размера блока"""
        padding_length = 8 - (len(text) % 8)
        if padding_length == 8:
            padding_length = 0
        return text + '\0' * padding_length

    def unpad_text(self, text):
        """Удаление дополнения из текста"""
        return text.rstrip('\0')

    def encrypt(self, plaintext):
        """Шифрование текста"""
        padded_text = self.pad_text(plaintext)
        encrypted_blocks = []
        for i in range(0, len(padded_text), 8):
            block_text = padded_text[i:i + 8]
            # print(f"\nОбработка блока {i // 8 + 1}: '{block_text}'")
            block_bits = self.string_to_bit_array(block_text)
            encrypted_bits = self.encrypt_block(block_bits)
            encrypted_blocks.append(self.bit_array_to_string(encrypted_bits))
        return ''.join(encrypted_blocks)

    def decrypt(self, ciphertext):
        """Дешифрование текста"""
        decrypted_blocks = []

        for i in range(0, len(ciphertext), 8):
            block_text = ciphertext[i:i + 8]
            # print(f"\nОбработка блока {i // 8 + 1}")
            block_bits = self.string_to_bit_array(block_text)
            decrypted_bits = self.decrypt_block(block_bits)
            decrypted_blocks.append(self.bit_array_to_string(decrypted_bits))

        return self.unpad_text(''.join(decrypted_blocks))


def format_binary_display(bits, group=8):
    """Форматирование битов для красивого отображения"""
    result = []
    for i in range(0, len(bits), group):
        group_bits = bits[i:i + group]
        result.append(''.join(str(bit) for bit in group_bits))
    return ' '.join(result)


def bytes_to_hex(text):
    """Преобразование байтов в hex строку"""
    return ''.join(f'{ord(c):02x}' for c in text)


def main():
    key = "\x00\x00\x00\x00\x00\x00\x00"
    plaintext = "hello"
    print(f"Ключ: '{key}', длина: {len(key)} символов = {len(key) * 8} бит")
    print(f"Исходный текст: '{plaintext}', длина: {len(plaintext)} символов = {len(plaintext) * 8} бит")
    des = DES(key)
    ciphertext = des.encrypt(plaintext)
    print(f"Зашифрованный текст (hex): {bytes_to_hex(ciphertext)}")
    decrypted = des.decrypt(ciphertext)
    print(f"Расшифрованный текст: '{decrypted}'")


if __name__ == "__main__":
    main()
