//
// Created by 陆鹏睿 on 2023/5/25.
//

#ifndef UNTITLED97_SEATT_H
#define UNTITLED97_SEATT_H

#include <cstring>
#include "pq.h"
//class seat{
//public:
//    int nowseat[101];
//public:
//    seat(){
//        for(int i=0;i<=100;i++){
//            nowseat[i]=0;
//        }
//    }
//    seat(int num){
//        for(int i=0;i<=100;i++){
//            nowseat[i]=num;
//
//        }
//    }
//    seat(const seat&other){
//        for(int i=0;i<=100;i++){
//            nowseat[i]=other.nowseat[i];
//
//        }
//    }
//    bool &operator=(const seat&other){
//        for(int i=0;i<=100;i++){
//            nowseat[i]=other.nowseat[i];
//
//        }
//    }
//    ~seat(){}
//    friend bool operator<(const seat &x1,const seat &x2){
//        return x1.nowseat[0]<x2.nowseat[0];
//    }
//};
class all_seat{
public:
    int everydayseat[101];
public:
    all_seat(){
        for(int i=0;i<=100;i++){
            everydayseat[i]=0;
        }
    }
    all_seat(int tmp){
        for(int i=0;i<=100;i++){
            everydayseat[i]=tmp;
        }
    }
    all_seat(const all_seat &other){
        for(int i=0;i<=100;i++){
            everydayseat[i]=other.everydayseat[i];
        }
    }
    friend bool operator<(const all_seat &x1,const all_seat &x2){
        return x1.everydayseat[0]<x2.everydayseat[0];
    }
    friend bool operator>(const all_seat &x1,const all_seat &x2){
        return x1.everydayseat[0]<x2.everydayseat[0];
    }
    friend bool operator==(const all_seat &x1,const all_seat &x2){
        return x1.everydayseat[0]<x2.everydayseat[0];
    }
    friend bool operator!=(const all_seat &x1,const all_seat &x2){
        return x1.everydayseat[0]<x2.everydayseat[0];
    }
    friend bool operator<=(const all_seat &x1,const all_seat &x2){
        return x1.everydayseat[0]<x2.everydayseat[0];
    }
    friend bool operator>=(const all_seat &x1,const all_seat &x2){
        return x1.everydayseat[0]<x2.everydayseat[0];
    }
};
#endif //UNTITLED97_SEATT_H
