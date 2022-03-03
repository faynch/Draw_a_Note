#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>

#include <QColor>
#include <QColorDialog>
#include <QGridLayout>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set background
    QPixmap bg(":/img/img/BgProject.jpg");
    bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, bg);
    this->setPalette(palette);

    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->stackedWidget->setCurrentIndex(0);

    draw = new Draw(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Menu Bar
void MainWindow::on_CloseBT_clicked()
{
    QApplication::quit();
}

void MainWindow::on_MaxBT_clicked()
{
    this->showFullScreen();
    draw->resize(1260,660);
    QPixmap bg(":/img/img/BgProject2.jpg");
    bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, bg);
    this->setPalette(palette);
}

void MainWindow::on_MinBT_clicked()
{
    this->showMinimized();
    draw->resize(720, 410);
    QPixmap bg(":/img/img/BgProject.jpg");
    bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, bg);
    this->setPalette(palette);
}

void MainWindow::on_MenuBT_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_AboutBT_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_OkAboutBT_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


//Menu
void MainWindow::on_DrawBT_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_NoteBT_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

//Draw
//change pen color
void MainWindow::on_red_pen_clicked()
{
    draw->setPenColor("#DA121A");
}

void MainWindow::on_yellow_pen_clicked()
{
    draw->setPenColor("#FCDD09");
}

void MainWindow::on_blue_pen_clicked()
{
    draw->setPenColor("#0F47AF");
}

void MainWindow::on_green_pen_clicked()
{
    draw->setPenColor("#078930");
}

void MainWindow::on_orange_pen_clicked()
{
    draw->setPenColor(QColor(255, 147, 0));
}

void MainWindow::on_purple_pen_clicked()
{
    draw->setPenColor(QColor(83, 27, 147));
}

void MainWindow::on_black_pen_clicked()
{
    draw->setPenColor(Qt::black);
}

void MainWindow::on_color_pen_clicked()
{
    QColor newColor = QColorDialog::getColor();

    if (newColor.isValid())
        draw->setPenColor(newColor);
}

void MainWindow::on_eraser_clicked()
{
    draw->setPenColor(Qt::white);
}

void MainWindow::on_font_width_valueChanged(int value)
{
    draw->setPenWidth(value);
}

void MainWindow::on_NewDrawBT_clicked()
{
    file_path = "";
    draw->clearDrawingBoarding();
    check = true;
}

void MainWindow::on_OpenDrawBT_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file...",
                                                     "/Users/faynch/Documents/Year1/sem2_year1/C++/Project/Draw");
    file_path = file_name;
    if(!file_name.isEmpty()){
        draw->openImage(file_name);
        check = false;
    }
}

void MainWindow::on_SaveDrawBT_clicked()
{
    if(check){
        QString file_name = QFileDialog::getSaveFileName(this,"Save file...",
                                                         "/Users/faynch/Documents/Year1/sem2_year1/C++/Project/Draw",
                                                         tr("Images (*.png *.jpg)"));
        file_path = file_name;
        check = false;
    }
    check = draw->saveImage(file_path);
}

//Note
void MainWindow::on_OpenNoteBT_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file...",
                                                     "/Users/faynch/Documents/Year1/sem2_year1/C++/Project/Note");
    QFile file(file_name);
    file_path = file_name;
    if (!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"warning!","file not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEditNote->document()->setPlainText(text);
}

void MainWindow::on_SaveNoteBT_clicked()
{
    QFileInfo check_file(file_path);

    if(!(check_file.exists() && check_file.isFile())){
        QString file_name = QFileDialog::getSaveFileName(this,"Save file...",
                                                         "/Users/faynch/Documents/Year1/sem2_year1/C++/Project/Note");
        file_path = file_name;
    }
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"warning!","unable to save file");
        return;
    }
    QTextStream out(&file);
    QString text = ui->plainTextEditNote->document()->toPlainText();
    out << text;
    file.flush();
    file.close();
    QMessageBox::information(this,"","file save successfully");
}

void MainWindow::on_NewNoteBT_clicked()
{
    file_path = "";
    ui->plainTextEditNote->clear();
}






