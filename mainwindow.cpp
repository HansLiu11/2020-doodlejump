#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <iostream>
#include <ctime>
#include  <QtDebug>
#define Plat_size 30
#define JUNGLE 0
#define SPACE 1
#define UNDERWATER 2
#define HOP 3

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0,0,600,800)),
    timer(new QTimer),
    b_timer(new QTimer)
{
    srand(static_cast<unsigned>(time(NULL)));
    ui->setupUi(this);
    this->setMaximumSize(600,850);
    this->setMinimumSize(600,850);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stackedWidget->setCurrentIndex(0);
    plf_ptr.resize(Plat_size);
    ui->Hop_bottom->hide();
    connect(timer, SIGNAL(timeout()), this, SLOT(jump()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::set(){
    score = 0; count=0; t=0,dy = -10;
    switch (bg_theme) {
    case JUNGLE:
        scene->setBackgroundBrush(QPixmap (":/res/jungle-bck.png"));
        pausebg = new QGraphicsPixmapItem(QPixmap(":/res/pause.png").scaled(600,800));
        scene->addItem(pausebg);
        pausebg->setZValue(10);
        line = new QGraphicsPixmapItem(QPixmap(":/res/jungles.png").scaled(600,750));
        scene->addItem(line);
        line->setZValue(5);
    break;
    case SPACE:
        scene->setBackgroundBrush(QPixmap (":/res/space-bck2.png"));
        pausebg = new QGraphicsPixmapItem(QPixmap(":/res/space_pause.png").scaled(600,800));
        scene->addItem(pausebg);
        pausebg->setZValue(10);
        break;
    case UNDERWATER:
        scene->setBackgroundBrush(QPixmap (":/res/underwater-bck.png"));
        pausebg = new QGraphicsPixmapItem(QPixmap(":/res/underwater_pause.png").scaled(600,800));
        scene->addItem(pausebg);
        pausebg->setZValue(10);
        line = new QGraphicsPixmapItem(QPixmap(":/res/underwater-light (2).png").scaled(600,750));
        scene->addItem(line);
        line->setZValue(5);
        break;
    case HOP:
        scene->setBackgroundBrush(QPixmap (":/res/hop-bck2.png"));
        pausebg = new QGraphicsPixmapItem(QPixmap(":/res/hop_pause.png").scaled(600,800));
        scene->addItem(pausebg);
        pausebg->setZValue(10);
        break;
    }
    player = new QGraphicsPixmapItem(QPixmap(":/res/char1.png").scaled(100,100));
    scene->addItem(player);
    player->setPos(250,600);
    generate();
    ui->scoreLb->setNum(score);
    timer->start(8);
    b_timer->start(4);
    fly_md = false;invin_md = false;shield_est = false;hole_est = false;
    pausebg->hide();ui->Resumebt->setVisible(false);ui->pauselb->setVisible(false);ui->pic1->hide();

}
void MainWindow::generate(){
    int i,x,y,r;
    unsigned long c,d;
    srand(static_cast<unsigned>(time(NULL)));
    r = rand() % 1200;
    for(i=0; i<Plat_size; ++i){
        c = static_cast<unsigned long>(i);
        x = rand()%static_cast<int>(scene->width()-100);
        y =(i==0)? r:static_cast<int>(plf_ptr.at(c-1)->y()+plf_ptr.at(c-1)->pixmap().height()+rand()% 130);
        plf_ptr[c] = genplat();
        plf_ptr[c]->setPlat();
        plf_ptr[c]->setPos(x,y);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(plf_ptr.at(c)));
    }
    d = rand()%Plat_size;
    trp = new trampo(plf_ptr.at(d));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(trp));

}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch (e->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        dx=-4;
        if(fly_md)
            player->setPixmap(QPixmap(":/res/jetdood_L.png").scaled(100,140));
        else if(invin_md)
            player->setPixmap(QPixmap(":/res/invincible2.png").scaled(100,100));
        else
            player->setPixmap(QPixmap(":/res/char2.png").scaled(100,100));
        player->setPos(player->x()+dx,player->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        dx= 4;
        if(fly_md)
            player->setPixmap(QPixmap(":/res/jetdood_R.png").scaled(100,140));
        else if(invin_md)
            player->setPixmap(QPixmap(":/res/invincible1.png").scaled(100,100));
        else
            player->setPixmap(QPixmap(":/res/char1.png").scaled(100,100));
        player->setPos(player->x()+dx,player->y());
        break;
    }
}
void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button()==Qt::LeftButton && !fly_md){
        player->setPixmap(QPixmap(":/res/dood.png").scaled(100,100));
        b = new bullet(mon_ptr);
        b->setPixmap(QPixmap(":/res/egg.png").scaled(30, 30));
        b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
        b->connect(b_timer, SIGNAL(timeout()), b, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        QTimer::singleShot(500,this,SLOT(setPic()));

    }
}
void MainWindow::setPic(){
    player->setPixmap(QPixmap(":/res/char1.png").scaled(100,100));
}
void MainWindow::sethard(){
    int r;
    unsigned long c,d;
    bool collide = false;
    monster* ptr;

    do{d = rand() % Plat_size;}while(plf_ptr.at(d)->y()+plf_ptr.at(d)->pixmap().height() >0);
    sd = new shield(plf_ptr.at(d));
    shield_est = true;
    scene->addItem(static_cast<QGraphicsPixmapItem*>(sd));
    do{d = rand() % Plat_size;}while(plf_ptr.at(d)->y()+plf_ptr.at(d)->pixmap().height() >0 ||
                                     (plf_ptr.at(d)->x()+plf_ptr.at(d)->pixmap().width()/2-30 == sd->x() && plf_ptr.at(d)->y() == sd->y()+40));
    jet = new jetpack(plf_ptr.at(d));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(jet));
    jet_est = true;

    r = rand() % 2;
    switch(r){
    case 0:
        hole_est = true;
        while(1){
            ho = new hole;
            for(int i=0;i< Plat_size;++i){
                c = static_cast<unsigned long>(i);
                if(ho->collidesWithItem(jet,Qt::IntersectsItemShape) && ho->collidesWithItem(plf_ptr.at(c),Qt::IntersectsItemShape)){
                    collide = true;
                    delete ho;
                    break;
                }
                else
                    continue;
            }
            if(collide)
                continue;
            else
                break;
        }
        scene->addItem(static_cast<QGraphicsPixmapItem*>(ho));
    break;
    case 1:
        while(1){      //generate monster and detect the intersection between plf&plf2
            do{d = rand() % Plat_size;}while(plf_ptr.at(d)->y()+plf_ptr.at(d)->pixmap().height() >0);
            ptr = genmonst(plf_ptr.at(d));
            for(int i=0;i< Plat_size;++i){
                c = static_cast<unsigned long>(i);
                if(ptr->collidesWithItem(jet,Qt::IntersectsItemShape) && ptr->collidesWithItem(plf_ptr.at(c),Qt::IntersectsItemShape) && ptr->y()+ptr->pixmap().height()-plf_ptr.at(c)->y() >11 ){
                    collide = true;
                    ptr->dis_time();
                    delete ptr;
                    break;
                }
                else
                    continue;
            }
            if(collide)
                continue;
            else
                break;
        }
        scene->addItem(static_cast<QGraphicsPixmapItem*>(ptr));
        mon_ptr.push_back(ptr);
    break;
    }

}
void MainWindow::invincible_end(){
    invin_md = false; t = 0;
    player->setPixmap(QPixmap(":/res/char1.png").scaled(100,100));
}

