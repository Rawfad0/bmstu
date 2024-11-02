import sys
import json
import time
import out.main as main


def func_test(test_case):
    for point in test_case['clipper']:
        x, y = point
        window.x_entry.setText(str(x))
        window.y_entry.setText(str(y))
        window.add_clipper_point_with_check()
    window.close_clipper()
    for point in test_case['polygon']:
        x, y = point
        window.x_entry.setText(str(x))
        window.y_entry.setText(str(y))
        window.add_polygon_point_with_check()
    window.close_polygon()
    window.clip()


def test_main():
    for test in tests['tests']:
        tb = time.time()
        func_test(test)
        window.canvas.pixmap().toImage().save(f"results/test_{test['num']}_result.png")
        # window.canvas.print_png(f"results/test_{test['num']}_result.png")
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
