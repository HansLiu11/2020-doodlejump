#include "doodle.h"
#define Plat_size 15
#define MON_SIZE 3

doodle::doodle():time1(new QTimer),timer(new QTimer)
{

}
void doodle::move_L(){
    dx=-6;
    this->setPixmap(QPixmap(":/res/char2.png").scaled(80,80));
    setPos(x()+dx,y());
}
void doodle::move_R(){
    dx=+6;
    this->setPixmap(QPixmap(":/res/char1.png").scaled(80,80));
    setPos(x()+dx,y());
}
void doodle::play(){

}
void doodle::jump(){

}
void doodle::shoot(){
    b = new bullet(mon_ptr);
    b->setPixmap(QPixmap(":/res/手裏劍.png").scaled(60, 60));
    b->setPos(this->x() + this->pixmap().width() / 2 - b->pixmap().width() / 2, this->y() - b->pixmap().height());
    //b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    this->scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));

}
