import itertools


def bruteforce(src_matrix):
    routes = itertools.permutations(range(len(src_matrix)))
    min_cost = float('inf')
    min_route = None
    for route in routes:
        current_cost = sum(src_matrix[start_city][end_city] for start_city, end_city in zip(route, route[1:]))
        if current_cost < min_cost:
            min_cost = current_cost
            min_route = route
    return min_route, min_cost


matrix = [
    [ 0,  5, 6, 14, 15],
    [ 5,  0, 7, 10,  6],
    [ 6,  7, 0,  8,  7],
    [14, 10, 8,  0,  9],
    [15,  6, 7,  9,  0]
]

if __name__ == "__main__":
    print(bruteforce(matrix))
