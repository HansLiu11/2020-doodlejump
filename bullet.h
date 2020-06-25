#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "monster.h"
#include "basics.h"

class bullet: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    bullet(vector<monster*>  m);

public slots:
    void fly();

private:
    vector<monster*> mon;
    basics b;
};

#endif // BULLET_H
