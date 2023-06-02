#ifndef TOKENSCANNER_H
#define TOKENSCANNER_H
#include <string>
#include <cstring>
#include <iostream>
#include "vector.h"
#include <cstdio>
class Tokenscanner
{
private:
    std::string inputline;
    int p=0;
public:
    ~Tokenscanner(){}
    void setInput(const std::string &s){
        inputline=s;
        p=0;
    }
    void setInput(const char *s){
        inputline=s;
        p=0;
    }
    std::string nextToken(){
        int i=p;
        if(inputline[p]=='\0')return "";
        while(inputline[p]==' '){i++;p++;}
        while(inputline[p]!=' ' && inputline[p]!='\0'){p++;}
        return inputline.substr(i,p-i);
    }
    int check_num(const std::string &s){
        int ans=0;
        for(int i=0;i<s.size();i++)ans=ans*10+s[i]-'0';
        return ans;
    }
};

#endif
