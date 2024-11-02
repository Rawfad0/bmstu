import sys
import json
import time
import out.main as main


def func_test(test_case):
    window.reset()
    window.function_combo_box.setCurrentIndex(test_case['func_id'])
    window.x_from_entry.setText(str(test_case['x_from']))
    window.z_from_entry.setText(str(test_case['z_from']))
    window.x_to_entry.setText(str(test_case['x_to']))
    window.z_to_entry.setText(str(test_case['z_to']))
    window.x_step_entry.setText(str(test_case['x_step']))
    window.z_step_entry.setText(str(test_case['z_step']))
    window.ox_rotate_entry.setText(str(test_case['ox_rotate']))
    window.oy_rotate_entry.setText(str(test_case['oy_rotate']))
    window.oz_rotate_entry.setText(str(test_case['oz_rotate']))
    window.scale_entry.setText(str(test_case['scale']))
    window.rotate_ox()
    window.rotate_oy()
    window.rotate_oz()
    window.draw()


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
