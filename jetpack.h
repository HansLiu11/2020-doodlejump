#ifndef JETPACK_H
#define JETPACK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <cstdlib>
#include "platform.h"

class jetpack: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    jetpack(platform* t);
    void fly(double &dy);
    void move(double dy);

public slots:
    void pos();

private:
    platform *tar;
};

#endif // JETPACK_H
