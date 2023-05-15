// Draw.cpp
#include "Draw.h"

int Draw::offset=0;
int Draw::style1[927]={0};
int Draw::style2[972]={0};
int Draw::style3[207]={0};

Draw::Draw()
{
    initgraph(660,750,0x0);		// 初始化，显示一个宽660，长750,不要ege启动动画的窗口
    setcaption("Tetris");		//给窗口命名
    std::ifstream infile;
    infile.open("styleFiles/style1.txt");
    for(int i=0;i<927;i++)
    {
        infile>>style1[i];
    }
    infile.close();
    infile.open("styleFiles/style2.txt");
    for(int i=0;i<972;i++)
    {
        infile>>style2[i];
    }
    infile.close();
    infile.open("styleFiles/style3.txt");
    for(int i=0;i<207;i++)
    {
        infile>>style3[i];
    }
    infile.close();
}

void Draw::cloud(int x,int y)
{
    setfillcolor(WHITE);
    setcolor(WHITE);
    setlinewidth(1);
    pieslice(x,y,0,360,30);
    pieslice(x+50,y,0,360,40);
    pieslice(x+100,y,0,360,50);
    pieslice(x+150,y,0,360,40);
    pieslice(x+200,y,0,360,30);
}

void Draw::fillroundrect(int left, int top, int right, int bottom, int width, int height)
{
    int x1 = left;
    int y1 = top;
    int x2 = right;
    int y2 = bottom;

    // 绘制矩形的四个角
    sector(x1+width,y1+height,90,180,width,height);     // 左上角
    sector(x2-width,y1+height,0,90,width,height);       // 右上角
    sector(x1+width,y2-height,180,270,width,height);    // 左下角
    sector(x2-width,y2-height,270,360,width,height);    // 右下角

    // 绘制矩形的内部区域
    int points[]=
    {
        x1+width,y1,//1
        x1+width,y1+height,//2
        x1,y1+height,//3
        x1,y2-height,//4
        x1+width,y2-height,//5
        x1+width,y2,//6
        x2-width,y2,//7
        x2-width,y2-height,//8
        x2,y2-height,//9
        x2,y1+height,//10
        x2-width,y1+height,//11
        x2-width,y1,//12
        x1+width,y1//13
    };
    fillpoly(13, points);
}

void Draw::roundrectBox(int left,int top,int right,int bottom,int width,int height,Color lineColor,Color fillColor)
{
    int linewidth=5;
    // 画外圈圆角矩形
    setlinewidth(1);
    setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
    setfillcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
    fillroundrect(left,top,right,bottom,width,height);
    // 画内圈圆角矩形
    setcolor(EGERGB(fillColor.red,fillColor.green,fillColor.blue));
    setfillcolor(EGERGB(fillColor.red,fillColor.green,fillColor.blue));
    fillroundrect(left+linewidth,top+linewidth,right-linewidth,bottom-linewidth,width-linewidth,height-linewidth);
}

