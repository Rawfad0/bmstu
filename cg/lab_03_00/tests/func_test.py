import sys
import json
import time
import out.main as main


def func_test(test_case):
    window.algs_combo_box.setCurrentIndex(test_case['func_id'])
    if test_case['command_type'] == "draw_line":
        window.line_begin_x_entry.setText(str(test_case['line_begin_x']))
        window.line_begin_y_entry.setText(str(test_case['line_begin_y']))
        window.line_end_x_entry.setText(str(test_case['line_end_x']))
        window.line_end_y_entry.setText(str(test_case['line_end_y']))
        window.draw_line()
    elif test_case['command_type'] == "draw_spectre":
        window.spectre_degree_entry.setText(str(test_case['angle']))
        window.spectre_length_entry.setText(str(test_case['length']))
        window.draw_spectre()


def test_main():
    for test in tests['tests']:
        tb = time.time()
        func_test(test)
        window.canvas.pixmap().toImage().save(f"results/test_{test['num']}_result.png")
        with open(f"results/test_{test['num']}_description.txt", 'w') as descr_f:
            descr_f.write(test['description'])
        window.canvas.clear_canvas()
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
