#ifndef PLATFORM2_H
#define PLATFORM2_H

#include <QTimer>
#include <platform.h>

class platform2:public platform
{
    Q_OBJECT

public:
    platform2();
    void jump(double & );
    void move(double dy);
    void setPlat();

public slots:
    void move_RL();
    void dissappear();

private:
    double dx ;
    QTimer *timer;
};

#endif // PLATFORM2_H
