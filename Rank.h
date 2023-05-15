// Rank.h
#ifndef RANK_H
#define RANK_H

#include "Draw.h"


class Rank
{
private:
    Draw draw;
    char name[5][5][20];// 5个文件,每个文件5个记录,每个记录20个字符
    int highestScore[5][5];
    int year[5][5];
    int month[5][5];
    int day[5][5];
    int level;  // 记录当前查看的难度
public:
    // 默认构造函数
    Rank();
    // 初始化函数,主要负责初始化文件和成员变量
    void init();
    // rank界面渲染函数
    void run(int &pageFlag);
    /*
        鼠标有效事件判断函数,返回值为0表示无效事件,1表示悬停左按钮,2表示悬停右按钮,3表示悬停返回按钮
        11表示左键点击左按钮,21表示左键点击右按钮,31表示左键点击返回按钮
    */
    int mouseJudge(int flag);
};

#endif