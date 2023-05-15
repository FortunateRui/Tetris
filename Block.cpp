// Block.cpp

#include "Block.h"

const int Block::kindArray[7]={0,1,3,5,7,11,15};

int Block::map[10][20] = {0};
const int Block::shape[19][4][2]=
{
    {{1,1},{2,1},{1,2},{2,2}},                              // 正方型shape[0][][]
    {{0,2},{1,2},{2,2},{3,2}},{{2,0},{2,1},{2,2},{2,3}},    // ——型shape[1~2][][]
    {{2,1},{3,1},{1,2},{2,2}},{{2,0},{2,1},{3,1},{3,2}},    //反Z型shape[3~4][][]
    {{1,1},{2,1},{2,2},{3,2}},{{3,0},{2,1},{3,1},{2,2}},    //Z型shape[5~6][][]
    {{1,1},{1,2},{2,2},{3,2}},{{2,0},{3,0},{2,1},{2,2}},
    {{1,1},{2,1},{3,1},{3,2}},{{2,2},{3,0},{3,1},{3,2}},    //反L型shape[7~10][][]
    {{1,2},{2,2},{3,2},{3,1}},{{2,0},{2,1},{2,2},{3,2}},
    {{1,1},{2,1},{3,1},{1,2}},{{2,0},{3,0},{3,1},{3,2}},    //L型shape[11~14][][]
    {{2,1},{1,2},{2,2},{3,2}},{{2,0},{2,1},{3,1},{2,2}},
    {{1,1},{2,1},{3,1},{2,2}},{{3,0},{2,1},{3,1},{3,2}}     //T型shape[15~18][][]
};

Block::Block()
:x(3),y(-2),last_x(3),last_y(-2),style(1)
{
    srand((unsigned)time(NULL));
    color_block=color[rand()%7];
    kind=kindArray[rand()%7];
    last_kind=kind;
}
Block::Block(int style_)
:x(3),y(-2),last_x(3),last_y(-2),style(style_)
{
    srand((unsigned)time(NULL));
    color_block=color[(rand()+time(0))%7];
    kind=kindArray[(rand()+time(0))%7];
    last_kind=kind;
    if(style==4)
    {
        style=(rand()%3)+1;
    }
}
int Block::changeKind(int kind)
{
    if(kind==0) return 0;
    if(kind==1 || kind==2) return (kind%2+1);
    if(kind==3 || kind==4) return ((kind-2)%2+3);
    if(kind==5 || kind==6) return ((kind-4)%2+5);
    if(kind>=7 && kind <=10) return ((kind-6)%4+7);
    if(kind>=11 && kind<= 14) return ((kind-10)%4+11);
    if(kind>=15 && kind<=18) return ((kind-14)%4+15);
    return 0;
}

bool Block::checkMove(int move)
{
    switch(move)
    {
    case 0:
        //输入为0,即向下移动
        for(int i=0;i<4;i++)
        {
            if( (y+1+shape[kind][i][1])>19 || map[x+shape[kind][i][0]][y+1+shape[kind][i][1]]==1 )
                return false;
        }
        break;
    case 1:
        //输入为1,即左移动
        for(int i=0;i<4;i++)
        {
            if( (x-1+shape[kind][i][0])<0 || map[x-1+shape[kind][i][0]][y+shape[kind][i][1]]==1 )
                return false;
        }
        break;
    case 2:
        //输入为2,即右移动
        for(int i=0;i<4;i++)
        {
            if( (x+1+shape[kind][i][0])>9 || map[x+1+shape[kind][i][0]][y+shape[kind][i][1]]==1 )
                return false;
        }
        break;
    case 3:
        //输入为3,即旋转
        for(int i=0;i<4;i++)
        {
            if( (x+shape[changeKind(kind)][i][0])>9 ||
                (x+shape[changeKind(kind)][i][0])<0 ||
                (y+shape[changeKind(kind)][i][1])>19 ||
                (y+shape[changeKind(kind)][i][1])<0 ||
                map[x+shape[changeKind(kind)][i][0]][y+shape[changeKind(kind)][i][1]]==1
              )
              return false;
        }
        break;
    default:
        return false;
        break;
    }
    return true;
}

void Block::moveAndDraw(int move)
{
    switch(move)
    {
    case 0:
        //输入为0,即向下移动
        last_x=x;
        last_y=y;
        last_kind=kind;
        y++;
        break;
    case 1:
        //输入为1,即左移动
        last_x=x;
        last_y=y;
        last_kind=kind;
        x--;
        break;
    case 2:
        //输入为2,即右移动
        last_x=x;
        last_y=y;
        last_kind=kind;
        x++;
        break;
    case 3:
        //输入为3,即旋转
        last_x=x;
        last_y=y;
        last_kind=kind;
        kind=changeKind(kind);
        break;
    default:
        break;
    }
    for(int i=0;i<4;i++)
    {   //擦除上一次的方块
        if(last_y+shape[last_kind][i][1]<0) continue;
        draw.clearSquare(last_x+shape[last_kind][i][0],last_y+shape[last_kind][i][1]);
    }
    for(int i=0;i<4;i++)
    {   //画出这一次的方块
        if(y+shape[kind][i][1]<0) continue;
        draw.square(x+shape[kind][i][0],y+shape[kind][i][1],color_block,style);
    }
}

void Block::operator++(int)
{
    this->moveAndDraw(0);
}