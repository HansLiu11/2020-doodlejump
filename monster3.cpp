#include "monster3.h"

monster3::monster3():mv_timer(new QTimer)
{
    setPos(rand()%520,rand()% 800 -1600);
    setPixmap(QPixmap(":/res/monster3.png").scaled(80,80));
    mv_timer->start(30);
    this->connect(mv_timer,SIGNAL(timeout()),this,SLOT(move_RL()));
}
void monster3::move_RL(){
    if(count == 5){
        dh=-4;
        rl = false;
    }
    else if(count == 0){
        dh = 4;
        rl = true;
    }
    if(rl == true)
        count++;
    else
        count--;
    setPos(x(),y()+dh);
}
void monster3::pause(){
    mv_timer->stop();
}
void monster3::timeon(){
    mv_timer->start(30);
}
void monster3::dis_time(){
    disconnect(mv_timer,SIGNAL(timeout()),this,SLOT(move_RL()));
}
