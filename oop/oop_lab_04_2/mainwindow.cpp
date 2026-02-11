#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "Elevator at floor 1";
    qDebug() << "Cabin movement unlocked";
    qDebug() << "Doors closed";

    ui->setupUi(this);

    this->setFixedSize(500, 500);
    this->_layout = std::make_unique<QVBoxLayout>();

    this->ui->centralwidget->setLayout(this->_layout.get());

    this->_layout->addWidget(this->_elevator.widget());
}

MainWindow::~MainWindow()
{
    delete ui;
}
