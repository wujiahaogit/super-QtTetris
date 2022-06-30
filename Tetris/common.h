#ifndef COMMON_H
#define COMMON_H

#define block_r 25 //方块尺寸
#define main_bd_h 20 //游戏主界面长度
#define main_bd_w 10 //宽度
#define BIANK 5 //边框

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

//以4×4方格的左上顶点来记录block的位置
struct block_point{
    int pos_x;
    int pos_y;
};

#endif // COMMON_H
