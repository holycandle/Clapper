//定义
#include "define.h"
#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
#include <iomanip>
#include <cctype>
#include <random>

using namespace std;
uniform_int_distribution<unsigned> u(1, 7);
int Whole = 1, Round = 1;
float win_round = 0.0;
//定义局数、回合数、玩家胜利局数

Action_inf Com, Player,First_act_inf;
Hero COM ("Com",Com.Rec,Com);
Hero PLAYER ("New",Player.Rec,Player);
Hero First_hero("New", First_act_inf.Rec, First_act_inf);
//对电脑、玩家档案初始定义

//人物的构造函数
Hero::Hero(string _name, Action& _act, Action_inf& _act_inf, int _life, int _power, int _crit_rate, int _crit_checker,
	 float _win_rate, unsigned int _pray, bool _rep_note)
{
	name = _name;
	act = _act;
	act_inf = _act_inf;
	life = _life;
	power = _power;
	crit_rate = _crit_rate;
	crit_checker = _crit_checker;
	win_rate = _win_rate;
	pray = _pray;
	rep_note = _rep_note;
}

//打印菜单
int Menu(void) 
{
	int choice;
	do {
		cout << "        *************************          " << endl;
		cout << "        *        菜 单 栏       *          " << endl;
		cout << "        *     1.开 始 游 戏     *          " << endl;
		cout << "        *     2.调 试 模 式     *          " << endl;
		cout << "        *     3.游 戏 玩 法     *          " << endl;
		cout << "        *     4.游 戏 图 鉴     *          " << endl;
		cout << "        *     5.制 作 人 员     *          " << endl;
		cout << "        *     6.退 出 游 戏     *          " << endl;
		cout << "        *************************          " << endl;
		cout << "        输入你的选择:";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(999, '\n');
		}
		cin>>choice;
		system("cls");
		switch (choice)
		{
		case 1:
			PLAYER.Name();
			return 1;
		case 2:
			return 2;
		case 3:
			cout << "游戏玩法:  待补充       " << endl;
			break;
		case 4:
			cout << "游戏图鉴:  待补充       " << endl;
			break;
		case 5:
			cout << "     制 作 人 员       " << endl;
			cout << "     CannonBox       \n" << endl;
			cout << "     Version:1.2.0       " << endl;
			break;
		case 6:
			return 5;
		default:
			cout << "没有这个选项!" << endl;

		}
		cout << "按任意键返回菜单栏       " << endl;
		system("pause");
		system("cls");
	} while ((choice != 1)||(choice!=2) || (choice != 6) || cin.fail());
	return choice;
}

//玩家为角色取名
void Hero:: Name(void) 
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

//电脑随机决定行动
void Hero::Com_act(Hero& PLAYER_ACT) 
{

	if (Round == 1)
	{
		++power;
	}
	else
	{
		do {
			do {
				act = Number_to_action(u(e));
			} while ((PLAYER_ACT.power < 5 && act.num == def) || (pray < 3 && act.num == rep));
			
			//若电脑power>=4，电脑 祈祷 概率随 电脑life 减小而增大	
			//触发|上帝已死|后，电脑 忏悔概率为1/2
			if (power >= 4)                              
			{
				if (e() % life == 0 && pray < 3)
				{
					act = Number_to_action(6);
				}
				else if (e() % 2 == 0 && pray >= 3)
				{
					act = Number_to_action(7);
				}
			}

			//若电脑power>=5，电脑 斩杀 概率随 玩家life 减小而增大，最大1/2
			if (power >= 5)                        
			{
				if (e() % PLAYER_ACT.life != 0)
				{
					act = Number_to_action(5);
				}
			}

			//若玩家power>=5,电脑1/4概率 防御
			if (PLAYER_ACT.power >= 5)      
			{
				if (e() % 4 == 0)
				{
					act = Number_to_action(3);
				}
			}

			//若power为0，电脑 恢复/闪避=2/1
			if (power == 0)                
			{
				if (e() % 3 != 0)
				{
					act = Number_to_action(1);
				}
				else
				{
					act = Number_to_action(2);
				}
			}
		} while (power + act.POW < 0);
		power += act.POW;
	}
	//增加相应行为次数
	++act.time;
	//增加信仰值                  
	pray += act.pray;        
	//随机重置电脑暴击率
	act_inf.Pra.crit_rate = e() % 6 + 3;
	act_inf.Rep.crit_rate = e() % 6 + 10;
}

