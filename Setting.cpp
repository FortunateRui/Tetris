// Setting.cpp
#include "Setting.h"

Setting::Setting()
:level(3),style(4)
{}

void Setting::init()
{
    std::ifstream infile;
    infile.open("option.txt");
    infile>>level>>style;
    infile.close();
    draw.optionPage(level,style);
}

void Setting::run(int& pageFlag)
{
    init();
    int flag=0;                 //记录鼠标的有效事件
    while(1)
    {
        Sleep(10);
        flag=mouseJudge(flag);
        if(flag==1||flag==11)
        {
            // 悬停level左箭头
            draw.roundrectButton(280,210,580,265,20,20,Color{139,69,19},Color{240,230,140},1);
            draw.optionLevel(level);
            if(flag==11)
            {
                // 点击level左箭头
                draw.roundrectButton(280,210,580,265,20,20,Color{139,69,19},Color{240,230,140},1);
                level=(level+3)%5+1;
                draw.optionLevel(level);
                Sleep(500);
            }
        }
        else if(flag==2||flag==21)
        {
            // 悬停level右箭头
            draw.roundrectButton(280,210,580,265,20,20,Color{139,69,19},Color{240,230,140},2);
            draw.optionLevel(level);
            if(flag==21)
            {
                // 点击level右箭头
                draw.roundrectButton(280,210,580,265,20,20,Color{139,69,19},Color{240,230,140},2);
                level=(level+5)%5+1;
                draw.optionLevel(level);
                Sleep(500);
            }
        }
        else if(flag==3||flag==31)
        {
            // 悬停style左箭头
            draw.roundrectButton(280,310,580,365,20,20,Color{139,69,19},Color{240,230,140},1);
            draw.optionStyle(style);
            if(flag==31)
            {
                // 点击style左箭头
                draw.roundrectButton(280,310,580,365,20,20,Color{139,69,19},Color{240,230,140},1);
                style=(style+4)%5;
                draw.optionStyle(style);
                draw.optionSquare(style);
                Sleep(500);
            }
        }
        else if(flag==4||flag==41)
        {
            // 悬停style右箭头
            draw.roundrectButton(280,310,580,365,20,20,Color{139,69,19},Color{240,230,140},2);
            draw.optionStyle(style);
            if(flag==41)
            {
                // 点击style右箭头
                draw.roundrectButton(280,310,580,365,20,20,Color{139,69,19},Color{240,230,140},2);
                style=(style+1)%5;
                draw.optionStyle(style);
                draw.optionSquare(style);
                Sleep(500);
            }
        }
        else if(flag==5||flag==51)
        {
            // 悬停home按钮
            draw.homeButton(600,65,Color{240,230,140},1);
            if(flag==51)
            {
                // 点击home按钮
                draw.homeButton(600,65,Color{240,230,140},1);
                std::ofstream outfile;
                outfile.open("option.txt");
                outfile<<level<<" "<<style;
                outfile.close();
                pageFlag=0;
                return;
                break;
            }
        }
        else
        {
            draw.optionPage(level,style);
        }
    }
}

int Setting::mouseJudge(int flag)
{
    int mouseX;
    int mouseY;
    mouse_msg msg;
    while(mousemsg())
    {
        msg = getmouse();
        mouseX = msg.x;
        mouseY = msg.y;
        if(mouseX>=280&&mouseX<=355&&mouseY>=210&&mouseY<=265&&msg.is_left()&&msg.msg==mouse_msg_down)
        {
            return 11;
            break;
        }
        else if(mouseX>=280&&mouseX<=355&&mouseY>=210&&mouseY<=265)
        {
            return 1;
            break;
        }
        else if(mouseX>=505&&mouseX<=580&&mouseY>=210&&mouseY<=265&&msg.is_left()&&msg.msg==mouse_msg_down)
        {
            return 21;
            break;
        }
        else if(mouseX>=505&&mouseX<=580&&mouseY>=210&&mouseY<=265)
        {
            return 2;
            break;
        }
        else if(mouseX>=280&&mouseX<=355&&mouseY>=310&&mouseY<=365&&msg.is_left()&&msg.msg==mouse_msg_down)
        {
            return 31;
            break;
        }
        else if(mouseX>=280&&mouseX<=355&&mouseY>=310&&mouseY<=365)
        {
            return 3;
            break;
        }
        else if(mouseX>=505&&mouseX<=580&&mouseY>=310&&mouseY<=365&&msg.is_left()&&msg.msg==mouse_msg_down)
        {
            return 41;
            break;
        }
        else if(mouseX>=505&&mouseX<=580&&mouseY>=310&&mouseY<=365)
        {
            return 4;
            break;
        }
        else if(((pow((mouseX-600),2)+pow((mouseY-65),2))<=1600)&&msg.is_left())
        {
            return 51;
            break;
        }
        else if((pow((mouseX-600),2)+pow((mouseY-65),2))<=1600)
        {
            return 5;
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