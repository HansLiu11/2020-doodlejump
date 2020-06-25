#ifndef MONSTER1_H
#define MONSTER1_H

#include "monster.h"
#include "platform.h"

class monster1:public monster
{
public:
    monster1(platform* t);
    ~monster1(){}
    void pause();
    void timeon();
    void dis_time();

public slots:
    void move_RL();

private:
    platform *tar;
    QTimer *timer ;
};

#endif // MONSTER1_H
