//定义
#include "clapper.h"
#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
#include<iomanip>
using namespace std;

int Whole = 1, Round = 1;
float win_round = 0.0;
//定义局数、回合数、玩家胜利局数
Hero COM = { "Com", 3, rec, 1, 5, 0, 0, 0.0, 0,true },
MY = { "\0", 3, rec, 0, 5, 0, 0, 0.0, 0,true };
//对电脑、玩家档案初始定义


int menu(void) //打印菜单
{
	int choice;
	do {
		cout << "        *************************          " << endl;
		cout << "        *        菜 单 栏       *          " << endl;
		cout << "        *     1.开 始 游 戏     *          " << endl;
		cout << "        *     2.游 戏 玩 法     *          " << endl;
		cout << "        *     3.游 戏 图 鉴     *          " << endl;
		cout << "        *     4.制 作 人 员     *          " << endl;
		cout << "        *     5.退 出 游 戏     *          " << endl;
		cout << "        *************************          " << endl;
		cout << "输入你的选择:";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			name(MY);
			return 1;
		case 2:
			cout << "游戏玩法:  待补充       " << endl;
			break;
		case 3:
			cout << "游戏图鉴:  待补充       " << endl;
			break;
		case 4:
			cout << "     制 作 人 员       " << endl;
			cout << "     CannonBox       \n" << endl;
			cout << "     Version:1.2.0       " << endl;
			break;
		case 5:
			return 5;
		default:
			cout << "没有这个选项!" << endl;

		}
		cout << "按任意键返回菜单栏       " << endl;
		system("pause");
		system("cls");
	} while (choice != 1 || choice != 5);
	return choice;
}

void name(Hero& NAME) //玩家为角色取名
{
	cout << "为你的角色取个名字(至多7个字符):\n";
	cin.ignore();
	getline(cin,NAME.name);
	while (NAME.name.length() > 7)
	{
		cout << "你的名称太长了!再取一个吧:\n";
		getline(cin, NAME.name);
	}
}

string action(Hero& ACTION) //根据行为值返回行为
{
	switch (ACTION.act)
	{
	case rec:
		return "恢复";
	case dod:
		return "闪避";
	case def:
		return "防御";
	case hit:
		return "攻击";
	case kil:
		return "斩杀";
	case pra:
		return "祈祷";
	case rep:
		return "忏悔";

	default:
		return "\0";
	}
}

int power_checker(const Act POWER) //用于根据行为判断能量变化,返回消耗的能量值
{
	int power;
	switch (POWER)
	{
	case rec:
		power = 1;
		break;
	case dod:
		power = 0;
		break;
	case def:
		power = -1;
		break;
	case hit:
		power = -1;
		break;
	case kil:
		power = -5;
		break;
	case pra:
		power = -4;
		break;
	case rep:
		power = -4;
	}
	return power;
}

void com_act(Hero& COM_ACT, Hero& MY_ACT) //电脑随机决定行动
{
	srand((unsigned)time(NULL));
	if (Round > 1)
	{
		do {
			do {
				COM_ACT.act = (Act)(rand() % 7 + 1);
			} while ((MY_ACT.power < 5 && COM_ACT.act == def) || (COM_ACT.pra_time < 3 && COM_ACT.act == rep));

			if (COM_ACT.power == 0)
			{
				if (rand() % 3 != 0)
				{
					COM_ACT.act = rec;
				}
				else
				{
					COM_ACT.act = dod;
				}
			}

			if (COM_ACT.power >= 4)
			{
				if (rand() % COM_ACT.life == 0 && COM_ACT.pra_time < 3)
				{
					COM_ACT.act = pra;
				}
				else if (rand() % 2 == 0 && COM_ACT.pra_time >= 3)
				{
					COM_ACT.act = rep;
				}
			}

			if (COM_ACT.power >= 5)
			{
				if (rand() % MY_ACT.life != 0)
				{
					COM_ACT.act = kil;
				}
			}

			if (MY_ACT.power >= 5)
			{
				if (rand() % 4 == 0)
				{
					COM_ACT.act = def;
				}
			}
		} while (COM_ACT.power + power_checker(COM_ACT.act) < 0);
		COM_ACT.power += power_checker(COM_ACT.act);
	}
	if (COM_ACT.act == pra)
	{
		++COM_ACT.pra_time;
	}
}

