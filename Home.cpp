//Home.cpp
#include "Home.h"

Home::Home(){}

void Home::init()
{
    // 初始化option文件
    std::ifstream infile;
    infile.open("option.txt");
    if (!infile) {
        std::ofstream outfile("option.txt");
        outfile <<3<<' '<<4;
        outfile.close();
    }
    infile.close();
    // 初始化record文件
    infile.open("record1.txt");
    if (!infile) {
        std::ofstream outfile("record1.txt");
        for(int i=0;i<5;i++)outfile<<"NULL 0 0 0 0"<<std::endl;
        outfile.close();
    }
    else
    {
        for(int i=0;i<5;i++)
    {
        char temp1[20];
        int temp2;
        infile>>temp1>>score[i]>>temp2>>temp2>>temp2;
    }
    for(int i=1;i<5;i++)
    {
        if(score[i]>score[i-1])throw "Abnormal data in record1.txt";
    }
    }
    infile.close();
    infile.open("record2.txt");
    if (!infile) {
        std::ofstream outfile("record2.txt");
        for(int i=0;i<5;i++)outfile<<"NULL 0 0 0 0"<<std::endl;
        outfile.close();
    }
    else
    {
        for(int i=0;i<5;i++)
    {
        char temp1[20];
        int temp2;
        infile>>temp1>>score[i]>>temp2>>temp2>>temp2;
    }
    for(int i=1;i<5;i++)
    {
        if(score[i]>score[i-1])throw "Abnormal data in record2.txt";
    }
    }
    infile.close();
    infile.open("record3.txt");
    if (!infile) {
        std::ofstream outfile("record3.txt");
        for(int i=0;i<5;i++)outfile<<"NULL 0 0 0 0"<<std::endl;
        outfile.close();
    }
    else
    {
        for(int i=0;i<5;i++)
    {
        char temp1[20];
        int temp2;
        infile>>temp1>>score[i]>>temp2>>temp2>>temp2;
    }
    for(int i=1;i<5;i++)
    {
        if(score[i]>score[i-1])throw "Abnormal data in record3.txt";
    }
    }
    infile.close();
    infile.open("record4.txt");
    if (!infile) {
        std::ofstream outfile("record4.txt");
        for(int i=0;i<5;i++)outfile<<"NULL 0 0 0 0"<<std::endl;
        outfile.close();
    }
    else
    {
        for(int i=0;i<5;i++)
    {
        char temp1[20];
        int temp2;
        infile>>temp1>>score[i]>>temp2>>temp2>>temp2;
    }
    for(int i=1;i<5;i++)
    {
        if(score[i]>score[i-1])throw "Abnormal data in record4.txt";
    }
    }
    infile.close();
    infile.open("record5.txt");
    if (!infile) {
        std::ofstream outfile("record5.txt");
        for(int i=0;i<5;i++)outfile<<"NULL 0 0 0 0"<<std::endl;
        outfile.close();
    }
    else
    {
        for(int i=0;i<5;i++)
    {
        char temp1[20];
        int temp2;
        infile>>temp1>>score[i]>>temp2>>temp2>>temp2;
    }
    for(int i=1;i<5;i++)
    {
        if(score[i]>score[i-1])throw "Abnormal data in record5.txt";
    }
    }
    infile.close();
}

void Home::run(int &pageFlag)
{
    // 初始化home界面
    Draw draw;
    draw.homePage(0);
    try{init();}             // 检查文件是否有被非法修改的异常并处理
    catch(const char* msg)
    {
        MessageBox(NULL,msg,"Error",MB_OK|MB_ICONERROR);
        pageFlag=9;
        return;
    }
    int flag=0;                 //记录鼠标的有效事件
    while(1)
    {
        Sleep(10);
        flag=mouseJudge(flag);
        if(flag==1||flag==11)
        {
            draw.homePage(1);
            if(flag==11)
            {
                // 进入设置
                pageFlag=2;
                return;
                break;
            }
        }
        else if(flag==2||flag==21)
        {
            draw.homePage(2);
            if(flag==21)
            {
                // 进入游戏
                pageFlag=1;
                return;
                break;
            }
        }
        else if(flag==3||flag==31)
        {
            draw.homePage(3);
            if(flag==31)
            {
                // 进入排行榜
                pageFlag=3;
                return;
                break;
            }
        }
        else
        {
            draw.homePage(0);
        }
    }

}

int Home::mouseJudge(int flag)
{
    int mouseX;
    int mouseY;
    mouse_msg msg;
    while(mousemsg())
    {
        msg = getmouse();
        mouseX = msg.x;
        mouseY = msg.y;
        if(mouseX>=60&&mouseX<=140&&mouseY>=510&&mouseY<=590&&msg.is_left())
        {
            return 11;
            break;
        }
        else if(mouseX>=60&&mouseX<=140&&mouseY>=510&&mouseY<=590)
        {
            return 1;
            break;
        }
        else if(mouseX>=230&&mouseX<=430&&mouseY>=510&&mouseY<=590&&msg.is_left())
        {
            return 21;
            break;
        }
        else if(mouseX>=230&&mouseX<=430&&mouseY>=510&&mouseY<=590)
        {
            return 2;
            break;
        }
        else if(mouseX>=520&&mouseX<=600&&mouseY>=510&&mouseY<=590&&msg.is_left())
        {
            return 31;
            break;
        }
        else if(mouseX>=520&&mouseX<=600&&mouseY>=510&&mouseY<=590)
        {
            return 3;
            break;
        }
        else if(flag!=0)
        {
            return 0;
            break;
        }
    }
    return flag;
}