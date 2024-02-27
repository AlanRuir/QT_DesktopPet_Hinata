#include "shimeji.h"
#include "ui_shimeji.h"

Shimeji::Shimeji(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shimeji)
{
    ui->setupUi(this);
    this->setFixedSize(128, 128);
    //设置窗口的控制栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | this->windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->shimejiCurrentImgUrl = "://img/shime1.png";
    this->walkTimeoutId = this->startTimer(250);        //每300毫秒走一步
    this->moveTimeoutId = this->startTimer(30);
    this->downTimeoutId = this->startTimer(7);
    this->modelTimeoutId = this->startTimer(10000);     //每10秒切换一次走路模式
    this->moveLeft = false;
    this->oldPosX = this->frameGeometry().x();
    this->walkFlag = false;
    this->sitFlag = true;
    this->canBeWalk = false;

    //获取当前设备屏幕可用大小
    this->screenAvailableX = QGuiApplication::primaryScreen()->availableGeometry().width();
    this->screenAvailableY = QGuiApplication::primaryScreen()->availableGeometry().height();

    this->canBeDown = this->frameGeometry().y() < this->screenAvailableY - this->height();
}

Shimeji::~Shimeji()
{
    delete ui;
}

void Shimeji::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    painter.drawPixmap(0, 0, QPixmap(this->shimejiCurrentImgUrl));

    painter.end();
}

void Shimeji::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == this->modelTimeoutId)
    {
        qsrand(QTime::currentTime().msec() + QTime::currentTime().second());
        this->walkModel = qrand() % 7;
    }

    if(ev->timerId() == this->walkTimeoutId)
    {
        if((0 == this->walkModel % 4) && this->canBeWalk)
        {
            if(this->walkFlag)
            {
                this->shimejiCurrentImgUrl = "://img/shime2.png";
                if(this->frameGeometry().left() > 0)        //保证宠物在可用屏幕内走动
                {
                    this->move(this->frameGeometry().topLeft() + QPoint(-5, 0));
                    this->walkFlag = !this->walkFlag;
                }else
                {
                    this->shimejiCurrentImgUrl = "://img/shime1.png";
                }
            }else
            {
                this->shimejiCurrentImgUrl = "://img/shime3.png";
                if(this->frameGeometry().left() > 0)
                {
                    this->move(this->frameGeometry().topLeft() + QPoint(-5, 0));
                    this->walkFlag = !this->walkFlag;
                }else
                {
                    this->shimejiCurrentImgUrl = "://img/shime1.png";
                }
            }
        }else if((0 == this->walkModel % 5) && this->canBeWalk)
        {
            if(this->walkFlag)
            {
                this->shimejiCurrentImgUrl = "://img/shime47.png";
                if(this->frameGeometry().left() + this->width() < this->screenAvailableX)       //保证宠物在可用屏幕内走动
                {
                    this->move(this->frameGeometry().topLeft() + QPoint(5, 0));
                }
                this->walkFlag = !this->walkFlag;
            }else
            {
                this->shimejiCurrentImgUrl = "://img/shime48.png";
                if(this->frameGeometry().left() + this->width() < this->screenAvailableX)
                {
                    this->move(this->frameGeometry().topLeft() + QPoint(5, 0));
                }
                this->walkFlag = !this->walkFlag;
            }
        }else if((0 == this->walkModel % 6) && this->canBeWalk)
        {
            if(this->sitFlag)
            {
                this->shimejiCurrentImgUrl = "://img/shime16.png";
                this->sitFlag = !this->sitFlag;
            }
        }else if((0 == this->walkModel % 7) && this->canBeWalk)
        {
            if(this->sitFlag)
            {
                this->shimejiCurrentImgUrl = "://img/shime1.png";
                this->sitFlag = !this->sitFlag;
            }
        }else
        {
            this->shimejiCurrentImgUrl = "://img/shime1.png";
        }

        this->update();
    }

    if(ev->timerId() == this->moveTimeoutId)
    {
        this->moveLeft = (this->frameGeometry().x() - this->oldPosX) < 0;
        this->oldPosX = this->frameGeometry().x();
    }

    if(ev->timerId() == this->downTimeoutId)
    {
        if(this->canBeDown)
        {
            if(this->frameGeometry().y() < this->screenAvailableY - this->height())
            {
                this->shimejiCurrentImgUrl = "://img/shime22.png";
                this->move(this->frameGeometry().topLeft() + QPoint(0, 3));
            }
            else
            {
                this->shimejiCurrentImgUrl = "://img/shime1.png";
                this->canBeDown = false;
                this->canBeWalk = true;
            }

            this->update();
        }
    }
}

void Shimeji::mousePressEvent(QMouseEvent *ev)
{
    this->canBeWalk = false;

    if(Qt::RightButton == ev->button())
    {
        this->close();
    }else if(Qt::LeftButton == ev->button())
    {
        this->shimejiCurrentImgUrl = "://img/shime1.png";
        //求出按下点与窗口坐标差值
        this->posDeviation = ev->globalPos() - this->frameGeometry().topLeft();
    }

    this->update();
}

void Shimeji::mouseReleaseEvent(QMouseEvent *)
{
    this->canBeWalk = false;

    if(this->frameGeometry().y() < this->screenAvailableY - this->height())
    {
        this->canBeDown = true;
    }
}

void Shimeji::mouseMoveEvent(QMouseEvent *ev)
{
    this->canBeWalk = false;

    if(ev->buttons() & Qt::LeftButton)
    {
        this->move(ev->globalPos() - this->posDeviation);
    }

    if(this->moveLeft)
    {
        this->shimejiCurrentImgUrl = "://img/shime8.png";
    }else
    {
        this->shimejiCurrentImgUrl = "://img/shime7.png";
    }

    this->update();
}

