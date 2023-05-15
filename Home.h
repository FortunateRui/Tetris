//Home.h
#ifndef HOME_H
#define HOME_H

#include "Draw.h"
#include <ege/sys_edit.h>

class Home
{
private:
    int score[5];
public:
    //默认构造函数
    Home();
    // 初始化函数,主要负责初始化文件
    void init();
    //主界面渲染函数
    void run(int &pageFlag);
    /* 
        鼠标有效事件判断函数
        返回值0代表无效事件,1代表悬停设置按钮,2代表悬停start按钮,3代表悬停排行榜
        11代表点击设置按钮,12代表点击start按钮,13代表点击排行榜按钮
    */
    int mouseJudge(int flag);

};

#endif