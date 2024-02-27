#ifndef SHIMEJI_H
#define SHIMEJI_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QScreen>
#include <QTime>

namespace Ui {
class Shimeji;
}

class Shimeji : public QWidget
{
    Q_OBJECT

public:
    explicit Shimeji(QWidget *parent = nullptr);
    ~Shimeji();

protected:
    void paintEvent(QPaintEvent *ev) override;
    void timerEvent(QTimerEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;

private:
    Ui::Shimeji *ui;
    QString shimejiCurrentImgUrl;
    QPoint posDeviation;        //鼠标按下点与窗口左上角的位置差
    int walkTimeoutId;
    int moveTimeoutId;
    int downTimeoutId;
    int modelTimeoutId;
    bool moveLeft;      //左走标志位
    int oldPosX;
    double screenAvailableX;        //当前屏幕可用窗口大小
    double screenAvailableY;
    bool canBeDown;         //下落标志位
    bool canBeWalk;         //走路标志位
    bool walkFlag;          //走路标志位
    bool sitFlag;           //坐站标志位
    int walkModel;          //走路模式
};

#endif // SHIMEJI_H
