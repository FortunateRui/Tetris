// Rank.cpp
#include "Rank.h"

Rank::Rank()
:level(3)
{}

void Rank::init()
{
    for(auto&c:name)for(auto&cc:c)for(auto&ccc:cc)ccc='\0';
    for(auto&c:highestScore)for(auto&cc:c)cc=0;
    for(auto&c:year)for(auto&cc:c)cc=0;
    for(auto&c:month)for(auto&cc:c)cc=0;
    for(auto&c:day)for(auto&cc:c)cc=0;
    std::ifstream infile;
    infile.open("option.txt");
    infile>>level;
    infile.close();
    infile.open("record1.txt");
    for(int i=0;i<5;i++)infile>>name[0][i]>>highestScore[0][i]>>year[0][i]>>month[0][i]>>day[0][i];
    infile.close();
    infile.open("record2.txt");
    for(int i=0;i<5;i++)infile>>name[1][i]>>highestScore[1][i]>>year[1][i]>>month[1][i]>>day[1][i];
    infile.close();
    infile.open("record3.txt");
    for(int i=0;i<5;i++)infile>>name[2][i]>>highestScore[2][i]>>year[2][i]>>month[2][i]>>day[2][i];
    infile.close();
    infile.open("record4.txt");
    for(int i=0;i<5;i++)infile>>name[3][i]>>highestScore[3][i]>>year[3][i]>>month[3][i]>>day[3][i];
    infile.close();
    infile.open("record5.txt");
    for(int i=0;i<5;i++)infile>>name[4][i]>>highestScore[4][i]>>year[4][i]>>month[4][i]>>day[4][i];
    infile.close();
    draw.rankPage(level);
}

void Rank::run(int& pageFlag)
{
    init();
    int flag=0;                 //记录鼠标的有效事件
    while(1)
    {
        Sleep(10);
        flag=mouseJudge(flag);
        if(flag==1||flag==11)
        {
            draw.roundrectButton(230,150,430,200,20,20,Color{139, 69, 19},Color{240, 230, 140},1);
            draw.rankLevel(level);
            if(flag==11)
            {
                // 点击左箭头
                draw.roundrectButton(230,150,430,200,20,20,Color{139, 69, 19},Color{240, 230, 140},1);
                level=(level+3)%5+1;
                draw.rankPage(level);
                for(int i=0;i<5;i++)
                {
                    draw.rankLine(i,name[level-1][i],highestScore[level-1][i],year[level-1][i],month[level-1][i],day[level-1][i]);
                }
                Sleep(500);
            }
        }
        else if(flag==2||flag==21)
        {
            draw.roundrectButton(230,150,430,200,20,20,Color{139, 69, 19},Color{240, 230, 140},2);
            draw.rankLevel(level);
            if(flag==21)
            {
                // 点击右箭头
                draw.roundrectButton(230,150,430,200,20,20,Color{139, 69, 19},Color{240, 230, 140},2);
                level=(level+5)%5+1;
                draw.rankPage(level);
                for(int i=0;i<5;i++)
                {
                    draw.rankLine(i,name[level-1][i],highestScore[level-1][i],year[level-1][i],month[level-1][i],day[level-1][i]);
                }
                Sleep(500);
            }
        }
        else if(flag==3||flag==31)
        {
            draw.homeButton(600,85,Color{240,230,140},1);
            if(flag==31)
            {
                // 点击home按钮
                draw.homeButton(600,85,Color{240,230,140},1);
                pageFlag=0;
                return;
                break;
            }
        }
        else
        {
            draw.rankPage(level);
            for(int i=0;i<5;i++)
            {
                draw.rankLine(i,name[level-1][i],highestScore[level-1][i],year[level-1][i],month[level-1][i],day[level-1][i]);
            }
        }
    }

}

int Rank::mouseJudge(int flag)
{
    int mouseX;
    int mouseY;
    mouse_msg msg;
    while(mousemsg())
    {
        msg = getmouse();
        mouseX = msg.x;
        mouseY = msg.y;
        if(mouseX>=230&&mouseX<=280&&mouseY>=150&&mouseY<=200&&msg.is_left()&&msg.msg==mouse_msg_down)
        {
            return 11;
            break;
        }
        else if(mouseX>=230&&mouseX<=280&&mouseY>=150&&mouseY<=200)
        {
            return 1;
            break;
        }
        else if(mouseX>=380&&mouseX<=430&&mouseY>=150&&mouseY<=200&&msg.is_left()&&msg.msg==mouse_msg_down)
        {
            return 21;
            break;
        }
        else if(mouseX>=380&&mouseX<=430&&mouseY>=150&&mouseY<=200)
        {
            return 2;
            break;
        }
        else if(((pow((mouseX-600),2)+pow((mouseY-85),2))<=1600)&&msg.is_left())
        {
            return 31;
            break;
        }
        else if((pow((mouseX-600),2)+pow((mouseY-85),2))<=1600)
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