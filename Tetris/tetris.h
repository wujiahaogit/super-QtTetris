#ifndef TETRIS_H
#define TETRIS_H

#include <QWidget>
#include "common.h"
struct Block{ //七种方块的结构体
    block_point bp{0,0};
    int btype=0;
    int shape=0;
    int bb[4][4];
};
QT_BEGIN_NAMESPACE
namespace Ui { class Tetris; }
QT_END_NAMESPACE

class Tetris : public QWidget
{
    Q_OBJECT

public:
    void Initgame(); //初始化
    void Startgame(); //开始游戏
    void Gameover(); //结束游戏
    int board[main_bd_h][main_bd_w]; //主界面
    Block next; //提示方格
    Block cur; //当前下落方格
    void Generate();//next -> cur
    void Generatenext(); // 创建 next
    bool Canmove(int x0, int y0); //坐标点是否能变换(up down left right)
    void killLines(); //消除满行
    int Linenum(); //返回从上到下数的第一个满行
    bool game_over(); //判断是否结束游戏
    void rotate(); //旋转
    bool if_rotate(); //判断能否旋转
    void move(int,int); // 移动
    void ResetBlock();// block迭代
    void move_block(Direction dir);//block ->move
public:
    explicit Tetris(QWidget *parent = 0);
    ~Tetris();
    virtual void paintEvent(QPaintEvent *event); //场景刷新
    virtual void timerEvent(QTimerEvent *event); //定时器事件
    virtual void keyPressEvent(QKeyEvent *event); //键盘响应
private:
    Ui::Tetris *ui;
    int score;  //游戏分数
    int game_timer; //方块下落计时器
    int paint_timer; //渲染刷新计时器
    int speed_ms; //下落时间间隔
    int refresh_ms; //刷新时间间隔
};
#endif // TETRIS_H
