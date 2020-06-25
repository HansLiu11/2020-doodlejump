#include "bullet.h"
#include <QTimer>

bullet::bullet(vector<monster*> m)
{
    mon = m ;
}
void bullet::fly()
{
    unsigned long c;
    setPos(x(), y() - 3);
    for (int i=0;i< mon.size();++i) {
        c = static_cast<unsigned long>(i);
        if(this->collidesWithItem(mon.at(c),Qt::IntersectsItemShape )){
            mon.at(c)->pause();
            mon.at(c)->setPos(0,790);
            this->scene()->removeItem(this);
            delete this;
            break;
        }
    }
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }

}