void my_act(Hero& MY_ACT) //玩家决策行动
{
	int temp_act;
	cin >> temp_act;
	while ((temp_act > 6) || (temp_act < 1))
	{
		cout << "行为无效,请重新决策:";
		cin >> temp_act;
	}
	while (MY_ACT.power + power_checker((Act)temp_act) < 0)
	{
		cout << "能量不足,请重新决策:";
		cin >> temp_act;
	}
	if (temp_act == 6)
	{
		if (MY_ACT.pra_time >= 3)
			temp_act = 7;
		else
		{
			++MY_ACT.pra_time;
		}
	}
	MY_ACT.act = (Act)temp_act;
}

int situ(const Act com_act, const Act my_act) //根据行为值返回对应的唯一情况值
{
	int situation = com_act * 10 + my_act;
	return situation;
}

void face(Hero& FACE) //打印界面
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "第" << Whole << "局|第" << Round << "回合" << endl;
	cout << "1.恢 复  2.闪 避  3.防 御" << endl
		<< "4.攻 击  5.斩 杀  ";
	if (FACE.pra_time < 3)
	{
		cout << "6.祈 祷" << endl;
	}
	else
	{
		cout << "6.忏 悔" << endl;
	}
	cout << "请输入你的行动:";
	my_act(FACE);
	cout << "\n玩家\t\t生命\t\t行为\t\t能量\t\t暴击率\t\t胜率\n";
}

int life(Hero& COM_LIFE, Hero& MY_LIFE) //判断生命增减,并返回伤害值
{
	srand((unsigned)time(NULL));
	unsigned int hurt = 0;
	int situation = situ(COM_LIFE.act, MY_LIFE.act);
	//根据情况值进行分类
	switch (situation)
	{
	case 74:
		COM_LIFE.crit_plus = rand() % 6 + 10;
	case 14:
		hurt = 1;
		if ((rand() % 100 + 1) <= MY_LIFE.crit_rate)
		{
			hurt = 2;
			MY_LIFE.crit_checker = 2;
		}
		goto COM_HURT;
	case 75:
		COM_LIFE.crit_plus = rand() % 6 + 10;
	case 15:
	case 25:
	case 45:
		hurt = 1;
		if ((rand() % 100 + 1) <= MY_LIFE.crit_rate)
		{
			if ((hurt = rand() % 2 + 2) > 1)
			{
				MY_LIFE.crit_checker = 2;
				if (hurt > 2)
				{
					MY_LIFE.crit_checker = 3;
				}
			}
		}
		goto COM_HURT;
	case 35:
		hurt = 0;
		COM_LIFE.crit_plus = rand() % 4 + 3;
		goto COM_HURT;
	case 66:
		MY_LIFE.crit_plus = rand() % 6 + 3;
		MY_LIFE.crit_rate += MY_LIFE.crit_plus;
		++MY_LIFE.life;
	case 61:
	case 62:
	case 63:
	case 64:
		hurt = -1;
		COM_LIFE.crit_plus = rand() % 6 + 3;
		goto COM_HURT;
	case 65:
		hurt = 0;
		COM_LIFE.crit_plus = rand() % 6 + 3;
		goto COM_HURT;
	case 71:
	case 72:
	case 73:
		COM_LIFE.crit_plus = rand() % 6 + 10;
		goto COM_HURT;

	COM_HURT:
		COM_LIFE.crit_rate += COM_LIFE.crit_plus;
		COM_LIFE.life -= hurt;
		break;

	case 47:
		COM_LIFE.crit_plus = rand() % 6 + 10;
	case 41:
		hurt = 1;
		if ((rand() % 100 + 1) <= COM_LIFE.crit_rate)
		{
			hurt = 2;
			COM_LIFE.crit_checker = 2;
		}
		goto MY_HURT;
	case 57:
		MY_LIFE.crit_plus = rand() % 6 + 10;
	case 51:
	case 52:
	case 54:
		hurt = 1;
		if ((rand() % 100 + 1) <= COM_LIFE.crit_rate)
		{
			if ((hurt = rand() % 2 + 2) > 1)
			{
				COM_LIFE.crit_checker = 2;
				if (hurt > 2)
				{
					MY_LIFE.crit_checker = 3;
				}
			}
		}
		goto MY_HURT;
	case 53:
		hurt = 0;
		MY_LIFE.crit_plus = rand() % 6 + 3;
		goto MY_HURT;
	case 16:
	case 26:
	case 36:
	case 46:
		hurt = -1;
		MY_LIFE.crit_plus = rand() % 6 + 3;
		goto MY_HURT;
	case 56:
		hurt = 0;
		MY_LIFE.crit_plus = rand() % 6 + 3;
		goto MY_HURT;
	case 17:
	case 27:
	case 37:
		hurt = 0;
		MY_LIFE.crit_plus = rand() % 6 + 10;
		goto MY_HURT;

	MY_HURT:
		MY_LIFE.crit_rate += MY_LIFE.crit_plus;
		MY_LIFE.life -= hurt;
		break;

	default:
		hurt = 0;
	}

	return hurt;
}

