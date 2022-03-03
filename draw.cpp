#include "draw.h"
#include "ui_draw.h"


Draw::Draw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StaticContents);

    //set backgrond of the drawboard
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    //check the user is drawing or not
    draw = false;
    //set the pen
    penColor = Qt::black;
    penWidth = 5;
}

Draw::~Draw()
{
    delete ui;
}

void Draw::setPenColor(QColor tempColor)
{
    penColor = tempColor;
};

void Draw::setPenWidth(int tempWidth)
{
    penWidth = tempWidth;
};

//open the existing image
bool Draw::openImage(QString &fileName){
    if(!image.load(fileName)){
        return false;
    }
    QSize newSize = image.size().expandedTo(size());
    resizeImage(&image, newSize);
    update();
    return true;
}

bool Draw::saveImage(QString &fileName){
    resizeImage(&image, size());
    if(image.save(fileName)){
        QMessageBox::information(this,"","file save successfully");
        return false;
    }
    QMessageBox::warning(this,"warning!","unable to save file");
    return true;
}

void Draw::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        point = event->pos();
        draw = true;
    }
}
void Draw::mouseMoveEvent(QMouseEvent *event){
    if(draw){
        drawLineTo(event->pos());
    }
}

void Draw::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && draw){
        drawLineTo(event->pos());
        draw = false;
    }
}

//Updates the draw area where we are painting
void Draw::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect tempRect = event->rect();
    painter.drawImage(tempRect, image, tempRect);
}

//Make sure that the area we are drawing on remains as large as the widget
void Draw::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

//Used to draw on the widget
void Draw::drawLineTo(const QPoint &tempPoint){
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(point, tempPoint);

    update(QRect(point, tempPoint).normalized().adjusted(-penWidth, -penWidth, +penWidth, +penWidth));
    point = tempPoint;
}

void Draw::resizeImage(QImage *image, const QSize &tempSize)
{
    if (image->size() == tempSize){
        return;
    }

    QImage tempImage(tempSize, QImage::Format_RGB32);
    tempImage.fill(Qt::white);

    QPainter painter(&tempImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = tempImage;
}

void Draw::clearDrawingBoarding(){
    image.fill(Qt::white);
    update();
}
