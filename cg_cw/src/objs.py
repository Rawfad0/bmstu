import numpy as np
import abc
from math import sin, cos
import numba

EPSILON = 1.5*10**(-3)


def translate_tm(translation: tuple[float, float, float]):
    tx, ty, tz = translation
    return np.reshape(np.array(
        [
            1, 0, 0, tx,
            0, 1, 0, ty,
            0, 0, 1, tz,
            0, 0, 0, 1
        ]), [4, 4])


def rotate_x_tm(rotation_angle: float):
    theta = np.radians(rotation_angle)
    return np.reshape(np.array(
        [
            1, 0, 0, 0,
            0, cos(theta), -sin(theta), 0,
            0, sin(theta),  cos(theta), 0,
            0, 0, 0, 1
        ]), [4, 4])


def rotate_y_tm(rotation_angle: float):
    theta = np.radians(rotation_angle)
    return np.reshape(np.array(
        [
            cos(theta), 0, sin(theta), 0, 0,
            0, 1, 0, 0,
            -sin(theta), 0, cos(theta), 0,
            0, 0, 0, 1
        ]), [4, 4])


def rotate_z_tm(rotation_angle: float):
    theta = np.radians(rotation_angle)
    return np.reshape(np.array(
        [
            cos(theta), -sin(theta), 0, 0,
            sin(theta), cos(theta), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]), [4, 4])


def rotate_axis(axis, t):
    t = np.radians(t)
    ux, uy, uz = axis
    return np.reshape(np.array(
        [
            ux*ux*(1-cos(t)) + cos(t),    ux*uy*(1-cos(t)) - uz*sin(t), ux*uz*(1-cos(t)) + uy*sin(t), 0,
            ux*uy*(1-cos(t)) + uz*sin(t), uy*uy*(1-cos(t)) + cos(t),    uy*uz*(1-cos(t)) - ux*sin(t), 0,
            ux*uz*(1-cos(t)) - uy*sin(t), uy*uz*(1-cos(t)) + ux*sin(t), uz*uz*(1-cos(t)) + cos(t),    0,
            0,                            0,                            0,                            1
        ]), [4, 4])


def scale_tm(scaling: tuple[float, float, float]):
    kx, ky, kz = scaling
    return np.reshape(np.array(
        [
            kx, 0, 0, 0,
            0, ky, 0, 0,
            0, 0, kz, 0,
            0, 0, 0, 1
        ]), [4, 4])


class Object:
    def __init__(self):
        self.object = None

    def transform(self, transform_matrix):
        pass


class Camera(Object):
    # h_fov - horizontal field of view
    # v_fov - vertical field of view
    def __init__(self,
                 # center=np.array([0.0, 0.0, 0.0, 1.0]),
                 # h_dir=np.array([0.0, 1.0, 0.0]),
                 # v_dir=np.array([1.0, 0.0, 0.0]),
                 center=np.array([0.0, 0.0, 0.0, 1.0]),
                 h_dir=np.array([1.0, 0.0, 0.0]),
                 v_dir=np.array([0.0, 0.0, -1.0]),
                 # direction=np.array([1.0, 0.0, 0.0, 0.0]),
                 h_fov: float = 60.0,
                 v_fov: float = 45.0,
                 min_z: float = 1.0,
                 max_z: float = 100.0) -> None:
        self.center = center
        self.h_dir = h_dir
        self.v_dir = v_dir
        # self.direction = direction
        self.h_fov: float = h_fov
        self.v_fov: float = v_fov
        self.min_z: float = min_z
        self.max_z: float = max_z

        self.rays_cache = None

    def move(self, transform_matrix):
        self.center = np.matmul(transform_matrix, self.center)

    def move_d(self, dx, dy, dz):
        self.center += [dx, dy, dz, 0]

    # left (<0) or right (>0)
    def move_left_right(self, d):
        h_dir = np.append(self.h_dir, 0.0)
        self.center += h_dir*d

    # up (<0) or down (>0)
    def move_up_down(self, d):
        v_dir = np.append(self.v_dir, 0.0)
        self.center += v_dir*d

    # forward (>0) or backward (<0)
    def move_forward_back(self, d):
        n_dir = np.cross(self.h_dir, self.v_dir)
        n_dir = np.append(n_dir, 0.0)
        self.center += n_dir*d

    def rotate(self, transform_matrix):
        h_dir = np.append(self.h_dir, 1.0)
        v_dir = np.append(self.v_dir, 1.0)
        # print(h_dir, v_dir)
        h_dir = np.matmul(transform_matrix, h_dir)[:3]
        v_dir = np.matmul(transform_matrix, v_dir)[:3]
        self.h_dir = h_dir / np.linalg.norm(self.h_dir, ord=2)
        self.v_dir = v_dir / np.linalg.norm(self.v_dir, ord=2)
        # print(self.h_dir, self.v_dir)

    # left (>0) or right (<0)
    def rotate_left_right(self, t):
        self.rotate(rotate_z_tm(t))

    # up (>0) or down (<0)
    def rotate_up_down(self, t):
        self.rotate(rotate_axis(self.h_dir, t))


