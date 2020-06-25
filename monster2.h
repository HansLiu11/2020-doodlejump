#ifndef MONSTER2_H
#define MONSTER2_H

#include "monster.h"
#include <QTimer>

class monster2:public monster
{
public:
    monster2();
    ~monster2(){}
    void setmonster();
    void pause();
    void timeon();
    void dis_time();

public slots:
    void move_RL();

private:
    QTimer* mv_timer;
    int count = 0,dx;
    bool rl;

};

#endif // MONSTER2_H