void Draw::roundrectButton(int left,int top,int right,int bottom,int width,int height,Color lineColor,Color fillColor,int flag)
{
    int linewidth=5;
    int buttonWidth=right-left;
    int buttonHeight=bottom-top;
    int* leftArrow=new int[8];
    int* rightArrow=new int[8];
    leftArrow[0]=(int)(left+0.2*buttonWidth/4);
    leftArrow[1]=(int)(top+0.5*buttonHeight);
    leftArrow[2]=(int)(left+0.8*buttonWidth/4);
    leftArrow[3]=(int)(top+0.2*buttonHeight);
    leftArrow[4]=(int)(left+0.8*buttonWidth/4);
    leftArrow[5]=(int)(top+0.8*buttonHeight);
    leftArrow[6]=(int)(left+0.2*buttonWidth/4);
    leftArrow[7]=(int)(top+0.5*buttonHeight);
    rightArrow[0]=(int)(right-0.2*buttonWidth/4);
    rightArrow[1]=(int)(top+0.5*buttonHeight);
    rightArrow[2]=(int)(right-0.8*buttonWidth/4);
    rightArrow[3]=(int)(top+0.2*buttonHeight);
    rightArrow[4]=(int)(right-0.8*buttonWidth/4);
    rightArrow[5]=(int)(top+0.8*buttonHeight);
    rightArrow[6]=(int)(right-0.2*buttonWidth/4);
    rightArrow[7]=(int)(top+0.5*buttonHeight);
    // 画roundrectBox
    roundrectBox(left,top,right,bottom,width,height,lineColor,fillColor);
    // 画中间的线
    setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
    setlinewidth(linewidth-1);
    line((int)(left+buttonWidth/4),top+linewidth,(int)(left+buttonWidth/4),bottom-linewidth+1);
    line((int)(right-buttonWidth/4),top+linewidth,(int)(right-buttonWidth/4),bottom-linewidth+1);
    // 画左右三角形
    setlinewidth(1);
    if(flag==0)
    {
        setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
        setfillcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
        fillpoly(4,leftArrow);
        fillpoly(4,rightArrow);
    }
    else if(flag==1)
    {
        setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
        setfillcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
        fillpoly(4,rightArrow);
        setcolor(EGERGB(lineColor.red+50,lineColor.green+50,lineColor.blue+50));
        setfillcolor(EGERGB(lineColor.red+50,lineColor.green+50,lineColor.blue+50));
        fillpoly(4,leftArrow);
    }
    else if(flag==2)
    {
        setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
        setfillcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
        fillpoly(4,leftArrow);
        setcolor(EGERGB(lineColor.red+50,lineColor.green+50,lineColor.blue+50));
        setfillcolor(EGERGB(lineColor.red+50,lineColor.green+50,lineColor.blue+50));
        fillpoly(4,rightArrow);
    }
    delete[] leftArrow;
    delete[] rightArrow;
}
void Draw::homePage(int flag)
{
    // 绘制背景色
    setbkcolor(EGERGB(0, 191, 255));
    cleardevice();
    // 绘制太阳
    setfillcolor(YELLOW);
    setcolor(YELLOW);
    pieslice(60,60,0,360,50);
    for (int i = 0; i < 12; i++)
    {
        double angle = i*PI/6 + offset*PI/(180*3);  // 当前光线的起始角度
        int start_x = 60;
        int start_y = 60;
        int end_x = 60 + 80*cos(angle);
        int end_y = 60 - 80*sin(angle);  // 光线的终点坐标
        line(start_x, start_y, end_x, end_y);  // 绘制光线
    }
    // 绘制云朵
    cloud((offset-230),150);
    cloud((((300+offset)%920)-230),50);
    cloud((((600+offset)%920)-230),180);
    cloud((((900+offset)%920)-230),130);
    
    // 绘制草地
    setfillcolor(GREEN);
    setcolor(GREEN);
    bar(0, 550, 660, 750);

    // 绘制文字
    int TetrisX=80,TetrisY=250;
    setfont(180,0,"Arial Rounded MT Bold");
    setfontbkcolor(EGERGB(0, 191, 255));
    setcolor(EGERGB(255,0,0));
    outtextxy(TetrisX,TetrisY, "T");
    setcolor(EGERGB(0,0,255));
    outtextxy(TetrisX+100,TetrisY, "e");
    setcolor(EGERGB(255,165,0));
    outtextxy(TetrisX+200,TetrisY, "t");
    setcolor(EGERGB(255,255,0));
    outtextxy(TetrisX+270,TetrisY, "r");
    setcolor(EGERGB(0,255,0));
    outtextxy(TetrisX+345,TetrisY, "i");
    setcolor(EGERGB(128,0,128));
    outtextxy(TetrisX+385,TetrisY, "s");
    // 绘制开始按钮
    if(flag==2)
    {
        // hover时的按钮
        setlinewidth(1);
        setfont(96,0,"Arial Rounded MT Bold");
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        setfontbkcolor(EGERGB(0,255,255));
        fillroundrect(210,502,450,598,12,12);
        setcolor(EGERGB(255,0,0));
        outtextxy(230,502, "Start");
    }
    else
    {
        setlinewidth(1);
        setfont(80,0,"Arial Rounded MT Bold");
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        setfontbkcolor(EGERGB(0,255,255));
        fillroundrect(230,510,430,590,10,10);
        setcolor(EGERGB(255,0,0));
        outtextxy(245,510, "Start");
    }
    // 绘制设置按钮
    if(flag==1)
    {
        // hover时的按钮
        setlinewidth(1);
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        fillroundrect(52,502,148,598,12,12);
        int x=100,y=550;
        int r1=22*1.2,r2=7*1.2;
        setcolor(EGERGB(192,192,192));
        setfillcolor(EGERGB(192,192,192));
        pieslice(x,y,0,360,r1);
        setcolor(EGERGB(192,192,192));
        setfillcolor(EGERGB(192,192,192));
        setlinewidth(10*1.2);
        for (int i = 0; i < 8; i++)
        {
            double angle = i*45*PI/180;  // 当前齿的起始角度
            int end_x = x + 27*1.2*cos(angle);
            int end_y = y - 27*1.2*sin(angle);  // 齿的终点坐标
            line(x,y,end_x,end_y);  // 绘制齿
        }
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        pieslice(x,y,0,360,r2);
    }
    else
    {   
        setlinewidth(1);
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        fillroundrect(60,510,140,590,10,10);
        int x=100,y=550;
        int r1=22,r2=7;
        setcolor(EGERGB(192,192,192));
        setfillcolor(EGERGB(192,192,192));
        pieslice(x,y,0,360,r1);
        setcolor(EGERGB(192,192,192));
        setfillcolor(EGERGB(192,192,192));
        setlinewidth(10);
        for (int i = 0; i < 8; i++)
        {
            double angle = i*45*PI/180;  // 当前齿的起始角度
            int end_x = x + 27*cos(angle);
            int end_y = y - 27*sin(angle);  // 齿的终点坐标
            line(x,y,end_x,end_y);  // 绘制齿
        }
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        pieslice(x,y,0,360,r2);
    }
    // 绘制排行按钮
    if(flag==3)
    {
        setlinewidth(1);
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        fillroundrect(512,502,608,598,12,12);
        setlinewidth(2.4);
        setcolor(EGERGB(0,0,0));
        line(524,586,596,586);
        int points1[]=
        {
            524+26,584,//1
            524+26,514,//2
            524+44,514,//3
            524+44,584,//4
            524+26,584,//5
        };
        int points2[]=
        {
            524+8,584,//1
            524+8,536,//2
            524+26,536,//3
            524+26,584,//4
            524+8,584,//5
        };
        int points3[]=
        {
            524+44,584,//1
            524+44,547,//2
            524+62,547,//3
            524+62,584,//4
            524+44,584,//5
        };
        setcolor(EGERGB(255,255,0));
        setfillcolor(EGERGB(255,255,0));
        fillpoly(5, points2);
        setcolor(EGERGB(255,192,203));
        setfillcolor(EGERGB(255,192,203));
        fillpoly(5, points3);
        setcolor(EGERGB(0,191,255));
        setfillcolor(EGERGB(0,191,255));
        fillpoly(5, points1);
    }
    else
    {
        setlinewidth(1);
        setcolor(EGERGB(0,255,255));
        setfillcolor(EGERGB(0,255,255));
        fillroundrect(520,510,600,590,10,10);
        setlinewidth(2);
        setcolor(EGERGB(0,0,0));
        line(530,580,590,580);
        int points1[]=
        {
            537+15,578,//1
            537+15,520,//2
            537+30,520,//3
            537+30,578,//4
            537+15,578,//5
        };
        int points2[]=
        {
            537,578,//1
            537,540,//2
            537+15,540,//3
            537+15,578,//4
            537,578,//5
        };
        int points3[]=
        {
            537+30,578,//1
            537+30,550,//2
            537+45,550,//3
            537+45,578,//4
            537+30,578,//5
        };
        setcolor(EGERGB(255,255,0));
        setfillcolor(EGERGB(255,255,0));
        fillpoly(5, points2);
        setcolor(EGERGB(255,192,203));
        setfillcolor(EGERGB(255,192,203));
        fillpoly(5, points3);
        setcolor(EGERGB(0,191,255));
        setfillcolor(EGERGB(0,191,255));
        fillpoly(5, points1);
    }

    offset=(offset+1)%999999; //递增，同时取模防止数值过大造成溢出
}

