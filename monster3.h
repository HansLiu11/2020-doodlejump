#ifndef MONSTER3_H
#define MONSTER3_H

#include "monster.h"
#include <QTimer>

class monster3:public monster
{
public:
    monster3();
    ~monster3(){}
    void pause();
    void timeon();
    void dis_time();

public slots:
    void move_RL();

private:
    QTimer* mv_timer;
    int count = 0,dh;
    bool rl;
};

#endif // MONSTER3_H
