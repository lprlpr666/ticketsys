//
// Created by 陆鹏睿 on 2023/5/21.
//

#ifndef UNTITLED97_TRAIN_H
#define UNTITLED97_TRAIN_H

#include "vector.h"
#include "bpt.h"
#include "daytime.h"
using namespace std;
class myhashtrainforid
{
public:
    size_t ID_hash;
    myhashtrainforid(){ID_hash=0;}
    myhashtrainforid(const myhashtrainforid &x1)
    {
        ID_hash=x1.ID_hash;
    }
    myhashtrainforid(const char *x){ID_hash=get_my_hash(x);}
    friend bool operator < (const myhashtrainforid &x1,const myhashtrainforid &x2) {
        return x1.ID_hash<x2.ID_hash;
    }
    friend bool operator <= (const myhashtrainforid &x1,const myhashtrainforid &x2) {
        return x1.ID_hash<=x2.ID_hash;
    }
    friend bool operator > (const myhashtrainforid &x1,const myhashtrainforid &x2) {
        return x1.ID_hash>x2.ID_hash;
    }
    friend bool operator == (const myhashtrainforid &x1,const myhashtrainforid &x2) {
        return x1.ID_hash==x2.ID_hash;
    }
    friend bool operator != (const myhashtrainforid &x1,const myhashtrainforid  &x2) {
        return x1.ID_hash!=x2.ID_hash;
    }
    myhashtrainforid operator = (const myhashtrainforid  &x){
        ID_hash=x.ID_hash;
        return *this;
    }
    size_t get_my_hash(const char* x){
        std::size_t hash = 0;
        for(int i=0;i<strlen(x);i++){
            hash=(hash*31)+x[i];
        }
        return hash;
    }
};
class station
{
public:
    char name[33];
    station(){name[0]=0;}
    station(char *x){
        strcpy(name,x);
    }
    ~station(){
        name[0]=0;
    }
    station(const std::string &s){
        strcpy(name,s.c_str());
    }
    friend bool operator<(const station &x1,const station &x2){
        return strcmp(x1.name,x2.name)<0;
    }
    friend bool operator<=(const station &x1,const station &x2){
        return strcmp(x1.name,x2.name)<=0;
    }
    friend bool operator == (const station &x1,const station &x2) {
        return strcmp(x1.name,x2.name)==0;
    }
    friend bool operator != (const station &x1,const station &x2) {
        return strcmp(x1.name,x2.name)!=0;
    }
};
class traintrain{
public:
    char trainid[21];
    int stationNUm;
    char stations[100][31];
    int seatnum;
    int prices[100];
    int traveltime[100];
    daytime starttime;
    int stopoverTimes[100];
    monthtime saledatamonth1;
    monthtime saledatamonth2;
    char type;
    bool release;
    int sumtime[100];
    int sumprices[100];
    friend bool operator < (const traintrain &obj1,const traintrain &obj2){
        return strcmp(obj1.trainid,obj2.trainid)<0;
    }
    traintrain(){
        trainid[0]=0;
        release=0;
    }
    traintrain operator=(const traintrain&other){
        strcpy(trainid,other.trainid);
        for(int i=0;i<=99;i++){
            strcpy(stations[i],other.stations[i]);
            prices[i]=other.prices[i];
            traveltime[i]=other.traveltime[i];
            stopoverTimes[i]=other.stopoverTimes[i];
            sumprices[i]=other.sumprices[i];
            sumtime[i]=other.sumtime[i];
            release = other.release;
        }
        stopoverTimes[other.stationNUm-2]=0;
        stopoverTimes[other.stationNUm-1]=0;
        stationNUm=other.stationNUm;
        seatnum=other.seatnum;
        starttime=other.starttime;
        saledatamonth1=other.saledatamonth1;
        saledatamonth2=other.saledatamonth2;
        type=other.type;

        return *this;
    }
    traintrain(const traintrain&other):stationNUm(other.stationNUm),
    seatnum(other.seatnum),starttime(other.starttime),
    saledatamonth1(other.saledatamonth1),saledatamonth2(other.saledatamonth2),type(other.type)
    ,release(other.release)
    {
        strcpy(trainid,other.trainid);
        for(int i=0;i<=99;i++){
            strcpy(stations[i],other.stations[i]);
            prices[i]=other.prices[i];
            traveltime[i]=other.traveltime[i];
            stopoverTimes[i]=other.stopoverTimes[i];
            sumprices[i]=other.sumprices[i];
            sumtime[i]=other.sumtime[i];
            release = other.release;
        }
        stopoverTimes[stationNUm-2]=0;
        stopoverTimes[stationNUm-1]=0;
    }
//    traintrain operator=(const traintrain&other){
//        traintrain tmp(other);
//        return tmp;
//    }

