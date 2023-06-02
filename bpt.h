#ifndef DATABASE
#define DATABASE
#define blocks 1024
#define half blocks/2
#define downhald half-1
#define downdownhald half-2

#include <exception>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <fstream>
#include "utility.h"
#include "vector.h"
#include "stack.h"
template<class KEEE,class T>
class oprbpt
{
public:
    class datapair{
    public:
        KEEE first;
        T second;
        datapair(const KEEE &x1,const T &x2):first(x1),second(x2){
        }
        friend bool operator == (const datapair &x1,const datapair &x2){
            return x1.first==x2.first&&x1.second==x2.second;
        }
        friend bool operator != (const datapair &x1,const datapair &x2){
            return !(x1==x2);
        }
        friend bool operator < (const datapair &x1,const datapair &x2){
            return x1.first<x2.first||(x1.first==x2.first&& x1.second<x2.second);
        }
        friend bool operator > (const datapair &x1,const datapair &x2){
            return x1.first>x2.first||(x1.first==x2.first&& x1.second>x2.second);
        }
        friend bool operator >= (const datapair &x1,const datapair &x2){
            return x1>x2||x1==x2;
        }
        friend bool operator <= (const datapair &x1,const datapair &x2){
            return x1<x2||x1==x2;
        }
        datapair operator = (const datapair &x){
            first=x.first;
            second=x.second;
            return *this;
        }
        datapair()=default;
        ~datapair(){
            second.~T();
        }
    };
    class head
    {
    public:

        int headroot=1;
        int blocknum=1;
        head()=default;
        head(int x1,int x2):headroot(x1),blocknum(x2){}
        ~head(){
            headroot=1;
            blocknum=1;
        }
    };
    enum nodetype{index,leaf};
    std::fstream file;
    head heading;
    int sznd=sizeof(node);
    int szhding=sizeof(head);
    seqStack<int>stck;
    class node
    {
    public:

        nodetype type=leaf;
        int pos_of_fa=0;
        int now_num=0;
        int edge[blocks+1];
        datapair value[blocks];
        int rightblock=0,leftblock=0;
        node operator=(const node &other){
            type=other.type;
            pos_of_fa=other.pos_of_fa;
            now_num=other.now_num;
            for(int i=0;i<blocks;i++){
                value[i]=other.value[i];
                edge[i]=other.edge[i];
            }
            edge[blocks]=other.edge[blocks];
            return *this;
        }
        node()=default;
        ~node()=default;
        node (int l,int r ):leftblock(l),rightblock(r){}
        node(int pos){
            head::file.seekg(0);head::file.read(reinterpret_cast<char*>(&head::heading),head::szhding);
        }
    };

    inline void gethead(head &heading){
        file.seekg(0);file.read(reinterpret_cast<char*>(&heading),szhding);
    }
    inline void writehead(head &heading){
        file.seekp(0);file.write(reinterpret_cast<char*>(&heading),szhding);
    }
    inline void getnode(node &mynode,int num){
        file.seekg(szhding+(num-1)*sznd);file.read(reinterpret_cast<char*>(&mynode),sznd);
    }
    inline void writenode(node &mynode,int num){
        file.seekp(szhding+(num-1)*sznd);file.write(reinterpret_cast<char*>(&mynode),sznd);
    }
    void create(const char *name);
    void changeroot(node &root){
        root.rightblock=0;
        root.leftblock=0;
        node rootegde;
        getnode(rootegde,root.edge[0]);
        rootegde.pos_of_fa=0;
        rootegde.leftblock=0;
        rootegde.rightblock=0;
        writenode(rootegde,root.edge[0]);
        heading.headroot=root.edge[0];
        root.edge[0]=0;
        root.edge[1]=0;
    }

    void clear() ;
    oprbpt(){}
    oprbpt(const char* name){
        std::ifstream in;
        in.open(name);
        if(!in){
            create(name);
        }
        file.open(name);
        gethead(heading);
    }
    ~oprbpt(){
        clear();
    }

    datapair searchpair(KEEE key,T val) {
        datapair pair(key,val);
        node tmp;
        int find= finddataposition(pair,heading.headroot);
        getnode(tmp,find);

    }
//
//
    sjtu::vector<T> search(KEEE key);//

    datapair *myupper_bound_to_key(datapair *first,datapair *last,const datapair &key);

    datapair *mylower_bound_to_key(datapair *first,datapair *last,const datapair &key);
//
    bool findmynode(const datapair &x,node &tmp,int &pos,int &dis);//not used yet

    int finddataposition(const datapair &pair,int num);//

    void insert_balance(int fa_pos,int son_pos,const datapair &obj);//

    void devideleaf(int pos);//

    void insert(KEEE key,T val);//

    void erase_balance_index(node &tmp,int pos,datapair delindex);

    void  erase_balance_leaf(int pos);//

    void erase(KEEE key,T val);

    node createnewblock(node &node1, int nowposition);//

    node createfather(node &node1,node &node2,int position1,int position2);//

//    void updata_father_in_erase(node &tmp, node &fa) {
//        int dis=mylower_bound(fa.value,fa.value+fa.now_num,tmp.value[1])-fa.value;
//        fa.value[dis]=tmp.value[0];
//    }
};

