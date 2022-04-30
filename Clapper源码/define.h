//结构、函数原形
#ifndef DEFINE_H
#define DEFINE_H
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

struct Action    //行为的属性
{
	string name;   //行为名称
	Act num;       //行为数值
	unsigned int DFS;    //防御力
	int ATK;             //攻击力
	int POW;             //耗能值
	int LIF;             //治愈力
	bool real_atk;       //是否为真实伤害
	int crit_rate;       //对爆击率的影响
	int pra_time;        //对信仰值的影响
	
};
static Action Rec = { "恢复",rec,0,0,1,0,false,0,0 };
static Action Dod = { "闪避",dod,1,0,0,0,false,0,0 };
static Action Def = { "防御",def,5,0,0,0,false,0,0 };
static Action Hit = { "攻击",hit,0,1,-1,0,false,0,0 };
static Action Kil = { "斩杀",kil,0,1,-5,0,true,0,0 };
static Action Pra = { "祈祷",pra,1,0,-4,1,false,0,1 };
static Action Rep = { "忏悔",rep,1,0,-4,0,false,0,1 };


class Hero
{
private:
	string name;           //成员名称
	int life;              //成员的生命值
	Action act;            //成员的行为
	int power;             //成员具有的能量
	int crit_rate;         //成员的暴击率
	int crit_checker;      //检查成员时否暴击,以暴击伤害呈现
	int crit_plus;         //记录成员每次增加的暴击率
	float win_rate;        //成员的胜率
	unsigned int pra_time; //记录成员的祈祷次数
	bool rep_note;         //判断是否已经触发|上帝已死|
public:
	Hero(string _name="/0", int _life=3, Action& _act=Rec, int _power=0, int _crit_rate=5, int _crit_checker=0,
		int _crit_plus=0, float _win_rate=0, unsigned int _pra_time=0, bool _rep_note=true);
	bool Ending(Hero& MY)
	{
		return(life > 0 && MY.life > 0);
	};
	void Name(void);
	void Com_act(Hero& MY_ACT);
	Action& Number_to_action(int number);
	void My_act(void);
	void Face(void);
	int Life(Hero &MY_LIFE);
	void Win_rate(Hero& MY_WIN);
	void Inf(void);
	void Note(void);
	int Again(void);
	void First(void);
	//函数声明
};

int Menu(void);
#endif