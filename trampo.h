#ifndef TRAMPO_H
#define TRAMPO_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <cstdlib>
#include "platform.h"



class trampo: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    trampo(platform* t);
    void bounce(double &dy);
    void move(double dy);

public slots:
    void pos();

private:
    platform *tar;
};

#endif // TRAMPO_H
