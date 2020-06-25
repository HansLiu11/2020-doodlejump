#include "platform.h"


platform::platform()
{

}
void platform::move(double dy){
    setPos(x(),y()-dy);
}
void platform::jump(double & y){
    y = -8;
}