template<class KEEE, class T>
typename oprbpt<KEEE, T>::datapair *
oprbpt<KEEE, T>::mylower_bound_to_key(oprbpt::datapair *first, oprbpt::datapair *last, const oprbpt::datapair& key) {
    if (first->first == last->first)return first;
    last--;
    if (key.first > last->first)return last + 1;
    while (first->first < last->first) {
        datapair *mid = first + (last - first) / 2;
        if (mid->first< key.first) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return first;
}

template<class KEEE, class T>
typename oprbpt<KEEE, T>::datapair *oprbpt<KEEE, T>::myupper_bound_to_key(oprbpt::datapair *first, oprbpt::datapair *last, const oprbpt::datapair &key) {
    if (first->first == last->first)return first;
    last--;
    if (!(key.first < last->first))return last + 1;
    while (first->first < last->first) {
        datapair *mid = first + (last - first) / 2;
        if (key.first < mid->first) {
            last = mid;
        } else {
            first = mid + 1;
        }
    } return first;
}

template<class KEEE,class T>




bool oprbpt<KEEE,T>::findmynode(const oprbpt::datapair &x, oprbpt::node &tmp,int &pos,int &dis) {
    pos= finddataposition(x,heading.headroot);
    getnode(tmp,pos);
    dis= mylower_bound(tmp.value,tmp.value+tmp.now_num,x)-tmp.value;
    if(tmp.value[dis]!=x||dis==tmp.now_num)return false;//must have"||dis==tmp.now_num"or it will get wa on oj;
    else{
        return true;
    }
}


template<class KEEE,class T>
typename oprbpt<KEEE,T>::node oprbpt<KEEE,T>::createnewblock(oprbpt::node &temp1, int nowposition) {
    if(stck.isEmpty()){
        int tmpp=stck.pop();
        node temp2(nowposition,temp1.rightblock);
        if(temp1.rightblock){
            node tmp;
            getnode(tmp,temp1.rightblock);
            tmp.leftblock=tmpp;
            writenode(tmp,temp1.rightblock);
            temp1.rightblock=tmpp;
            for(int i=0;i<half;i++)temp2.value[i]=temp1.value[half+i];
            temp2.now_num=half;
            temp1.now_num=half;
            return temp2;
        }
    }
    node temp2(nowposition,temp1.rightblock);
    if(temp1.rightblock){
        node tmp;
        getnode(tmp,temp1.rightblock);
        tmp.leftblock=heading.blocknum+1;
        writenode(tmp,temp1.rightblock);
    }
    temp1.rightblock=++heading.blocknum;
    for(int i=0;i<half;i++)temp2.value[i]=temp1.value[half+i];
    temp2.now_num=half;
    temp1.now_num=half;
    return temp2;
}

template<class KEEE,class T>
void oprbpt<KEEE,T>::erase(KEEE key, T val) {
    datapair obj(key,val);
    int pos,dis;
    node temp;
    if(!findmynode (obj,temp,pos,dis)){
        return;
    }
    //rroot
    //directly
    if(pos==heading.headroot){
        for(int i=dis;i<temp.now_num-1;i++)temp.value[i]=temp.value[i+1];
        temp.now_num--;
        writenode(temp,pos);
        return;
    }
    if(dis==0){
//            node fa;
//            node tmpp(temp);
//            getnode(fa,temp.pos_of_fa);
//            int t1=mylower_bound(fa.value,fa.value+fa.now_num,temp.value[0])-fa.value;
//            while(t1==0){
//                getnode(fa,tmpp.pos_of_fa);
//                fa.value[0]=tmpp.value[1];
//                writenode(fa,tmpp.pos_of_fa);
//                if(fa.pos_of_fa==0){
//                    break;
//                }
//                tmpp=fa;
//                getnode(fa,fa.pos_of_fa);
//                t1=mylower_bound(fa.value,fa.value+fa.now_num,tmpp.value[0])-fa.value;
//            }
//        fa.value[t1]=temp.value[1];
//        writenode(fa,temp.pos_of_fa);


        node fa;
        node tmpp(temp);
        getnode(fa,temp.pos_of_fa);
        int dis2=mylower_bound(fa.value,fa.value+fa.now_num,temp.value[0])-fa.value;
        while(dis2==0&&fa.value[0]!=temp.value[0]){
            tmpp=fa;
            if(tmpp.pos_of_fa){
                getnode(fa,tmpp.pos_of_fa);
                dis2=mylower_bound(fa.value,fa.value+fa.now_num,temp.value[0])-fa.value;
            }
            else{
                for(int i=dis2;i<temp.now_num-1;i++)temp.value[i]=temp.value[i+1];
                temp.now_num--;
                writenode(temp,pos);
                if(temp.now_num<downhald) erase_balance_leaf(pos);
                return;
            }
        }
        fa.value[dis2]=temp.value[1];
        writenode(fa,tmpp.pos_of_fa);
    }
    for(int i=dis;i<temp.now_num-1;i++)temp.value[i]=temp.value[i+1];
    temp.now_num--;
    writenode(temp,pos);
    if(temp.now_num<downhald) erase_balance_leaf(pos);
}



template<class KEEE,class T>
void oprbpt<KEEE,T>:: erase_balance_leaf(int pos) {
    node tmp,tmp_left,tmp_right;
    getnode(tmp,pos);
    node tmp_fa;
    getnode(tmp_fa,tmp.pos_of_fa);

    if(!tmp.leftblock){
        getnode(tmp_right,tmp.rightblock);
        if(tmp_right.now_num>downhald){
            tmp.value[downdownhald]=tmp_right.value[0];
            for(int i=0;i<tmp_right.now_num-1;i++)tmp_right.value[i]=tmp_right.value[i+1];
            tmp_right.now_num--;
            tmp.now_num++;
            int dis=mylower_bound(tmp_fa.value,tmp_fa.value+tmp_fa.now_num,tmp.value[downdownhald])-tmp_fa.value;
            tmp_fa.value[dis]=tmp_right.value[0];
            writenode(tmp,pos);
            writenode(tmp_right,tmp.rightblock);
            writenode(tmp_fa,tmp.pos_of_fa);
            return;
        }
        else{
            for(int i=downdownhald;i<blocks-3;i++)
                tmp.value[i]=tmp_right.value[i-(downdownhald)];
            stck.push(tmp.rightblock);
            tmp.rightblock=tmp_right.rightblock;
            if(tmp.rightblock){
                node tmp2;
                getnode(tmp2,tmp.rightblock);
                tmp2.leftblock=pos;
                writenode(tmp2,tmp.rightblock);
            }
            tmp.now_num=blocks-3;
            writenode(tmp,pos);
            erase_balance_index(tmp_fa,tmp.pos_of_fa,tmp_right.value[0]);
        }
        return;
    }
    else if(!tmp.rightblock){
        getnode(tmp_left,tmp.leftblock);
        if(tmp_left.now_num>downhald){
            datapair tmpdata(tmp_left.value[tmp_left.now_num-1]);
            for(int i=tmp.now_num-1;i>=0;i--)tmp.value[i+1]=tmp.value[i];
            tmp.value[0]=tmpdata;
            tmp_left.now_num--;
            tmp.now_num++;
            //then updata father
//            updata_father_in_erase(tmp,tmp_fa);
//no neccessary to use function

            int dis=mylower_bound(tmp_fa.value,tmp_fa.value+tmp_fa.now_num,tmp.value[1])-tmp_fa.value;
            //it is the lower bound !!
            //not upper!
            tmp_fa.value[dis]=tmp.value[0];
            writenode(tmp,pos);
            writenode(tmp_left,tmp.leftblock);
            writenode(tmp_fa,tmp.pos_of_fa);
            return;//over
        }
        else{
            for(int i=downhald;i<blocks-3;i++) {
                tmp_left.value[i] = tmp.value[i - downhald];
            }
            stck.push(tmp_left.rightblock);
            tmp_left.rightblock=tmp.rightblock;
            if(tmp.rightblock){
                node tmp2;
                getnode(tmp2,tmp.rightblock);
                tmp2.leftblock=tmp.leftblock;
                writenode(tmp2,tmp.rightblock);
            }
            tmp_left.now_num=blocks-3;
            writenode(tmp_left,tmp.leftblock);
            node leftfa;
            getnode(leftfa,tmp_left.pos_of_fa);
            erase_balance_index(leftfa,tmp_left.pos_of_fa,tmp.value[0]);
            return;
        }
    }
    else {
        ////    merge into left
//    for(int i=downhald;i<blocks-3;i++) {
//                    tmp_left.value[i] = temp.value[i - downhald];
//                }
//                temp_left.rightblock=temp.rightblock;
//                if(temp.rightblock){
//                    node tmp2;
//                    getnode(tmp2,temp.rightblock);
//                    tmp2.leftblock=temp.leftblock;
//                    writenode(tmp2,temp.rightblock);
//                }
//                temp_left.now_num=blocks-3;
//                writenode(temp_left,temp.leftblock);
//                erase_balance_index(temp_left.pos_of_fa,temp.value[0]);
//                return;
//
//    //merge into right
//    //for(int i=downdownhald;i<blocks-3;i++)
//    //                temp.value[i]=temp_right.value[i-(downdownhald)];
//    //            temp.rightblock=temp_right.rightblock;
//    //            if(temp.rightblock){
//    //                node tmp2;
//    //                getnode(tmp2,temp.rightblock);
//    //                tmp2.leftblock=pos;
//    //                writenode(tmp2,temp.rightblock);
//    //            }
//    //            temp.now_num=size_of_block-3;
//    //            writenode(temp,pos);
//    //            erase_balance_index(temp.pos_of_fa,temp_right.value[0]);
////    for(int i=downdownhald;i<size_of_block-3;i++)
////        temp.value[i]=temp_right.value[i-(downdownhald)];
////    temp.rightblock=temp_right.rightblock;
////    updateleft(temp.rightblock,pos);
////    temp.now_num=size_of_block-3;
////    writenode(temp,pos);
////    erase_balance_index(temp.pos_of_fa,temp_right.value[0]);
        getnode(tmp_left,tmp.leftblock);
        getnode(tmp_right,tmp.rightblock);
        if(tmp_left.pos_of_fa==tmp.pos_of_fa){
            if(tmp_left.now_num>downhald){
                datapair tmpdata(tmp_left.value[tmp_left.now_num-1]);
                for(int i=tmp.now_num-1;i>=0;i--)tmp.value[i+1]=tmp.value[i];
                tmp.value[0]=tmpdata;
                tmp_left.now_num--;
                tmp.now_num++;
                //then updata father
//            updata_father_in_erase(tmp,tmp_fa);
//no neccessary to use function

                int dis=mylower_bound(tmp_fa.value,tmp_fa.value+tmp_fa.now_num,tmp.value[1])-tmp_fa.value;
                //it is the lower bound !!
                //not upper!
                tmp_fa.value[dis]=tmp.value[0];
                writenode(tmp,pos);
                writenode(tmp_left,tmp.leftblock);
                writenode(tmp_fa,tmp.pos_of_fa);
                return;//over
            }
            else{
                for(int i=downhald;i<blocks-3;i++) {
                    tmp_left.value[i] = tmp.value[i - downhald];
                }
                stck.push(tmp_left.rightblock);
                tmp_left.rightblock=tmp.rightblock;
                if(tmp.rightblock){
                    node tmp2;
                    getnode(tmp2,tmp.rightblock);
                    tmp2.leftblock=tmp.leftblock;
                    writenode(tmp2,tmp.rightblock);
                }
                tmp_left.now_num=blocks-3;
                writenode(tmp_left,tmp.leftblock);
                node leftfa;
                getnode(leftfa,tmp_left.pos_of_fa);
                erase_balance_index(leftfa,tmp_left.pos_of_fa,tmp.value[0]);
                return;
            }
        }
        else{
            if(tmp_right.now_num>downhald){
                tmp.value[downdownhald]=tmp_right.value[0];
                for(int i=0;i<tmp_right.now_num-1;i++)tmp_right.value[i]=tmp_right.value[i+1];
                tmp_right.now_num--;
                tmp.now_num++;
                int dis=mylower_bound(tmp_fa.value,tmp_fa.value+tmp_fa.now_num,tmp.value[downdownhald])-tmp_fa.value;
                tmp_fa.value[dis]=tmp_right.value[0];
                writenode(tmp,pos);
                writenode(tmp_right,tmp.rightblock);
                writenode(tmp_fa,tmp.pos_of_fa);
                return;
            }
            else{
                for(int i=downdownhald;i<blocks-3;i++)
                    tmp.value[i]=tmp_right.value[i-(downdownhald)];
                stck.push(tmp.rightblock);
                tmp.rightblock=tmp_right.rightblock;
                if(tmp.rightblock){
                    node tmp2;
                    getnode(tmp2,tmp.rightblock);
                    tmp2.leftblock=pos;
                    writenode(tmp2,tmp.rightblock);
                }
                tmp.now_num=blocks-3;
                writenode(tmp,pos);
                erase_balance_index(tmp_fa,tmp.pos_of_fa,tmp_right.value[0]);
            }
            return;
        }
    }

//    if(temp.leftblock)getnode(temp_left,temp.leftblock);
//    if(temp.rightblock)getnode(temp_right,temp.rightblock);
//    if(temp.leftblock==0||temp_left.pos_of_fa!=temp.pos_of_fa){
//        getnode(temp_right,temp.rightblock);
//        if(temp_right.now_num>downhald){
//            temp.value[downdownhald]=temp_right.value[0];
//            for(int i=0;i<temp_right.now_num-1;i++)temp_right.value[i]=temp_right.value[i+1];
//            temp_right.now_num--;
//            temp.now_num++;
//            int dis=mylower_bound(temp_fa.value,temp_fa.value+temp_fa.now_num,temp.value[downdownhald])-temp_fa.value;
//            temp_fa.value[dis]=temp_right.value[0];
//            writenode(temp,pos);
//            writenode(temp_right,temp.rightblock);
//            writenode(temp_fa,temp.pos_of_fa);
//            return;
//        }
//        else{
//            for(int i=downdownhald;i<blocks-3;i++)
//                temp.value[i]=temp_right.value[i-(downdownhald)];
//            temp.rightblock=temp_right.rightblock;
//            if(temp.rightblock){
//                node tmp2;
//                getnode(tmp2,temp.rightblock);
//                tmp2.leftblock=pos;
//                writenode(tmp2,temp.rightblock);
//            }
//            temp.now_num=size_of_block-3;
//            writenode(temp,pos);
//            erase_balance_index(temp.pos_of_fa,temp_right.value[0]);
//        }
//        return;
//    }
//    if(temp.rightblock==0||temp_right.pos_of_fa!=temp.pos_of_fa){
//        if(temp_left.now_num>downhald){
//            datapair tmpdata(temp_left.value[temp_left.now_num-1]);
//            for(int i=temp.now_num-1;i>=0;i--)temp.value[i+1]=temp.value[i];
//            temp.value[0]=tmpdata;
//            temp_left.now_num--;
//            temp.now_num++;
//            //then updata father
////            updata_father_in_erase(temp,temp_fa);
////no neccessary to use function
//
//            int dis=mylower_bound(temp_fa.value,temp_fa.value+temp_fa.now_num,temp.value[1])-temp_fa.value;
//            //it is the lower bound !!
//            //not upper!
//            temp_fa.value[dis]=temp.value[0];
//            writenode(temp,pos);
//            writenode(temp_left,temp.leftblock);
//            writenode(temp_fa,temp.pos_of_fa);
//            return;//over
//        }
//        else{
//            for(int i=downhald;i<size_of_block-3;i++) {
//                temp_left.value[i] = temp.value[i - downhald];
//            }
//            temp_left.rightblock=temp.rightblock;
//            if(temp.rightblock){
//                node tmp2;
//                getnode(tmp2,temp.rightblock);
//                tmp2.leftblock=temp.leftblock;
//                writenode(tmp2,temp.rightblock);
//            }
//            temp_left.now_num=size_of_block-3;
//            writenode(temp_left,temp.leftblock);
//            erase_balance_index(temp_left.pos_of_fa,temp.value[0]);
//            return;
//        }
//
//    }
////then deal with another situation
////    getnode(temp_left,temp.leftblock);
////    getnode(temp_right,temp.rightblock);
//    if(temp_left.now_num>downhald){
////        for(int i=temp.now_num;i>0;i--)temp.value[i]=temp.value[i-1];
////        temp.value[0]=temp_left.value[temp_left.now_num-1];
////        temp_left.now_num--;
////        temp.now_num++;
////        node temp_fa;
////        getnode(temp_fa,temp.pos_of_fa);
////        int dis=myupper_bound(temp_fa.value,temp_fa.value+temp_fa.now_num,
////                              temp.value[0])-temp_fa.value;
////        temp_fa.value[dis]=temp.value[0];
////        writenode(temp,pos);
////        writenode(temp_left,temp.leftblock);
////        writenode(temp_fa,temp.pos_of_fa);
////        return;
//        datapair tmpdata(temp_left.value[temp_left.now_num-1]);
//                    for(int i=temp.now_num-1;i>=0;i--)temp.value[i+1]=temp.value[i];
//                    temp.value[0]=tmpdata;
//                    temp_left.now_num--;
//                    temp.now_num++;
//                    //then updata father
//        //            updata_father_in_erase(temp,temp_fa);
//        //no neccessary to use function
//
//                    int dis=mylower_bound(temp_fa.value,temp_fa.value+temp_fa.now_num,temp.value[1])-temp_fa.value;
//
//        //it is the lower bound !!
//        //not upper!
//
//
//                    temp_fa.value[dis]=temp.value[0];
//                    writenode(temp,pos);
//                    writenode(temp_left,temp.leftblock);
//                    writenode(temp_fa,temp.pos_of_fa);
//                    return;//over
//
//        //temp.value[downdownhald]=temp_right.value[0];
//        //            for(int i=0;i<temp_right.now_num-1;i++)temp_right.value[i]=temp_right.value[i+1];
//        //            temp_right.now_num--;
//        //            temp.now_num++;
//        //            int dis=mylower_bound(temp_fa.value,temp_fa.value+temp_fa.now_num,temp.value[downdownhald])-temp_fa.value;
//        //            temp_fa.value[dis]=temp_right.value[0];//修改
//        //            writenode(temp,pos);
//        //            writenode(temp_right,temp.rightblock);
//        //            writenode(temp_fa,temp.pos_of_fa);
//        //            return;
//    }
//    if(temp_right.now_num>downhald){
//        temp.value[downdownhald]=temp_right.value[0];
//        for(int i=0;i<temp_right.now_num-1;i++)temp_right.value[i]=temp_right.value[i+1];
//        temp_right.now_num--;
//        temp.now_num++;
//        int dis=mylower_bound(temp_fa.value,temp_fa.value+temp_fa.now_num,temp.value[downdownhald])-temp_fa.value;
//        temp_fa.value[dis]=temp_right.value[0];//修改
//        writenode(temp,pos);
//        writenode(temp_right,temp.rightblock);
//        writenode(temp_fa,temp.pos_of_fa);
//        return;
//    }
////    merge into left
//    for(int i=downhald;i<size_of_block-3;i++) {
//                    temp_left.value[i] = temp.value[i - downhald];
//                }
//                temp_left.rightblock=temp.rightblock;
//                if(temp.rightblock){
//                    node tmp2;
//                    getnode(tmp2,temp.rightblock);
//                    tmp2.leftblock=temp.leftblock;
//                    writenode(tmp2,temp.rightblock);
//                }
//                temp_left.now_num=size_of_block-3;
//                writenode(temp_left,temp.leftblock);
//                erase_balance_index(temp_left.pos_of_fa,temp.value[0]);
//                return;
//
//    //merge into right
//    //for(int i=downdownhald;i<size_of_block-3;i++)
//    //                temp.value[i]=temp_right.value[i-(downdownhald)];
//    //            temp.rightblock=temp_right.rightblock;
//    //            if(temp.rightblock){
//    //                node tmp2;
//    //                getnode(tmp2,temp.rightblock);
//    //                tmp2.leftblock=pos;
//    //                writenode(tmp2,temp.rightblock);
//    //            }
//    //            temp.now_num=size_of_block-3;
//    //            writenode(temp,pos);
//    //            erase_balance_index(temp.pos_of_fa,temp_right.value[0]);
////    for(int i=downdownhald;i<size_of_block-3;i++)
////        temp.value[i]=temp_right.value[i-(downdownhald)];
////    temp.rightblock=temp_right.rightblock;
////    updateleft(temp.rightblock,pos);
////    temp.now_num=size_of_block-3;
////    writenode(temp,pos);
////    erase_balance_index(temp.pos_of_fa,temp_right.value[0]);
}

template<class KEEE,class T>
void oprbpt<KEEE,T>::erase_balance_index(node &tmp,int pos, oprbpt::datapair delindex) {
    node ll;
    node l;
    //root situation

    if(pos==heading.headroot) {
        if (tmp.now_num == 1) {node ll;
            int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
            changeroot(tmp);
            tmp.now_num--;
            writenode(tmp,pos);
            return;
        }
        else {
            int dis = mylower_bound(tmp.value, tmp.value + tmp.now_num, delindex) - tmp.value;
            for (int i = dis; i < tmp.now_num - 1; i++) {
                tmp.value[i] = tmp.value[i + 1];tmp.edge[i+1] = tmp.edge[i + 2];
            }
            tmp.now_num--;
            writenode(tmp, pos);
            return;
        }
    }
    int dis=mylower_bound(tmp.value,tmp.value+tmp.now_num,delindex)-tmp.value;
    for(int i=dis;i<tmp.now_num-1;i++) {
        tmp.value[i] = tmp.value[i + 1];
        tmp.edge[i + 1] = tmp.edge[i + 2];
    }
    tmp.now_num--;
    if(tmp.now_num>=downhald){
        writenode(tmp,pos);
        return;
    }
    else{
        //it is not the root so it must have fa
        node fa;node ll;
        node l;
        int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
        getnode(fa,tmp.pos_of_fa);
        int tmpdis=myupper_bound(fa.value,fa.value+fa.now_num,tmp.value[0])-fa.value;
        if(tmpdis!=fa.now_num){
            node righttmp;
            int posr=fa.edge[tmpdis+1];node ll;
            int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
//            getnode(righttmp,tmp.rightblock);
//            while(righttmp.now_num==0){
//                getnode(righttmp,righttmp.rightblock);
//            }
//            tle!!
            getnode(righttmp,fa.edge[tmpdis+1]);
            if(righttmp.now_num>downhald){
                tmp.value[downdownhald]=fa.value[tmpdis];
                tmp.edge[downhald]=righttmp.edge[0];node ll;
                int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
//                fa.value[tmpdis]=righttmp.edge[0];
                node tmpupdate;
                getnode(tmpupdate,righttmp.edge[0]);
                tmpupdate.pos_of_fa=pos;
                writenode(tmpupdate,righttmp.edge[0]);
//                updatefather(righttmp.edge[0],pos);
                //getnode(temp,pos);
                //    temp.pos_of_fa=fa_pos;
                //    writenode(temp,pos);

                fa.value[tmpdis]=righttmp.value[0];
                for(int i=0;i<righttmp.now_num-1;i++){
                    righttmp.value[i]=righttmp.value[i+1];
                    righttmp.edge[i]=righttmp.edge[i+1];
                }
                //fa.value[tmpdis]=righttmp.value[0];
                righttmp.edge[righttmp.now_num-1]=righttmp.edge[righttmp.now_num];
                righttmp.now_num--;node ll3;
                int dis2=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
                tmp.now_num++;
                writenode(tmp,pos);
                writenode(righttmp,fa.edge[tmpdis+1]);
                writenode(fa,tmp.pos_of_fa);
            }
            else{
//                merge(pos,tmp,righttmp,fa,tmpdis);
                tmp.value[tmp.now_num]=fa.value[tmpdis];
                tmp.now_num++;
                for(int i=0;i<righttmp.now_num;i++){
                    tmp.value[tmp.now_num+i]=righttmp.value[i];
                    tmp.edge[tmp.now_num+i]=righttmp.edge[i];
                    node temp;node ll;
                    int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
//                    updatefather(righttmp.edge[i],pos);
                    node tempp;
                    getnode(tempp,righttmp.edge[i]);
                    tempp.pos_of_fa=pos;
                    writenode(tempp,righttmp.edge[i]);
                }
                tmp.now_num+=righttmp.now_num;
                tmp.edge[tmp.now_num]=righttmp.edge[righttmp.now_num];
//                updatefather(righttmp.edge[righttmp.now_num],pos);
                node tempp;
                getnode(tempp,righttmp.edge[righttmp.now_num]);
                tempp.pos_of_fa=pos;
                writenode(tempp,righttmp.edge[righttmp.now_num]);
                writenode(tmp,pos);
                if(righttmp.leftblock){
                    node l;
                    getnode(l,righttmp.leftblock);
                    if(l.rightblock==posr){
                        l.rightblock=0;node ll;
                        int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
                    }
                    //                updatefather(righttmp.edge[0],pos);
                    //getnode(temp,pos);
                    //    temp.pos_of_fa=fa_pos;
                    //    writenode(temp,pos);
                    writenode(l,righttmp.leftblock);
                }
                if(righttmp.rightblock){
                    node r;
                    getnode(r,righttmp.rightblock);
                    if(r.leftblock==posr){
                        r.rightblock=0;node ll;
                        int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
                    }
                    //                updatefather(righttmp.edge[0],pos);
                    //getnode(temp,pos);
                    //    temp.pos_of_fa=fa_pos;
                    //    writenode(temp,pos);
                    writenode(r,righttmp.rightblock);
                }
                erase_balance_index(fa,tmp.pos_of_fa,fa.value[tmpdis]);
            }
        }
        else{
            node lefttmp;
            int posl=fa.now_num-1;node ll;
            int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
            getnode(lefttmp,fa.edge[fa.now_num-1]);
            if(lefttmp.now_num>=half){
                for(int i=tmp.now_num;i>0;i--){
                    tmp.value[i]=tmp.value[i-1];
                    tmp.edge[i+1]=tmp.edge[i];
                }
                tmp.edge[1]=tmp.edge[0];
                tmp.edge[0]=lefttmp.edge[lefttmp.now_num];
                tmp.value[0]=fa.value[fa.now_num-1];
                // node xx;
                // getnode(xx,temp.edge[0]);
                // xx.pos_of_fa=pos;
                // writenode(xx,temp.edge[0]);
                node tmpupdate;node ll;
                int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
                getnode(tmpupdate,tmp.edge[0]);
                tmpupdate.pos_of_fa=pos;
                writenode(tmpupdate,tmp.edge[0]);

                tmp.now_num++;
                lefttmp.now_num--;
                fa.value[fa.now_num-1]=lefttmp.value[lefttmp.now_num];
                writenode(tmp,pos);
                writenode(lefttmp,fa.edge[fa.now_num-1]);
                writenode(fa,tmp.pos_of_fa);
            }
            else{

                lefttmp.value[lefttmp.now_num]=fa.value[fa.now_num-1];
                lefttmp.now_num++;
                for(int i=0;i<tmp.now_num;i++){
                    lefttmp.value[lefttmp.now_num+i]=tmp.value[i];
                    lefttmp.edge[lefttmp.now_num+i]=tmp.edge[i];
                    node temp;
//                        updatefather(tmp.edge[i],fa.edge[fa.now_num-1]);
                    node tempp;node ll;
                    int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
                    getnode(tempp,tmp.edge[i]);
                    tempp.pos_of_fa=fa.edge[fa.now_num-1];
                    writenode(tempp,tmp.edge[i]);
                }
                lefttmp.now_num+=tmp.now_num;
                lefttmp.edge[lefttmp.now_num]=tmp.edge[tmp.now_num];
                node tmp2;
                getnode(tmp2,tmp.edge[tmp.now_num]);
                tmp2.pos_of_fa=fa.edge[fa.now_num-1];
                writenode(tmp2,tmp.edge[tmp.now_num]);
                writenode(lefttmp,fa.edge[fa.now_num-1]);
                if(lefttmp.leftblock){
                    node l;
                    node ll;
                    int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
                    getnode(l,lefttmp.leftblock);
                    if(l.rightblock==posl){
                        l.rightblock=0;
                    }
                    writenode(l,lefttmp.leftblock);
                }
                if(lefttmp.rightblock){
                    node r;
                    node ll;
                    int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,l.value[0])-tmp.value;
                    getnode(r,lefttmp.rightblock);
                    if(r.leftblock==posl){
                        r.leftblock=0;
                    }
                    writenode(r,lefttmp.rightblock);
                    head i;
                }
                erase_balance_index(fa,tmp.pos_of_fa,fa.value[fa.now_num-1]);

            }
        }
    }

}


