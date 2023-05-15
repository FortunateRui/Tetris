// Game.cpp
#include "Game.h"

Game::Game()
:level(3),style(4),currentBlock(NULL),nextBlock(NULL),isOver(false)
{
    for(int i=0;i<5;i++)
    {
        name[i][0]='N';
        name[i][1]='U';
        name[i][2]='L';
        name[i][3]='L';
        highestScore[i]=0;
        year[i]=0;
        month[i]=0;
        day[i]=0;
    }
}

void Game::init()
{
    currentBlock=NULL;
    nextBlock=NULL;
    isOver=false;
    for(auto &m:Block::map)for(auto &n:m)n=0;
    for(auto &c: name)for(auto &cc: c)cc='\0';
    for(auto &c: name)c[0]='N',c[1]='U',c[2]='L',c[3]='L';
    for(auto &c: highestScore)c=0;
    for(auto &c: year)c=0;
    for(auto &c: month)c=0;
    for(auto &c: day)c=0;

    std::ifstream infile;
    infile.open("option.txt");
    infile >> level>>style;
    infile.close();
    switch(level)
    {
    case 1:
        infile.open("record1.txt");
        for(int i=0;i<5;i++)
        {
            infile>>name[i]>>highestScore[i]>>year[i]>>month[i]>>day[i];
        }
        infile.close();
        break;
    case 2:
        infile.open("record2.txt");
        for(int i=0;i<5;i++)
        {
            infile>>name[i]>>highestScore[i]>>year[i]>>month[i]>>day[i];
        }
        infile.close();
        break;
    case 3:
        infile.open("record3.txt");
        for(int i=0;i<5;i++)
        {
            infile>>name[i]>>highestScore[i]>>year[i]>>month[i]>>day[i];
        }
        infile.close();
        break;
    case 4:
        infile.open("record4.txt");
        for(int i=0;i<5;i++)
        {
            infile>>name[i]>>highestScore[i]>>year[i]>>month[i]>>day[i];
        }
        infile.close();
        break;
    case 5:
        infile.open("record5.txt");
        for(int i=0;i<5;i++)
        {
            infile>>name[i]>>highestScore[i]>>year[i]>>month[i]>>day[i];
        }
        infile.close();
        break;
    }
    draw.gamePage(level,highestScore[0]);
    draw.homeButton(590,70,Color{0,0,0},0);
    draw.gameScore(0);
    flushkey();// 清空键盘缓冲区
    flushmouse();// 清空鼠标缓冲区
}

