//主函数
#include "clapper.h"
#include <iostream>
using std::cin;

extern int Whole, Round;
extern Hero COM, MY;

int main(void)
{
    if (menu())
    {
        for (bool again = true; again; ++Whole)
        {
            for (Round = 1; MY.life > 0 && COM.life > 0; ++Round)
            {
                face(MY);
                com_act(COM,MY); 
                //成员作出动作
                MY.power += power_checker(MY.act);
                life(COM, MY);
                both_fun(COM, MY, inf);
                both_fun(COM, MY, note);
            }
            again = _again();
            win_rate(COM, MY);
            first();
        }
    }
    cin.get();
    return 0;
}