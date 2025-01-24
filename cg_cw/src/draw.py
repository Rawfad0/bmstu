import random
import time

from PyQt6.QtGui import QPixmap, QPainter, QColor, QMouseEvent, QKeyEvent, QImage, qRgb
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QLabel

from objs import Camera, Scene, PointCloud
from objs import translate_tm, rotate_x_tm, scale_tm
from utils import *
import numpy as np
from numba import jit, prange

from time import time
import timeit

from ray_tracing import (
    ray_tracing as rt,
    ray_tracing_parallel as rtp,
    ray_tracing_seq as rts,
    ray_tracing1 as rt1,
    ray_tracing_record as rtr,
)
from z_buffer import (
    z_buffer as zb,
)
from draw_points import draw_points


class Drawer:
    def __init__(self, canvas, scene, main_camera, secondary_camera):
        self.canvas: Canvas = canvas
        self.width = canvas.width
        self.height = canvas.height
        self.scene: Scene = scene
        self.camera: Camera = main_camera
        self.camera2: Camera = secondary_camera

        self.pattern = self.ray_tracing
        self.pattern_arg = None

        self.camera.center = np.array([0.0, -10.0, 0.0, 1.0])
        self.camera2.center = np.array([0.0, -10.0, 0.0, 1.0])

    def ray_tracing(self):
        c_buffer = np.full([self.height, self.width, 3], 0, dtype=np.uint8)
        d_buffer = np.full([self.height, self.width], -1.0)
        camera = (self.camera.center,
                  self.camera.h_dir,
                  self.camera.v_dir,
                  self.camera.h_fov,
                  self.camera.v_fov,
                  self.camera.min_z,
                  self.camera.max_z)
        objs = tuple([(obj.points, obj.triangles) for obj in self.scene.objs])

        c_buffer, d_buffer, rays = rt(c_buffer, d_buffer, self.height, self.width, camera, objs)
        return c_buffer, d_buffer, rays

    def ray_tracing_record(self):
        camera = (self.camera.center,
                  self.camera.h_dir,
                  self.camera.v_dir,
                  self.camera.h_fov,
                  self.camera.v_fov,
                  self.camera.min_z,
                  self.camera.max_z)
        objs = tuple([(obj.points, obj.triangles) for obj in self.scene.objs])
        k = rtr(self.height, self.width, camera, objs)
        return k

    def record(self):
        t, buffers = record_func_time(self.ray_tracing, reps=1, v=True, text="raytracing ")
        # k = self.ray_tracing_record()
        r = self.camera.center[:3] - self.scene.objs[0].mass_center()
        d = np.linalg.norm(r, ord=2)
        with open("../data/data.txt", 'a') as f:
            f.write(f"{t}, {d}\n")
        return buffers

    def ray_tracing1(self):
        c_buffer = np.full([self.height, self.width, 3], 0, dtype=np.uint8)
        d_buffer = np.full([self.height, self.width], -1.0)
        camera = (self.camera.center,
                  self.camera.h_dir,
                  self.camera.v_dir,
                  self.camera.h_fov,
                  self.camera.v_fov,
                  self.camera.min_z,
                  self.camera.max_z)
        points = []
        triangles = []
        for obj in self.scene.objs:
            for triangle in obj.triangles:
                v0, v1, v2 = triangle
                pl = len(points)
                triangles.append([v0 + pl, v1 + pl, v2 + pl])
            points.extend(obj.points)
        points = np.array(points)
        triangles = np.array(triangles)
        # print(points)
        # print(triangles)
        objs = (points, triangles)

        c_buffer, d_buffer = rt1(c_buffer, d_buffer, self.height, self.width, camera, objs)
        return c_buffer, d_buffer

    def ray_tracing_parallel(self):
        c_buffer = np.full([self.height, self.width, 3], 0, dtype=np.uint8)
        d_buffer = np.full([self.height, self.width], -1.0)
        camera = (self.camera.center,
                  self.camera.h_dir,
                  self.camera.v_dir,
                  self.camera.h_fov,
                  self.camera.v_fov,
                  self.camera.min_z,
                  self.camera.max_z)
        objs = tuple([(obj.points, obj.triangles) for obj in self.scene.objs])
        c_buffer, d_buffer = rtp(c_buffer, d_buffer, self.height, self.width, camera, objs)
        return c_buffer, d_buffer

    def ray_tracing_by_rays(self, ray_ids):
        c_buffer = np.full([self.height * self.width, 3], 0, dtype=np.uint8)
        d_buffer = np.full([self.height * self.width], -1.0)

        camera = (self.camera.center,
                  self.camera.h_dir,
                  self.camera.v_dir,
                  self.camera.h_fov,
                  self.camera.v_fov,
                  self.camera.min_z,
                  self.camera.max_z)
        objs = tuple([(obj.points, obj.triangles) for obj in self.scene.objs])
        c_buffer, d_buffer, rays = rts(c_buffer, d_buffer, self.height, self.width, camera, objs, ray_ids)
        c_buffer = c_buffer.reshape([self.height, self.width, 3])
        d_buffer = d_buffer.reshape([self.height, self.width])
        rays = rays.reshape([self.height, self.width, 3])
        return c_buffer, d_buffer, rays

    def random_ray_tracing(self, n=30000):
        return self.ray_tracing_by_rays(
            random.sample([i for i in range(self.height * self.width)], n)
        )

    def lidar_vertical_lines(self, n=30):
        if n + 1 > self.width:
            return None
        return self.ray_tracing_by_rays(
            [i for i in range(self.width * self.height)
             if (i % self.width) % round(self.width / (n + 1)) == 0]
        )

    def lidar_horizontal_lines(self, n=30):
        return self.ray_tracing_by_rays(
            [i for i in range(self.width * self.height)
             if (i // self.width) % round(self.height / (n + 1)) == 0]
        )

    def lidar_ort_grid(self, n=30):
        return self.ray_tracing_by_rays(
            [i for i in range(self.width * self.height)
             if (i % self.width) % round(self.width / (n + 1)) == 0 or (i // self.width) % round(self.height / (n + 1)) == 0]
        )

    def lidar_eq_dist(self, n=3):
        return self.ray_tracing_by_rays(
            [i for i in range(self.width * self.height) if i % n == 0]
        )

    # 1.5 ms
    @staticmethod
    @jit(nopython=True, parallel=False)
    def distance_grad(buffers, height, width, min_z, max_z):
        c_buffer, d_buffer = buffers[0:2]
        min_d, max_d = max_z, min_z

        for i in range(height):
            for j in range(width):
                d = d_buffer[i][j]
                if d > max_d:
                    max_d = d
                if d != -1 and d < min_d:
                    min_d = d
        # print(min_d, max_d)

        delta_d = max_d - min_d
        if delta_d == 0:
            delta_d = 1
        min_i, max_i = 127, 255
        delta_i = max_i - min_i
        for i in prange(height):
            for j in prange(width):
                d = d_buffer[i][j]
                if d != -1:
                    c = int(min_i + delta_i * (max_d - d) / delta_d)    # чем меньше расстояние - тем ярче
                    c_buffer[i][j] = np.array([c, c, c], dtype=np.uint8)
        return c_buffer, d_buffer

    def z_buffer(self):
        c_buffer = np.full([self.height, self.width, 3], 0, dtype=np.uint8)
        # d_buffer = np.full([self.height, self.width], -1.0)
        d_buffer = np.full([self.height, self.width], self.camera.max_z)
        camera = (self.camera.center,
                  self.camera.h_dir,
                  self.camera.v_dir,
                  self.camera.min_z,
                  self.camera.max_z)
        points = []
        triangles = []
        for obj in self.scene.objs:
            for triangle in obj.triangles:
                v0, v1, v2 = triangle
                pl = len(points)
                triangles.append([v0 + pl, v1 + pl, v2 + pl])
            points.extend(obj.points)
        points = np.array(points)
        triangles = np.array(triangles)
        objs = (points, triangles)
        new_basis_points = np.full((len(points), 3), np.array([0., 0., 0.]))
        c_buffer = zb(c_buffer, d_buffer, self.height, self.width, camera, objs, new_basis_points)
        return c_buffer

    def draw_points(self):
        if len(self.scene.point_clouds):
            tb = time()
            c_buffer = np.full([self.height, self.width, 3], 0, dtype=np.uint8)
            d_buffer = np.full([self.height, self.width], -1.0)
            camera = (self.camera2.center,
                      self.camera2.h_dir,
                      self.camera2.v_dir,
                      self.camera2.min_z,
                      self.camera2.max_z)
            points = []
            for point_cloud in self.scene.point_clouds:
                points.extend(point_cloud.points)
            points = np.array(points)
            # print(points)
            new_basis_points = np.full((len(points), 3), np.array([0., 0., 0.]))
            c_buffer, d_buffer = draw_points(c_buffer, d_buffer, self.height, self.width, camera, points, new_basis_points)
            record_procedure_time(self.canvas.draw_buffer, c_buffer, v=True, text="draw")
            te = time()
            if te - tb != 0:
                print(f"FPS: {1/(te - tb)}")
            else:
                print("FPS: None")
        else:
            self.canvas.clear_canvas()

    def get_point_cloud(self):
        if len(self.scene.objs):
            if self.pattern_arg is None:
                t, buffers = record_func_time(self.pattern, reps=1, v=True, text="raytracing ")
            else:
                t, buffers = record_func_time(self.pattern, self.pattern_arg, reps=1, v=True, text="raytracing ")
            point_cloud = PointCloud()
            d_buffer, rays = buffers[1], buffers[2]
            record_procedure_time(point_cloud.add_from_ray_tracing, self.camera.center, rays, d_buffer, v=True, text="add_from_ray_tracing")
            return point_cloud

    def scan(self, add_point_cloud_callback_func):
        if len(self.scene.objs):
            point_cloud = self.get_point_cloud()
            self.scene.add_point_cloud(point_cloud)
            add_point_cloud_callback_func()

    def script_exec(self, script):
        save = [self.camera.center.copy(), self.camera.h_dir.copy(), self.camera.v_dir.copy()]
        print(save)
        point_cloud = PointCloud()
        for step in script:
            dx, dy, dz, lr, ud = step
            self.camera.move_d(dx, dy, dz)
            self.camera.rotate_left_right(lr)
            self.camera.rotate_up_down(ud)
            points = self.get_point_cloud().points
            point_cloud.add_points(points)
        self.scene.add_point_cloud(point_cloud)
        print(save)
        self.camera.center = save[0]
        self.camera.h_dir = save[1]
        self.camera.v_dir = save[2]

    def draw(self):
        tb = time()
        if len(self.scene.objs):
            # t, c_buffer = record_func_time(self.z_buffer, v=True, text="z-buffer")
            # record_procedure_time(self.canvas.draw_buffer, c_buffer, v=True, text="draw")
            if self.pattern_arg is None:
                t, buffers = record_func_time(self.pattern, reps=1, v=True, text="raytracing ")
                # t, buffers = record_func_time(self.record, reps=1, v=True, text="raytracing ")
            else:
                t, buffers = record_func_time(self.pattern, self.pattern_arg, reps=1, v=True, text="raytracing ")

            t, buffers = record_func_time(self.distance_grad,
                                          buffers, self.height, self.width,
                                          self.camera.min_z, self.camera.max_z,
                                          v=True, text="dist_grad")
            record_procedure_time(self.canvas.draw_buffer, buffers[0], v=True, text="draw")
        else:
            self.canvas.clear_canvas()
        te = time()
        if te - tb != 0:
            print(f"FPS: {1/(te - tb)}")
        else:
            print("FPS: None")


class Canvas(QLabel):
    def __init__(self, callback):
        super().__init__()
        self.width = 800
        self.height = 600
        pixmap = QPixmap(self.width, self.height)
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)

        self.red = np.array([255, 0, 0], dtype=np.uint8)
        self.green = np.array([0, 255, 0], dtype=np.uint8)
        self.blue = np.array([0, 0, 255], dtype=np.uint8)
        self.black = np.array([0, 0, 0], dtype=np.uint8)
        self.white = np.array([255, 255, 255], dtype=np.uint8)
        # print('black', self.black, self.black.dtype, self.black[0].dtype, self.black[1].dtype, self.black[2].dtype)
        self.callback = callback

    def mousePressEvent(self, ev: QMouseEvent) -> None:
        point = int(ev.position().x()), int(ev.position().y())
        if ev.button() == Qt.MouseButton.LeftButton:
            self.callback.draw()
        # if ev.button() == Qt.MouseButton.RightButton:
        #     self.callback.add_clipper_point(point)

    def draw_point(self, point: tuple[int, int], color: tuple[int, int, int]):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawPoint(*point)
        painter.end()
        self.setPixmap(pixmap)

    def draw_line(self, point_beg: tuple[int, int], point_end: tuple[int, int], color: tuple[int, int, int] = (255, 255, 255)):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawLine(*point_beg, *point_end)
        painter.end()
        self.setPixmap(pixmap)

    # 0.6ms
    def draw_buffer(self, buffer):
        # buffer = np.flipud(buffer)
        # buffer = np.array(buffer, dtype=np.uint8)                                           # 0.2 ms
        image = QImage(buffer.data, self.width, self.height, QImage.Format.Format_RGB888)   # 0.02ms
        self.setPixmap(QPixmap.fromImage(image))                                            # 0.4 ms

    def clear_canvas(self):
        buffer = np.full([self.height, self.width, 3], 0, dtype=np.uint8)
        image = QImage(buffer.data, self.width, self.height, QImage.Format.Format_RGB888)
        self.setPixmap(QPixmap.fromImage(image))

    # # 500ms
    # def draw_buffer_painter(self, buffer):
    #     buffer.reverse()    # перевернуть изображение
    #
    #     pixmap = self.pixmap()
    #     painter = QPainter(pixmap)
    #     for i, line in enumerate(buffer):
    #         for j, pixel in enumerate(line):
    #             painter.setPen(QColor(*pixel))
    #             painter.drawPoint(j, i)
    #
    #     painter.end()
    #     self.setPixmap(pixmap)

    # # 95 ms
    # def draw_buffer_by_points(self, buffer):
    #     buffer.reverse()
    #
    #     image = QImage(self.width, self.height, QImage.Format.Format_RGB32)
    #     for i, line in enumerate(buffer):
    #         for j, pixel in enumerate(line):
    #             image.setPixel(j, i, qRgb(*pixel))
    #     self.setPixmap(QPixmap.fromImage(image))

    # # 56ms
    # def draw_buffer(self, buffer):
    #     buffer.reverse()
    #     np_buf = np.array(buffer, dtype=np.uint8)                                       # 56ms
    #     # print(np_buf.shape)
    #     # print(*np_buf[600-20])
    #     image = QImage(np_buf, self.width, self.height, QImage.Format.Format_RGB888)    # 0.02ms
    #     self.setPixmap(QPixmap.fromImage(image))                                        # 0.4 ms