void Draw::square(int x,int y,Color color,int style)
{
    setlinewidth(1);
    setcolor(EGERGB(color.red,color.green,color.blue));
    setfillcolor(EGERGB(color.red,color.green,color.blue));
    fillroundrect(x*30+17,y*30+137,x*30+46,y*30+166,4,4);
    switch(style)
    {
    case 0:
        break;
    case 1:
        int p1[927];
        for(int i=0;i<927;i++)
        {
            p1[i]=style1[i];
        }
        for(int i=0;i<309;i++)
        {
            p1[i*3]+=x*30+17;
            p1[i*3+1]+=y*30+137;
        }
        putpixels(309,p1);
        break;
    case 2:
        int p2[972];
        for(int i=0;i<972;i++)
        {
            p2[i]=style2[i];
        }
        for(int i=0;i<324;i++)
        {
            p2[i*3]+=x*30+17;
            p2[i*3+1]+=y*30+137;
        }
        putpixels(324,p2);
        break;
    case 3:
        int p3[207];
        for(int i=0;i<207;i++)
        {
            p3[i]=style3[i];
        }
        for(int i=0;i<69;i++)
        {
            p3[i*3]+=x*30+17;
            p3[i*3+1]+=y*30+137;
        }
        putpixels(69,p3);
        break;
    }
}

