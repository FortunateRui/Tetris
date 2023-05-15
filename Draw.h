// Draw.h
// 画图类，包含了一些画图函数，所有的画图都在这里完成
#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include <fstream>
#include <graphics.h>
#include "General.h"

class Draw
{
private:
    static int offset;          // homePage中的偏移量
    static int style1[927];     // 保存方块的图案1
    static int style2[972];     // 保存方块的图案2
    static int style3[207];     // 保存方块的图案3
public:
    // 初始化一些基本变量,打开窗口
    Draw();
    // 画出homePage
    void homePage(int flag);
    // 画云
    void cloud(int x, int y);
    // 画圆角矩形
    void fillroundrect(int left, int top, int right, int bottom, int width, int height);
    // 画圆角矩形框
    void roundrectBox(int left,int top,int right,int bottom,int width,int height,Color lineColor,Color fillColor);
    // 画圆角矩形按钮,flag=0表示无事件,flag=1表示左按钮悬停,flag=2表示右按钮悬停
    void roundrectButton(int left,int top,int right,int bottom,int width,int height,Color lineColor,Color fillColor,int flag);
    // 画方块,style为0~3,0为空样式
    void square(int x, int y, Color color,int style);
    // 通过背景色覆盖的方式擦除方块
    void clearSquare(int x, int y);
    // 画游戏界面的静态部分
    void gamePage(int level,int highestScore);
    // 画游戏当前得分
    void gameScore(int score);
    // 画home按钮,0代表未悬停,1代表悬停
    void homeButton(int x,int y,Color bkColor,int flag);
    // 画游戏结束界面,flag为0代表未进入排行,1代表进入排行
    void gameOver(int flag);
    // 画排行榜界面
    void rankPage(int level);
    // 画排行榜的每一行
    void rankLine(int i,char name[],int score,int year,int month,int day);
    // 画排行榜选项中的level数值
    void rankLevel(int level);
    // 画设置界面的静态部分
    void optionPage(int level,int style);
    // 画设置界面中的level数值
    void optionLevel(int level);
    // 画设置界面中的style数值
    void optionStyle(int style);
    // 画设置界面中的方块
    void optionSquare(int style);
};

#endif