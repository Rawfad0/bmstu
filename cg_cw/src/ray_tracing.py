import numpy as np
from numba import jit, prange
from math import pi, tan, cos

EPSILON = 1.5*10**(-3)


@jit(nopython=True, parallel=False)
def point_visibility(camera, p) -> bool:
    center, h_dir, v_dir, h_fov, v_fov, min_z, max_z = camera
    z = np.cross(h_dir, v_dir)

    pi * h_fov / 360
    pi - pi * h_fov / 360

    h = tan(pi * h_fov / 360)  # расстояние по горизонтали
    v = tan(pi * v_fov / 360)  # расстояние по вертикали

    l = -h_dir * h + z
    r = h_dir * h + z
    u = -v_dir * v + z
    d = v_dir * v + z

    return True


@jit(nopython=True, parallel=False)
def triangle_visibility(camera, v0, v1, v2):
    if point_visibility(camera, v0):
        return True
    if point_visibility(camera, v1):
        return True
    if point_visibility(camera, v2):
        return True
    return False


@jit(nopython=True, parallel=False)
def filter_triangles(objs, camera):
    points, triangles = objs
    triangles2 = []
    for t_i in range(len(triangles)):
        i0, i1, i2 = triangles[t_i]
        v0, v1, v2 = points[i0], points[i1], points[i2]
        if triangle_visibility(camera, v0, v1, v2):
            triangles2.append(triangles[t_i])
    return triangles2


@jit(nopython=True, parallel=True)
def comp_rays(height, width, h_dir, v_dir, h_fov, v_fov):
    z = np.cross(h_dir, v_dir)
    z /= np.linalg.norm(z, ord=2)
    h = 2 * tan(pi * h_fov / 360) / width   # расстояние по горизонтали
    v = 2 * tan(pi * v_fov / 360) / height  # расстояние по вертикали
    rays = np.zeros((height, width, 3))

    for i in prange(height):
        for j in prange(width):
            res = (j + 0.5 - width / 2) * h * h_dir + (i + 0.5 - height / 2) * v * v_dir + z
            res /= np.linalg.norm(res, ord=2)
            rays[i][j] = res
    return rays


@jit(nopython=True, parallel=False)
def intersection_cube_assessment(points, ray):
    # # C numba.jit(nopython=True) не работает
    # x_min, y_min, z_min, q = points.min(axis=0)
    # x_max, y_max, z_max, q = points.max(axis=0)

    x_min, x_max, y_min, y_max, z_min, z_max = 0, 0, 0, 0, 0, 0

    for point in points:
        x, y, z, d = point
        if x < x_min:
            x_min = x
        if x > x_max:
            x_max = x
        if y < y_min:
            y_min = y
        if y > y_max:
            y_max = y
        if z < z_min:
            z_min = z
        if z > z_max:
            z_max = z

    origin, direction = ray
    xr, yr, zr = origin[:3]
    xa, ya, za = direction

    # Пересечение с гранью x_min
    if xa != 0:
        t = (x_min - xr) / xa
        if y_min < yr + ya * t < y_max and z_min < zr + za * t < z_max:
            return True

    # Пересечение с гранью x_max
    if xa != 0:
        t = (x_max - xr) / xa
        if y_min < yr + ya * t < y_max and z_min < zr + za * t < z_max:
            return True

    # Пересечение с гранью y_min
    if ya != 0:
        t = (y_min - yr) / ya
        if x_min < xr + xa * t < x_max and z_min < zr + za * t < z_max:
            return True

    # Пересечение с гранью y_max
    if ya != 0:
        t = (y_max - yr) / ya
        if x_min < xr + xa * t < x_max and z_min < zr + za * t < z_max:
            return True

    # Пересечение с гранью z_min
    if za != 0:
        t = (z_min - zr) / za
        if x_min < xr + xa * t < x_max and y_min < yr + ya * t < y_max:
            return True

    # Пересечение с гранью z_max
    if za != 0:
        t = (z_max - zr) / za
        if x_min < xr + xa * t < x_max and y_min < yr + ya * t < y_max:
            return True

    return False


