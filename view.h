#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QDialog
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
private:
    Ui::View *ui;
    QPainter painter;
    QList<QString> fileList;
    QPoint interval;
    QPoint pos;
    int rotateAngle;
    QMatrix matrix;
    bool isPress;
    float zoomValue;
    int index;
};
#endif // VIEW_H
