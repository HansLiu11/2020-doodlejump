#include "shield.h"

shield::shield(platform* t):tar(t)
{
    setPos(tar->x()+tar->pixmap().width()/2-30,tar->y()-40);
    setPixmap(QPixmap(":/res/shield.png").scaled(60,70));
}
void shield::move(double dy){
    setPos(x(),y()-dy);
}

