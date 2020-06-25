#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>

class platform: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    platform();
    virtual void jump(double & y);
    virtual void move(double dy);
    virtual void setPlat() = 0 ;

public slots:
    virtual void move_RL(){}
    virtual void dissappear(){}
protected:
    QGraphicsPixmapItem *plf;

};

#endif // PLATFORM_H
