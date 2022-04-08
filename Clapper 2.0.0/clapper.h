//结构、函数原形
#include <string>
using std::string;
typedef enum
{
	rec = 1,
	dod,
	def,
	hit,
	kil,
	pra,
	rep
} Act;
//所有行为种类

struct Hero
{
	string name;           //成员名称
	int life;              //成员的生命值
	Act act;               //成员的行为
	int power;             //成员具有的能量
	int crit_rate;         //成员的暴击率
	int crit_checker;      //检查成员时否暴击,以暴击伤害呈现
	int crit_plus;         //记录成员每次增加的暴击率
	float win_rate;        //成员的胜率
	unsigned int pra_time; //记录成员的祈祷次数
};

bool menu(void);
string action(Hero& ACTION);
int power_checker(Act POWER);
void com_act(Hero& COM_ACT,Hero& MY_ACT);
void my_act(Hero& MY_ACT);
int situ(const Act com_act, const Act my_act);
void face(Hero& FACE);
int life(Hero& COM_LIFE, Hero& MY_LIFE);
void win_rate(Hero& COM_WIN, Hero MY_WIN);
void inf(Hero& HERO);
void note(Hero& NOTE);
bool _again(void);
void first(void);
void both_fun(Hero& COM_FUN, Hero& MY_FUN,void (*both)(Hero&));
//函数声明