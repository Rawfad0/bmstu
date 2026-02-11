#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "actions.h"
#include "errors.h"
#include "error_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui 
{ 
    class MainWindow; 
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void action_load_clicked();

    void action_save_clicked();

    void action_info_file_clicked();

    void action_info_program_clicked();

    void action_info_author_clicked();

private slots:
    rc_t draw();

    void on_move_button_clicked();

    void on_rotate_button_clicked();

    void on_scale_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif
