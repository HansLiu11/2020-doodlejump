#include "monster2.h"

monster2::monster2():mv_timer(new QTimer)
{
    setPos(rand()%500,rand()% 800 -1600);
    setPixmap(QPixmap(":/res/monster2.png").scaled(100,60));
    mv_timer->start(80);
    this->connect(mv_timer,SIGNAL(timeout()),this,SLOT(move_RL()));
}

void monster2::move_RL(){
    if(count == 20){
        dx=-12;
        rl = false;
    }
    else if(count == 0){
        dx = 12;
        rl = true;
    }
    if(rl == true)
        count++;
    else
        count--;
    setPos(x()+dx,y());
}
void monster2::setmonster(){
    int r = rand()%2;
    switch (r) {
    case 1:
        dx = 12;
        rl = true;
        break;
    case 2:
        dx = -12;
        rl = false;
        break;
    }
}
void monster2::pause(){
    mv_timer->stop();
}
void monster2::timeon(){
    mv_timer->start(80);
}
void monster2::dis_time(){
    disconnect(mv_timer,SIGNAL(timeout()),this,SLOT(move_RL()));
}
