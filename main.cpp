// main.cpp
//main文件，包含了main函数，程序从该函数开始
#include "Home.h"
#include "Game.h"
#include "Rank.h"
#include "Setting.h"


int main()
{
	int pageFlag=0;// 用于判断跳转至哪个界面,0为homePage,1为gamePage,2为optionPage,3为rankPage
	Home home;
	Game game;
	Rank rank;
	Setting setting;
	while(1)
	{
		if(pageFlag==0)
		{
			// 进入主界面
			home.run(pageFlag);
		}
		else if(pageFlag==1)
		{
			// 进入游戏
			game.play(pageFlag);
		}
		else if(pageFlag==2)
		{
			// 进入设置
			setting.run(pageFlag);
		}
		else if(pageFlag==3)
		{
			// 进入排行榜
			rank.run(pageFlag);
		}
		else if(pageFlag==9)
		{
			// 退出游戏
			break;
		}
	}
	closegraph();
	return 0;
}