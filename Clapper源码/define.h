//结构、函数原形
#ifndef DEFINE_H
#define DEFINE_H
#include <string>
#include <random>
#include <ctime>
#include <iostream>
using namespace std;
static default_random_engine e((unsigned int)time(NULL));
//所有行为种类
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

//行为信息
struct Action            //行为的属性
{
	unsigned int time;   //行为次数
	string name;         //行为名称
	Act num;             //行为数值
	unsigned int DFS;    //防御力
	int ATK;             //攻击力
	int POW;             //耗能值
	int LIF;             //治愈力
	bool real_atk;       //是否为真实伤害
	int crit_rate;       //对爆击率的影响
	int pray;            //虔诚度

	Action& operator=(const Action& a)
	{
		time = a.time;
		name = a.name;
		num = a.num;
		DFS = a.DFS;
		ATK = a.ATK;
		POW = a.POW;
		LIF = a.LIF;
		real_atk = real_atk;
		crit_rate = a.crit_rate;
		pray = a.pray;
		return *this;
	}

};

//玩家的行为档案
struct Action_inf
{
	Action Rec = { 0,"恢复",rec,0,0,1,0,false,0,0 };
	Action Dod = { 0,"闪避",dod,1,0,0,0,false,0,0 };
	Action Def = { 0,"防御",def,5,0,-1,0,false,0,0 };
	Action Hit = { 0,"攻击",hit,0,1,-1,0,false,0,0 };
	Action Kil = { 0,"斩杀",kil,0,1,-5,0,true,0,0 };
	Action Pra = { 0,"祈祷",pra,1,0,-4,1,false,e() % 6 + 3,1 };
	Action Rep = { 0,"忏悔",rep,1,0,-4,0,false, e() % 6 + 10,1 };
};

//玩家信息
class Hero
{
private:
	string name;           //成员名称
	Action act;            //当前行为
	Action_inf act_inf;    //行为档案
	int life;              //生命
	int power;             //能量
	int crit_rate;         //暴击率
	int crit_checker;      //检查成员是否暴击,以暴击伤害呈现
	float win_rate;        //胜率
	unsigned int pray;     //信仰值
	bool rep_note;         //判断是否已经触发|上帝已死|
	friend int Inf(const unsigned int& all_whole);
	
public:
	Hero(string _name,Action& _act, Action_inf& _act_inf, int _life=3, int _power=0, int _crit_rate=5, int _crit_checker=0
		, float _win_rate=0, unsigned int _pray=0, bool _rep_note=true);
	bool Ending(Hero& MY)
	{
		return(life > 0 && MY.life > 0);
	};
	void Name(void);
	void Face(void);
	void Com_act(Hero& MY_ACT);
	Action& Number_to_action(int&& number);
	void Player_act(void);
	void Player_act(Hero& COM_ACT);
	int Life(Hero &MY_LIFE);
	void Win_rate(Hero& MY_WIN);
	void Inf(void);
	void Note(void);
	int Again(void);
	void First(int again);
	
	//函数声明
	Hero& operator=(const Hero& a)
	{
		act = a.act;
		act_inf = a.act_inf;
		life = a.life;
		power = a.power;
		crit_rate = a.crit_rate;
		crit_checker = a.crit_checker;
		pray = a.pray;
		rep_note = a.rep_note;
		return *this;
	}
};

int Menu(void);
#endif