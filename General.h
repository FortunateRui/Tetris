// General.h
// 通用头文件，包含了一些常用的结构体和常量
#ifndef GENERAL_H
#define GENERAL_H

struct Color
{
    int red;
    int green;
    int blue;
};
static const Color color[7] = 
{
    {0, 255, 255},  // 青色
    {0, 0, 255},    // 蓝色
    {255, 165, 0},  // 橙色
    {255, 255, 0},  // 黄色
    {0, 255, 0},    // 绿色
    {128, 0, 128},  // 紫色
    {255, 0, 0}     // 红色
};
#endif