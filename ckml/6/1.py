import re


class Field:

    def __init__(self):
        self.dict = dict()
        self.keys = set()

    @staticmethod
    def regex_translate(key):
        pattern1, pattern2 = "^(\S)(\d+)$", "^(\d+)(\S)$"
        m1, m2 = re.match(pattern1, key), re.match(pattern2, key)
        if m1 is not None:
            tkey = m1.group(1).lower() + m1.group(2)
        elif m2 is not None:
            tkey = m2.group(2).lower() + m2.group(1)
        else:
            raise ValueError
        return tkey

    def translate(self, key):
        if type(key) is str:
            tkey = self.regex_translate(key)
        elif type(key) is tuple:
            if len(key) == 2:
                tkey = self.regex_translate(f"{key[0]}{key[1]}")
            else:
                raise ValueError
        else:
            raise TypeError
        return tkey

    def __setitem__(self, key, value):
        tkey = self.translate(key)
        # print(key, tkey)
        self.dict[tkey] = value
        self.keys.add(tkey)

    def __getitem__(self, key):
        tkey = self.translate(key)
        return self.dict.get(tkey)

    def __delitem__(self, key):
        tkey = self.translate(key)
        self.dict.pop(tkey)
        self.keys.remove(tkey)

    def __contains__(self, key):
        tkey = self.translate(key)
        return tkey in self.keys

    def __iter__(self):
        return self.dict.values().__iter__()


field = Field()

field[1, 'a'] = 25
field['a', 1] = 25
field['a', '1'] = 25
field['1', 'a'] = 25
field['1a'] = 25
field['a1'] = 25
field[1, 'A'] = 25 # Все то же самое работает и с заглавными буквами
field['A', 1] = 25
field['A', '1'] = 25
field['1', 'A'] = 25
field['1A'] = 25
field['A1'] = 25

print((1, 'a') in field == True)
print("A1" in field == True)
print(('D', '4') in field == False)

print(field["C5"] is None)

print([i for i in field])
