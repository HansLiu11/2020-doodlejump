#include "trampo.h"

trampo::trampo(platform* t):tar(t)
{
    setPos(tar->x()+tar->pixmap().width()/2-20,tar->y()-15);
    setPixmap(QPixmap(":/res/prop.png").scaled(60,30));

}
void trampo::bounce(double & dy){
    dy = -14;
}
void trampo::move(double dy){
    setPos(x(),y()-dy);
}
void trampo::pos(){ //set on platform
    setPos(tar->x()+tar->pixmap().width()/2-20,tar->y()-15);
}

