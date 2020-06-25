#include "platform3.h"

platform3::platform3()
{

}

void platform3::move_RL(){
    if(x() < 0)
        dx = 1;
    else if (x()+this->pixmap().width() > this->scene()->width())
        dx = -1;
    setPos(x()+dx,y());
}
void platform3::setPlat(){
    this->setPixmap(QPixmap(":/res/platform3.png").scaled(100,30));
    int r = rand()%2;
    switch (r) {
    case 0:
        dx = 1;
        break;
    case 1:
        dx = -1;
        break;
    }
}
