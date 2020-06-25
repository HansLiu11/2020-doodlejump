#include "jetpack.h"

jetpack::jetpack(platform *t):tar(t)
{
    setPos(tar->x()+tar->pixmap().width()/2-30,tar->y()-75);
    setPixmap(QPixmap(":/res/jetpack.png").scaled(60,80));
}
void jetpack::fly(double &dy){
    dy = -20;
}
void jetpack::move(double dy){
    setPos(x(),y()-dy);
}
void jetpack::pos(){
    setPos(tar->x()+tar->pixmap().width()/2-30,tar->y()-75);
}
