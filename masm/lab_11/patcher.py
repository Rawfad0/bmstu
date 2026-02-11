"""
PASSWORD:
mov     dword [ esp+    $00000038], $73736170
C7      44      24      38          70 61 73 73

password -> esp+38

welcome to my crack me:
mov     dword [ esp],   $00406044
C7      04      24      44 60 40 00

CALC:
esp = 0061FED0
     +      38
      0061FF08
      
RESULT:
mov     dword [ esp],   $0061FF08  
C7      04      24      08 FF 61 00    
"""


filename = "crackme_copy.exe"

print(f"Патчер программы {filename}.")
print("1. Изменить количество попыток;")
print("2. Вывести пароль вместо приглашения.")
choice = int(input(": "))
if choice == 1:
    buf_size = 5
    new_attempts_number = int(input("Введите новое количество попыток: "))
    if 0 <= new_attempts_number <= 100:
        # Задает число из которого вычитается число неудачных попыток (для вывода)
        # mov eax, 5
        # B8 05 00 00 00
        printer_attempts_code = b"\xb8\x05\x00\x00\x00"


        # Задает количество попыток
        # cmp dword ptr [esp+4Ch], 5
        # 83 7C 24 4C 05
        counter_attempts_code = b"\x83\x7c\x24\x4c\x05"

        with open(filename, "r+b") as f:
            f.seek(0, 2)                                                        # Переместиться в конец файла
            size = f.tell()                                                     # Узнать текущий индекс (он же размер файла)
            f.seek(0, 0)                                                        # Переместиться в начало файла
            while f.tell() != size - buf_size:
                buf = f.read(buf_size)                                          # Считать символы в буфер
                if buf == printer_attempts_code:
                    f.seek(-buf_size + 1, 1)                                    # Перейти к заменяемому символу
                    f.write(new_attempts_number.to_bytes(1, "little"))          # Записать новое значение
                    f.seek(buf_size - 2, 1)                                     # Пройти дальше
                    print("Выводимое количество попыток успешно пропатчено.")
                if buf == counter_attempts_code:
                    f.seek(-buf_size + 4, 1)                                    # Перейти к заменяемому символу
                    f.write(new_attempts_number.to_bytes(1, "little"))          # Записать новое значение
                    f.seek(buf_size - 5, 1)                                     # Пройти дальше
                    print("Количество попыток успешно пропатчено.")
                f.seek(-buf_size + 1, 1)                                        # Следующее чтение со следующего символа
    else:
        print("Количество меньше 0 или больше 100.")
elif choice == 2:
    buf_size = 7
    # Задает приглашение
    prompt_code = b"\xC7\x04\x24\x44\x60\x40\x00"
    password_addres = (b"\x08", b"\xFF", b"\x61", b"\x00")
    with open(filename, "r+b") as f:
            f.seek(0, 2)                                                        # Переместиться в конец файла
            size = f.tell()                                                     # Узнать текущий индекс (он же размер файла)
            f.seek(0, 0)                                                        # Переместиться в начало файла
            while f.tell() != size - buf_size:
                buf = f.read(buf_size)                                          # Считать символы в буфер
                if buf == prompt_code:
                    f.seek(-buf_size + 3, 1)                                    # Перейти к заменяемому символу
                    for ch in password_addres:
                        f.write(ch)                                             # Записать новое значение
                    print("Приглашение успешно пропатчено.")
                f.seek(-buf_size + 1, 1)    
else:
    print("Нет пункта меню.")
    