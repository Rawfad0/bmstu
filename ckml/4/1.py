import re


def check_string(string) -> bool:
    pattern = re.compile(
        r'^('
        r'(\+7|8)?[\s-]?(\d{3}|\(\d{3}\))[\s-]?\d{3}(-?\d{2}){2}'
        r')$|^('
        r'([a-zA-Z0-9]+|\.[a-zA-Z0-9]{2,})(\.[a-zA-Z0-9]{2,})*@[a-zA-Z0-9]*(\.[a-zA-Z0-9]{2,})+'
        r')$'
    )

    return bool(pattern.match(string))


strings = """8(916)010-01-20
8916000000000
8916000000
89160000000
+79160000000
9160000000
8(916)000-00-00
+7(916)000-00-00
(916)000-00-00
8 (916) 000-00-00
+7 (916) 000-00-00
(916) 000-00-00
8(916)0000000
+7(916)0000000
(916)0000000
8-916-000-00-00
+7-916-000-00-00
916-000-00-00
abc@abc.ab
abc@abc.ab.ab
a@ab.ab
abc.abc@abc.abc
Невалидные адреса:
@abc.abc
abc@abc
abc@abc.a
abc@abc.abc.a
abc@abc.
abc@abc@abc""".split('\n')

for s in strings:
    print(f'"{s}"', check_string(s))