void win_rate(Hero& COM_WIN, Hero& MY_WIN) //计算成员胜率
{
	if (COM_WIN.life <= 0)
	{
		++win_round;
	}
	MY_WIN.win_rate = win_round / Whole * 100;
	if (Whole - win_round <= 0)
	{
		COM_WIN.win_rate = 0;
	}
	else
	{
		COM_WIN.win_rate = (Whole - win_round) / Whole * 100;
	}
}

void inf(Hero& HERO) //打印电脑和玩家的信息
{
	cout << HERO.name << "\t\t";
	for (int i = 0; i < HERO.life && HERO.life > 0; i++)
	{
		cout << "+";
	}
	if (HERO.crit_rate >= 100)
	{
		HERO.crit_rate = 100;
	}
	cout << "\t\t" << action(HERO)
		<< "\t\t" << HERO.power
		<< "\t\t" << HERO.crit_rate << "\%"
		<< "\t\t" << fixed << setprecision(2) << HERO.win_rate << "\%" << endl;
}

void note(Hero& NOTE) //在旁输出特殊情况
{
	bool rep_note = true;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	cout << "\n";

	if (NOTE.crit_checker) //若成员造成暴击,则打印暴击情况
	{
		cout << NOTE.name << "造成了暴击!,造成了" << NOTE.crit_checker << "点伤害" << endl;
		NOTE.crit_checker = 0;
	}

	if (NOTE.act == pra)
	{
		cout << NOTE.name << "进行了虔诚的\'祈 祷\',生命 + 1,暴击率 + " << NOTE.crit_plus << "\%!" << endl;
	}

	if (NOTE.act == rep)
	{
		cout << NOTE.name << "进行了虔诚的\'忏 悔\',暴击率 + " << NOTE.crit_plus << "\%!" << endl;
	}

	if (NOTE.pra_time == 3 && NOTE.rep_note)
	{
		cout << "|上 帝 已 死|," << NOTE.name << "触 发 \'|忏 悔|\'" << endl;
		NOTE.rep_note = false;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int _again(void)
{
	int again;
	if (COM.life > 0)
	{
		MessageBox(NULL, (LPCTSTR)TEXT("你被计算机打败了！"), (LPCTSTR)TEXT("胜负已分"), MB_OK);
	}
	else
	{
		MessageBox(NULL, (LPCTSTR)TEXT("恭喜你打败了计算机"), (LPCTSTR)TEXT("胜负已分"), MB_OK);
	}
	again = MessageBox(NULL, (LPCTSTR)TEXT("还想再来一局？"), (LPCTSTR)TEXT("胜负已分"), MB_YESNO);
	return again;
}

void first(void) //进行初始化
{
	COM.life = MY.life = 3;
	COM.act = rec;
	COM.power = 1;
	MY.power = 0;
	COM.crit_rate = MY.crit_rate = 5;
	COM.pra_time = MY.pra_time = 0;
}

void both_fun(Hero& COM_FUN, Hero& MY_FUN, void (*both)(Hero&))  //方便直接对成员进行同一操作
{
	both(COM_FUN);
	both(MY_FUN);
}