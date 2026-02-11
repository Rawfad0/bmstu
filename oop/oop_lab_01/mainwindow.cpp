#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsView *view = ui->graphicsView;
    QGraphicsScene *scene = new QGraphicsScene(this);

    view->setScene(scene);
    view->setAlignment(Qt::AlignTop | Qt::AlignRight);
    view->setStyleSheet("QGraphicsView {background-color: white}");

    connect(ui->action_load, &QAction::triggered, this, &MainWindow::action_load_clicked);
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::action_save_clicked);
    connect(ui->action_info_file, &QAction::triggered, this, &MainWindow::action_info_file_clicked);
    connect(ui->action_info_program, &QAction::triggered, this, &MainWindow::action_info_program_clicked);
    connect(ui->action_info_author, &QAction::triggered, this, &MainWindow::action_info_author_clicked);
}

MainWindow::~MainWindow()
{
    request_t request;
    request.action = DESTRUCT;
    action_controller(request);
    delete ui;
}

rc_t MainWindow::draw()
{
    QGraphicsView *view = ui->graphicsView;
    QGraphicsScene *scene = view->scene();
    auto rect_content = view->contentsRect();
    scene->setSceneRect(0, 0, rect_content.width(), rect_content.height());

    request_t request;
    request.action = DRAW;
    request.view = {
                    .scene = scene,
                    .width = scene->width(),
                    .height = scene->height()
                    };

    return action_controller(request);
}

void MainWindow::action_save_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    QByteArray path_utf = path.toUtf8();

    request_t request;
    request.action = WRITE;
    request.filename = path_utf.data();

    rc_t rc = action_controller(request);
    if (rc)
        error_handler(rc);
    else
    {
        rc = draw();
        if (rc)
            error_handler(rc);
    }
}

void MainWindow::action_load_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    QByteArray path_utf = path.toUtf8();

    request_t request;
    request.action = READ;
    request.filename = path_utf.data();
    
    rc_t rc = action_controller(request);
    if (rc)
        error_handler(rc);
    else
    {
        rc = draw();
        if (rc)
            error_handler(rc);
    }
}

void MainWindow::action_info_file_clicked()
{
    QMessageBox::information(0,
                             "Информация о входном файле",
                             "Файл должен содержать количество точек\n"
                             "Затем уже должны идти аргументы в строго в порядке:\n"
                             "x y z\n"
                             "После ввода все точек нужно отметить количество ребер\n"
                             "Затем уже идут нумерация связи точек(нумериция с 0) связи в любом порядке:\n"
                             "точка_1 точка_2\n\n"
                             "PS. Проверяй данные в файле!");
}

void MainWindow::action_info_program_clicked()
{
    QMessageBox::information(0,
                             "Информация о программе",
                             "Программа предназначаена для представления 3D объектов,"
                             "а также их сдвига, поворота и масштабирования.\n");
}

void MainWindow::action_info_author_clicked()
{
    QMessageBox::information(0,
                             "Информация об авторе программы",
                             "Автор программы: Равашдех Фадей ИУ7-45Б");
}

void MainWindow::on_move_button_clicked()
{
    QDoubleSpinBox *entry_dx = ui->enterXMoving;
    QDoubleSpinBox *entry_dy = ui->enterYMoving;
    QDoubleSpinBox *entry_dz = ui->enterZMoving;

    request_t request;
    request.action = MOVE;
    request.move = {
           .dx = entry_dx->value(),
           .dy = entry_dy->value(),
           .dz = entry_dz->value()
    };

    rc_t rc = action_controller(request);
    if (rc)
        error_handler(rc);
    else
    {
        rc = draw();
        if (rc)
            error_handler(rc);
    }
}

void MainWindow::on_rotate_button_clicked()
{
    QDoubleSpinBox *entry_ax = ui->X_angle_entry;
    QDoubleSpinBox *entry_ay = ui->Y_angle_entry;
    QDoubleSpinBox *entry_az = ui->Z_angle_entry;

    request_t request;
    request.action = ROTATE;
    request.rotate = {
           .ax = entry_ax->value(),
           .ay = entry_ay->value(),
           .az = entry_az->value()
    };

    rc_t rc = action_controller(request);
    
    if (rc)
        error_handler(rc);
    else
    {
        rc = draw();
        if (rc)
            error_handler(rc);
    }
}

void MainWindow::on_scale_button_clicked()
{
    QDoubleSpinBox *entry_kx = ui->enterXScale;
    QDoubleSpinBox *entry_ky = ui->enterYScale;
    QDoubleSpinBox *entry_kz = ui->enterZScale;
    
    request_t request;
    request.action = SCALE;
    request.scale = {
           .kx = entry_kx->value(),
           .ky = entry_ky->value(),
           .kz = entry_kz->value()
    };

    rc_t rc = action_controller(request);
    if (rc)
        error_handler(rc);
    else
    {
        rc = draw();
        if (rc)
            error_handler(rc);
    }
}
