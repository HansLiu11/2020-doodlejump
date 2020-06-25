#include "monster1.h"

monster1::monster1(platform* t):tar(t),timer(new QTimer)
{
    setPos(tar->x()+tar->pixmap().width()/2-50,tar->y()-60);
    this->setPixmap(QPixmap(":/res/monster1.png").scaled(100,70));
    timer->start(8);
    connect(timer,SIGNAL(timeout()),this,SLOT(move_RL()));
}

void monster1::move_RL(){
    setPos(tar->x()+tar->pixmap().width()/2-50,tar->y()-60);
}
void monster1::pause(){
    timer->stop();
}
void monster1::timeon(){
    timer->start(8);
}
void monster1::dis_time(){
    disconnect(timer,SIGNAL(timeout()),this,SLOT(move_RL()));
}
