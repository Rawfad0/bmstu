import json


def mean_age(json_string):
    s = 0
    j = json.loads(json_string)
    for person in j:
        s += person['age']
    d = {'mean_age': s / len(j)}
    return json.dumps(d)


json_str = '''[
        {
            "name": "Петр",
            "surname": "Петров",
            "patronymic": "Васильевич",
            "age": 23,
            "occupation": "ойтишнек"
        },
        {
            "name": "Василий",
            "surname": "Васильев",
            "patronymic": "Петрович",
            "age": 24,
            "occupation": "дворник"
        }
    ]'''

print(mean_age(json_str))