# MT-check
@jit(nopython=True, parallel=False)
def intersect_triangle(ray, v0, v1, v2):
    v0, v1, v2 = v0[:3], v1[:3], v2[:3]
    origin, direction = ray
    origin = origin[:3]
    edge1, edge2 = v1 - v0, v2 - v0

    pvec = np.cross(direction, edge2)   # векторное
    det = np.dot(edge1, pvec)
    if -EPSILON < det < EPSILON:
        return -1, None     # луч параллелен треугольнику

    inv_det = 1.0 / det

    tvec = origin - v0
    u = np.dot(tvec, pvec) * inv_det
    if u < -EPSILON or u > 1.0 + EPSILON:
        return -1, None

    qvec = np.cross(tvec, edge1)
    v = np.dot(direction, qvec) * inv_det

    if v < -EPSILON or u + v > 1.0 + EPSILON:
        return -1, None

    t = np.dot(edge2, qvec) * inv_det
    # print("t", t)
    if t < 0.0:
        return -1, None     # пересечение с прямой, но не с лучом
    if u < EPSILON or v < EPSILON or u + v > 1.0 - EPSILON:
        return t, np.array([0, 0, 255], dtype=np.uint8)
    return t, np.array([255, 255, 255], dtype=np.uint8)


@jit(nopython=True, parallel=False)
def intersect_obj(ray, points, triangles, max_z):
    if intersection_cube_assessment(points, ray):
        min_d = max_z
        min_d_c = None
        for i in prange(len(triangles)):
            i0, i1, i2 = triangles[i]
            v0, v1, v2 = points[i0], points[i1], points[i2]
            d, c = intersect_triangle(ray, v0, v1, v2)
            if d != -1 and d < min_d:
                min_d = d
                min_d_c = c
        if min_d < 0 or min_d == max_z:
            return False, None, None
        return True, min_d, min_d_c
    else:
        return False, None, None


@jit(nopython=True, parallel=False)
def ray_tracing(c_buffer, d_buffer, height, width, camera, objs):
    center, h_dir, v_dir, h_fov, v_fov, min_z, max_z = camera
    rays = comp_rays(height, width, h_dir, v_dir, h_fov, v_fov)
    for i in prange(height):
        for j in prange(width):
            min_d = max_z
            res_color = None
            for k in prange(len(objs)):
                points, triangles = objs[k]
                b, d, color = intersect_obj((center, rays[i][j]), points, triangles, max_z)
                if b and d < min_d and min_z < d < max_z:
                    min_d = d
                    res_color = color
            if res_color is not None:
                c_buffer[i][j] = res_color
                d_buffer[i][j] = min_d
    return c_buffer, d_buffer, rays


@jit(nopython=True, parallel=False)
def intersect_obj_record(ray, points, triangles, max_z):
    k = 0
    if intersection_cube_assessment(points, ray):
        for i in prange(len(triangles)):
            k += 1
    return k


@jit(nopython=True, parallel=False)
def ray_tracing_record(height, width, camera, objs):
    counter = 0
    center, h_dir, v_dir, h_fov, v_fov, min_z, max_z = camera
    rays = comp_rays(height, width, h_dir, v_dir, h_fov, v_fov)
    for i in prange(height):
        for j in prange(width):
            for k in prange(len(objs)):
                points, triangles = objs[k]
                counter += intersect_obj_record((center, rays[i][j]), points, triangles, max_z)
    return counter


@jit(nopython=True, parallel=False)
def ray_tracing1(c_buffer, d_buffer, height, width, camera, objs):
    center, h_dir, v_dir, h_fov, v_fov, min_z, max_z = camera
    rays = comp_rays(height, width, h_dir, v_dir, h_fov, v_fov)
    points, triangles = objs
    triangles = filter_triangles(objs, camera)

    for i in prange(height):
        for j in prange(width):
            ray = (center, rays[i][j])
            if intersection_cube_assessment(points, ray):
                min_d = max_z
                min_d_c = None
                for t_i in prange(len(triangles)):
                    i0, i1, i2 = triangles[t_i]
                    v0, v1, v2 = points[i0], points[i1], points[i2]
                    d, c = intersect_triangle(ray, v0, v1, v2)
                    if d != -1 and d < min_d:
                        min_d = d
                        min_d_c = c
                if min_d < 0 or min_d == max_z:
                    d_buffer[i][j], c_buffer[i][j] = -1, np.array([0, 0, 0], dtype=np.uint8)
                else:
                    d_buffer[i][j], c_buffer[i][j] = min_d, min_d_c
            else:
                d_buffer[i][j], c_buffer[i][j] = -1, np.array([0, 0, 0], dtype=np.uint8)

    return c_buffer, d_buffer