//玩家决策行动
void Hero:: Player_act(void) 
{
	cout << "请输入你的行动:";
	unsigned int temp_act;
	cin>>temp_act;
	while ((temp_act < 1) || (temp_act > 6) || cin.fail())
	{
		cout << "\n行为无效,请重新决策:";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(999,'\n');
		}
		cin>>temp_act;

	}
	while ((power + Number_to_action(temp_act).POW < 0 )||cin.fail())
	{
		cout << "能量不足,请重新决策:";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(999,'\n');
		}
		cin >> temp_act;
		
	}
	if (temp_act == 6)
	{
		if (pray >= 3)
		{
			temp_act = 7;
		}
		else
		{
			++pray;
		}
	}
	act = Number_to_action(temp_act);
	//增加相应行为次数
	++act.time;
	//增加信仰值 
	power += act.POW;
	//随机重置电脑暴击率
	act_inf.Pra.crit_rate = e() % 6 + 3;
	act_inf.Rep.crit_rate = e() % 6 + 10;
}

//调试模式下的新方案
void Hero::Player_act(Hero& COM_ACT)
{
	if (Round == 1)
	{
		++power;
	}
	else
	{
		do {
			do {
				act = Number_to_action(u(e));
			} while ((COM_ACT.power < 5 && act.num == def) || (pray < 3 && act.num == rep));

			//若电脑power>=5，电脑 斩杀 概率随 玩家life 减小而增大，最大1/2
			if (power >= 5)
			{
				if (e() % COM_ACT.life != 0)
				{
					act = Number_to_action(5);
				}
			}

			//若电脑power>=4，电脑 祈祷 概率随 电脑life 减小而增大	
			//触发|上帝已死|后，电脑 忏悔概率为1/2
			if (power >= 4)
			{
				if (e() % life == 0 && pray < 3)
				{
					act = Number_to_action(6);
				}
				else if (e() % 2 == 0 && pray >= 3)
				{
					act = Number_to_action(7);
				}
			}

			//若玩家power>=5,电脑1/4概率 防御
			if (COM_ACT.power >= 5)
			{
				if (e() % 4 == 0)
				{
					act = Number_to_action(3);
				}
			}

			//若power为0，电脑 恢复/闪避=2/1
			if (power == 0)
			{
				if (e() % 3 != 0)
				{
					act = Number_to_action(1);
				}
				else
				{
					act = Number_to_action(2);
				}
			}
		} while (power + act.POW < 0);
		power += act.POW;
	}
	//增加相应行为次数
	++act.time;
	//增加信仰值                  
	pray += act.pray;
	//随机重置电脑暴击率
	act_inf.Pra.crit_rate = e() % 6 + 3;
	act_inf.Rep.crit_rate = e() % 6 + 10;
}

//根据数字返回行为
Action& Hero:: Number_to_action(int&& number)
{
	switch (number)
	{
	case 1:return act_inf.Rec;
	case 2:return act_inf.Dod;
	case 3:return act_inf.Def;
	case 4:return act_inf.Hit;
	case 5:return act_inf.Kil;
	case 6:return act_inf.Pra;
	case 7:return act_inf.Rep;
	default:return act_inf.Rec;
	}
}

//打印界面
void Hero:: Face(void) 
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	
	cout << "1.恢 复  2.闪 避  3.防 御" << endl
		<< "4.攻 击  5.斩 杀  ";
	if (pra < 3)
	{
		cout << "6.祈 祷" << endl;
	}
	else
	{
		cout << "6.忏 悔" << endl;
	}
}