class Point:
    def __init__(self, x: float, y: float, z: float) -> None:
        self.x = x
        self.y = y
        self.z = z


class Vector(Point):
    def __init__(self, point: Point = None, x: float = None, y: float = None, z: float = None) -> None:
        super().__init__(x, y, z)
        if point is None:
            pass

    def vec_length(self):
        pass

    def normalize(self):
        pass


# class Direction(Vector):
#     def __init__(self, vector: Vector, x: float, y: float, z: float):
#         super().__init__()
#
#     def normalize(self):


class Edge:
    def __init__(self, p1, p2) -> None:
        self.p1 = p1
        self.p2 = p2


class Model:
    @abc.abstractmethod
    def read_from_file(self, filename):
        pass

    @abc.abstractmethod
    def write_to_file(self, filename):
        pass

    @abc.abstractmethod
    def transform(self, matrix):
        pass


class WireModel(Model):
    def __init__(self):
        self.points = []
        self.edges = []
        self.matrix = [
            [
                1 for i in range(len(self.points))
                if (i, j) in self.edges or (j, i) in self.edges
            ]
            for j in range(len(self.points))
        ]

    def read_from_file(self, filename):
        with open(filename, 'r') as f:
            pn, en = map(int, f.readline().split())
            for _ in range(pn):
                self.points.append(np.array(list(map(float, f.readline().split()))+[1]).reshape(4))
            for _ in range(en):
                self.edges.append(np.array(list(map(int, f.readline().split()))))

    def write_to_file(self, filename):
        with open(filename, 'w') as f:
            f.write(f"{len(self.points)} {len(self.edges)}")
            for point in self.points:
                f.write(*point)
            for edge in self.edges:
                f.write(*edge)

    def transform(self, matrix):
        # print("TRANSFORM")
        # print(matrix)
        for i in range(len(self.points)):
            # print(i, *self.points[i], end=' | ')
            self.points[i] = np.matmul(matrix, self.points[i])
            # print(*self.points[i])


class MeshModel(Model):
    def __init__(self):
        self.points = np.array([])
        self.triangles = np.array([])
        self.name = ""

    def mass_center(self):
        r = np.array([0., 0., 0.])
        for point in self.points:
            r += point[:3]
            # print(r)
        r /= len(self.points)
        # r = self.points.sum() / len(self.points)
        print("mass center", r)
        return r

    def read_from_file(self, filename):
        with open(filename, 'r') as f:
            pn, tn, self.name = f.readline().split()
            pn, tn = int(pn), int(tn)
            points = np.full((pn, 4), 1.0)
            triangles = np.full((tn, 3), 0)
            for i in range(pn):
                arr = list(map(float, f.readline().split()))+[1.0]
                points[i] = np.array(arr)
            for i in range(tn):
                arr = np.array(list(map(int, f.readline().split())))
                triangles[i] = np.array(arr)
        self.points = points
        self.triangles = triangles
        return self.name

    def write_to_file(self, filename):
        with open(filename, 'w') as f:
            f.write(f"{len(self.points)} {len(self.triangles)} {self.name}")
            for point in self.points:
                f.write(*point)
            for triangle in self.triangles:
                f.write(*triangle)

    def transform(self, matrix):
        for i in range(len(self.points)):
            self.points[i] = np.matmul(matrix, self.points[i])


class PointCloud:
    def __init__(self):
        self.points = []

    def add_point(self, point):
        self.points.append(point)

    def add_points(self, points):
        self.points.extend(points)

    def add_from_ray_tracing(self, center, rays, dists):
        height, width = dists.shape
        for i in range(height):
            for j in range(width):
                if dists[i][j] != -1:
                    # print(i, j, rays[i][j])
                    point = center[:3] + rays[i][j] * dists[i][j]
                    self.add_point(point)


class Scene:
    def __init__(self):
        self.objs = []
        self.point_clouds = []

    def add_obj(self, obj):
        self.objs.append(obj)

    def add_point_cloud(self, point_cloud):
        self.point_clouds.append(point_cloud)


def main():
    pass
    # wm = WireModel()
    # wm.read_from_file("cube.txt")
    # cam = Camera(h_fov=160, v_fov=80)
    # print(cam.rays(4, 8))


if __name__ == "__main__":
    main()