template<class KEEE,class T>
void oprbpt<KEEE,T>::insert(KEEE key, T val) {
//    node tmp;
//    getnode(tmp,heading.headroot);
//    if(tmp.type!=leaf)tmp= findmynode(datapair(key,val),tmp);
    int nowposition= finddataposition(datapair(key,val),heading.headroot);
    node tmp;
    getnode(tmp,nowposition);
    int dis=mylower_bound(tmp.value,tmp.value+tmp.now_num,datapair(key,val))-tmp.value;
    for(int i=tmp.now_num;i>dis;i--){
        tmp.value[i]=tmp.value[i-1];
    }
    tmp.value[dis]=datapair(key,val);
    tmp.now_num++;
    writenode(tmp,nowposition);
    if(tmp.now_num==blocks)devideleaf(nowposition);
}

template<class KEEE,class T>
sjtu::vector<T> oprbpt<KEEE,T>::search(KEEE key) {
    int num=finddataposition(datapair(key,T()),heading.headroot);
    node tmp;
    getnode(tmp,num);
    int dis=mylower_bound_to_key(tmp.value,tmp.value+tmp.now_num,datapair(key,T()))-tmp.value;
    if(dis==tmp.now_num){
        if(!tmp.rightblock)return sjtu::vector<T>();
        else{
            node tmp2;
            getnode(tmp2,tmp.rightblock);
            if(tmp2.value[0].first!=key)return sjtu::vector<T>();
            else{
                sjtu::vector<T> myfind;
                while(1) {
                    dis= myupper_bound_to_key(tmp2.value,tmp2.value+tmp2.now_num,datapair(key,T()))-tmp2.value;
                    if(dis<tmp2.now_num){
                        for (int i = 0; i < dis; i++) {
                            myfind.push_back(tmp2.value[i].second);
                        }
                        return myfind;
                    }
//                    if(dis==0){
//                        if(key==tmp2.value[0].first){
//                            myfind.push_back(tmp2.value[0].second);return myfind;
//                        }
//                        return myfind;
//                    }
                    for (int i = 0; i < tmp2.now_num; i++) {
                        myfind.push_back(tmp2.value[i].second);
                    }
                    tmp=tmp2;
                    int tt=tmp2.rightblock;
                    if(tt==0)return myfind;//this is important and kill me many times!!
                    getnode(tmp2,tt);
                    if(tmp2.value[0].first!=key)return myfind;
                    else continue;
                }
            }
        }
    }//using upperboundtokey may have bug;

        //below is the safe method

        //if(dis==tmp.now_num){
        //        if(!tmp.rightblock)return sjtu::vector<T>();
        //        else{
        //            node tmp2;
        //            getnode(tmp2,tmp.rightblock);
        //            if(tmp2.value[0].first!=key)return sjtu::vector<T>();
        //            else{
        //                sjtu::vector<T> myfind;
        //                while(1) {
        //                    for (int i = 0; i < tmp2.now_num; i++) {
        //                        if (tmp2.value[i].first==key)myfind.push_back(tmp2.value[i].second);
        //                        else return myfind;
        //                    }
        //                    tmp=tmp2;
        //                    int tt=tmp2.rightblock;
        //                    if(tt==0)return myfind;//this is important and kill me many times!!
        //                    getnode(tmp2,tt);
        //                    if(tmp2.value[0].first!=key)return myfind;
        //                    else continue;
        //                }
        //            }
        //        }
        //    }


    else{
        sjtu::vector<T> myfind;
        for (int i = dis; i < tmp.now_num; i++) {
            if (tmp.value[i].first==key)myfind.push_back(tmp.value[i].second);
            else return myfind;
        }
        if(tmp.rightblock==0)return myfind;
        node tmp2;
        getnode(tmp2,tmp.rightblock);
        if(tmp2.value[0].first!=key)return myfind;
        while(1) {
            dis= myupper_bound_to_key(tmp2.value,tmp2.value+tmp2.now_num,datapair(key,T()))-tmp2.value;
            if(dis<tmp2.now_num&&dis!=0){//through test it must have the condition dis!=0 because it may be an empty node!!!
                for (int i = 0; i < dis; i++) {
                    myfind.push_back(tmp2.value[i].second);
                }
                return myfind;
            }
            if(dis==0){
                for (int i = 0; i < tmp2.now_num; i++) {
                    myfind.push_back(tmp2.value[i].second);
                }
                tmp = tmp2;
                int tt = tmp2.rightblock;
                if (tt == 0)return myfind;//this is important and kill me many times!!
                getnode(tmp2, tt);
                if (tmp2.value[0].first != key)return myfind;
                else continue;
            }
            else {
                for (int i = 0; i < tmp2.now_num; i++) {
                    myfind.push_back(tmp2.value[i].second);
                }
                tmp = tmp2;
                int tt = tmp2.rightblock;
                if (tt == 0)return myfind;//this is important and kill me many times!!
                getnode(tmp2, tt);
                if (tmp2.value[0].first != key)return myfind;
                else continue;
            }
        }
    }
}
template<class KEEE,class T>
typename oprbpt<KEEE,T>::node oprbpt<KEEE,T>::createfather(oprbpt::node &temp1, oprbpt::node &temp2, int p1,int p2) {
    node father;
    father.edge[0]=p1;
    father.edge[1]=p2;
    temp1.pos_of_fa=++heading.blocknum;
    temp2.pos_of_fa=heading.blocknum;
    father.value[0]=temp2.value[0];
    father.now_num=1;father.type=index;
    writenode(temp1,p1);
    writenode(temp2,p2);
    writenode(father,heading.blocknum);
    heading.headroot=heading.blocknum;
    return father;
}
template<class KEEE,class T>
void oprbpt<KEEE,T>::devideleaf(int nowposition) {
    node temp1;
    getnode(temp1, nowposition);
//    node temp2 = createnewblock(temp1,nowposition);
    if (stck.isEmpty()) {
        int tmpp = stck.pop();
        node erase,e1,e2;
        getnode(erase,tmpp);
        if(erase.leftblock){
            getnode(e1,erase.leftblock);
            if(e1.rightblock==tmpp)e1.rightblock=0;

        }
        if(erase.rightblock){
            getnode(e2,erase.rightblock);
            if(e2.leftblock==tmpp)e2.leftblock=0;

        }
        node temp2(nowposition, temp1.rightblock);
        if (temp1.rightblock) {
            node tmp;
            getnode(tmp, temp1.rightblock);
            tmp.leftblock = tmpp;
            writenode(tmp, temp1.rightblock);
            temp1.rightblock = tmpp;
            for (int i = 0; i < half; i++)temp2.value[i] = temp1.value[half + i];
            temp2.now_num = half;
            temp1.now_num = half;
        }
        if (temp1.pos_of_fa == 0) {
            node father;
            father.edge[0]=nowposition;
            father.edge[1]=tmpp;
            temp1.pos_of_fa=++heading.blocknum;
            temp2.pos_of_fa=heading.blocknum;
            father.value[0]=temp2.value[0];
            father.now_num=1;father.type=index;
            writenode(temp1,nowposition);
            writenode(temp2,tmpp);
            writenode(father,heading.blocknum);
            heading.headroot=heading.blocknum;
//            createfather(temp1, temp2, nowposition, tmpp );
        } else {
            temp2.pos_of_fa = temp1.pos_of_fa;
            writenode(temp1, nowposition);
            writenode(temp2, tmpp );
            insert_balance(temp1.pos_of_fa, tmpp, temp2.value[0]);
        }
        return;
    }
    node temp2(nowposition, temp1.rightblock);
    if (temp1.rightblock) {
        node tmp;
        getnode(tmp, temp1.rightblock);
        tmp.leftblock = heading.blocknum + 1;
        writenode(tmp, temp1.rightblock);
    }
    temp1.rightblock = ++heading.blocknum;
    for (int i = 0; i < half; i++)temp2.value[i] = temp1.value[half + i];
    temp2.now_num = half;
    temp1.now_num = half;

    if (temp1.pos_of_fa == 0) {
        createfather(temp1, temp2, nowposition, heading.blocknum);
    } else {
        temp2.pos_of_fa = temp1.pos_of_fa;
        writenode(temp1, nowposition);
        writenode(temp2, heading.blocknum);
        insert_balance(temp1.pos_of_fa, heading.blocknum, temp2.value[0]);
    }
}

