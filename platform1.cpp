#include "platform1.h"
#include <QDebug>

platform1::platform1(){}

void platform1::setPlat(){
    this->setPixmap(QPixmap(":/res/platform1.png").scaled(100,30));
}
