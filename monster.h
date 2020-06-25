#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>


using namespace std;

class monster:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    monster();
    virtual ~monster() {}
    virtual void setmonster();
    virtual void move(double dy);
    virtual void pause() {}
    virtual void timeon() {}
    virtual void dis_time(){}

public slots:
    virtual void move_RL(){}

protected:
};

#endif // MONSTER_H