template<class KEEE,class T>
void oprbpt<KEEE,T>::insert_balance(int fa_pos, int son_pos, const oprbpt::datapair &obj) {
    node father;
    getnode(father,fa_pos);
    int t= myupper_bound(father.value,father.value+father.now_num,obj)-father.value;
    for(int i=father.now_num;i>t;i--){
        father.value[i]=father.value[i-1];
        father.edge[i+1]=father.edge[i];
    }
    father.value[t]=obj;father.edge[t+1]=son_pos;
    father.now_num++;
    writenode(father,fa_pos);
    if(father.now_num==blocks){
        heading.blocknum++;
        node newindex;
        newindex.type=index;
        newindex.now_num=half;
        node tmp;
        for(int i=half;i<blocks;i++){
            newindex.value[i-half]=father.value[i];
            newindex.edge[i-half]=father.edge[i];
            getnode(tmp,father.edge[i]);
            tmp.pos_of_fa=heading.blocknum;
            writenode(tmp,father.edge[i]);
        }
        newindex.edge[half]=father.edge[blocks];
        getnode(tmp,father.edge[blocks]);
        tmp.pos_of_fa=heading.blocknum;
        writenode(tmp,father.edge[blocks]);
        newindex.now_num=half;
        father.now_num=downhald;
        if(father.pos_of_fa==0){
            node newroot;
            newroot.edge[0]=fa_pos;
            newroot.edge[1]=heading.blocknum;
            heading.blocknum++;
            newroot.now_num=1;
            newroot.type=index;
            newroot.value[0]=father.value[downhald];
            writenode(newroot,heading.blocknum);
            newindex.pos_of_fa=heading.blocknum;
            father.pos_of_fa=heading.blocknum;
            writenode(father,fa_pos);
            writenode(newindex,heading.blocknum-1);
            heading.headroot=heading.blocknum;
        }
        else{
            newindex.pos_of_fa=father.pos_of_fa;
            writenode(newindex,heading.blocknum);
            writenode(father,fa_pos);
            insert_balance(father.pos_of_fa,heading.blocknum,father.value[downhald]);
        }
    }
}