@jit(nopython=True)
def comp_rays_seq1(height, width, h_dir, v_dir, h_fov, v_fov, seq):
    z = np.cross(h_dir, v_dir)
    z /= np.linalg.norm(z, ord=2)
    h = 2 * tan(pi * h_fov / 360) / width
    v = 2 * tan(pi * v_fov / 360) / height
    rays = np.zeros((len(seq), 3))
    for k in prange(len(seq)):
        i, j = divmod(seq[k], width)
        res = (j + 0.5 - width / 2) * h * h_dir + (i + 0.5 - height / 2) * v * v_dir + z
        res /= np.linalg.norm(res, ord=2)
        rays[k] = res
    return rays


@jit(nopython=True)
def comp_rays_seq(height, width, h_dir, v_dir, h_fov, v_fov, seq):
    z = np.cross(h_dir, v_dir)
    z /= np.linalg.norm(z, ord=2)
    h = 2 * tan(pi * h_fov / 360) / width   # расстояние по горизонтали
    v = 2 * tan(pi * v_fov / 360) / height  # расстояние по вертикали
    rays = np.zeros((height * width, 3))
    for k in prange(len(seq)):
        i, j = divmod(seq[k], width)
        res = (j + 0.5 - width / 2) * h * h_dir + (i + 0.5 - height / 2) * v * v_dir + z
        res /= np.linalg.norm(res, ord=2)
        rays[seq[k]] = res
    return rays


@jit(nopython=True, parallel=False)
def ray_tracing_seq1(c_buffer, d_buffer, height, width, camera, objs, ray_ids):
    center, h_dir, v_dir, h_fov, v_fov, min_z, max_z = camera
    rays = comp_rays_seq(height, width, h_dir, v_dir, h_fov, v_fov, ray_ids)
    for i in prange(len(ray_ids)):
        min_d = max_z
        res_color = None
        for k in prange(len(objs)):
            points, triangles = objs[k]
            b, d, color = intersect_obj((center, rays[i]), points, triangles, max_z)
            if b and d < min_d and min_z < d < max_z:
                min_d = d
                res_color = color
        if res_color is not None:
            c_buffer[ray_ids[i]] = res_color
            d_buffer[ray_ids[i]] = min_d
    return c_buffer, d_buffer, rays


@jit(nopython=True, parallel=False)
def ray_tracing_seq(c_buffer, d_buffer, height, width, camera, objs, ray_ids):
    center, h_dir, v_dir, h_fov, v_fov, min_z, max_z = camera
    rays = comp_rays_seq(height, width, h_dir, v_dir, h_fov, v_fov, ray_ids)

    for i in prange(len(ray_ids)):
        min_d = max_z
        res_color = None
        for k in prange(len(objs)):
            points, triangles = objs[k]
            b, d, color = intersect_obj((center, rays[ray_ids[i]]), points, triangles, max_z)
            if b and d < min_d and min_z < d < max_z:
                min_d = d
                res_color = color
        if res_color is not None:
            c_buffer[ray_ids[i]] = res_color
            d_buffer[ray_ids[i]] = min_d
    return c_buffer, d_buffer, rays


