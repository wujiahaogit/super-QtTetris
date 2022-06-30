#include <time.h>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QWidget>
#include "tetris.h"
#include "ui_tetris.h"

int types[8]{1,2,4,4,1,2,4,2};
//'0' I、J、L、O、S、T、Z
// 0 1 2 3 4 5 6 7

int itemi0[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
};
int itemi1[4][4]=
{
    {0,0,0,0},
    {0,0,0,0},
    {1,1,1,1},
    {0,0,0,0}
};
int itemj0[4][4]=
{
    {0,0,2,0},
    {0,0,2,0},
    {0,2,2,0},
    {0,0,0,0}
};
int itemj1[4][4]=
{
    {0,0,0,0},
    {0,2,0,0},
    {0,2,2,2},
    {0,0,0,0}
};
int itemj2[4][4]=
{
    {0,0,0,0},
    {0,2,2,0},
    {0,2,0,0},
    {0,2,0,0}
};
int itemj3[4][4]=
{
    {0,0,0,0},
    {0,0,0,0},
    {0,2,2,2},
    {0,0,0,2}
};
int iteml0[4][4]=
{
    {0,3,0,0},
    {0,3,0,0},
    {0,3,3,0},
    {0,0,0,0}
};
int iteml1[4][4]=
{
    {0,0,0,0},
    {0,3,3,3},
    {0,3,0,0},
    {0,0,0,0}
};
int iteml2[4][4]=
{
    {0,0,0,0},
    {0,3,3,0},
    {0,0,3,0},
    {0,0,3,0}
};
int iteml3[4][4]=
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,3},
    {0,3,3,3}
};
int items0[4][4]=
{
    {0,0,0,0},
    {0,5,5,0},
    {5,5,0,0},
    {0,0,0,0}
};
int items1[4][4]=
{
    {0,0,0,0},
    {5,0,0,0},
    {5,5,0,0},
    {0,5,0,0}
};
int itemz0[4][4]=
{
    {0,0,0,0},
    {7,7,0,0},
    {0,7,7,0},
    {0,0,0,0}
};
int itemz1[4][4]=
{
    {0,0,0,0},
    {0,7,0,0},
    {7,7,0,0},
    {7,0,0,0}
};
int itemt0[4][4]=
{
    {0,0,0,0},
    {0,6,0,0},
    {6,6,6,0},
    {0,0,0,0}
};
int itemt1[4][4]=
{
    {0,0,0,0},
    {0,6,0,0},
    {0,6,6,0},
    {0,6,0,0}
};
int itemt2[4][4]=
{
    {0,0,0,0},
    {0,0,0,0},
    {6,6,6,0},
    {0,6,0,0}
};
int itemt3[4][4]=
{
    {0,0,0,0},
    {0,6,0,0},
    {6,6,0,0},
    {0,6,0,0}
};
int itemo[4][4]=
{
    {0,0,0,0},
    {0,4,4,0},
    {0,4,4,0},
    {0,0,0,0}
};
Tetris::Tetris(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tetris)
{
    ui->setupUi(this);
    resize(main_bd_w*block_r+BIANK*4+4*block_r,main_bd_h*block_r+BIANK*2);
    Initgame();
}
void Tetris::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(BIANK,BIANK,main_bd_w*block_r,main_bd_h*block_r);
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(next.bb[i][j]){
                if(next.bb[i][j]==1)
                   painter.setBrush(QBrush(Qt::cyan,Qt::SolidPattern));
                else if(next.bb[i][j]==2)
                    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                else if(next.bb[i][j]==3)
                    painter.setBrush(QBrush(Qt::darkYellow,Qt::SolidPattern));
                else if(next.bb[i][j]==4)
                    painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
                else if(next.bb[i][j]==5)
                    painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                else if(next.bb[i][j]==6)
                    painter.setBrush(QBrush(Qt::magenta,Qt::SolidPattern));
                else if(next.bb[i][j]==7)
                    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(BIANK*3+main_bd_w*block_r+j*block_r,BIANK+i*block_r,block_r,block_r);
            }
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    painter.drawText(QRect(BIANK*3+main_bd_w*block_r,BIANK*2+4*block_r,block_r*4,block_r*4),Qt::AlignCenter,"score: "+QString::number(score));
    for(int i=0;i<main_bd_h;i++)
        for(int j=0;j<main_bd_w;j++)
        {
            if(board[i][j]){
                if(board[i][j]==1)
                   painter.setBrush(QBrush(Qt::cyan,Qt::SolidPattern));
                else if(board[i][j]==2)
                    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                else if(board[i][j]==3)
                    painter.setBrush(QBrush(Qt::darkYellow,Qt::SolidPattern));
                else if(board[i][j]==4)
                    painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
                else if(board[i][j]==5)
                    painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                else if(board[i][j]==6)
                    painter.setBrush(QBrush(Qt::magenta,Qt::SolidPattern));
                else if(board[i][j]==7)
                    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(j*block_r+BIANK,i*block_r+BIANK,block_r,block_r);
            }
       }

}
void Tetris::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==game_timer)
        move_block(DOWN);
    if(event->timerId()==paint_timer)
        update();
}

void Tetris::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        move_block(UP);
        break;
    case Qt::Key_Down:
        move_block(DOWN);
        break;
    case Qt::Key_Left:
        move_block(LEFT);
        break;
    case Qt::Key_Right:
        move_block(RIGHT);
        break;
    default:
        break;
    }
}