template<class KEEE,class T>
int oprbpt<KEEE,T>::finddataposition(const oprbpt::datapair &pair, int num) {
    node temp;getnode(temp,num);
    if(temp.type==leaf)return num;
    else{
        int dis=myupper_bound(temp.value,temp.value+temp.now_num,pair)-temp.value;
        return finddataposition(pair,temp.edge[dis]);
    }
}
template<class KEEE,class T>
void oprbpt<KEEE,T>::create(const char *name) {
    std::ofstream outfile(name);
    outfile.seekp(0);
    head heading;
    outfile.write(reinterpret_cast<char*>(&heading),szhding);
    outfile.seekp(szhding);
    node mynode;
    outfile.write(reinterpret_cast<char*>(&mynode),sznd);
}
template<class KEEE,class T>
void oprbpt<KEEE,T>::clear() {
    file.seekp(0);
    writehead(heading);
    file.clear();
    file.close();
}




#include <iostream>
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
#define size_of_block 1024/(sizeof(keys)+sizeof(T))*2
template<class keys,class T>
class bpt
{
private:
    class data{
    public:
        keys key;
        T value;
        data(){}
        data(const keys &obj,const T &value_){
            key=obj;
            value=value_;
        }
        friend bool operator < (const data &obj1,const data &obj2){
            if(obj1.key<obj2.key)return true;
            if(obj1.key == obj2.key && obj1.value < obj2.value)return true;
            return false;
        }
        friend bool operator > (const data &obj1,const data &obj2){
            return obj2<obj1;
        }
        friend bool operator == (const data &obj1,const data &obj2){
            return (!(obj1<obj2))&&(!(obj2<obj1));
        }
        friend bool operator >= (const data &obj1,const data &obj2){
            return !(obj1<obj2);
        }
        friend bool operator <= (const data &obj1,const data &obj2){
            return !(obj2<obj1);
        }
    };

    std::fstream opfile;

    class start
    {
    public:
        int pos_of_root;
        int num_of_block;
        start(){
            pos_of_root=1;
            num_of_block=1;
        }
        start(int pos_of_root_,int num_of_block_)
                :pos_of_root(pos_of_root_),num_of_block(num_of_block_){}
    };
    start head;
    enum nodetype{index,leaf};
    class node
    {
    public:
        nodetype type;
        int pos_of_fa;
        int now_num;
        int edge[size_of_block+1];
        data value[size_of_block];
        int front_pos,back_pos;
        node(){
            type=leaf;
            now_num=0;
            pos_of_fa=0;
            front_pos=0;
            back_pos=0;
            memset(edge,0,sizeof(edge));
        }
    };
    void writenode(node *obj,int num);
    void writenode_(node &obj,int num);
    //LinkedHashMap节点定义
    struct Node {
        int key;
        node* value;
        Node* prev;
        Node* next;

        Node()
                : prev(nullptr), next(nullptr) {}

        Node(int k,node* v)
                : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    // 哈希表节点定义
    struct Nodes {
        int key;
        Node* value;
        Nodes* next;

        Nodes(const int& k,Node* v)
                : key(k), value(v), next(nullptr) {}
    };
    class LinkedHashMap {
    public:
        class MyUnorderedMap {
        public:
            // 构造函数
            const static size_t TableSize=1024*1024/sizeof(node);
            MyUnorderedMap() {
                table = new Nodes*[TableSize]();
            }
            // 析构函数
            ~MyUnorderedMap() {
                clear();
                delete[] table;
            }

            void insert(const int& key, const node*& value);

            void erase(const int& key);

            Node*& operator[](const int& key);

            bool contains(const int& key) const;

            size_t size() const;

            void clear();

            Nodes** table;  // 哈希表数组

            int hashFunction(const int& key) const;
        };

        LinkedHashMap();

        ~LinkedHashMap() = default;

        Node* insert(const int& key,node* value);

        node* operator[](const int& key) {
            Node* node = map[key];
            moveToHead(node);
            return node->value;
        }

        bool contains(const int& key) const;

        void clear();

        Node* head;  // 链表头节点
        Node* tail;  // 链表尾节点
        MyUnorderedMap map;  // 哈希表，用于快速查找节点
        static const size_t capacity = 1024*1024/sizeof(node);  // 容量限制

        void insertToHead(Node* node);

        void moveToHead(Node* node);

        void removeNode(Node* node);

        Node* removeTail();
    };
    LinkedHashMap map;
    //int cnt=0;
    void getstart(start &st);
    void writestart(start &st);
    void getnode(node *&obj,int num);

