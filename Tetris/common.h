#ifndef COMMON_H
#define COMMON_H

#define block_r 25
#define main_bd_h 24
#define main_bd_w 10
#define BIANK 5

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};
struct block_point{
    int pos_x;
    int pos_y;
};

#endif // COMMON_H
