import numpy as np
from numba import jit


@jit(nopython=True)
def is_triangle_degenerate(p0, p1, p2):
    v0, v1, v2 = (p1 - p0)[:2], (p2 - p1)[:2], (p0 - p2)[:2]

    l0 = np.linalg.norm(v0, ord=2)
    l1 = np.linalg.norm(v1, ord=2)
    l2 = np.linalg.norm(v2, ord=2)
    if l1 + l2 <= l0 or l0 + l2 <= l1 or l0 + l1 <= l2:
        return True
    else:
        return False


# переход в базис камеры
@jit(nopython=True)
def transition_to_new_basis(center, h_dir, v_dir, points_src, points_dst):
    # tps = np.full((len(points), 3), np.array([0., 0., 0.]))
    n = np.cross(h_dir, v_dir)
    # print(center, h_dir, v_dir, n)
    # mtx = np.stack((h_dir, v_dir, n), axis=1)   # A
    mtx = np.stack((-v_dir, -h_dir, n), axis=1)
    # print(mtx)

    inv = np.linalg.inv(mtx)                    # A^-1
    # print(inv)
    mtx0 = -np.dot(inv, center.reshape(-1, 1))  # -(A^-1)*X0
    # print(mtx0)
    for i in range(len(points_src)):
        p = points_src[i][:3]
        # print(i, "before", p)
        p = (np.dot(inv, p.reshape(-1, 1)) + mtx0).reshape(1, -1)
        # print(i, "after", p)
        points_dst[i] = p

    return points_dst


# уравнение плоскости через смешанное произведение векторов
# возвращает A, B, C, D
@jit(nopython=True)
def plane_equation(p0, p1, p2):
    a, b = p1 - p0, p2 - p0     #
    ax, ay, az = a
    bx, by, bz = b
    px, py, pz = p0
    A = ay*bz - by*az
    B = ax*bz - bx*az
    C = ax*by - bx*ay
    D = -A*px - B*py - C*pz
    if C == 0:
        print("ZER0:", p0, p1, p2)
    return A, B, C, D


# def cross2d(a, b):
#     return a


@jit(nopython=True)
def point_in_triangle(p, p0, p1, p2):
    v0, v1, v2 = p0, p1, p2
    v0[2], v1[2], v2[2] = 0, 0, 0   # np.cross принимает 3х-мерные вектора, но z не нужен
    p0, p1, p2 = p - v0, p - v1, p - v2
    e0, e1, e2 = v1 - v0, v2 - v1, v0 - v2
    c0, c1, c2 = np.cross(e0, p0)[-1], np.cross(e1, p1)[-1], np.cross(e2, p2)[-1]
    # print(c0, c1, c2)
    # return all((c0 >= 0, c1 >= 0, c2 >= 0)) or all((c0 <= 0, c1 <= 0, c2 <= 0))
    return (c0 >= 0 and c1 >= 0 and c2 >= 0) or (c0 <= 0 and c1 <= 0 and c2 <= 0)


@jit(nopython=True)
def z_buffer(c_buffer, d_buffer, height, width, camera, objs, new_basis_points):
    k = 2
    center, h_dir, v_dir, min_z, max_z = camera
    points, triangles = objs
    # проецирование точек в пространство относительно камеры
    tps = transition_to_new_basis(center[:3], h_dir, v_dir, points, new_basis_points)
    # закраска треугольников по алгоритму z-буфера
    for triangle in triangles:
        i0, i1, i2 = triangle
        print(i0, i1, i2)
        v0, v1, v2 = tps[i0], tps[i1], tps[i2]
        print(v0, v1, v2)
        if not is_triangle_degenerate(v0, v1, v2):
            # print(v0, v1, v2)
            a, b, c, d = plane_equation(v0, v1, v2)
            if c == 0:
                print("C=0 => ZERO DIV")
            for i in range(height):
                for j in range(width):
                    px, py = (i - height // 2)/k, (j - width // 2)/k
                    pz = -(a*px + b*py + d) / c
                    if min_z > pz > max_z:
                        continue
                    p = np.array([px, py, 0])
                    if point_in_triangle(p, v0, v1, v2):
                        if pz < d_buffer[i][j]:
                            # print("printing")
                            d_buffer[i][j] = pz
                            c_buffer[i][j] = np.array([255, 255, 255], dtype=np.uint8)
                        # if pz > d_buffer[i][j]:
                        #     print("printing")
                        #     d_buffer[i][j] = pz
                        #     c_buffer[i][j] = np.array([255, 255, 255], dtype=np.uint8)

    return c_buffer