    int finds(const keys &key,int num);
    int find_pos(const data &obj,int num);
    void updatefather(int pos,int fa_pos);
    void updateleft(int pos,int left);
    void updateright(int pos,int right);
    void flashindex(int fa_pos,int son_pos,const data &obj);
    void devideleaf(int pos);
    bool judge(int pos,int fa,node*& temp){
        if(pos==0)return false;
        getnode(temp,pos);
        if(temp->pos_of_fa!=fa)return false;
        return true;
    }
    void merge(int pos,node* obj1,node* obj2,node* fa,int tx);
    void balanceindex(int pos,data delindex);
    void balanceleaf(int pos);
    void freshleft(int pos,const data &obj);
public:
    bpt(){}
    bpt(std::string name);
    void clear(std::string name);
    void setfile(std::string name);
    ~bpt();
    sjtu::vector<T> find(const keys &key);
    void insert(const keys &index,const T &val);
    void erase(keys key,T val);
    bool empty();
};

template<class keys, class T>
sjtu::vector<T> bpt<keys, T>::find(const keys &key) {
    int num = finds(key,head.pos_of_root);
    node* temp;
    getnode(temp,num);
    int l=0,r=temp->now_num-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(key<=temp->value[mid].key)r=mid;
        else l=mid+1;
    }
    int x=l;
    sjtu::vector<T> ans;
    if(temp->now_num==0)return ans;
    while(true){
        if(x==temp->now_num){
            if(temp->front_pos==0)break;
            getnode(temp,temp->front_pos);
            x=0;
        }
        //std::cout<<x<<'*'<<std::endl;
        if(temp->value[x].key==key)ans.push_back(temp->value[x].value);
        else if(key<temp->value[x].key)break;
        x++;
    }
    return ans;
}

template<class keys, class T>
bpt<keys, T>::~bpt() {
    writestart(head);
    for (int i = 0; i < map.map.TableSize; i++) {
        Nodes* currNode = map.map.table[i];
        while (currNode != nullptr) {
            Nodes* nextNode = currNode->next;
            writenode(currNode->value->value,currNode->value->key);
            delete currNode->value->value;
            delete currNode->value;
            delete currNode;
            currNode = nextNode;
        }
        map.map.table[i] = nullptr;
    }
    delete map.head;
    delete map.tail;
    opfile.close();
}

template<class keys, class T>
void bpt<keys, T>::setfile(std::string name) {
    std::ifstream in;
    in.open(name);
    if(!in){
        std::ofstream outfile(name);
        outfile.seekp(0);
        start t1;
        outfile.write(reinterpret_cast<char*>(&t1),sizeof(start));
        outfile.seekp(sizeof(start));
        node t2;
        outfile.write(reinterpret_cast<char*>(&t2),sizeof(node));
    }
    opfile.open(name);
    getstart(head);
}class vec_block
{
public:
    int data[100000];
    vec_block(){memset(data,0,sizeof(data));}
    vec_block(const vec_block &obj){
        for(int i=0;i<20000;i++)data[i]=obj.data[i];
    }
    vec_block operator= (const vec_block &obj){
        for(int i=0;i<20000;i++)data[i]=obj.data[i];
        return *this;
    }
};
template<class T>

class bpt2
{
public:
    std::fstream opfile;
    int max_num;
    Queue q;
    bpt2(std::string s){
        std::ifstream in;
        in.open(s);
        if(!in){
            std::ofstream outfile(s);
            outfile.seekp(0);
            int t1=1;
            outfile.write(reinterpret_cast<char*>(&t1),sizeof(int));
            vec_block tem;
            outfile.seekp(sizeof(int));
            outfile.write(reinterpret_cast<char*>(&tem),sizeof(vec_block));
        }

        opfile.open(s);
        opfile.seekg(0);
        opfile.read(reinterpret_cast<char*>(&max_num),sizeof(int));
        opfile.seekg(sizeof(int));
        vec_block temp;
        opfile.read(reinterpret_cast<char*>(&temp),sizeof(vec_block));
        q.front=nullptr;
        q.rear=nullptr;
        for(int i=0;i<20000;i++){
            if(temp.data[i]==0)break;
            q.enqueue(temp.data[i]);
        }
    }
    ~bpt2(){
        opfile.seekp(0);
        opfile.write(reinterpret_cast<char*>(&max_num),sizeof(int));
        vec_block temp;
        int cnt=-1;
        while(!q.isEmpty()){
            temp.data[++cnt]=q.getFront();
            q.dequeue();
        }
        opfile.seekp(sizeof(int));
        opfile.write(reinterpret_cast<char*>(&temp),sizeof(vec_block));
    }
    int insert(const T &obj){
        T obj_(obj);
        if(q.isEmpty()){
            opfile.seekp(sizeof(int)+sizeof(vec_block)+(max_num-1)*sizeof(T));
            opfile.write(reinterpret_cast<char*>(&obj_),sizeof(T));
            ++max_num;
            return max_num-1;
        }
        else{
            int x=q.getFront();
            q.dequeue();
            opfile.seekp(sizeof(int)+sizeof(vec_block)+(x-1)*sizeof(T));
            opfile.write(reinterpret_cast<char*>(&obj_),sizeof(T));
            return x;
        }
    }
    T find(int num){
        T temp;
        opfile.seekg(sizeof(int)+sizeof(vec_block)+(num-1)*sizeof(T));
        opfile.read(reinterpret_cast<char*>(&temp),sizeof(T));
        return temp;
    }
    void erase(int num){
        q.enqueue(num);
    }
    void clear(std::string s){
        std::ofstream file(s, std::ios::trunc);
        file.close();
        while(!q.isEmpty())q.dequeue();
        std::ifstream in;
        in.open(s);
        if(!in){
            std::ofstream outfile(s);
            outfile.seekp(0);
            int t1=1;
            outfile.write(reinterpret_cast<char*>(&t1),sizeof(int));
            vec_block tem;
            outfile.seekp(sizeof(int));
            outfile.write(reinterpret_cast<char*>(&tem),sizeof(vec_block));
        }
        opfile.open(s);
        opfile.seekg(0);
        opfile.read(reinterpret_cast<char*>(&max_num),sizeof(int));
        opfile.seekg(sizeof(int));
        vec_block temp;
        opfile.read(reinterpret_cast<char*>(&temp),sizeof(vec_block));
        q.front=nullptr;
        q.rear=nullptr;
        for(int i=0;i<100000;i++){
            if(temp.data[i]==0)break;
            q.enqueue(temp.data[i]);
        }
    }
};
template<class keys, class T>
void bpt<keys, T>::clear(std::string name) {
    std::ofstream file(name, std::ios::trunc);
    file.close();
    map.clear();
    std::ifstream in;
    in.open(name);
    if(!in){
        std::ofstream outfile(name);
        outfile.seekp(0);
        start t1;
        outfile.write(reinterpret_cast<char*>(&t1),sizeof(start));
        outfile.seekp(sizeof(start));
        node t2;
        outfile.write(reinterpret_cast<char*>(&t2),sizeof(node));
    }
    opfile.open(name);
    getstart(head);
}

template<class keys, class T>
bpt<keys, T>::bpt(std::string name) {
    std::ifstream in;
    in.open(name);
    if(!in){
        std::ofstream outfile(name);
        outfile.seekp(0);
        start t1;
        outfile.write(reinterpret_cast<char*>(&t1),sizeof(start));
        outfile.seekp(sizeof(start));
        node t2;
        outfile.write(reinterpret_cast<char*>(&t2),sizeof(node));
    }
    opfile.open(name);
    getstart(head);
}

template<class keys, class T>
void bpt<keys, T>::freshleft(int pos, const bpt::data &obj) {
    if(pos==0)return;
    node* temp;
    getnode(temp,pos);
    int t=sjtu::upper_bound(temp->value,temp->value+temp->now_num,obj)-temp->value;
    if(t!=0){
        temp->value[t-1]=obj;
    }
    else freshleft(temp->pos_of_fa,obj);
}

