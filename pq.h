#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.h"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
    template<typename T, class Compare = std::less<T>>
    class priority_queue {
    private:
        struct node{
            node *l,*r;
            T *value;
            int dist;
            node(const T &x){
                value=(T*)malloc(sizeof(T));
                new(value)T(x);
                l=NULL;
                r=NULL;
                dist=0;
            }
            ~node(){
                (*value).~T();
                free( value);
            }
        };
        node *head;
        int memnum=0;
        node *cpnd(node *Nd){
            if(Nd==NULL)return NULL;
            node *tmp=new node(*(Nd->value));
            if(Nd->r!=NULL)tmp->r= cpnd(Nd->r);
            if(Nd->l!=NULL)tmp->l= cpnd(Nd->l);
            return tmp;
        }
        void deleteall(node *now){
            if(now!=NULL) {
                if (now->l != NULL)deleteall(now->l);
                if (now->r != NULL)deleteall(now->r);
                delete now;
                now=NULL;
            }
        }
        node *merging(node *a,node *b){
            if(a==NULL)return b;
            if(b==NULL)return a;
            Compare cmp;
            if(cmp(*(a->value),*(b->value))){
                node *tmp=b;
                b=a;
                a=tmp;
            }
            a->r= merging(a->r,b);
            if(a->l==NULL){
                if(a->r!=NULL){
                    a->l=a->r;
                    a->r=NULL;
                }
            }
            else{
                if(a->r!=NULL){
                    if(a->l->dist<a->r->dist){
                        node *tmp=a->l;
                        a->l=a->r;
                        a->r=tmp;
                    }
                }
            }
            a->dist=(a->r==NULL?0:a->r->dist+1);
            return a;
        }
    public:
        /**
         * TODO constructors
         */
        priority_queue() {
            head=NULL;
        }
        priority_queue(const priority_queue &other) {
            memnum=other.memnum;
            head= cpnd(other.head);
        }
        /**
         * TODO deconstructor
         */
        ~priority_queue() {
            deleteall(head);
        }
        /**
         * TODO Assignment operator
         */
        priority_queue &operator=(const priority_queue &other) {
            if(this!=&other){
                memnum=other.memnum;
                deleteall(head);
                head= cpnd(other.head);
            }
            return *this;
        }
        /**
         * get the top of the queue.
         * @return a reference of the top element.
         * throw container_is_empty if empty() returns true;
         */
        const T & top() const {
            if(memnum<=0)throw container_is_empty();
            else{
                return *(head->value);
            }
        }
        /**
         * TODO
         * push new element to the priority queue.
         */
        void push(const T &e) {
            try{
                if(head)Compare()(e,*(head->value));
            }catch(runtime_error){
                e.~T();
                return;
            }
            memnum++;
            node *E=new node(e);
            head=merging(head,E);
        }
        /**
         * TODO
         * delete the top element.
         * throw container_is_empty if empty() returns true;
         */
        void pop() {
            if(memnum<=0)throw container_is_empty();
            else{
                memnum--;
                node *tmp=head;
                head=merging(head->l,head->r);
                delete tmp;
            }
        }
        /**
         * return the number of the elements.
         */
        size_t size() const {
            return memnum;
        }
        /**
         * check if the container has at least an element.
         * @return true if it is empty, false if it has at least an element.
         */
        bool empty() const {
            if(memnum<=0)return true;
            return false;

        }
        /**
         * merge two priority_queues with at least O(logn) complexity.
         * clear the other priority_queue.
         */
        void merge(priority_queue &other) {
            memnum=other.memnum+memnum;
            head=merging(head,other.head);
            other.memnum=0;
            other.head=NULL;
        }
    };

}

#endif
