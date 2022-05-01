//主函数
#include "define.h"
#include <iostream>
using namespace std;

extern int Whole, Round;
extern Action_inf Com, Player,First_act_inf;
extern Hero COM, PLAYER;
extern Hero First_hero;
extern float win_round;

int main(void)
{
	while (Menu() == 1)
	{
		for (int again = 6; again == 6; ++Whole)
		{
			for (Round=1; COM.Ending(PLAYER)&&Round<=999; ++Round)
			{
				PLAYER.Face(); 
				COM.Com_act(PLAYER);
				PLAYER.Player_act();
				//成员作出动作
				COM.Life(PLAYER);
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
			COM.First();
			PLAYER.First();
			//再来一局进行初始化
			system("cls");
		}
	}
	system("cls");
	cout << "已退出游戏" << endl;
	cin.get();
	return 0;
}