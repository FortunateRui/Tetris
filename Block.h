// Block.h
//此头文件是Block类的申明头文件
#ifndef BLOCK_H
#define BLOCK_H

#include "Draw.h"
#include "General.h"
#include <cstdlib>
#include <ctime>

class Block
{
public:
    int x;                  // 当前x坐标(左边是0处，地图宽度为10)
    int y;                  // 当前y坐标(上边是0处，地图高度为20)
    int kind;               // 当前样式(0~18,共19种样式)
    int last_x;             // 更新前的x坐标
    int last_y;             // 更新前的y坐标
    int last_kind;          // 更新前的样式
    int style;              // 方块片的图案样式0~3,3为空样式
    Color color_block;      // block的颜色
    Draw draw;              // 用于绘图的对象
    static int map[10][20];                 // 记录静止的方块
    static const int kindArray[7];          // 记录方块片的样式
    static const int shape[19][4][2];       // 记录方块片的形状
    // 生成方块片的构造函数
    Block();
    // 生成指定图案的方块片
    Block(int style);
    // 返回kind改变后的值，并不修改this.kind
    int changeKind(int kind);
    /*
        检查方块片移动或旋转是否合法以及是否触底
        move为移动方向,0代表下移,1代表左移,2代表右移,3代表旋转
        返回值0代表不合法,1代表合法
    */
    bool checkMove(int move);
    /*
        更新方块片移动或旋转
        move为移动方向,0代表下移,1代表左移,2代表右移,3代表旋转
    */
    void moveAndDraw(int move);
    // 后缀++运算符重载,用于方块片下落一格
    void operator++(int);
};
#endif