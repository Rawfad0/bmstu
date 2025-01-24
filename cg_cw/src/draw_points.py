import numpy as np
from numba import jit


# переход в базис камеры
@jit(nopython=True)
def transition_to_new_basis(center, h_dir, v_dir, points_src, points_dst):
    n = np.cross(h_dir, v_dir)
    print(n)
    mtx = np.stack((h_dir, v_dir, n), axis=1)     # A
    inv = np.linalg.inv(mtx)                    # A^-1
    mtx0 = -np.dot(inv, center.reshape(-1, 1))  # -(A^-1)*X0
    for i in range(len(points_src)):
        p = points_src[i][:3]
        p = (np.dot(inv, p.reshape(-1, 1)) + mtx0).reshape(1, -1)
        points_dst[i] = p
    return points_dst


@jit(nopython=True)
def draw_points(c_buffer, d_buffer, height, width, camera, points, new_basis_points):
    center, h_dir, v_dir, min_z, max_z = camera
    tps = transition_to_new_basis(center[:3], h_dir, v_dir, points, new_basis_points)
    for p in tps:
        if p[2] <= 0:
            continue
        # print(p, end=' ')
        rl = np.linalg.norm(p, ord=2)  # длина
        # p = 100 * p / p[2]    # z = 100
        # x, y = p[0], p[1]
        p = p / p[2]  # z = 100
        x, y = width*p[0], height*p[1]
        i, j = round(y + height // 2), round(x + width // 2)
        if 0 <= i < height and 0 <= j < width:
            # print(f"x,y={x},{y}; i,j={i},{j}; r={p}, rl={rl}; {d_buffer[i][j]}")
            if d_buffer[i][j] == -1 or rl < d_buffer[i][j]:
                d_buffer[i][j] = rl
                c_buffer[i][j] = np.array([255, 255, 255], dtype=np.uint8)
    return c_buffer, d_buffer
    # if (-(width // 2) < x < (width // 2)) and (-(height // 2) < y < (height // 2)):
    # for i in range(height):
    #     for j in range(width):
