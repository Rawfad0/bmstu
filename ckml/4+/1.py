import re


def is_valid_expression(expression):
    pattern = re.compile(
        r"^"
        r"(((\d+(\.\d*)?)|"
        r"(\((\s?\d+(\.\d*)?\s?[+\-*/]\s?)*\d+(\.\d*)?\)))"
        r"\s?[+\-*/]\s?)*"
        r"((\d+(\.\d*)?)|"
        r"(\((\s?\d+(\.\d*)?\s?[+\-*/]\s?)*\d+(\.\d*)?\)))"
        r"$"
    )
    return bool(pattern.match(expression))


print("Expected: True; Result: ", is_valid_expression("(8 + 3)"))

print("Expected: True; Result: ", is_valid_expression("(3 + 5) * (2 - 8)"))

print("Expected: True; Result: ", is_valid_expression("3 + 5 * (2 - 8)"))
# Должна вернуть True

print("Expected: False; Result: ", is_valid_expression("3 + 5 * ( 2 - 8"))
# Должна вернуть False, т.к. отсутствует закрывающая скобка

print("Expected: True; Result: ", is_valid_expression("3.14 + 2.718 / 1.618"))
# Должна вернуть True

print("Expected: False; Result: ", is_valid_expression("abc + 123"))
# Должна вернуть False, т.к. "abc" не является числом

print("Expected: False; Result: ", is_valid_expression("123 +"))
# Должна вернуть False, т.к. отсутствует второй операнд

print("Expected: True; Result: ", is_valid_expression("123 + (12)"))
# Должна вернуть True

print("Expected: True; Result: ", is_valid_expression("3+2"))
# Должна вернуть True