    traintrain(char *trainid1,
               int stationNUm1,
               string *stations1,
               int seatnum1,
               int *prices1,
               daytime starttime1,
               int * traveltime1,
               int *stopoverTimes1,
               monthtime saledatamonth11,
                monthtime saledatamonth21,
               char type1,bool release1):stationNUm(stationNUm1),seatnum(seatnum1),type(type1),
                           starttime(starttime1),
                           saledatamonth1(saledatamonth11),
                           saledatamonth2(saledatamonth21),
                           release(release1)
               {
        strcpy(trainid,trainid1);
                  for(int i=0;i<stationNUm1-2;i++){
                      strcpy(stations[i],stations1[i].c_str());
                      prices[i]=prices1[i];
                      traveltime[i]=traveltime1[i];
                      stopoverTimes[i]=stopoverTimes1[i];
                      release = release1;
                      if(i==0) {
                            sumtime[0]=traveltime[0]+stopoverTimes[0];
                            sumprices[0]=prices1[0];
                      }
                      else{
                          sumtime[i]=sumtime[i-1]+traveltime1[i]+stopoverTimes1[i];
                          sumprices[i]=sumprices[i-1]+prices1[i];
                      }
                  }
                   strcpy(stations[stationNUm1-1],stations1[stationNUm1-1].c_str());
                   strcpy(stations[stationNUm1-2],stations1[stationNUm1-2].c_str());
                   prices[stationNUm1-2]=prices1[stationNUm1-2];
                   traveltime[stationNUm1-2]=traveltime1[stationNUm1-2];
                   if(stationNUm1==2){
                       sumtime[0]=traveltime1[0];
                       sumprices[0]=prices1[0];
                   }
                   else{
                       sumprices[stationNUm1-2]=sumprices[stationNUm1-3]+prices1[stationNUm1-2];
                       sumtime[stationNUm1-2]=sumtime[stationNUm1-3]+traveltime1[stationNUm1-2];
                   }
                   stopoverTimes1[stationNUm1-2]=0;
                   stopoverTimes1[stationNUm1-1]=0;
    }
};



// 队列类


class everydaytrain
{
public:
    char trainID[21];
    int date;
    everydaytrain(){trainID[0]=0;}
    everydaytrain(char* trainID_,int date1):date(date1){
        strcpy(trainID,trainID_);
    }
    everydaytrain(const everydaytrain &other){
        strcpy(trainID,other.trainID);
        date=other.date;
    }
    friend bool operator<(const everydaytrain &x1,const everydaytrain &x2){
        if(strcmp(x1.trainID,x2.trainID)<0)return true;
        else if(strcmp(x1.trainID,x2.trainID)==0 && x1.date<x2.date)return true;
        else return false;
    }
    friend bool operator<=(const everydaytrain &x1,const everydaytrain &x2){
        if(strcmp(x1.trainID,x2.trainID)<0)return true;
        else if(strcmp(x1.trainID,x2.trainID)==0 && x1.date<=x2.date)return true;
        else return false;
    }
    friend bool operator>(const everydaytrain &x1,const everydaytrain &x2){
        if(strcmp(x1.trainID,x2.trainID)>0)return true;
        else if(strcmp(x1.trainID,x2.trainID)==0 && x1.date>x2.date)return true;
        else return false;
    }
    friend bool operator>=(const everydaytrain &x1,const everydaytrain &x2){
        if(strcmp(x1.trainID,x2.trainID)>0)return true;
        else if(strcmp(x1.trainID,x2.trainID)==0 && x1.date>=x2.date)return true;
        else return false;
    }
    friend bool operator==(const everydaytrain &x1,const everydaytrain &x2){
        return (!(x1<x2)) && (!(x2<x1));
    }
    friend bool operator!=(const everydaytrain &x1,const everydaytrain &x2){
        return !(x1==x2);
    }
};
class pairwithtrainandplace
{
public:
    char ID[21];
    int pos;
    pairwithtrainandplace(){ID[0]=0;}
    pairwithtrainandplace(char* ID_,int pos_):pos(pos_){
        strcpy(ID,ID_);
    }
    friend bool operator< (const pairwithtrainandplace &obj1,const pairwithtrainandplace &obj2){
        return strcmp(obj1.ID,obj2.ID)<0;
    }
};
class traindatabase{
public:
    bpt< myhashtrainforid ,int>bpt_train;
    bpt<station,pairwithtrainandplace> station_base;
    bpt2<traintrain> traindb;
    void settrainplus(string s){
    }
    traindatabase(): traindb("traindb.db"){

        bpt_train.setfile("bpt_train");
        station_base.setfile("station2.db");
    }
    void clear(){
        bpt_train.clear("bpt_train");
        station_base.clear("train.db");
        traindb.clear("traindb.db");
    }
    void add_train(char * trainiiid,const traintrain &tmp){

        bpt_train.insert( myhashtrainforid (trainiiid),traindb.insert(tmp));
    }

};
#endif //UNTITLED97_TRAIN_H
