#ifndef SHIELD_H
#define SHIELD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <cstdlib>
#include "platform.h"

class shield:public QObject,public QGraphicsPixmapItem
{

public:
    shield(platform* t);
    void move(double dy);

public slots:
    void pos();

private:
    platform* tar;


};

#endif // SHIELD_H
