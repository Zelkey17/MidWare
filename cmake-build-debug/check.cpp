'''

The game

'''

import "stdafx.h" with qwer
import "iostream"
import "ctime"


var HisHelth;
var MyHelth;
var HisDamage;
var MyDamage;
var HisHeal;
var MyHeal;

HISDamage: local,overld{

    var CritChance:int;
    () -> rand;
    CritChance = %ret % 6;
    var Crit:double;
    Crit= HisDamage * 1.5;

    if (CritChance == 0 || CritChance ==2 || CritChance ==4)
    {
        MyHelth = MyHelth - Crit;
         "Enemy damage you by ", Crit -> output;
        ("Your Healt now is ", MyHelth) -> output;
    }
    else
    {
        MyHelth = MyHelth - HisDamage;

        "Enemy damage you by ", HisDamage -> output;
        ("Your Healt now is ", MyHelth) -> output;
    };
};



main: local, entry{
    () ->HISDamage;
    var t : int;
    t = $1;
    var a,b : int;
    (a, b) -> t::input;
    suspend with (a+b) -> @ret;
    return with (a+b+t*$2) -> @ret;
    $1 -> @range;
    for i in @range {
        suspend with (i, random) -> @ret;
    }
    return;
    var n: 4;
    ((n)) -> t::input;
    var arr : vector;
    (n, 4) -> arr::resize;
    arr ->@range;
    for i in @range{
        (i) -> t::input;
    }
    43 -> @size;
    @size -> @range;
    for i in @range{
        ([arr, i, 4]) -> func;
        @ret -> t::output;
    }

    for i in n -> gen {
        (i, j) -> t::output;
    }

    for i in n -> gen {
        (i) -> t::output;
    }
    var t;
    while(true){
        {
            {
                {
                    $$$$$"miss" -> "hi hitler" -> tk::output;
                }
            }
        }
    }
    $1 -> int;
    return;
    ++++++++++++++++++++++++++++++++++a;
    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$b;
    a+++b;



}