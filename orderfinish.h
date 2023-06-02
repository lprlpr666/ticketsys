//
// Created by 陆鹏睿 on 2023/5/25.
//

#ifndef UNTITLED97_ORDER_H
#define UNTITLED97_ORDER_H

#include "user.h"
#include "train.h"
#include "time.h"
class orderfinish{
public:
    int cixu;
    char username[21];
    int buynum;
    char trainid[21];
    station from,to;
    int frompos,topos;
    Time leavingtime,arrivingtime;
    int price;
    int state;
    int days_to;
    //1   success
    //2    pending
    //3    refunded
    orderfinish(int cixu1,
                char *username1,
                int buynum1,
                char *trainid1,
                station from1, station to1, int frompos1, int topos1,
                Time leavingtime1, Time arrivingtime1,
                int price1, int dayto, int state1):
    cixu(cixu1),buynum(buynum1),from(from1),to(to1),
    leavingtime(leavingtime1),arrivingtime(arrivingtime1),price(price1),days_to(dayto)
,frompos(frompos1),topos(topos1)
    {
        strcpy(trainid,trainid1);
        strcpy(username,username1);
        state=state1;
    }
    orderfinish(const orderfinish&other): cixu(other.cixu), buynum(other.buynum), from(other.from), to(other.to),
                                          leavingtime(other.leavingtime), arrivingtime(other.arrivingtime), state(other.state)
                             , price(other.price), days_to(other.days_to), frompos(other.frompos), topos(other.topos)
     {
         strcpy(trainid,other.trainid);
         strcpy(username,other.username);
    }
    orderfinish(){}
    friend bool operator<(const orderfinish &x1, const orderfinish &x2){
       return x1.cixu>x2.cixu;
    }
    friend bool operator>(const orderfinish &x1, const orderfinish &x2){
        return x1.cixu<x2.cixu;
    }
    friend bool operator==(const orderfinish &x1, const orderfinish &x2){
        return x1.cixu==x2.cixu;
    }
    friend bool operator<=(const orderfinish &x1, const orderfinish &x2){
        return x1.cixu>=x2.cixu;
    }
    friend bool operator>=(const orderfinish &x1, const orderfinish &x2){
        return x1.cixu<=x2.cixu;
    }
    friend bool operator!=(const orderfinish &x1, const orderfinish &x2){
        return x1.cixu!=x2.cixu;
    }

};

#endif //UNTITLED97_ORDER_H
