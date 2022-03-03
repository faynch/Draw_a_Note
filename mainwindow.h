#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "draw.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Draw;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Create my own "Menu bar"
    void on_CloseBT_clicked();
    void on_MaxBT_clicked();
    void on_MinBT_clicked();

    void on_MenuBT_clicked();
    void on_AboutBT_clicked();

    //Mode in this App
    void on_DrawBT_clicked();
    void on_NoteBT_clicked();

    //Buttons in "About"
    void on_OkAboutBT_clicked();

//about "Draw"
    //Pen & Eraser
    void on_red_pen_clicked();
    void on_yellow_pen_clicked();
    void on_blue_pen_clicked();
    void on_green_pen_clicked();
    void on_orange_pen_clicked();
    void on_purple_pen_clicked();
    void on_black_pen_clicked();
    void on_color_pen_clicked();
    void on_eraser_clicked();
    void on_font_width_valueChanged(int value);

    //Buttons in "Draw"
    void on_NewDrawBT_clicked();
    void on_OpenDrawBT_clicked();
    void on_SaveDrawBT_clicked();

//about "Note"
    //Buttons in "Note"
    void on_OpenNoteBT_clicked();
    void on_SaveNoteBT_clicked();
    void on_NewNoteBT_clicked();


private:
    Ui::MainWindow *ui;
    Draw *draw;
    QString file_path;
    bool check = true; //Check the file has saved or not
};
#endif // MAINWINDOW_H
