def linear_search(arr, x):
    comparisons = 0
    xi = -1
    for i in range(len(arr)):
        comparisons += 1
        if arr[i] == x:
            xi = i
            break
    return xi, comparisons


def binary_search(arr, x):
    comparisons = 0
    l, r = 0, len(arr) - 1
    xi = -1
    while l <= r:
        m = (l + r) // 2
        # m = l + (r - l) // 2
        comparisons += 1
        if arr[m] < x:
            l = m + 1
        elif arr[m] > x:
            r = m - 1
        else:
            xi = m
            break
    return xi, comparisons
