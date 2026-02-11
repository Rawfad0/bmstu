import json


def analyze_salaries(filename):
    with open(filename, 'r') as f:
        salaries = json.load(f)
        res = dict()
        for salary in salaries:
            prof = salary['profession']
            slry = salary['salary']
            city = salary['city']
            if res.get(city) is None:
                res[city] = dict()
            if res[city].get(prof) is None:
                res[city][prof] = list()
            res[city][prof].append(slry)
    for city, profs in res.items():
        for prof, slries in profs.items():
            res[city][prof] = round(sum(slries) / len(slries), 2)
    return res


print(analyze_salaries('3.json'))
# Должна вернуть {'Москва': {'Программист': 165000.0}, 'Санкт-Петербург': {'Дизайнер': 100000.0, 'Программист': 160000.0}}
