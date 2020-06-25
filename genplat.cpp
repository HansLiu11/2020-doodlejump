#include "genplat.h"
#define PLATFORM_NUM 3
#define MONSTER_NUM 3
#define MONSTER_1 0
#define MONSTER_2 1
#define MONSTER_3 2

platform* genplat(){
    int plat_tp;
    platform* ptr;

    plat_tp = rand() % 30;
    if(plat_tp<=24){
        ptr = new platform1;
    }
    else if(plat_tp <29 && plat_tp>=25)
    {
        ptr = new platform3;
    }
    else{
        ptr = new platform2;
    }

    return ptr;
}
monster* genmonst(platform* p){
    int mon_tp;
    monster *ptr;

    mon_tp = rand() % MONSTER_NUM ;
    switch (mon_tp) {
    case MONSTER_1:
        ptr = new monster1(p);
        break;
    case MONSTER_2:
        ptr = new monster2;
        ptr->setmonster();
        break;
    case MONSTER_3:
        ptr = new monster3;
        ptr->setmonster();
        break;
    }
    return ptr;
}
platform2* genplat2(){
    platform2 *ptr = new platform2;
    return ptr;

}
