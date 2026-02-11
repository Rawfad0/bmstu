import re


# class Field:
#
#     @staticmethod
#     def regex_translate(key):
#         pattern1, pattern2 = "^(\S)(\d+)$", "^(\d+)(\S)$"
#         m1, m2 = re.match(pattern1, key), re.match(pattern2, key)
#         if m1 is not None:
#             tkey = m1.group(1).lower() + m1.group(2)
#         elif m2 is not None:
#             tkey = m2.group(2).lower() + m2.group(1)
#         else:
#             raise ValueError
#         return tkey
#
#     def translate(self, key):
#         if type(key) is str:
#             tkey = self.regex_translate(key)
#         elif type(key) is tuple:
#             if len(key) == 2:
#                 tkey = self.regex_translate(f"{key[0]}{key[1]}")
#             else:
#                 raise ValueError
#         else:
#             raise TypeError
#         return tkey
#
#     def __setitem__(self, key, value):
#         tkey = self.translate(key)
#         # print(key, value, tkey, tkey.upper(), self.__dict__, end='')
#         self.__setattr__(tkey, value)
#         self.__setattr__(tkey.upper(), value)
#         # print(self.__dict__)
#
#     def __getitem__(self, key):
#         tkey = self.translate(key)
#         return self.__dict__.get(tkey)
#
#     def __delitem__(self, key):
#         tkey = self.translate(key)
#         self.__delattr__(tkey)
#         self.__delattr__(tkey.upper())
#
#     def __contains__(self, key):
#         tkey = self.translate(key)
#         # print(key, tkey, self.__dict__.keys())
#         return tkey in self.__dict__.keys()
#
#     def __iter__(self):
#         return self.__dict__.values().__iter__()


class Field(object):
    def __init__(self):
        self.dict = dict()

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
        self.__setattr__(tkey, value)

    def __getitem__(self, key):
        tkey = self.translate(key)
        return self.dict.get(tkey)

    def __delitem__(self, key):
        tkey = self.translate(key)
        self.__delattr__(tkey)

    def __contains__(self, key):
        tkey = self.translate(key)
        # print(key, tkey, self.__dict__.keys())
        return tkey in self.dict.keys()

    def __iter__(self):
        return self.dict.values().__iter__()

    def __setattr__(self, key, value):
        if key[0].isalpha() and key[1].isdigit():
            tkey = self.translate(key)
            super().__setattr__(tkey, value)
            super().__setattr__(tkey.upper(), value)
            self.dict[tkey] = value
        else:
            super().__setattr__(key, value)

    def __delattr__(self, key):
        if key[0].isalpha() and key[1].isdigit():
            tkey = self.translate(key)
            super().__delattr__(tkey)
            super().__delattr__(tkey.upper())
            del self.dict[tkey]
        else:
            super().__delattr__(key)


field = Field()
print(field.__dict__)


print("START")
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

print((1, 'a') in field)
print("A1" in field)
print(('D', '4') in field)

print(field["C5"] is None)

print([i for i in field])

print("NEW")
field.a1 = 25
field.A1 = 25
field['b', 2] = 100
print(field.b2 == 100)
print(field.B2 == 100)