void Tetris::Generate()
{
    cur.btype=next.btype;
    cur.shape=next.shape;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            cur.bb[i][j]=next.bb[i][j];
        }
    }
    cur.bp={3,0};
}
void Tetris::Initgame()
{
    for(int i=0;i<main_bd_h;i++)
        for(int j=0;j<main_bd_w;j++)
            board[i][j]=0;

    speed_ms=800;
    refresh_ms=30;
    srand(time(0));
    score=0;
    Startgame();
}
void Tetris::Generatenext(){
    switch (next.shape){
    case 1: // I
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                next.bb[i][j]=itemi0[i][j];
            }
        }
        break;
    case 2: // J
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                next.bb[i][j]=itemj0[i][j];
            }
        }
        break;
    case 3:
        //##
        //L
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                next.bb[i][j]=iteml0[i][j];
            }
        }
        break;
    case 4:
        // ##
        // O
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                next.bb[i][j]=itemo[i][j];
            }
        }
        break;
    case 5:
        //#
        // S
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                next.bb[i][j]=items0[i][j];
            }
        }
        break;
    case 6:
        //  #
        //# T
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                next.bb[i][j]=itemt0[i][j];
            }
        }
        break;
    case 7:
        // #
        //  Z
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                next.bb[i][j]=itemz0[i][j];
            }
        }
        break;
    default:
        break;
    } //因为都是横着下来，纵坐标的最小值是-2.
}
void Tetris ::ResetBlock()
{
    Generate();
    int ID=rand()%7;
    next.shape=ID+1;
    Generatenext();
    cur.bp={main_bd_w/2-2,0};
}
void Tetris::Startgame()
{
    game_timer=startTimer(speed_ms);
    paint_timer=startTimer(refresh_ms);
    int ID=rand()%7;
    next.shape=ID+1;
    Generatenext();
    ResetBlock();
}

void Tetris::Gameover()
{
    //游戏结束停止计时器
    killTimer(game_timer);
    killTimer(paint_timer);
    QMessageBox::information(this,"failed","game over");

}
void Tetris::rotate()
{
    int temp[4][4];
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            temp[3-j][i]=cur.bb[i][j];
            if(cur.bb[i][j])
                board[i+cur.bp.pos_x][j+cur.bp.pos_y]=0;
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cur.bb[i][j]=temp[i][j];
            if(cur.bb[i][j])
                board[i+cur.bp.pos_x][j+cur.bp.pos_y]=cur.bb[i][j];
        }
    }
}
bool Tetris::if_rotate()
{
    int temp[4][4];
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            temp[3-j][i]=cur.bb[i][j];
        }
    }
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            int ti=cur.bp.pos_x+i,tj=cur.bp.pos_y+j;
            if((ti<0||ti>=20||tj<0||tj>=10)&&temp[i][j]>=1)
                return false;
            if(temp[i][j]>=1&&board[ti][tj]>=1)
                return false;
        }
    }
    return true;
}
bool Tetris::Canmove(int x0, int y0){ //判断能不能动的依据：创建一个新数组，对可能变化后的目标进行判定 如果结果为true直接移动
    if(x0==-1&&y0==0){
        return if_rotate();
    }
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            int ti=cur.bp.pos_x+i+x0,tj=cur.bp.pos_y+j+y0;
            if((ti<0||ti>=20||tj<0||tj>=10)&&cur.bb[i][j])
                return false;
            if(cur.bb[i][j]>=1&&board[ti][tj])
                return false;
        }
    }
    return true;
}
void Tetris::move(int x0,int y0)
{
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            if(cur.bb[i][j]){
                board[i+cur.bp.pos_x][j+cur.bp.pos_y]=0;
            }
        }
    }
    cur.bp.pos_x+=x0;
    cur.bp.pos_y+=y0;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            if(cur.bb[i][j]){
                board[i+cur.bp.pos_x][j+cur.bp.pos_y]=cur.bb[i][j];
            }
        }
    }
}
int Tetris::Linenum(){
    for (int j = 0; j < 20; j++){
        bool flag = true;
        for (int i = 0; i < 10; i++){
            if (board[j][i] == 0){
                flag = false;
                break;
            }
        }
        if (flag){
            return j;
        }
    }
    return -1;
}
void Tetris::killLines(){ //消行 思路：先找到能消的行，再将其上的行向下平移一行
    int count = 0;  //一次连续消掉的行数 最多为4（或许可以用在记分上）
    int temp = 0;
    temp = Linenum(); //刚才找到的列指标可消除的最小值
    while (temp != -1) { //可以消去
        for (int j = temp; j > 0; j--){
            for (int i = 0; i < 10; i++){
                board[j][i] = board[j-1][i];
            }
        }
        count++;
        temp = Linenum(); //判断能否连续消除
    }
    if(count==1) score+=100;
    else if(count==2) score+=200;
    else if(count==3) score+=400;
    else if(count==4) score+=800;
}
bool Tetris::game_over()
{
    for (int i = 0; i < 10; i++){
        if (board[0][i]>=1){
            return true;
        }
    }
    return false;
}
void Tetris::move_block(Direction dir)
{
    switch(dir)
    {
    case UP:
        if(Canmove(-1,0))
            rotate();
        break;
    case DOWN:
        if(Canmove(1,0))
            move(1,0);
        break;
    case LEFT:
        if(Canmove(0,-1))
            move(0,-1);
        break;
    case RIGHT:
        if(Canmove(0,1))
            move(0,1);
        break;
    default:
        break;
    }
    killLines();
    if(game_over())
        Gameover();
}
Tetris::~Tetris()
{
    delete ui;
}