void MainWindow::jump()
{
    int Y,x;
    unsigned long c,d;
    Y = static_cast<int>(player->y()+player->pixmap().height());
    if(fly_md)//fly with jetpack
    {
        ++count;
        if(count == 118){
            player->setPixmap(QPixmap(":/res/char1.png").scaled(100,100));
            fly_md = false;
            count = 0;
            timer->start(8);
        }
    }
    dy+=0.1;
    if(dx>0.0){dx = dx-0.2;}
    if (dx<0.0) {dx+=0.2;}
    player->setPos(static_cast<int>(player->x()+dx),static_cast<int>(player->y()+dy));
    if(Y >= scene->height()){
        timestop();
        QTimer::singleShot(500,this,SLOT(Gameover()));
    }
    for (int i = 0; i<Plat_size; ++i) {
        c = static_cast<unsigned long>(i);
        plf_ptr.at(c)->move_RL();
    }
    trp->pos();
    if(jet_est)jet->pos();

    if(dy > 1 && timer->interval() == 12){timer->start(8);}
    if(player->y() <= 200){
        player->setY(200);
        score += abs(dy);
        ui->scoreLb->setNum(score);
        for (int i=0;i< Plat_size;++i) {// platform move down
            c = static_cast<unsigned long>(i);
            plf_ptr[c]->move(dy);
            if(plf_ptr[c]->y() >= scene->height()){
                x = rand()%(static_cast<int>(scene->width())-100);
                plf_ptr[c]->setPos(x,plf_ptr.at(a)->y()-plf_ptr.at(a)->pixmap().height()-rand()% 130);
                a = static_cast<unsigned long>(i);
            }
        }
        for (int i=0;i<mon_ptr.size();++i) {//monster move down and rebuild
            c = static_cast<unsigned long>(i);
            mon_ptr[c]->move(dy);
            if(mon_ptr.at(c)->y() > scene->height()){
                 scene->removeItem(mon_ptr.at(c));
                 mon_ptr.at(c)->pause();
                 delete mon_ptr.at(c);
                 do{d = rand() % Plat_size;}while(plf_ptr.at(d)->y()+plf_ptr.at(d)->pixmap().height() >100);
                 mon_ptr.at(c) = genmonst(plf_ptr.at(d));
                 scene->addItem(static_cast<QGraphicsPixmapItem*>(mon_ptr.at(c)));
              }
        }
        trp->move(dy);//trampoline move down
        if(trp->y()>scene->height()){
            scene->removeItem(trp);
            delete  trp;
            do{d = rand() % Plat_size;}while(plf_ptr[d]->y()+plf_ptr.at(d)->pixmap().height() >100);
            trp = new trampo(plf_ptr.at(d));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(trp));
        }
        if(jet_est){// jetpack move down (if exist)
            jet->move(dy);
            if(jet->y()>scene->height()){
                scene->removeItem(jet);
                delete jet;
                jet_est = false;
            }
        }
        if(hole_est){//hole move down (if exist)
            ho->move(dy);
            if(ho->y()>scene->height()){
                scene->removeItem(ho);
                delete ho;
                hole_est=false;
            }
        }
        if(shield_est){
            sd->move(dy);//shield move down(if exist)
            if(sd->y()>scene->height()){
                scene->removeItem(sd);
                delete sd;
                shield_est =false;
            }
        }

    }
    for (int i = mon_ptr.size();i < score/5000;++i) {
        sethard();
    }
    if(dy>1 && !fly_md){
        for(int i=0;i < Plat_size;++i){
            c = static_cast<unsigned long>(i);
            if (player->collidesWithItem(plf_ptr[c],Qt::IntersectsItemShape)) {
                if(Y <= (plf_ptr[c]->y() + plf_ptr[c]->pixmap().height()))
                    plf_ptr[c]->jump(dy);
            }
        }
        if(player->collidesWithItem(trp,Qt::IntersectsItemShape)){
            if(player->y()+player->pixmap().height() <= (trp->y() + trp->pixmap().height())){
                trp->bounce(dy);
                timer->start(12);
            }
        }

    }
    if(jet_est){ // if colliding jetpack
        if(player->collidesWithItem(jet,Qt::IntersectsItemShape)){
            fly_md = true;
            jet->fly(dy);
            scene->removeItem(jet);
            delete jet;
            jet_est = false;
            timer->start(16);
            player->setPixmap(QPixmap(":/res/jetdood_R.png").scaled(100,140));
        }
    }
    if(shield_est){// if colliding shield
        if(player->collidesWithItem(sd,Qt::IntersectsItemShape)){
            invin_md = true;
            scene->removeItem(sd);
            delete sd;
            shield_est =false;
            player->setPixmap(QPixmap(":/res/invincible1.png").scaled(100,100));
        }
    }
    if(invin_md && t==0){
        QTimer::singleShot(4000,this,SLOT(invincible_end()));
        ++t;
    }
    for (int i = 0;i<mon_ptr.size();++i) {
        c = static_cast<unsigned long>(i);
        if(!fly_md && !invin_md && player->collidesWithItem(mon_ptr.at(c),Qt::IntersectsItemShape)){
           if(dy>1 && Y <= (mon_ptr.at(c)->y() + 10 )){
                dy = -8;
                mon_ptr.at(c)->pause();
                mon_ptr.at(c)->setPos(0,790);
            }
            else{
                 timestop();
                 QTimer::singleShot(1500,this,SLOT(Gameover()));
            }
        }
    }
    if(hole_est){
        if(!fly_md && !invin_md && player->collidesWithItem(ho,Qt::IntersectsItemShape)){
            timestop();
            QTimer::singleShot(1500,this,SLOT(Gameover()));
         }
    }
    if(player->x()>scene->width())player->setPos(0,player->y());
    else if (player->x()<0) player->setPos(scene->width(),player->y());
}
void MainWindow::Gameover(){
    unsigned long c;
    //scene->removeItem(pausebg);
    //delete pausebg;
    //scene->removeItem(line);
    //delete line;
    scene->removeItem(trp);
    delete trp;
    if(jet_est){scene->removeItem(jet);delete jet;}
    if(hole_est){scene->removeItem(ho);delete ho;}
    if(shield_est){scene->removeItem(sd);delete sd;}
    for(int i=0;i<Plat_size;++i){
        c = static_cast<unsigned long>(i);
        scene->removeItem(plf_ptr.at(c));
        delete plf_ptr.at(c);
    }
    for(int i=0 ; i<mon_ptr.size();++i){
        c = static_cast<unsigned long>(i);
        scene->removeItem(mon_ptr.at(c));
        delete mon_ptr.at(c);
    }
    mon_ptr.erase(mon_ptr.begin(),mon_ptr.end());
    ui->fscorelabel->setText("Final Score: "+ QString::number(score));
    ui->fscorelabel->setAlignment(Qt::AlignCenter);
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::timestop(){
    unsigned long c;
    timer->stop();
    b_timer->stop();
    for(int i=0 ; i<mon_ptr.size();++i){
        c = static_cast<unsigned long>(i);
        mon_ptr.at(c)->pause();
    }
}
void MainWindow::on_Pausebt_clicked()
{
    timestop();
    pausebg->show();ui->Resumebt->setVisible(true);ui->pauselb->setVisible(true);ui->pic1->show();
}

void MainWindow::on_Resumebt_clicked()
{
    unsigned long c;
    timer->start(8);
    b_timer->start(2);
    for(int i=0 ; i<mon_ptr.size();++i){
        c = static_cast<unsigned long>(i);
        mon_ptr.at(c)->timeon();
    }
    pausebg->hide();ui->Resumebt->setVisible(false);ui->pauselb->setVisible(false);
    ui->pic1->hide();
}

void MainWindow::on_playButton_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_menuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_JungleBT_clicked()
{
    bg_theme = 0;
    set();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_SpaceBt_clicked()
{
    bg_theme = 1;
    set();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_UWBt_clicked()
{
    bg_theme = 2;
    set();
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_HopBT_clicked()
{
    bg_theme = 3;
    ui->Hop_bottom->show();
    set();
    ui->stackedWidget->setCurrentIndex(2);
}