@jit(nopython=True, parallel=True)
def ray_tracing_parallel(c_buffer, d_buffer, height, width, camera, objs):
    center, h_dir, v_dir, h_fov, v_fov, min_z, max_z = camera
    rays = comp_rays(height, width, h_dir, v_dir, h_fov, v_fov)

    for i in range(height):
        for j in range(width):
            ray = rays[i][j]
            min_d = max_z
            min_d_c = np.array([0, 0, 0], dtype=np.uint8)
            for o_i in range(len(objs)):
                points, triangles = objs[o_i]

                intersection_cube_assessment_flag = False
                x_min, x_max, y_min, y_max, z_min, z_max = 0, 0, 0, 0, 0, 0
                for p_i in prange(len(points)):
                    x, y, z, q = points[p_i]
                    if x < x_min:
                        x_min = x
                    if x > x_max:
                        x_max = x
                    if y < y_min:
                        y_min = y
                    if y > y_max:
                        y_max = y
                    if z < z_min:
                        z_min = z
                    if z > z_max:
                        z_max = z

                origin, direction = center[:3], ray
                xr, yr, zr = origin
                xa, ya, za = direction
                # Пересечение с гранью x_min
                t = (x_min - xr) / xa
                if y_min < yr + ya * t < y_max and z_min < zr + za * t < z_max:
                    intersection_cube_assessment_flag = True
                else:
                    # Пересечение с гранью x_max
                    t = (x_max - xr) / xa
                    if y_min < yr + ya * t < y_max and z_min < zr + za * t < z_max:
                        intersection_cube_assessment_flag = True
                    else:
                        # Пересечение с гранью y_min
                        t = (y_min - yr) / ya
                        if x_min < xr + xa * t < x_max and z_min < zr + za * t < z_max:
                            intersection_cube_assessment_flag = True
                        else:
                            # Пересечение с гранью y_max
                            t = (y_max - yr) / ya
                            if x_min < xr + xa * t < x_max and z_min < zr + za * t < z_max:
                                intersection_cube_assessment_flag = True
                            else:
                                # Пересечение с гранью z_min
                                t = (z_min - zr) / za
                                if x_min < xr + xa * t < x_max and y_min < yr + ya * t < y_max:
                                    intersection_cube_assessment_flag = True
                                else:
                                    # Пересечение с гранью z_max
                                    t = (z_max - zr) / za
                                    if x_min < xr + xa * t < x_max and y_min < yr + ya * t < y_max:
                                        intersection_cube_assessment_flag = True

                if intersection_cube_assessment_flag:
                    for t_i in prange(len(triangles)):
                        d = -1.0
                        c = np.array([0, 0, 0], dtype=np.uint8)
                        i0, i1, i2 = triangles[t_i]
                        v0, v1, v2 = points[i0][:3], points[i1][:3], points[i2][:3]
                        edge1, edge2 = v1 - v0, v2 - v0

                        pvec = np.cross(direction, edge2)  # векторное
                        det = np.dot(edge1, pvec)
                        if -EPSILON < det < EPSILON:
                            d, c = -1.0, np.array([0, 0, 0], dtype=np.uint8)  # луч параллелен треугольнику
                        else:
                            inv_det = 1.0 / det
                            tvec = origin - v0
                            u = np.dot(tvec, pvec) * inv_det
                            if u < -EPSILON or u > 1.0 + EPSILON:
                                d, c = -1.0, np.array([0, 0, 0], dtype=np.uint8)
                            else:
                                qvec = np.cross(tvec, edge1)
                                v = np.dot(direction, qvec) * inv_det
                                if v < -EPSILON or u + v > 1.0 + EPSILON:
                                    d, c = -1.0, np.array([0, 0, 0], dtype=np.uint8)
                                else:
                                    t = np.dot(edge2, qvec) * inv_det
                                    if t < 0.0:
                                        d, c = -1.0, np.array([0, 0, 0], dtype=np.uint8)  # пересечение с прямой, но не с лучом
                                    else:
                                        if u < EPSILON or v < EPSILON or u + v > 1.0 - EPSILON:
                                            d, c = t, np.array([0, 0, 255], dtype=np.uint8)
                                        else:
                                            d, c = t, np.array([255, 255, 255], dtype=np.uint8)

                        if min_z < d < min_d:
                            min_d = d
                            min_d_c = c
                else:
                    continue
            if min_d < max_z:
                c_buffer[i][j] = min_d_c
                d_buffer[i][j] = min_d
    return c_buffer, d_buffer

