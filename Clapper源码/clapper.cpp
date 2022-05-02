//主函数
#include "define.h"
#include <iostream>
#include <windows.h>
#include <cstdio>

using namespace std;

extern int Whole, Round;
extern Action_inf Com, Player,First_act_inf;
extern Hero COM, PLAYER;
extern Hero First_hero;
extern float win_round;
extern int Inf(const unsigned int& all_whole);

unsigned int menu(Menu());
int main(void)
{
	while ( menu== 1)
	{
		for (int again = 6; again==6; ++Whole)
		{
			for (Round=1; COM.Ending(PLAYER)&&Round<=999; ++Round)
			{
				
                PLAYER.Face(); 
				COM.Com_act(PLAYER);
				PLAYER.Player_act();
				system("cls");
				cout << "第" << Whole << "局|第" << Round << "回合" << endl;
				//成员作出动作
				COM.Life(PLAYER);
				PLAYER.Life(COM);
				//判断生命增减
				cout << "\n玩家\t\t生命\t\t行为\t\t能量\t\t暴击率\t\t胜率\n";
				COM.Inf();
				PLAYER.Inf();
				//输出电脑、玩家信息
				COM.Note();
				PLAYER.Note();
				//旁白
			}
            again = COM.Again();
			COM.Win_rate(PLAYER);
			//计算胜率
			COM.First(again);
			PLAYER.First(again);
			//再来一局进行初始化
			system("cls");
		}
		menu = Menu();
	}

	//调试模式
	while (menu == 2)
	{
		unsigned int all_whole=9999;
		cout <<"已进入调试模式,请确定您已经使用了新方案"<<endl;
		cout << "请输入模拟的局数:";
		cin >> all_whole;
		for (; Whole<=all_whole; ++Whole)
		{
			for (Round = 1; COM.Ending(PLAYER) && Round <= 999; ++Round)
			{
				COM.Com_act(PLAYER);
				PLAYER.Player_act(COM);
				//成员作出动作
				COM.Life(PLAYER);
				PLAYER.Life(COM);
				//判断生命增减
			}
			COM.Win_rate(PLAYER);
			//计算胜率
			COM.First(6);
			PLAYER.First(6);
			//再来一局进行初始化
		}
		Inf(all_whole);
		COM.First(NULL);
		PLAYER.First(NULL);
		system("pause");
		system("cls");
		menu = Menu();
	}

	//退出游戏
	if (menu==6)
	{
		system("cls");
		cout << "已退出游戏" << endl;
		cin.get();
	}

	return 0;
}
