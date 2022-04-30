//定义
#include "define.h"
#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;

int Whole = 1, Round = 1;
float win_round = 0.0;
//定义局数、回合数、玩家胜利局数
Hero COM ("Com");
Hero MY;

//对电脑、玩家档案初始定义

Hero::Hero(string _name, int _life, Action& _act, int _power, int _crit_rate, int _crit_checker,
	int _crit_plus, float _win_rate, unsigned int _pra_time, bool _rep_note)
{
	name = _name;
	life = _life;
	act = _act;
	power = _power;
	crit_rate = _crit_rate;
	crit_checker = _crit_checker;
	crit_plus = _crit_plus;
	win_rate = _win_rate;
	pra_time = _pra_time;
	rep_note = _rep_note;
}

int Menu(void) //打印菜单
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
			MY.Name();
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

void Hero:: Name(void) //玩家为角色取名
{
	cout << "为你的角色取个名字(至多7个字符):\n";
	cin.ignore();
	getline(cin,name);
	while (name.length() > 7)
	{
		cout << "你的名称太长了!再取一个吧:\n";
		getline(cin, name);
	}
}

void Hero:: Com_act(Hero& MY_ACT) //电脑随机决定行动
{
	++power;
	srand((unsigned)time(NULL));
	if (Round > 1)
	{
		do {
			do {
				act = Number_to_action(rand() % 7 + 1);
			} while ((MY_ACT.power < 5 && act.num == def) || (pra_time < 3 && act.num == rep));

			if (power == 0)
			{
				if (rand() % 3 != 0)
				{
					act = Rec;
				}
				else
				{
					act = Dod;
				}
			}

			if (power >= 4)
			{
				if (rand() % life == 0 && pra_time < 3)
				{
					act = Pra;
				}
				else if (rand() % 2 == 0 && pra_time >= 3)
				{
					act = Rep;
				}
			}

			if (power >= 5)
			{
				if (rand() % MY_ACT.life != 0)
				{
					act = Kil;
				}
			}

			if (MY_ACT.power >= 5)
			{
				if (rand() % 4 == 0)
				{
					act = Def;
				}
			}
		} while (power + act.POW < 0);
		power += act.POW;
	}
	if (act.num == pra)
	{
		++pra_time;
	}
}

void Hero:: My_act() //玩家决策行动
{
	int temp_act;
	cin >> temp_act;
	while ((temp_act > 6) || (temp_act < 1))
	{
		cout << "行为无效,请重新决策:";
		cin >> temp_act;
	}
	while (power + Number_to_action(temp_act).POW < 0)
	{
		cout << "能量不足,请重新决策:";
		cin >> temp_act;
	}
	if (temp_act == 6)
	{
		if (pra_time >= 3)
			temp_act = 7;
		else
		{
			++pra_time;
		}
	}
	act = Number_to_action(temp_act);
	power += act.POW;
}

Action& Hero:: Number_to_action(int number)
{
	switch (number)
	{
	case 1:return Rec;
	case 2:return Dod;
	case 3:return Def;
	case 4:return Hit;
	case 5:return Kil;
	case 6:return Pra;
	case 7:return Rep;
	default:return Rec;
	}
}

void Hero:: Face(void) //打印界面
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "第" << Whole << "局|第" << Round << "回合" << endl;
	cout << "1.恢 复  2.闪 避  3.防 御" << endl
		<< "4.攻 击  5.斩 杀  ";
	if (pra_time < 3)
	{
		cout << "6.祈 祷" << endl;
	}
	else
	{
		cout << "6.忏 悔" << endl;
	}
	cout << "请输入你的行动:";
	My_act();
	cout << "\n玩家\t\t生命\t\t行为\t\t能量\t\t暴击率\t\t胜率\n";
}

int Hero:: Life(Hero& MY_LIFE) //判断生命增减,并返回伤害值
{
	srand((unsigned)time(NULL));
	unsigned int hurt = 0;
	int situation= act.num * 10 + MY_LIFE.act.num;
	//根据情况值进行分类
	switch (situation)
	{
	case 74:
		crit_plus = rand() % 6 + 10;
	case 14:
		hurt = 1;
		if ((rand() % 100 + 1) <= MY_LIFE.crit_rate)
		{
			hurt = 2;
			MY_LIFE.crit_checker = 2;
		}
		goto COM_HURT;
	case 75:
		crit_plus = rand() % 6 + 10;
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
		crit_plus = rand() % 4 + 3;
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
		crit_plus = rand() % 6 + 3;
		goto COM_HURT;
	case 65:
		hurt = 0;
		crit_plus = rand() % 6 + 3;
		goto COM_HURT;
	case 71:
	case 72:
	case 73:
		crit_plus = rand() % 6 + 10;
		goto COM_HURT;

	COM_HURT:
		crit_rate += crit_plus;
		life -= hurt;
		break;

	case 47:
		crit_plus = rand() % 6 + 10;
	case 41:
		hurt = 1;
		if ((rand() % 100 + 1) <= crit_rate)
		{
			hurt = 2;
			crit_checker = 2;
		}
		goto MY_HURT;
	case 57:
		MY_LIFE.crit_plus = rand() % 6 + 10;
	case 51:
	case 52:
	case 54:
		hurt = 1;
		if ((rand() % 100 + 1) <= crit_rate)
		{
			if ((hurt = rand() % 2 + 2) > 1)
			{
				crit_checker = 2;
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

void Hero:: Win_rate(Hero& MY_WIN) //计算成员胜率
{
	if (life <= 0)
	{
		++win_round;
	}
	MY_WIN.win_rate = win_round / Whole * 100;
	if (Whole - win_round <= 0)
	{
		win_rate = 0;
	}
	else
	{
		win_rate = (Whole - win_round) / Whole * 100;
	}
}

void Hero:: Inf(void) //打印电脑和玩家的信息
{
	cout << name << "\t\t";
	for (int i = 0; i < life && life > 0; i++)
	{
		cout << "+";
	}
	if (crit_rate >= 100)
	{
		crit_rate = 100;
	}
	cout << "\t\t" << act.name
		<< "\t\t" << power
		<< "\t\t" << crit_rate << "%"
		<< "\t\t" << fixed << setprecision(2) << win_rate << "%" << endl;
}

void Hero:: Note(void) //在旁输出特殊情况
{
	bool rep_note = true;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	cout << "\n";

	if (crit_checker) //若成员造成暴击,则打印暴击情况
	{
		cout << name << "造成了暴击!,造成了" << crit_checker << "点伤害" << endl;
		crit_checker = 0;
	}

	if (act.num == pra)
	{
		cout << name << "进行了虔诚的\'祈 祷\',生命 + 1,暴击率 + " << crit_plus << "%!" << endl;
	}

	if (act.num == rep)
	{
		cout << name << "进行了虔诚的\'忏 悔\',暴击率 + " << crit_plus << "%!" << endl;
	}

	if (pra_time == 3 && rep_note)
	{
		cout << "|上 帝 已 死|," << name << "触 发 \'|忏 悔|\'" << endl;
		rep_note = false;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int Hero:: Again(void)
{
	int again;
	if (life > 0)
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

void Hero:: First(void) //进行初始化
{
	life = 3;
	act = Rec;
	power = 0;
	crit_rate = 5;
	crit_checker = 0;
	crit_plus = 0;
	win_rate = 0;
	pra_time = 0;
	rep_note = true;
}
