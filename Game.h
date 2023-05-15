// Game.h
#ifndef GAME_H
#define GAME_H
#include <chrono>
#include "Draw.h"
#include "Block.h"
#include <ege/sys_edit.h>
#include <windows.h>

class Game
{
private:
    int level;              // 记录该局游戏的难度
    int style;              // 记录该局游戏的样式
    Block* currentBlock;    // 指向当前存活的方块片
    Block* nextBlock;       // 指向下一个方块片
    bool isOver;            // 记录游戏是否结束
    Draw draw;              // 游戏界面绘制类
    char name[5][20];
    int highestScore[5];
    int year[5];
    int month[5];
    int day[5];
public:
    // 默认构造函数，初始化一些基本变量
    Game();
    // 游戏静态界面渲染函数,函数中会读取level和当前难度的highestScore
    void init();
    // 游戏动态函数
    void play(int &pageFlag);
    // 得分函数,函数中会更新map,并判断是否有满行,消去满行且更新绘图,返回值为此次得分
    int getScore(Block* block);
    // 游戏结束函数
    void over(int score,int &pageFlag);
    // 鼠标有效事件判断函数,返回值为0~2,0表示无效事件,1表示悬停按钮,2表示左键点击按钮
    int mouseJudge(int flag);
};

#endif