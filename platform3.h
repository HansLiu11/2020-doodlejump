#ifndef PLATFORM3_H
#define PLATFORM3_H

#include <QTimer>
#include <platform.h>

class platform3:public platform
{
    Q_OBJECT

public:
    platform3();
    void setPlat();
public slots:
    void move_RL();

private:
    double dx = 4 ;

};

#endif // PLATFORM3_H
