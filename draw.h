#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPalette>
#include <QColor>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QMessageBox>

namespace Ui {
class Draw;
}

class Draw : public QWidget
{
    Q_OBJECT

public:
    explicit Draw(QWidget *parent = nullptr);
    ~Draw();

public:

    void setPenColor(QColor tempColor);
    void setPenWidth(int tempWidth);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &tempSize);
    void clearDrawingBoarding();

    bool openImage(QString &fileName);
    bool saveImage(QString &fileName);

private:
    Ui::Draw *ui;
    int penWidth;
    QPoint point;
    QImage image;
    QColor penColor;

    bool draw;
};

#endif // DRAW_H