template<class keys, class T>
void bpt<keys, T>::balanceleaf(int pos) {//平衡叶子节点，现在大小小于size_of_block-1
    node *temp,*temp_back=nullptr,*temp_front=nullptr;//前兄弟和后兄弟节点
    getnode(temp,pos);
    if(!temp->back_pos && !temp->front_pos)return;//前后都没有节点，说明是孤寡，只可能是根节点
    if(!judge(temp->back_pos,temp->pos_of_fa,temp_back)){//后面没有节点或者后面的节点并非兄弟节点
        getnode(temp_front,temp->front_pos);//获得前面一个节点
        if(temp_front->now_num>size_of_block/2-1){//可以借
            temp->value[size_of_block/2-2]=temp_front->value[0];
            for(int i=0;i<temp_front->now_num-1;i++)temp_front->value[i]=temp_front->value[i+1];
            temp_front->now_num--;
            temp->now_num++;
            node* temp_fa;
            getnode(temp_fa,temp->pos_of_fa);
            int t=sjtu::upper_bound(temp_fa->value,temp_fa->value+temp_fa->now_num,
                                    temp->value[size_of_block/2-2])-temp_fa->value;
            temp_fa->value[t-1]=temp_front->value[0];
        }
        else{//不能借，要合并
            for(int i=size_of_block/2-2;i<size_of_block-3;i++)
                temp->value[i]=temp_front->value[i-(size_of_block/2-2)];
            temp->front_pos=temp_front->front_pos;
            updateleft(temp->front_pos,pos);
            temp->now_num=size_of_block-3;
            balanceindex(temp->pos_of_fa,temp_front->value[0]);
        }
        return;
    }
    if(!judge(temp->front_pos,temp->pos_of_fa,temp_front)){//前面一个节点不存在或非兄弟
        if(temp_back->now_num>size_of_block/2-1){//借
            for(int i=temp->now_num;i>0;i--)temp->value[i]=temp->value[i-1];
            temp->value[0]=temp_back->value[temp_back->now_num-1];
            temp_back->now_num--;
            temp->now_num++;
            node* temp_fa;
            getnode(temp_fa,temp->pos_of_fa);
            int t=sjtu::upper_bound(temp_fa->value,temp_fa->value+temp_fa->now_num,
                                    temp->value[0])-temp_fa->value;
            temp_fa->value[t]=temp->value[0];
        }
        else{//合并
            for(int i=size_of_block/2-1;i<size_of_block-3;i++)
                temp_back->value[i]=temp->value[i-size_of_block/2+1];
            temp_back->front_pos=temp->front_pos;
            updateleft(temp_back->front_pos,temp->back_pos);
            temp_back->now_num=size_of_block-3;
            balanceindex(temp_back->pos_of_fa,temp->value[0]);
        }
        return;
    }
    //走到这里说明左右都有且是兄弟
    // getnode(temp_back,temp->back_pos);
    // getnode(temp_front,temp->front_pos);

    if(temp_back->now_num>size_of_block/2-1){//找前面借
        for(int i=temp->now_num;i>0;i--)temp->value[i]=temp->value[i-1];
        temp->value[0]=temp_back->value[temp_back->now_num-1];
        temp_back->now_num--;
        temp->now_num++;
        node* temp_fa;
        getnode(temp_fa,temp->pos_of_fa);
        int t=sjtu::upper_bound(temp_fa->value,temp_fa->value+temp_fa->now_num,
                                temp->value[0])-temp_fa->value;
        temp_fa->value[t]=temp->value[0];
        return;
    }
    if(temp_front->now_num>size_of_block/2-1){//找后面借
        temp->value[size_of_block/2-2]=temp_front->value[0];
        for(int i=0;i<temp_front->now_num-1;i++)temp_front->value[i]=temp_front->value[i+1];
        temp_front->now_num--;
        temp->now_num++;
        node* temp_fa;
        getnode(temp_fa,temp->pos_of_fa);
        int t=sjtu::upper_bound(temp_fa->value,temp_fa->value+temp_fa->now_num,
                                temp->value[size_of_block/2-2])-temp_fa->value;
        temp_fa->value[t-1]=temp_front->value[0];//修改
        return;
    }
    //都不能借，只好找前面合并
    for(int i=size_of_block/2-2;i<size_of_block-3;i++)
        temp->value[i]=temp_front->value[i-(size_of_block/2-2)];
    temp->front_pos=temp_front->front_pos;
    updateleft(temp->front_pos,pos);
    temp->now_num=size_of_block-3;
    balanceindex(temp->pos_of_fa,temp_front->value[0]);
}

template<class keys, class T>
void bpt<keys, T>::balanceindex(int pos, bpt::data delindex) {
    node* temp;
    getnode(temp,pos);
    if(pos==head.pos_of_root && temp->now_num==1){
        node* son;
        getnode(son,temp->edge[0]);
        son->pos_of_fa=0;
        head.pos_of_root=temp->edge[0];
        return;
    }
    int t=sjtu::upper_bound(temp->value,temp->value+temp->now_num,delindex)-temp->value;
    for(int i=t-1;i<temp->now_num-1;i++)temp->value[i]=temp->value[i+1];
    for(int i=t;i<temp->now_num;i++)temp->edge[i]=temp->edge[i+1];
    temp->now_num--;
    if(pos==head.pos_of_root)return;

    if(temp->now_num<size_of_block/2-1){
        node* fa;
        getnode(fa,temp->pos_of_fa);
        int tx=sjtu::upper_bound(fa->value,fa->value+fa->now_num,temp->value[0])-fa->value;
        if(tx!=fa->now_num){
            node* rightbro;
            getnode(rightbro,fa->edge[tx+1]);
            if(rightbro->now_num>=size_of_block/2){
                temp->edge[size_of_block/2-1]=rightbro->edge[0];
                updatefather(rightbro->edge[0],pos);
                temp->value[size_of_block/2-2]=fa->value[tx];
                fa->value[tx]=rightbro->value[0];
                for(int i=0;i<rightbro->now_num-1;i++){
                    rightbro->value[i]=rightbro->value[i+1];
                    rightbro->edge[i]=rightbro->edge[i+1];
                }
                rightbro->edge[rightbro->now_num-1]=rightbro->edge[rightbro->now_num];
                rightbro->now_num--;
                temp->now_num++;
            }
            else{
                merge(pos,temp,rightbro,fa,tx);
                balanceindex(temp->pos_of_fa,fa->value[tx]);
            }
        }
        else{
            node *leftbro;
            getnode(leftbro,fa->edge[tx-1]);
            if(leftbro->now_num>=size_of_block/2){
                for(int i=temp->now_num;i>0;i--){
                    temp->value[i]=temp->value[i-1];
                    temp->edge[i+1]=temp->edge[i];
                }
                temp->edge[1]=temp->edge[0];
                temp->edge[0]=leftbro->edge[leftbro->now_num];
                temp->value[0]=fa->value[fa->now_num-1];
                updatefather(temp->edge[0],pos);
                temp->now_num++;
                leftbro->now_num--;
                fa->value[tx-1]=leftbro->value[leftbro->now_num];
            }
            else{
                merge(fa->edge[tx-1],leftbro,temp,fa,tx-1);
                balanceindex(temp->pos_of_fa,fa->value[tx-1]);
            }
        }
    }
}

template<class keys, class T>
void bpt<keys, T>::merge(int pos, bpt::node *obj1, bpt::node *obj2, bpt::node *fa, int tx) {
    obj1->value[obj1->now_num]=fa->value[tx];
    obj1->now_num++;
    for(int i=0;i<obj2->now_num;i++){
        obj1->value[obj1->now_num+i]=obj2->value[i];
        obj1->edge[obj1->now_num+i]=obj2->edge[i];
        node temp;
        updatefather(obj2->edge[i],pos);
    }
    obj1->now_num+=obj2->now_num;
    obj1->edge[obj1->now_num]=obj2->edge[obj2->now_num];
    updatefather(obj2->edge[obj2->now_num],pos);
}

template<class keys, class T>
void bpt<keys, T>::insert(const keys &index, const T &val) {
    data obj(index,val);
    int pos=find_pos(obj,head.pos_of_root);
    node* temp;
    getnode(temp,pos);
    int t=sjtu::upper_bound(temp->value,temp->value+temp->now_num,obj)-temp->value;
    for(int i=temp->now_num;i>t;i--)temp->value[i]=temp->value[i-1];
    temp->value[t]=obj;
    temp->now_num++;
    if(temp->now_num==size_of_block)devideleaf(pos);
}

template<class keys, class T>
void bpt<keys, T>::erase(keys key, T val) {
    data obj(key,val);
    int pos=find_pos(obj,head.pos_of_root);
    node* temp;
    getnode(temp,pos);
    int t=sjtu::upper_bound(temp->value,temp->value+temp->now_num,obj)-temp->value;
    if(!(temp->value[t-1]==obj))return;
    t--;
    if(t==0 && head.pos_of_root!=pos){
        if(temp->now_num!=1){
            node* fa;
            getnode(fa,temp->pos_of_fa);
            int t1=sjtu::upper_bound(fa->value,fa->value+fa->now_num,temp->value[0])-fa->value;
            if(t1!=0){
                fa->value[t1-1]=temp->value[1];
            }
            else freshleft(fa->pos_of_fa,temp->value[1]);
        }
        else{
            node* fa;
            getnode(fa,temp->pos_of_fa);
            node *left,*right;
            if(!judge(temp->back_pos,temp->pos_of_fa,left)){
                getnode(right,temp->front_pos);
                int t1=sjtu::upper_bound(fa->value,fa->value+fa->now_num,temp->value[0])-fa->value;
                if(t1!=0){
                    fa->value[t1-1]=right->value[0];
                }
                else freshleft(fa->pos_of_fa,right->value[0]);
            }
            else if(!judge(temp->front_pos,temp->pos_of_fa,right)){
                int t1=sjtu::upper_bound(fa->value,fa->value+fa->now_num,temp->value[0])-fa->value;
                if(t1!=0){
                    fa->value[t1-1]=left->value[left->now_num-1];
                }
                else freshleft(fa->pos_of_fa,left->value[left->now_num-1]);
            }
            else{
                getnode(right,temp->front_pos);
                int t1=sjtu::upper_bound(fa->value,fa->value+fa->now_num,temp->value[0])-fa->value;
                if(t1!=0){
                    fa->value[t1-1]=right->value[0];
                }
                else freshleft(fa->pos_of_fa,right->value[0]);
            }
        }
    }
    for(int i=t;i<temp->now_num-1;i++)temp->value[i]=temp->value[i+1];
    temp->now_num--;
    if(temp->now_num<size_of_block/2-1)balanceleaf(pos);
}

template<class keys, class T>
bool bpt<keys, T>::empty() {
    node* root;
    getnode(root,head.pos_of_root);
    if(root->type==leaf && root->now_num==0)return true;
    else return false;
}

template<class keys, class T>
void bpt<keys, T>::devideleaf(int pos) {
    node* temp1;
    getnode(temp1,pos);
    node temp2;
    temp2.back_pos=pos;
    temp2.front_pos=temp1->front_pos;
    updateleft(temp1->front_pos,head.num_of_block+1);
    temp1->front_pos=head.num_of_block+1;
    for(int i=0;i<size_of_block/2;i++)temp2.value[i]=temp1->value[size_of_block/2+i];
    temp2.now_num=size_of_block/2;
    temp1->now_num=size_of_block/2;
    if(temp1->pos_of_fa==0){
        temp1->pos_of_fa=head.num_of_block+2;
        temp2.pos_of_fa=head.num_of_block+2;
        writenode_(temp2,head.num_of_block+1);
        head.num_of_block++;
        node temp3;
        temp3.now_num=1;
        temp3.edge[0]=pos;
        temp3.edge[1]=head.num_of_block;
        temp3.value[0]=temp2.value[0];
        temp3.type=index;
        writenode_(temp3,head.num_of_block+1);
        head.num_of_block++;
        head.pos_of_root=head.num_of_block;
    }
    else{
        temp2.pos_of_fa=temp1->pos_of_fa;
        writenode_(temp2,head.num_of_block+1);
        head.num_of_block++;
        flashindex(temp1->pos_of_fa,head.num_of_block,temp2.value[0]);
    }
}