void Draw::clearSquare(int x,int y)
{
    setcolor(BLACK);
    setfillcolor(BLACK);
    setlinewidth(1);
    fillroundrect(x*30+17,y*30+137,x*30+46,y*30+166,4,4);
}

void Draw::gamePage(int level, int highestScore)
{
    int TIPSTOP=400;
    int frame_a[]={0,0, 0,120, 330,120, 330,0, 0,0};
    int frame_a1[]={15,15, 15,105, 135,105, 135,15, 15,15};
    int frame_a2[]={135,15, 135,105, 315,105,315,15,135,15};
    int frame_b[]={0,120, 0,750, 330,750, 330,120, 0,120};
    int frame_b1[]={15,135, 15,738, 318,738, 318,135, 15,135};
    int frame_c[]={330,0, 330,750, 660,750, 660,0, 330,0};
    int frame_c1[]={343,15, 343,737, 645,737, 645,15, 343,15};
    char highestScore_str[6]="0";
    char level_str[2]="0";
    char r[]="R: Restart/Start";
    char space[]="space: stop/continue";
    char ad1[]="A/D:";
    char ad2[]="move left/right one space";
    char qe1[]="W:";
    char qe2[]="clockwise rotation block";
    char s[]="S: accelerate block drop";
    clearviewport();
    setcolor(EGERGB(255,255,255));
    setfillcolor(EGERGB(0,191,255));
    setfontbkcolor(EGERGB(0,0,0));
    setlinewidth(2);
    fillpoly(5,frame_a);
    fillpoly(5,frame_b);
    fillpoly(5,frame_c);
    setfillcolor(EGERGB(0,0,0));
    fillpoly(5,frame_a1);
    fillpoly(5,frame_a2);
    fillpoly(5,frame_b1);
    fillpoly(5,frame_c1);
    setfont(25,0,"Arial Rounded MT Bold");
    outtextxy(20,20,"Score:");
    outtextxy(355,TIPSTOP,r);
    outtextxy(355,TIPSTOP+60,space);
    outtextxy(355,TIPSTOP+120,ad1);
    outtextxy(355,TIPSTOP+150,ad2);
    outtextxy(355,TIPSTOP+210,qe1);
    outtextxy(355,TIPSTOP+240,qe2);
    outtextxy(355,TIPSTOP+300,s);
    setfont(30,0,"Arial Rounded MT Bold");
    outtextxy(355,130,"Level:");
    sprintf(level_str,"%d",level);
    outtextxy(435,130,level_str);
    setfont(50,0,"Arial Rounded MT Bold");
    outtextxy(355,170,"Best Score:");
    setfont(100,0,"Arial Rounded MT Bold");
    sprintf(highestScore_str,"%d",highestScore);
    outtextxy(355,230,highestScore_str);
}