void Game::play(int &pageFlag)
{
    init();
    int score=0;
    currentBlock=new Block(style);
    Sleep(500);
    int mouseFlag=0;   // 用于存储鼠标事件
    while(!isOver)
    {
        //更新并绘画nextBlock
        nextBlock=new Block(style);
        setcolor(EGERGB(0,0,0));
        setfillcolor(EGERGB(0,0,0));
        setlinewidth(1);
        bar(136,16,314,104);
        for(int i=0;i<4;i++)
        {
            draw.square(5+Block::shape[nextBlock->kind][i][0],-5+Block::shape[nextBlock->kind][i][1],nextBlock->color_block,nextBlock->style);
        }
        // 当前方块存活期间的循环,也是主要的循环
        int times=0;    // 用于决定方块自然下落的速度
        while(1)
        {
            if(times==0)
            {   
                // 方块无法下落时跳出循环,放在这里而不是循环判断里,是为了方块最后还能左右移动和旋转
                if(!currentBlock->checkMove(0))break; 
                (*currentBlock)++;// 当前方块自然下落一格
            }
            // 键盘事件处理
            if(kbhit())
            {
                char input=getch();
                switch(input)
                {
                case 'w':
                case 'W':
                    if(currentBlock->checkMove(3))currentBlock->moveAndDraw(3);
                    break;
                case 'a':
                case 'A':
                    if(currentBlock->checkMove(1))currentBlock->moveAndDraw(1);
                    break;
                case 's':
                case 'S':
                    if(currentBlock->checkMove(0))currentBlock->moveAndDraw(0);
                    break;
                case 'd':
                case 'D':
                    if(currentBlock->checkMove(2))currentBlock->moveAndDraw(2);
                    break;
                case 0x20:
                    // 暂停
                    while(1)
                    {
                        // 键盘事件处理
                        if(kbhit())
                        {
                            char input_temp=getch();
                            if(input_temp==0x20)break;
                            if(input_temp=='r'||input_temp=='R')
                            {
                                pageFlag=1;
                                return;
                                break;
                            }
                        }
                        // 鼠标事件处理
                        int lastMouseFlag=mouseFlag;
                        mouseFlag=mouseJudge(mouseFlag);
                        if(mouseFlag!=lastMouseFlag)
                        {
                            if(mouseFlag==0)
                            {
                                draw.homeButton(590,70,Color{0,0,0},0);
                            }
                            if(mouseFlag==1)
                            {
                                draw.homeButton(590,70,Color{0,0,0},1);
                            }
                            if(mouseFlag==2)
                            {
                                draw.homeButton(590,70,Color{0,0,0},1);
                                pageFlag=0;
                                return;
                            }
                        }
                        Sleep(10);
                    }
                    break;
                case 'r':
                case 'R':
                    pageFlag=1;
                    return;
                    break;
                }
            }

            // 鼠标事件处理
            int lastMouseFlag=mouseFlag;
            mouseFlag=mouseJudge(mouseFlag);
            if(mouseFlag!=lastMouseFlag)
            {
                if(mouseFlag==0)
                {
                    draw.homeButton(590,70,Color{0,0,0},0);
                }
                if(mouseFlag==1)
                {
                    draw.homeButton(590,70,Color{0,0,0},1);
                }
                if(mouseFlag==2)
                {
                    draw.homeButton(590,70,Color{0,0,0},1);
                    pageFlag=0;
                    return;
                }
            }

            
            // 根据等级决定方块自然下落的速度
            times++;
            times%=20*(6-level);
            Sleep(10);
        }
        // 方块无法下落时的处理,判断游戏是否结束
        for(int i=0;i<4;i++)
        {
            if(currentBlock->y + Block::shape[currentBlock->kind][i][1]<0)
            {
                isOver=true;
                break;
            }
        }
        if(isOver)continue;
        // 游戏未结束时的处理
        score+=getScore(currentBlock);
        draw.gameScore(score);
        delete currentBlock;
        currentBlock=nextBlock;
    }
    // 游戏结束时的处理
    delete currentBlock;
    currentBlock=NULL;
    nextBlock=NULL;
    over(score,pageFlag);
}

int Game::getScore(Block* block)
{   
    for(int i=0;i<4;i++)
    {
        Block::map[(block->x)+Block::shape[block->kind][i][0]][(block->y)+Block::shape[block->kind][i][1]]=1;
    }
    int full_line=0;
    for(int i=19;i>=0;i--)
    {
        int flag=1;
        for(int j=0;j<10;j++)
        {
            if(Block::map[j][i]==0)
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            full_line++;
            for(int j=i;j>0;j--)
            {
                for(int k=0;k<10;k++)
                {
                    Block::map[k][j]=Block::map[k][j-1];
                }
            }
            for(int j=0;j<10;j++)
            {
                Block::map[j][0]=0;
            }
            i++;
        }
    }
    if(full_line==0)return 0;
    srand((unsigned)time(NULL));
    Color color_temp=color[rand()%7];
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(Block::map[i][j]==0)
            {
                draw.clearSquare(i,j);
            }
            else
            {
                draw.square(i,j,color_temp,block->style);
            }
        }
    }
    switch(full_line)
    {
    case 1:
        return 1;
    case 2:
        return 3;
    case 3:
        return 6;
    case 4:
        return 10;
    }
    return 0;
}