template<class keys, class T>
void bpt<keys, T>::flashindex(int fa_pos, int son_pos, const bpt::data &obj) {
    node* temp;
    getnode(temp,fa_pos);
    int t=sjtu::upper_bound(temp->value,temp->value+temp->now_num,obj)-temp->value;
    for(int i=temp->now_num;i>t;i--){
        temp->value[i]=temp->value[i-1];
        temp->edge[i+1]=temp->edge[i];
    }//proofed
    temp->value[t]=obj;
    temp->edge[t+1]=son_pos;
    temp->now_num++;
    if(temp->now_num==size_of_block){
        node temp2;
        int mid=size_of_block/2;
        temp2.now_num=mid-1;
        for(int i=mid+1;i<size_of_block;i++){
            temp2.value[i-mid-1]=temp->value[i];
            temp2.edge[i-mid-1]=temp->edge[i];
            updatefather(temp->edge[i],head.num_of_block+1);
        }
        temp2.edge[mid-1]=temp->edge[size_of_block];
        updatefather(temp->edge[size_of_block],head.num_of_block+1);
        temp->now_num=mid;
        temp2.type=index;
        if(temp->pos_of_fa==0){
            temp->pos_of_fa=head.num_of_block+2;
            temp2.pos_of_fa=head.num_of_block+2;
            writenode_(temp2,head.num_of_block+1);
            head.num_of_block++;
            node temp3;
            temp3.edge[0]=fa_pos;
            temp3.edge[1]=head.num_of_block;
            temp3.value[0]=temp->value[mid];
            temp3.now_num=1;
            temp3.type=index;
            writenode_(temp3,head.num_of_block+1);
            head.num_of_block++;
            head.pos_of_root=head.num_of_block;
        }
        else{
            temp2.pos_of_fa=temp->pos_of_fa;
            writenode_(temp2,head.num_of_block+1);
            head.num_of_block++;
            flashindex(temp->pos_of_fa,head.num_of_block,temp->value[mid]);
        }
    }
}

template<class keys, class T>
void bpt<keys, T>::updateright(int pos, int right) {
    if(pos==0)return;
    node* temp;
    getnode(temp,pos);
    temp->front_pos=right;
}

template<class keys, class T>
void bpt<keys, T>::updateleft(int pos, int left) {
    if(pos==0)return;
    node* temp;
    getnode(temp,pos);
    temp->back_pos=left;
}

template<class keys, class T>
void bpt<keys, T>::updatefather(int pos, int fa_pos) {
    node* temp;
    getnode(temp,pos);
    temp->pos_of_fa=fa_pos;
}

template<class keys, class T>
int bpt<keys, T>::find_pos(const bpt::data &obj, int num) {
    node* temp;
    getnode(temp,num);
    if(temp->type==leaf)return num;
    else{
        int t=sjtu::upper_bound(temp->value,temp->value+temp->now_num,obj)-temp->value;
        //if(temp->edge[t]>head.num_of_block)std::cout<<114514<<std::endl;
        return find_pos(obj,temp->edge[t]);
    }
}

template<class keys, class T>
int bpt<keys, T>::finds(const keys &key, int num) {
    node* temp;
    getnode(temp,num);
    if(temp->type == leaf)return num;
    int l = 0, r = temp->now_num - 1, mid;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (temp->value[mid].key < key)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return finds(key,temp->edge[r+1]);
}

template<class keys, class T>
void bpt<keys, T>::getnode(bpt::node *&obj, int num) {
    if(!map.contains(num)){
        node* newNode = new node();
        Node* x=map.insert(num,newNode);
        if(x!=nullptr){
            writenode(x->value,x->key);
            map.map.erase(x->key);
            delete x->value;
            delete x;
        }
        opfile.seekg(sizeof(start) + (num-1)*sizeof(node));
        opfile.read(reinterpret_cast<char*>(newNode),sizeof(node));
        obj=newNode;
    }
    else obj=map[num];
}

template<class keys, class T>
void bpt<keys, T>::writestart(bpt::start &st) {
    opfile.seekp(0);
    opfile.write(reinterpret_cast<char*>(&st),sizeof(start));
}

template<class keys, class T>
void bpt<keys, T>::getstart(bpt::start &st) {
    opfile.seekg(0);
    opfile.read(reinterpret_cast<char*>(&st),sizeof(start));
}

template<class keys, class T>
typename bpt<keys, T>::Node *bpt<keys, T>::LinkedHashMap::removeTail() {
    Node* tailNode = tail->prev;
    removeNode(tailNode);
    return tailNode;
}

template<class keys, class T>
void bpt<keys, T>::LinkedHashMap::removeNode(bpt::Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

template<class keys, class T>
void bpt<keys, T>::LinkedHashMap::moveToHead(bpt::Node *node) {
    removeNode(node);
    insertToHead(node);
}

template<class keys, class T>
void bpt<keys, T>::LinkedHashMap::insertToHead(bpt::Node *node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

template<class keys, class T>
void bpt<keys, T>::LinkedHashMap::clear() {
    for (int i = 0; i < map.TableSize; i++) {
        Nodes* currNode = map.table[i];
        while (currNode != nullptr) {
            Nodes* nextNode = currNode->next;
            delete currNode->value->value;
            delete currNode->value;
            delete currNode;
            currNode = nextNode;
        }
        map.table[i] = nullptr;
    }
    head->next = tail;
    tail->prev = head;
}

template<class keys, class T>
bool bpt<keys, T>::LinkedHashMap::contains(const int &key) const {
    return map.contains(key);
}

template<class keys, class T>
typename bpt<keys, T>::Node *&bpt<keys, T>::LinkedHashMap::MyUnorderedMap::operator[](const int &key) {
    int index = hashFunction(key);
    Nodes* currNode = table[index];

    while (currNode != nullptr) {
        if (currNode->key == key)
            return currNode->value;

        currNode = currNode->next;
    }

    Nodes* newNode = new Nodes(key,nullptr);
    newNode->next = table[index];
    table[index] = newNode;

    return newNode->value;
}

template<class keys, class T>
typename bpt<keys, T>::Node *bpt<keys, T>::LinkedHashMap::insert(const int &key, bpt::node *value) {
    if (map.contains(key)) {
        // 键已存在，更新值并将节点移到链表头部
        Node* node_ = map[key];
        node_->value = value;
        moveToHead(node_);
        return nullptr;
    } else {
        // 键不存在，创建新节点并插入到链表头部
        Node* node_ = new Node(key, value);
        map[key] = node_;
        insertToHead(node_);

        // 检查容量是否超出限制
        if (map.size() > capacity) {
            // 超出限制，移除链表尾部的节点
            Node* tailNode = removeTail();
            return tailNode;
            // map.erase(tailNode->key);
            // delete tailNode->value;
            // delete tailNode;
        }
        return nullptr;
    }
}

template<class keys, class T>
bpt<keys, T>::LinkedHashMap::LinkedHashMap() {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}

template<class keys, class T>
int bpt<keys, T>::LinkedHashMap::MyUnorderedMap::hashFunction(const int &key) const {
    return std::hash<int>()(key) % TableSize;
}

template<class keys, class T>
void bpt<keys, T>::LinkedHashMap::MyUnorderedMap::clear() {
    for (int i = 0; i < TableSize; i++) {
        Nodes* currNode = table[i];
        while (currNode != nullptr) {
            Nodes* nextNode = currNode->next;
            delete currNode;
            currNode = nextNode;
        }
        table[i] = nullptr;
    }
}

template<class keys, class T>
size_t bpt<keys, T>::LinkedHashMap::MyUnorderedMap::size() const {
    size_t count = 0;

    for (int i = 0; i < TableSize; i++) {
        Nodes* currNode = table[i];
        while (currNode != nullptr) {
            count++;
            currNode = currNode->next;
        }
    }

    return count;
}

template<class keys, class T>
bool bpt<keys, T>::LinkedHashMap::MyUnorderedMap::contains(const int &key) const {
    int index = hashFunction(key);
    Nodes* currNode = table[index];

    while (currNode != nullptr) {
        if (currNode->key == key)
            return true;

        currNode = currNode->next;
    }

    return false;
}

template<class keys, class T>
void bpt<keys, T>::LinkedHashMap::MyUnorderedMap::erase(const int &key) {
    int index = hashFunction(key);
    Nodes* currNode = table[index];
    Nodes* prevNode = nullptr;

    while (currNode != nullptr) {
        if (currNode->key == key) {
            if (prevNode != nullptr)
                prevNode->next = currNode->next;
            else
                table[index] = currNode->next;

            delete currNode;
            break;
        }

        prevNode = currNode;
        currNode = currNode->next;
    }
}

template<class keys, class T>
void bpt<keys, T>::LinkedHashMap::MyUnorderedMap::insert(const int &key, const bpt::node *&value) {
    int index = hashFunction(key);
    Nodes* newNode = new Nodes(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

template<class keys, class T>
void bpt<keys, T>::writenode_(bpt::node &obj, int num) {
    opfile.seekp(sizeof(start)+(num-1)*sizeof(node));
    opfile.write(reinterpret_cast<char*>(&obj),sizeof(node));
}

template<class keys, class T>
void bpt<keys, T>::writenode(bpt::node *obj, int num) {
    opfile.seekp(sizeof(start)+(num-1)*sizeof(node));
    opfile.write(reinterpret_cast<char*>(obj),sizeof(node));
}

#endif
