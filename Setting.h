// Setting.h
#ifndef SETTING_H
#define SETTING_H

#include "Draw.h"

class Setting
{
private:
    Draw draw;
    int level;  // 记录当前难度
    int style;  // 记录当前方块样式
public:
    Setting();
    void init();
    void run(int &pageFlag);
     /*
        鼠标有效事件判断函数
        返回值为0表示无效事件,1表示悬停level左按钮,2表示悬停level右按钮
        3表示悬停style左按钮,4表示悬停style右按钮,5表示悬停home按钮
        11表示左键点击level左按钮,21表示左键点击level右按钮
        31表示左键点击style左按钮,41表示左键点击style右按钮
        51表示左键点击home按钮
    */
    int mouseJudge(int flag);
};

#endif