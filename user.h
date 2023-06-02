//
// Created by 陆鹏睿 on 2023/5/21.
//

#ifndef UNTITLED97_USER_H
#define UNTITLED97_USER_H
#include "bpt.h"
#include "map.h"
class username
{
public:
    size_t hashing;
    username():hashing(0)
    {}
    username(const username &other):hashing(other.hashing) {}
    username(const char *tmp){hashing=get_my_hash_char(tmp);}
    username operator=(const username &other){
        hashing=other.hashing;
        return *this;
    }
    username(const std::string &tmp){hashing=get_my_hash_string(tmp);}
    friend bool operator < (const username &x1,const username &x2) {
        return x1.hashing<x2.hashing;
    }
    friend bool operator <= (const username &x1,const username &x2) {
        return x1.hashing<=x2.hashing;
    }
    friend bool operator == (const username &x1,const username &x2) {
        return x1.hashing==x2.hashing;
    }
    friend bool operator != (const username &x1,const username &x2) {
        return x1.hashing!=x2.hashing;
    }
    size_t get_my_hash_string(const string& tmp){
        std::size_t hash = 0;
        for(int i=0;i<tmp.size();i++){
            hash=(hash*113)+tmp[i];
        }
        return hash;
    }
    size_t get_my_hash_char(const char* tmp){
        std::size_t hash = 0;
        for(int i=0;i<strlen(tmp);i++){
            hash=(hash*113)+tmp[i];
        }
        return hash;
    }
};
class account{
public:
    char username[21];
    char realname[20];
    char mailaddress[31];
    int privilige;
    int ifonline=0;
    //不会用到
public:
    friend bool operator < (const account &x1,const account &x2){
        return strcmp(x1.username,x2.username)<0;
    }
    account() { username[0] = 0; }
    account(char *password1 ,char *realname1,char *mail1,char *username1 ,int pri)
    {
        strcpy(username,username1);
        strcpy(password,password1);
        strcpy(realname,realname1);
        strcpy(mailaddress,mail1);
        privilige=pri;
    }
    int getprevillige(){
        return privilige;
    }
    void qr(){
        cout<<username<<" "<<realname<<" "<<mailaddress<<" "<<privilige<<"\n";
    }
    void modify(char *username2,
    char *password2,
    char *realname2,
    char *mail2,
    int privilige2){
        if(password2[0]!=0)strcpy(password,password2);
        strcpy(username,username2);

        if(realname2[0]!=0)strcpy(realname,realname2);
        if(mail2[0]!=0)strcpy(mailaddress,mail2);
        if(privilige2!=-1)privilige=privilige2;
    }

    char password [31];
};
class user{
public:
    bpt<username,account>bppt;
public:
    sjtu::map<int,int> loginmembers;
    user(){
        bppt.setfile("user.db");
    }
public:
    void offline(){
        loginmembers.clear();
    }
    void insert(char *username4,account &tmp){
        bppt.insert(username(username4),tmp);
    }
    void eraseuser(char *username3,account &tmp){
        bppt.erase(username(username3),tmp);
    }
    sjtu::vector<account> finduser(char *username2){
        return bppt.find(username(username2));
    }
    void adduser( char *password1 ,char *realname1,char *mail1,char *username1 ,int pri=10)
    {
        account newact(password1,realname1,mail1,username1,pri);
        bppt.insert(username(username1),newact);
    }
    void clear(){
        loginmembers.clear();
        bppt.clear("user.db");
    }
    int login(char *username2,char *password2){
        sjtu::vector<account> myfind(finduser(username2));
        account tmp=myfind[0];
        if(myfind.empty())
        {
            return -1;
        }
        if (strcmp(tmp.password,password2)!=0){
            return -1;
        }
        username tmpuser(username2);
        if(loginmembers.find((tmpuser.hashing))!=loginmembers.end()){
            return -1;
        }
        else {
            loginmembers.insert({tmpuser.hashing, tmp.privilige});
            return 1;
        }
    }
    int logout(char *username3){
        sjtu::vector<account> myfind= finduser(username3);
        if(myfind.empty()) {
            return -1;
        }
        username tmpuser(username3);

        if(loginmembers.find(tmpuser.hashing)==loginmembers.end())return -1;
        else {
            loginmembers.erase(loginmembers.find(tmpuser.hashing));
            return 1;
        }
    }
public:

};

#endif //UNTITLED97_USER_H
