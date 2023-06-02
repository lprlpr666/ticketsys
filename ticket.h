//
// Created by 陆鹏睿 on 2023/5/26.
//

#ifndef UNTITLED97_TICKET_H
#define UNTITLED97_TICKET_H

#include "bpt.h"
#include "train.h"


class everydayticketsys
{
public:
    int everydayticket[100];
    everydayticketsys(){}
    everydayticketsys(const everydayticketsys &other){
        for(int i=0;i<100;i++)everydayticket[i]=other.everydayticket[i];
    }
    everydayticketsys(int *t,int num){
        for(int i=0;i<num;i++)everydayticket[i]=t[i];
    }
    everydayticketsys(int numing,int num){
        for(int i=0;i<num;i++)everydayticket[i]=numing;
    }
    friend bool operator<(const everydayticketsys &x1,const everydayticketsys &x2){
        return false;
    }
    everydayticketsys operator=(const everydayticketsys &x){
        for(int i=0;i<101;i++)everydayticket[i]=x.everydayticket[i];
        return *this;
    }
};
class ticket_base
{
public:
    bpt<everydaytrain,int> ticket_base_;
    bpt2<everydayticketsys> ticket_database;
    ticket_base():ticket_database("ticket_database.db"){
        ticket_base_.setfile("ticket.db");
    }
    everydayticketsys query(const everydaytrain &i1){
        return ticket_database.find(ticket_base_.find(i1)[0]);
    }
};
#endif //UNTITLED97_TICKET_H
