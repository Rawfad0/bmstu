import sys
import json
import time
import out.main as main


def func_test(test_case):
    p1, p2 = test_case['clipper']
    x1, y1 = p1
    x2, y2 = p2
    window.clipper_begin_x_entry.setText(str(x1))
    window.clipper_begin_y_entry.setText(str(y1))
    window.clipper_end_x_entry.setText(str(x2))
    window.clipper_end_y_entry.setText(str(y2))
    window.add_clipper_with_check()
    for line_segment in test_case['line_segments']:
        p1, p2 = line_segment
        x1, y1 = p1
        window.line_begin_x_entry.setText(str(x1))
        window.line_begin_y_entry.setText(str(y1))
        x2, y2 = p2
        window.line_end_x_entry.setText(str(x2))
        window.line_end_y_entry.setText(str(y2))
        window.add_line_segment_with_check()
    window.clip()


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
