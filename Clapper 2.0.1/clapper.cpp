//主函数
#include "clapper.h"
#include <iostream>
using namespace std;

extern int Whole, Round;
extern Hero COM, MY;
extern float win_round;

int main(void)
{
	while (menu() == 1)
	{
		for (int again = 6; again == 6; ++Whole)
		{
			for (Round = 1; MY.life > 0 && COM.life > 0; ++Round)
			{
				face(MY);
				com_act(COM, MY);
				//成员作出动作
				MY.power += power_checker(MY.act);
				life(COM, MY);
				both_fun(COM, MY, inf);
				both_fun(COM, MY, note);
			}
			again = _again();
			win_rate(COM, MY);
			first();
			system("cls");
		}
	}
	system("cls");
	cout << "已退出游戏" << endl;
	cin.get();
	return 0;
}