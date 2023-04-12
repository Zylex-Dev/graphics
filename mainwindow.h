#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include "paint_widget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_Menu_Color_currentIndexChanged(int index);

    void on_comboBox_Menu_Time_currentIndexChanged(int index);

    void on_pushButton_Menu_Draw_clicked();

    void on_pushButton_Image_BackToMenu_clicked();




    void on_spinBox_Stars_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    int combobox_house;
    int combobox_time;
    int combobox_stars;
    int countstar;


};

#endif // MAINWINDOW_H
