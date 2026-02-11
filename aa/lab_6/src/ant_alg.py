import itertools
from math import inf
from random import random


FULL = 1
ANT = 2
BOTH = 3
MIN_PHEROMONE = 0.001
START_PHEROMON = 1


# стоимость маршрута
def get_cost(matrix, route):
    cur_cost = 0
    for num in range(len(route) - 1):
        start_city = route[num]
        end_city = route[num + 1]
        cur_cost += matrix[start_city][end_city]
    return cur_cost


# все маршруты
def get_all_routes(cities):
    routes = []
    for route in itertools.permutations(cities, len(cities)):
        route = list(route)
        route.append(route[0])
        routes.append(route)
    return routes


# длина оптимального пути
def get_q(matrix, size):
    q = 0
    count = 0
    for i in range(size):
        for j in range(i + 1, size):
            q += matrix[i][j] * 2
            count += 2
    return q / count


# матрицу видимостей городов.
def get_proximity(matrix, size):
    proximity = [[0 for i in range(size)] for j in range(size)]
    for i in range(size):
        for j in range(i):
            proximity[i][j] = 1 / matrix[i][j] # видимость обратно пропорциональна расстоянию между этими городами.
            proximity[j][i] = proximity[i][j]
    return proximity


# посещенные города
def get_visited_cities(cities, count_ants):
    visited = [[] for _ in range(count_ants)]
    for ant in range(count_ants):
        visited[ant].append(cities[ant])
    return visited


# вероятность перехода k-ого муравья из города i в j по формуле
def get_probability(pheromones, proximity, visited, a, b, ant, city_count):
    # Вероятности того, что муравей перейдет в город city
    probabilities = [0] * city_count
    # Муравей находится в последнем посещенном городе
    now_city = visited[ant][-1]
    for city in range(city_count):
        if city not in visited[ant]:
            # Желание муравья перейти в город city
            probabilities[city] = (pheromones[now_city][city] ** a) * (proximity[now_city][city] ** b)
        else:
            probabilities[city] = 0
    # Cумма желаний муравья перейти из текущего города ко всем другим еще не посещенным городам
    sum_p = sum(probabilities)
    for city in range(city_count):
        probabilities[city] /= sum_p
    return probabilities


# случайный выбор города
def choose_city(probabilities):
    num = random()
    value = 0
    for i in range(len(probabilities)):
        value += probabilities[i]
        if value > num:
            return i


# принадлежит ли город машруту
def check_route(i, j, route):
    for city_i, city in enumerate(route):
        if city == i and city_i + 1 < len(route) and route[city_i + 1] == j:
            return True
    return False


# обновление феромона
def update_pheromone(visited, matrix, pheromones, city_count, p, q, elite_ants_count, min_cost):
    for i in range(city_count):
        for j in range(city_count):
            add = 0
            for ant in range(city_count):
                if check_route(i, j, visited[ant]):
                    cost = get_cost(matrix, visited[ant])
                    add += q / cost
            pheromones[i][j] *= (1 - p)
            pheromones[i][j] += add + elite_ants_count * q / min_cost
            if pheromones[i][j] < MIN_PHEROMONE:
                pheromones[i][j] = MIN_PHEROMONE
    return pheromones


def ant_algorithm(matrix, size, a, b, p, iterations, elite_ants_count):
    cities = [i for i in range(size)]
    min_cost = inf
    min_route = None
    # Длина среднего пути (Ant Colony Optimization)
    # Q — регулируемый параметр, значение которого выбирают одного порядка с длиной оптимального маршрута
    q = get_q(matrix, size)

    proximity = get_proximity(matrix, size)     # Матрица видимости всех городов
    pheromones = [[START_PHEROMON for i in range(size)] for j in range(size)]   # Матрица феромонов
    count_ants = size
    for _ in range(iterations):
        visited = get_visited_cities(cities, count_ants)    # начальные города, из которых муравьи начнут путь
        for ant in range(count_ants):
            while len(visited[ant]) != count_ants:
                pk = get_probability(pheromones, proximity, visited, a, b, ant, size)    # вероятность перехода
                next_city = choose_city(pk)             # выбор следующего города
                visited[ant].append(next_city)
            visited[ant].append(visited[ant][0])        # замыкание маршрута
            cur_cost = get_cost(matrix, visited[ant])   # стоимость полученного маршрута
            if cur_cost < min_cost:
                min_cost = cur_cost     # обновление минимального пути
                min_route = visited[ant]
        # Обновить значения феромона на всех путях
        pheromones = update_pheromone(visited, matrix, pheromones, size, p, q, elite_ants_count, min_cost)
    return min_route, min_cost


# вывод маршрута и его стоимости
def print_route(route, cost):
    for num in range(len(route)):
        if num != len(route) - 1:
            print(route[num] + 1, "->", end=" ")
    print(route[0] + 1)
    print("Стоимость: ", cost)