void Draw::gameScore(int score)
{
    setfont(50,0,"Arial Rounded MT Bold");
    setfontbkcolor(EGERGB(0,0,0));
    setcolor(EGERGB(255,255,255));
    outtextxy(20,50,"     ");
    char score_str[6]="0";
    sprintf(score_str,"%d",score);
    outtextxy(20,50,score_str);
}

void Draw::homeButton(int x,int y,Color bkColor,int flag)
{
    setcolor(EGERGB(bkColor.red,bkColor.green,bkColor.blue));
    setfillcolor(EGERGB(bkColor.red,bkColor.green,bkColor.blue));
    setlinewidth(1);
    fillellipse(x,y,44,44);
    if(flag==0)
    {
        setcolor(EGERGB(168,0,0));
        setlinewidth(5);
        circle(x,y,40);
        line(x,y-23,x-25,y-5);
        line(x,y-23,x+25,y-5);
        line(x-16,y-11,x-16,y+17);
        line(x+16,y-11,x+16,y+17);
        line(x-16,y+17,x+16,y+17);
    }
    else
    {
        setcolor(EGERGB(255,0,0));
        setfillcolor(EGERGB(255,0,0));
        setlinewidth(1);
        fillellipse(x,y,44,44);
        setlinewidth(5);
        setcolor(EGERGB(255,255,255));
        line(x,y-23,x-25,y-5);
        line(x,y-23,x+25,y-5);
        line(x-16,y-11,x-16,y+17);
        line(x+16,y-11,x+16,y+17);
        line(x-16,y+17,x+16,y+17);
    }
}

void Draw::gameOver(int flag)
{
    if(flag==0)
    {
        char over_text1[]="Game Over";
        char over_text2[]="Press \'r\' to continue";
        setfontbkcolor(EGERGB(0,0,0));
        setcolor(EGERGB(255,255,255));
        setfont(60,0,"Arial Rounded MT Bold");
        outtextxy(25,315,over_text1);
        setfont(30,0,"Arial Rounded MT Bold");
        outtextxy(35,435,over_text2);
    }
    else if(flag==1)
    {
        char over_text1[]="Game Over";
        char over_text2[]="You are in the top5!";
        setfontbkcolor(EGERGB(0,0,0));
        setcolor(EGERGB(255,255,255));
        setfont(60,0,"Arial Rounded MT Bold");
        outtextxy(25,315,over_text1);
        setfont(30,0,"Arial Rounded MT Bold");
        outtextxy(50,435,over_text2);
        setfont(28,0,"Arial Rounded MT Bold");
        outtextxy(25,470,"Please enter your name:");
    }
    else
    {
        char over_text1[]="Game Over";
        char over_text2[]="You are in the top5!";
        setfontbkcolor(EGERGB(0,0,0));
        setcolor(EGERGB(255,255,255));
        setfont(60,0,"Arial Rounded MT Bold");
        outtextxy(25,315,over_text1);
        setfont(30,0,"Arial Rounded MT Bold");
        outtextxy(50,435,over_text2);
        setfont(28,0,"Arial Rounded MT Bold");
        outtextxy(25,470,"Press \'r\' to continue");
    }
}

