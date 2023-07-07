#include "view.h"
#include "ui_view.h"
#include "QDebug"
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QStyle>
#include <QStyleOption>

View::View(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    zoomValue = 1.0;
}

View::~View()
{
    delete ui;
}

void View::paintEvent(QPaintEvent *)
{
    if (index < 0 || index >= fileList.length()) {
        return;
    }

    QPixmap pix(fileList[index]);

    int width, height, imgWidth, imgHeight;

    if ((rotateAngle / 90) % 2 == 0) {
        imgWidth = pix.size().width() * zoomValue;
        imgHeight = pix.size().height() * zoomValue;
    } else {
        imgWidth = pix.size().height() * zoomValue;
        imgHeight = pix.size().width() * zoomValue;
    }

    width = qMin(imgWidth, ui->label->size().width());
    height = width * imgHeight / imgWidth;
    height = qMin(height, ui->label->size().height());
    width = height * imgWidth / imgHeight;

    QPixmap dest=pix.scaled(QSize(width, height), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QMatrix matrix;
    matrix.rotate(rotateAngle);
    ui->label->setPixmap(dest.transformed(matrix));
}

void View::wheelEvent(QWheelEvent *event)
{
    int value = event->delta();
    if (value > 0) {
        zoomValue+=0.05;
        qDebug() << "value>0 " << zoomValue;
    }else {
        zoomValue-=0.05;
        qDebug() << "value<0 " << zoomValue;
    }

    update();
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    if (!isPress) {
        return;
    }

    setCursor(Qt::SizeAllCursor);
    QPoint pos = event->pos();
    interval = pos - this->pos;
    this->pos = pos;
    update();
}

void View::mousePressEvent(QMouseEvent *event)
{
    pos = event->pos();
    isPress = true;
}

void View::mouseReleaseEvent(QMouseEvent *)
{

    isPress = false;
}

void View::on_pushButton_clicked()
{
    if (index < 1) {
        index = fileList.length();
    } else {
        index--;
    }


    update();
}

void View::on_pushButton_2_clicked()
{
    if (index >= fileList.length()) {
        index = 0;
    } else {
        index++;
    }
}

void View::on_pushButton_3_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this, "请选择图片所在目录");

    QDir dir(path);
    auto imgList = dir.entryList(QStringList()<<"*.png" << "*.bmp" << "*.jpg" << "*.tif" << "*.gif");
    QStringList* list = new QStringList();

    for (auto file : imgList) {
        fileList.append(path + "/" + file);

        list->append(file);
    }

    index = 0;
}

// 左旋
void View::on_pushButton_4_clicked()
{
    rotateAngle -= 90;
    if (rotateAngle < -270) {
        rotateAngle = 0;
    }
}

// 右旋
void View::on_pushButton_5_clicked()
{
    rotateAngle += 90;
    if (rotateAngle > 270) {
       rotateAngle = 0;
    }
}

