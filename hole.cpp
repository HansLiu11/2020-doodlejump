#include "hole.h"

hole::hole()
{
    setPos(rand()%500,rand()% 800 -1200);
    setPixmap(QPixmap(":/res/hole.png").scaled(100,100));
}
