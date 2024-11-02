import sys
import json
import time
import out.main as main


def func_test(test_case):
    window.delay_entry.setText(str(test_case['delay']))
    for figure in test_case['figures']:
        for point in figure:
            x, y = point
            window.add_point_x_entry.setText(str(x))
            window.add_point_y_entry.setText(str(y))
            window.add_point_with_check()
        window.close_polyline()
    for ellipse in test_case['ellipses']:
        rx, ry, cx, cy = ellipse
        window.ellipse_center_x_entry.setText(str(rx))
        window.ellipse_center_y_entry.setText(str(ry))
        window.ellipse_radius_x_entry.setText(str(cx))
        window.ellipse_radius_y_entry.setText(str(cy))
        window.draw_ellipse()
    xs, ys = test_case['seed_point']
    window.add_point_x_entry.setText(str(xs))
    window.add_point_y_entry.setText(str(ys))
    window.add_seed_point()
    window.fill()


def test_main():
    for test in tests['tests']:
        tb = time.time()
        func_test(test)
        window.canvas.pixmap().toImage().save(f"results/test_{test['num']}_result.png")
        with open(f"results/test_{test['num']}_description.txt", 'w') as descr_f:
            descr_f.write(test['description'])
        window.clear()
        te = time.time()
        testing_time = (te - tb) * 1000
        results.append(f"{test['num']} {testing_time}\n")
    with open(f"results/functest_tmp.txt", 'w') as f:
        f.writelines(results)


if __name__ == "__main__":
    results = []
    with open("./tests/data.json", 'r') as f:
        tests = json.load(f)
    app = main.QApplication(sys.argv)
    window = main.MainWindow()
    test_main()
