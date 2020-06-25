#include "monster.h"
#include <cstdlib>
#include <QTime>
#include <ctime>

monster::monster()
{

}
void monster::move(double dy){
    setPos(x(),y()-dy);
}
void monster::setmonster(){

}

