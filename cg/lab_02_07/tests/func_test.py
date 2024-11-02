import sys
import json
import time
import out.main as main


def enter_input_data(window, inputs):
    entries = [
        window.move_dx_entry,
        window.move_dy_entry,
        window.rotate_center_x_entry,
        window.rotate_center_y_entry,
        window.rotate_angle_entry,
        window.scale_center_x_entry,
        window.scale_center_y_entry,
        window.scale_kx_entry,
        window.scale_ky_entry,
    ]
    for i in range(len(entries)):
        entries[i].setText(inputs[i])


def func_test(test_case):
    for i in range(len(test_case['commands'])):
        command = test_case['commands'][i]
        if command['command'] == 'move':
            inputs = [command['dx'], command['dy'], '0', '0', '0', '0', '0', '1', '1']
            enter_input_data(window, inputs)
            window.move_figure()
        elif command['command'] == 'rotate':
            inputs = ['0', '0', command['cx'], command['cy'], command['angle'], '0', '0', '1', '1']
            enter_input_data(window, inputs)
            window.rotate_figure()
        elif command['command'] == 'scale':
            inputs = ['0', '0', '0', '0', '0', command['cx'], command['cy'], command['kx'], command['ky']]
            enter_input_data(window, inputs)
            window.scale_figure()


def test_main():
    for test in tests['tests']:
        tb = time.time()
        func_test(test)
        window.canvas.print_png(f"results/test_{test['num']}_result.png")
        with open(f"results/test_{test['num']}_description.txt", 'w') as descr_f:
            descr_f.write(test['description'])
        window.restart()
        te = time.time()
        testing_time = (te - tb) * 1000
        results.append(f"{test['num']} {testing_time}\n")
    with open(f"results/functest_tmp.txt", 'w') as f:
        f.writelines(results)


if __name__ == "__main__":
    results = []
    with open("./tests/data.json", 'r') as f:
        tests = json.load(f)
    main.init_figure()
    app = main.QApplication(sys.argv)
    window = main.MainWindow()
    test_main()