//判断生命增减,并返回伤害值
int Hero:: Life(Hero& ANOTHER_LIFE) 
{
	//造成的伤害
	unsigned int hurt = 0;    
	const int situation= act.num * 10 + ANOTHER_LIFE.act.num;     
	
	//根据情况值进行分类
	switch (situation)
	{
	case 74:
	case 14:
		hurt = 1;
		if ((e() % 100 + 1) <= ANOTHER_LIFE.crit_rate)
		{
			hurt = 2;
			ANOTHER_LIFE.crit_checker = 2;
		}
		goto HURT;
	case 75:
	case 15:
	case 25:
	case 45:
		hurt = 1;
		if ((e() % 100 + 1) <= ANOTHER_LIFE.crit_rate)
		{
			if ((hurt = e() % 2 + 2) > 1)
			{
				ANOTHER_LIFE.crit_checker = 2;
				if (hurt > 2)
				{
					ANOTHER_LIFE.crit_checker = 3;
				}
			}
		}
		goto HURT;
	case 35:
		hurt = 0;
		goto HURT;
	case 66:
		ANOTHER_LIFE.crit_rate += ANOTHER_LIFE.act.crit_rate;
		++ANOTHER_LIFE.life;
	case 61:
	case 62:
	case 63:
	case 64:
		hurt = -1;
		goto HURT;
	case 65:
		hurt = 0;
		goto HURT;
	case 71:
	case 72:
	case 73:
		goto HURT;

	HURT:
		crit_rate += act.crit_rate;
		life -= hurt;
		break;

	default:
		hurt = 0;
	}
	return hurt;
}

//计算成员胜率
void Hero:: Win_rate(Hero& PLAYER_WIN) 
{
	if (life <= 0)
	{
		++win_round;
	}
	PLAYER_WIN.win_rate = win_round / Whole * 100;win_rate = (Whole - win_round) / Whole * 100;
	
}

//打印电脑和玩家的信息
void Hero:: Inf(void) 
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

//调试模式，显示最终胜率
int Inf(const unsigned int& all_whole)
{
	cout << "\n模拟完成,总局数:" << all_whole << endl
		<< "旧方案胜率: " << COM.win_rate << endl
		<< "新方案胜率: " << PLAYER.win_rate << endl;
	cout << "\n结论:";
	if (COM.win_rate - PLAYER.win_rate >= 5)
	{
		cout << "旧方案 优于 新方案" << endl;
		return -1;
	}
	else if (PLAYER.win_rate - COM.win_rate >= 5)
	{
		cout << "新方案 优于 旧方案" << endl;
		return 1;
	}
	else
	{
		cout << "新方案 与 旧方案 不相上下" << endl;
		return 0;
	}
}

//在旁输出特殊情况void Hero:: Inf(void)
void Hero:: Note(void) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	cout << "\n";

	if (crit_checker) //若成员造成暴击,则打印暴击情况
	{
		cout << name << "造成了暴击!,造成了" << crit_checker << "点伤害" << endl;
		crit_checker = 0;
	}

	if (act.num == pra)
	{
		cout << name << "进行了虔诚的\'祈 祷\',生命 + 1,暴击率 + " << act.crit_rate << "%!" << endl;
	}

	if (act.num == rep)
	{
		cout << name << "进行了虔诚的\'忏 悔\',暴击率 + " << act.crit_rate << "%!" << endl;
	}

	if (pray == 3 && rep_note)
	{
		cout << "|上 帝 已 死|," << name << "触 发 \'|忏 悔|\'" << endl;
		rep_note = false;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//一局游戏结束后的弹窗
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

//重来一局进行初始化
void Hero:: First(int again)
{
	*this = First_hero;
	if (again != 6)
	{
		this->win_rate = First_hero.win_rate;
	}
}