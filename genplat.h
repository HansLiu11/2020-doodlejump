#ifndef GENPLAT_H
#define GENPLAT_H
#include "platform.h"
#include "platform1.h"
#include "platform2.h"
#include "platform3.h"
#include "monster.h"
#include "monster1.h"
#include "monster2.h"
#include "monster3.h"
#include "hole.h"

platform* genplat();
monster* genmonst(platform* p);
platform2* genplat2();

#endif // GENPLAT_H
