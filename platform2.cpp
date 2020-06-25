#include "platform2.h"

platform2::platform2()
{

}
void platform2::jump(double & ){
    this->setPixmap(QPixmap(":/res/platform2_break.png").scaled(100,50));
    QTimer::singleShot(500,this,SLOT(dissappear()));
    dx = 0;
}
void platform2::move(double dy){
    setPos(x(),y()-dy);
    if(this->y() >= this->scene()->height()){
        this->setPixmap(QPixmap(":/res/platform2.png").scaled(100,40));
        show();
    }
}
void platform2::move_RL(){
    if(x() < 0)
        dx = 1;
    else if (x()+this->pixmap().width() > this->scene()->width())
        dx = -1;
    setPos(x()+dx,y());
}
void platform2::setPlat(){
    this->setPixmap(QPixmap(":/res/platform2.png").scaled(100,40));
    int r = rand()%4;
    switch (r) {
    case 0:
        dx = 1;
        break;
    case 1:
        dx = -1;
        break;
    case 2: case 3:
        dx = 0;
        break;
    }
}
void platform2::dissappear(){
     hide();
}
