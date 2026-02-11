t = {
    'M': 1000,
    'CM': 900,
    'D': 500,
    'CD': 400,
    'C': 100,
    'XC': 90,
    'L': 50,
    'XL': 40,
    'X': 10,
    'IX': 9,
    'V': 5,
    'IV': 4,
    'I': 1
}


def roman_to_arabic(roman_str):
    a = 0
    i = 0
    while i < len(roman_str):
        if i == len(roman_str) - 1:
            a += t[roman_str[i]]
            i += 1
        elif roman_str[i:i+2] in t:
            a += t[roman_str[i:i+2]]
            i += 2
        else:
            a += t[roman_str[i]]
            i += 1
    return a


roman_to_arabic("IX") # должна вывести 9
roman_to_arabic("CM") # должна вывести 900
roman_to_arabic("MMMCMXCIX") # должна вывести 3999