void Game::over(int score,int &pageFlag)
{
    // 保存分数
    int i=0;
    for(i=0;i<5;i++)
    {
        if(score>=highestScore[i])break;
    }
    for(int j=4;j>i;j--)
    {
        for(int k=0;k<20;k++)name[j][k]=name[j-1][k];
        highestScore[j]=highestScore[j-1];
        year[j]=year[j-1];
        month[j]=month[j-1];
        day[j]=day[j-1];
    }
    for(auto &c:name[i])c='\0';
    name[i][0]='P';name[i][1]='l';name[i][2]='a';name[i][3]='y';name[i][4]='e';name[i][5]='r';
    highestScore[i]=score;
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = std::localtime(&now_time_t);
    year[i]=now_tm->tm_year+1900;
    month[i]=now_tm->tm_mon+1;
    day[i]=now_tm->tm_mday;
    std::ofstream outfile;
    switch(level)
    {
    case 1:
        outfile.open("record1.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 2:
        outfile.open("record2.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 3:
        outfile.open("record3.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 4:
        outfile.open("record4.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 5:
        outfile.open("record5.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    }
    if (i!=5)
    {
        // 画出请输入名字界面
        draw.gameOver(1);
    R_flag:
        char inputStr[39];
        for(auto &c:inputStr)c='\0';
        sys_edit editBox;
        editBox.create(false);						//创建，false表示单行，true表示多行
        editBox.move(25,505);						//设置位置
        editBox.size(280,34);	                    //设置尺寸
        editBox.setmaxlen(19);						//设置允许输入的字符数
        editBox.visible(true);						//设置可见性
        editBox.setfocus();							//设置获取焦点
        editBox.setbgcolor(EGERGB(0,0,0));			//设置背景色
        editBox.setfont(30, 0, "Arial");	        //设置字体
        editBox.setcolor(EGERGB(255,255,255));	    //设置字体颜色
        while(1)
        {
            char ch=getch();
            if(ch=='\r'||ch==0x20)
            break;
        }
        flushkey();
        editBox.gettext(20,inputStr);				    //获取文本
        try
        {
            if(inputStr[19]!='\0')throw 1;
            if((inputStr[0]=='N'||inputStr[0]=='n')&&
               (inputStr[1]=='U'||inputStr[1]=='u')&&
               (inputStr[2]=='L'||inputStr[2]=='l')&&
               (inputStr[3]=='L'||inputStr[3]=='l')&&
               (inputStr[4]=='\0'||inputStr[4]==' '))
            throw 2;
        }catch(int error)
        {
            if(error==1)
            {
                const char str1[]="Your name is too long!";
                const char str2[]="Error";
                MessageBox(NULL,str1,str2,MB_OK|MB_ICONERROR);
                goto R_flag;
            }
            if(error==2)
            {
                const char str1[]="Your name can't be NULL!";
                const char str2[]="Error";
                MessageBox(NULL,str1,str2,MB_OK|MB_ICONERROR);
                goto R_flag;
            }
        }
        editBox.destroy();							//销毁
        for(int j=0;j<20;j++)name[i][j]=inputStr[j];
        draw.gameOver(2);
    }
    else
    {
        draw.gameOver(0);
    }
    // std::ofstream outfile;
    switch(level)
    {
    case 1:
        outfile.open("record1.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 2:
        outfile.open("record2.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 3:
        outfile.open("record3.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 4:
        outfile.open("record4.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    case 5:
        outfile.open("record5.txt");
        for(int i=0;i<5;i++)
        {
            outfile<<name[i]<<' '<<highestScore[i]<<' '<<year[i]<<' '<<month[i]<<' '<<day[i]<<std::endl;
        }
        outfile.close();
        break;
    }
    int mouseFlag=0;
    while(1)
    {
        Sleep(10);
        // 键盘事件处理
        if(kbhit())
        {
            char input_temp=getch();
            if(input_temp=='r'||input_temp=='R')
            {
                pageFlag=1;
                return;
                break;
            }
        }
        // 鼠标事件处理
        int lastMouseFlag=mouseFlag;
        mouseFlag=mouseJudge(mouseFlag);
        if(mouseFlag!=lastMouseFlag)
        {
            if(mouseFlag==0)
            {
                draw.homeButton(590,70,Color{0,0,0},0);
            }
            if(mouseFlag==1)
            {
                draw.homeButton(590,70,Color{0,0,0},1);
            }
            if(mouseFlag==2)
            {
                draw.homeButton(590,70,Color{0,0,0},1);
                pageFlag=0;
                return;
            }
        }
    }
}

int Game::mouseJudge(int flag)
{
    int mouseX;
    int mouseY;
    mouse_msg msg;
    while(mousemsg())
    {
        msg = getmouse();
        mouseX = msg.x;
        mouseY = msg.y;
        if(((pow((mouseX-590),2)+pow((mouseY-70),2))<=1600)&&msg.is_left())
        {
            return 2;
            break;
        }
        else if((pow((mouseX-590),2)+pow((mouseY-70),2))<=1600)
        {
            return 1;
            break;
        }
        else if(flag!=0)//原本有有效事件，但此时在非按钮区域
        {
            return 0;
            break;
        }
        else ;// 无效事件
    }
    return flag;
}