void Draw::rankPage(int level)
{
    clearviewport();
    Color lineColor={139, 69, 19};
    Color fillColor={240, 230, 140};
    // 画出背景
    setbkcolor(EGERGB(fillColor.red,fillColor.green,fillColor.blue));
    setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
    setfontbkcolor(EGERGB(fillColor.red,fillColor.green,fillColor.blue));
    // 画出标题
    setfont(150,0,"Arial Rounded MT Bold");
    outtextxy(165,0,"Rank");
    // 画出level选择框
    setfont(60,0,"Arial Rounded MT Bold");
    outtextxy(20,145,"level:");
    roundrectButton(230,150,430,200,20,20,lineColor,fillColor,0);
    // 画出level
    rankLevel(level);
    // 画出home按钮
    homeButton(600,85,fillColor,0);
    // 画出排行榜
    char num[3];
    for(int i=0;i<5;i++)
    {
        sprintf(num,"%d",i+1);
        num[1]='.';
        num[2]='\0';
        setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
        setfontbkcolor(EGERGB(fillColor.red,fillColor.green,fillColor.blue));
        setfont(60,0,"Arial Rounded MT Bold");
        outtextxy(10,250+i*100,num);
        roundrectBox(70,250+i*100,640,310+i*100,20,20,lineColor,fillColor);
    }
}

void Draw::rankLine(int i,char name[],int score,int year,int month,int day)
{
    roundrectBox(70,250+i*100,640,310+i*100,20,20,Color{139,69,19},Color{240,230,140});
    setfont(35,0,"Arial Rounded MT Bold");
    setfontbkcolor(EGERGB(240,230,140));
    setcolor(EGERGB(139,69,19));
    outtextxy(90,260+i*100,name);
    char score_str[6];
    sprintf(score_str,"%d",score);
    outtextxy(300,260+i*100,score_str);
    char date_str[11];
    sprintf(date_str,"%d/%d/%d",year,month,day);
    outtextxy(450,260+i*100,date_str);
}

void Draw::rankLevel(int level)
{
    setfont(40,0,"Arial Rounded MT Bold");
    setcolor(EGERGB(139,69,19));
    setfontbkcolor(EGERGB(240,230,140));
    char level_str[2];
    sprintf(level_str,"%d",level);
    outtextxy(320,155,level_str);
}

void Draw::optionPage(int level,int style)
{
    Color lineColor={139, 69, 19};
    Color fillColor={240, 230, 140};
    // 画出背景
    setbkcolor(EGERGB(fillColor.red,fillColor.green,fillColor.blue));
    setcolor(EGERGB(lineColor.red,lineColor.green,lineColor.blue));
    setfontbkcolor(EGERGB(fillColor.red,fillColor.green,fillColor.blue));
    clearviewport();
    // 画出标题
    setfont(130,0,"Arial Rounded MT Bold");
    outtextxy(140,0,"Option");
    // 画出option文字
    setfont(70,0,"Arial Rounded MT Bold");
    outtextxy(100,200,"level:");
    outtextxy(100,300,"style:");
    // 画出home按钮
    homeButton(600,65,fillColor,0);
    // 画出按钮
    roundrectButton(280,210,580,265,20,20,lineColor,fillColor,0);
    roundrectButton(280,310,580,365,20,20,lineColor,fillColor,0);
    // 画出level和style
    optionLevel(level);
    optionStyle(style);
    optionSquare(style);
}

void Draw::optionLevel(int level)
{
    setfont(45,0,"Arial Rounded MT Bold");
    setfontbkcolor(EGERGB(240, 230, 140));
    setcolor(EGERGB(139, 69, 19));
    char level_str[2]={'\0'};
    sprintf(level_str,"%d",level);
    outtextxy(420,215,level_str);
}

void Draw::optionStyle(int style)
{
    setfont(45,15,"Arial Rounded MT Bold");
    setfontbkcolor(EGERGB(240, 230, 140));
    setcolor(EGERGB(139, 69, 19));
    char style_str[7]={'\0'};
    if(style!=4&&style!=0)sprintf(style_str,"style%d",style);
    else if(style==4)sprintf(style_str,"random");
    else if(style==0)sprintf(style_str,"none");
    outtextxy(375,315,style_str);
}

void Draw::optionSquare(int style)
{
    if(style<4)
    {
        srand((unsigned)time(NULL));
        Color color_temp=color[rand()%7];
        square(20,6,color_temp,style);
    }
    else
    {
        square(20,6,Color{240, 230, 140},0);
    }
}