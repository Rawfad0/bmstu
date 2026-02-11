def form_matrix(imtx, n):
    matrix = [[0 for j in range(n)] for i in range(n)]
    for i in range(n):
        for j in range(n):
            if i == j:
                matrix[i][j] = imtx[i][j] - sum(imtx[i])
            else:
                matrix[i][j] = imtx[j][i]
    return matrix


def gauss_method(A, b):
    n = len(A)
    M = [A[i] + [b[i]] for i in range(n)]
    for i in range(n):
        max_row = max(range(i, n), key=lambda r: abs(M[r][i]))
        if M[max_row][i] == 0:
            raise ValueError("Система не имеет уникального решения (нулевой ведущий элемент).")
        M[i], M[max_row] = M[max_row], M[i]
        pivot = M[i][i]
        M[i] = [m / pivot for m in M[i]]
        for j in range(i + 1, n):
            factor = M[j][i]
            M[j] = [M[j][k] - factor * M[i][k] for k in range(n + 1)]

    x = [0] * n
    for i in range(n - 1, -1, -1):
        x[i] = M[i][-1] - sum(M[i][j] * x[j] for j in range(i + 1, n))

    return x


def solve_probs(intensity_matrix):
    n = len(intensity_matrix)
    left_part = form_matrix(intensity_matrix, n)
    for i in range(n):
        left_part[-1][i] = 1
    right_part = [0] * n
    right_part[-1] = 1
    solution = gauss_method(left_part, right_part)
    return solution


def solve_times(intensity_matrix):
    with open('config.txt', 'r') as f:
        TIME_MAX = float(f.readline())
        TIME_STEP = float(f.readline())
        EPS = float(f.readline())
    n = len(intensity_matrix)
    matrix = form_matrix(intensity_matrix, n)
    p_ref = solve_probs(intensity_matrix)
    times = [None for i in range(n)]
    p = [0] * n
    p[0] = 1
    cur_time = 0
    while cur_time < TIME_MAX:
        cur_time += TIME_STEP
        prev_p = p.copy()
        for i in range(n):
            for j in range(n):
                p[i] += matrix[i][j] * prev_p[j] * TIME_STEP
        for i in range(n):
            if times[i] is None and abs(p[i] - prev_p[i]) < EPS and abs(p[i] - p_ref[i]) < EPS:
                times[i] = cur_time
        print(times)
        if not (None in times):
            break
    return times
