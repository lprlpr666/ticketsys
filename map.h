//
// Created by 陆鹏睿 on 2023/5/29.
//

#ifndef STRAIN_MAP_H
#define STRAIN_MAP_H
/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.h"
#include "exceptions.h"
//#include "type_traits.h"
namespace sjtu {
// 1. 定义一个 type_traits 模板类
    template<typename T>
    struct my_type_traits{
        using iterator_assignable = typename T::iterator_assignable;
    };

// 2. 定义两个类，表示迭代器是否可被赋值的特性
    struct my_true_type{
        using iterator_assignable = std::true_type;
    };

    struct my_false_type{
        using iterator_assignable = std::false_type;
    };








    template<
            class Key,
            class T,
            class Compare = std::less<Key>
    > class map {
        int sizeofmap=0;
        enum colour{black,red};





    public:

        /**
         * the internal type of data.
         * it should have a default constructor, a copy constructor.
         * You can use sjtu::map as value_type by typedef.
         */
        typedef pair<const Key, T> value_type;
    private:struct rbtreenode{
            value_type value;
            rbtreenode *left,*right,*father;
            colour col;
            rbtreenode():left(nullptr),right(nullptr),father(nullptr){}
            rbtreenode(const rbtreenode&other):value(other.value),left(nullptr),right(nullptr),father(nullptr){

            }
            rbtreenode(value_type p):value(p),left(nullptr),right(nullptr),father(nullptr){
                col=red;
            }
            ~rbtreenode(){
//            value.first.~Key();
//            value.second.~T();
            }
        };
    public:rbtreenode *head= nullptr;
        rbtreenode *root= (rbtreenode*)malloc(sizeof(rbtreenode));
    private:
        rbtreenode* nodecopy(rbtreenode *p){
            if(p==NULL)return NULL;
            else{
                rbtreenode* left = nodecopy(p->left);    //递归拷贝当前结点的左孩子结点
                rbtreenode* right= nodecopy(p->right);    //递归拷贝当前结点的右孩子结点

                rbtreenode* q = new rbtreenode(p->value);
                q->col=p->col;
                q->left = left;
                q->right = right;
                if(NULL != left)
                    left->father = q;    //若当前结点不是叶子节点，则将左孩子的父节点指针指向当前结点
                if(NULL != right)
                    right->father = q;    //若当前结点不是叶子节点，则将右孩子的父节点指针指向当前结点
                return q;
            }
        }

        void Rightspan(rbtreenode *parent) {
            if(parent==head){
                parent->father=parent->left;
                head=parent->left;
                parent->left->father= nullptr;
                parent->left= nullptr;
                rbtreenode *r=head->right;
                head->right=parent;
                if(r) { parent->left = r; r->father=parent;}
            }
            else{
                if(parent->father->left==parent){
                    parent->father->left=parent->left;
                    parent->left->father=parent->father;
                }
                else{
                    parent->father->right=parent->left;
                    parent->left->father=parent->father;
                }
                rbtreenode *tmp=parent->left;
                parent->left= nullptr;
                parent->father=tmp;
                if(tmp->right){
                    parent->left=tmp->right;
                    tmp->right->father=parent;
                }
                tmp->right=parent;
            }
        }


        void Leftspan(rbtreenode *parent) {
            if(parent==head){
                parent->father=parent->right;
                head=parent->right;
                parent->right->father= nullptr;
                parent->right= nullptr;
                rbtreenode *l=head->left;
                head->left=parent;
                if(l) { parent->right =l; l->father=parent;}
            }
            else{
                if(parent->father->left==parent){
                    parent->father->left=parent->right;
                    parent->right->father=parent->father;
                }
                else{
                    parent->father->right=parent->right;
                    parent->right->father=parent->father;
                }
                rbtreenode *tmp=parent->right;
                parent->right= nullptr;
                parent->father=tmp;
                if(tmp->left){
                    parent->right=tmp->left;
                    tmp->left->father=parent;
                }
                tmp->left=parent;
            }
        }
        void LR(rbtreenode *parent){
            Leftspan(parent->left);
            Rightspan(parent);
        }
        void RL(rbtreenode *parent){
            Rightspan(parent->right);
            Leftspan(parent);
        }
        void deleteall(rbtreenode *node){
            if(node== nullptr)return;
            if(node->right)deleteall(node->right);
            if(node->left)deleteall(node->left);
            delete node;
        }




    public:

        /**
         * see BidirectionalIterator at CppReference for help.
         *
         * if there is anything wrong throw invalid_iterator.
         *     like it = map.begin(); --it;
         *       or it = map.end(); ++end();
         */
        class const_iterator;
        class iterator {
        public: using iterator_assignable = my_true_type::iterator_assignable;
        private:
//            int iffind=0;
//        rbtreenode* midOrder(const Key &key, rbtreenode *node){
//
//            rbtreenode *finding;
//
//            if(!iffind&&node->left)finding=midOrder(key,node->left);
//            Compare cmp;
//            if((!iffind)&&cmp(key,node->value.first)){
//                iffind++;
//                finding=node;
//            }
//            if(!iffind&&node->right)finding=midOrder(key,node->right);
//            return finding;
//        }
//        rbtreenode* smallmidOrder(const Key &key, rbtreenode *node){
//
//            rbtreenode *finding;
//            if(!iffind&&node->right)finding=smallmidOrder(key,node->right);
//
//            Compare cmp;
//            if((!iffind)&&cmp(node->value.first,key)){
//                iffind++;
//                finding=node;
//            }
//            if(!iffind&&node->left)finding=smallmidOrder(key,node->left);
//            return finding;
//        }
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            rbtreenode *iter;
            rbtreenode *iterhead;
            rbtreenode *iterroot;
            bool isend= false;
            iterator() {
                iter= nullptr;
                iterhead= nullptr;
                iterroot= nullptr;
                // TODO
            }
            iterator(const iterator &other) {
                // TODO
                iter=other.iter;
                iterhead=other.iterhead;
                iterroot=other.iterroot;
                isend=other.isend;
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                //iter++

                iterator tmp(*this);

                if(isend)throw index_out_of_bound();

                if(iter->right){
                    iter=iter->right;
                    while(iter->left)iter=iter->left;
                }
                else{
                    iterator newiter(*this);
                    while(newiter.iter->father&&newiter.iter->father->right==newiter.iter)newiter.iter=newiter.iter->father;
                    if(!newiter.iter->father)isend=1;
                    else{
                        iter=newiter.iter->father;
                    }
                }
                return tmp;
            }
            /**
             * TODO ++iter
             */
            iterator & operator++() {
                if(isend)throw index_out_of_bound();

                if(iter->right){
                    iter=iter->right;
                    while(iter->left)iter=iter->left;
                }
                else{
                    iterator newiter(*this);
                    while(newiter.iter->father&&newiter.iter->father->right==newiter.iter)newiter.iter=newiter.iter->father;
                    if(!newiter.iter->father)isend=1;
                    else{
                        iter=newiter.iter->father;
                    }
                }
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator newiterr(*this);
                if(isend) {if(iterhead== nullptr)throw index_out_of_bound();
                    isend = 0;
                    iter=iterhead;
                    while(iter->right)iter=iter->right;
                    return newiterr;
                }
                if(iter->left){
                    iter=iter->left;
                    while(iter->right)iter=iter->right;
                    isend=0;
                }
                else{
                    while(iter->father&&iter->father->left==iter)iter=iter->father;
                    if(!iter->father)throw index_out_of_bound();
                    else{
                        isend=0;
                        iter=iter->father;
                    }
                };
                return newiterr;
            }
            /**
             * TODO --iter
             */
            iterator & operator--() {
                if(isend) {if(iterhead== nullptr)throw index_out_of_bound();
                    isend = 0;
                    iter=iterhead;
                    while(iter->right)iter=iter->right;
                    return *this;
                }
                if(iter->left){
                    iter=iter->left;
                    while(iter->right)iter=iter->right;
                    isend=0;
                }
                else{
                    while(iter->father&&iter->father->left==iter)iter=iter->father;
                    if(!iter->father)throw index_out_of_bound();
                    else{
                        isend=0;
                        iter=iter->father;
                    }
                };
                return *this;

            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            value_type & operator*() const {
                return iter->value;
            }
            bool operator==(const iterator &rhs) const {
                if(iterroot!=rhs.iterroot)return false;
                if(isend!=rhs.isend)return false;
                if(isend==1&&rhs.isend==1)return true;
                if(iter==rhs.iter)return true;
                return false;
            }
            bool operator==(const const_iterator &rhs) const {
                if(iterroot!=rhs.iterroot)return false;
                if(isend!=rhs.isend)return false;
                if(isend==1&&rhs.isend==1)return true;
                if(iter==rhs.iter)return true;
                return false;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this==rhs);
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(*this==rhs);
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            value_type* operator->() const noexcept {
                return &(iter->value);
            }
        };

        class const_iterator {

        public:using iterator_assignable = my_false_type::iterator_assignable;

            // it should has similar member method as iterator.
            //  and it should be able to construct from an iterator.
        private:
            int iffind=0;
//        rbtreenode* midOrder(const Key &key, rbtreenode *node){
//
//            rbtreenode *finding;
//
//            if(!iffind&&node->left)finding=midOrder(key,node->left);
//            Compare cmp;
//            if((!iffind)&&cmp(key,node->value.first)){
//                iffind++;
//                finding=node;
//            }
//            if(!iffind&&node->right)finding=midOrder(key,node->right);
//            return finding;
//        }
//        rbtreenode* smallmidOrder(const Key  &key, rbtreenode *node){
//
//            rbtreenode *finding;
//            if(!iffind&&node->right)finding=smallmidOrder(key,node->right);
//
//            Compare cmp;
//            if((!iffind)&&cmp(node->value.first,key)){
//                iffind++;
//                finding=node;
//            }
//            if(!iffind&&node->left)finding=smallmidOrder(key,node->left);
//            return finding;
//        }
            // data members.
        public:
            rbtreenode *iter;
            rbtreenode *iterhead;
            rbtreenode *iterroot;
            bool isend= false;
            const_iterator() {
                // TODO
                iter= nullptr;
                iterhead= nullptr;
                iterroot= nullptr;
            }
            const_iterator(const const_iterator &other) {
                iter=other.iter;
                iterhead=other.iterhead;
                isend=other.isend;
            }
            const_iterator(const iterator &other) {
                iter=other.iter;
                isend=other.isend;
            }
            // And other methods in iterator.
            // And other methods in iterator.
            const_iterator operator++(int) {
                const_iterator tmp=*this;
                if(isend)throw index_out_of_bound();
                iffind=0;
                if(iter->right){
                    iter=iter->right;
                    while(iter->left)iter=iter->left;
                }
                else{
                    const_iterator newiter(*this);
                    while(newiter.iter->father&&newiter.iter->father->right==newiter.iter)newiter.iter=newiter.iter->father;
                    if(!newiter.iter->father)isend=1;
                    else{
                        iter=newiter.iter->father;
                    }
                }
                return tmp;
            }
            /**
             * TODO ++iter
             */
            const_iterator & operator++() {


                if(isend)throw index_out_of_bound();
                iffind=0;
                if(iter->right){
                    iter=iter->right;
                    while(iter->left)iter=iter->left;
                }
                else{
                    const_iterator newiter(*this);
                    while(newiter.iter->father&&newiter.iter->father->right==newiter.iter)newiter.iter=newiter.iter->father;
                    if(!newiter.iter->father)isend=1;
                    else{
                        iter=newiter.iter->father;
                    }
                }
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator newiter(*this);
                if(isend) {if(iterhead== nullptr)throw index_out_of_bound();
                    isend = 0;
                    iter=iterhead;
                    while(iter->right)iter=iter->right;
                    return newiter;
                }
                if(iter->left){
                    iter=iter->left;
                    while(iter->right)iter=iter->right;
                    isend=0;
                }
                else{
                    while(iter->father&&iter->father->left==iter)iter=iter->father;
                    if(!iter->father)throw index_out_of_bound();
                    else{
                        isend=0;
                        iter=iter->father;
                    }
                };
                return newiter;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                if(isend) {if(iterhead== nullptr)throw index_out_of_bound();
                    isend = 0;
                    iter=iterhead;
                    while(iter->right)iter=iter->right;
                    return *this;
                }
                if(iter->left){
                    iter=iter->left;
                    while(iter->right)iter=iter->right;
                    isend=0;
                }
                else{
                    while(iter->father&&iter->father->left==iter)iter=iter->father;
                    if(!iter->father)throw index_out_of_bound();
                    else{
                        isend=0;
                        iter=iter->father;
                    }
                };
                return *this;

            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            const value_type & operator*() const {
                if(isend)throw runtime_error();
                return iter->value;
            }
            bool operator==(const iterator &rhs) const {
                if(iterroot!=rhs.iterroot)return false;
                if(isend!=rhs.isend)return false;
                if(isend==1&&rhs.isend==1)return true;
                if(iter==rhs.iter)return true;
                return false;
            }
            bool operator==(const const_iterator &rhs) const {
                if(iterroot!=rhs.iterroot)return false;
                if(isend!=rhs.isend)return false;
                if(isend==1&&rhs.isend==1)return true;
                if(iter==rhs.iter)return true;
                return false;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this==rhs);
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(*this==rhs);
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            const value_type* operator->() const noexcept {
                if(isend)throw runtime_error();
                return &(iter->value);
            }
            // And other methods in iterator.
        };
        /**
         * TODO two constructors
         */
        map() {
            sizeofmap=0;
        }
        map(const map &other) {
            head= nodecopy(other.head);
            sizeofmap=other.sizeofmap;
        }
        /**
         * TODO assignment operator
         */
        map & operator=(const map &other) {
            if(other.head==head)return *this;
            clear();
            head= nodecopy(other.head);
            sizeofmap=other.sizeofmap;
            return *this;
        }
        /**
         * TODO Destructors
         */
        ~map() {
            deleteall(head);
            free(root);
        }
        /**
         * TODO
         * access specified element with bounds checking
         * Returns a reference to the mapped value of the element with key equivalent to key.
         * If no such element exists, an exception of type `index_out_of_bound'
         */
        T & at(const Key &key) {
            if(find(key)==end())throw index_out_of_bound();
            return (*this)[key];
        }
        const T & at(const Key &key) const {
            if(find(key)==cend())throw index_out_of_bound();
            return (*this)[key];
        }
        /**
         * TODO
         * access specified element
         * Returns a reference to the value that is mapped to a key equivalent to key,
         *   performing an insertion if such key does not already exist.
         */
        T & operator[](const Key &key) {
            if(head== nullptr){
                head=new rbtreenode (pair<Key,T>(key,{}));
                head->col=black;
                sizeofmap++;
                return head->value.second;
            }
            auto t= insert(pair<Key,T>(key,{})).first;
            return t.iter->value.second;
//        rbtreenode *findp=head;
//        iterator iter;
//        Compare cmp;
//        if(head== nullptr){
//            head=new rbtreenode (pair<Key,T>(key,{}));
//            head->col=black;
//            sizeofmap++;
//            return head->value.second;
//        }
//        while(1){
//            if(!cmp(key,findp->value.first)&&!cmp(findp->value.first,key)){
//                iter.iter=findp;
//                return findp->value.second;
//            }
//
//            if(cmp(key,findp->value.first)){
//                if(findp->left){
//                    findp=findp->left;
//                }
//                else{
//                    iter=insert(pair<Key,T>(key,{})).first;
//                    return iter.iter->value.second;
//                }
//            }
//            else{
//                if(findp->right){
//                    findp=findp->right;
//                }
//                else{
//                    iter=insert(pair<Key,T>(key,{})).first;
//                    return iter.iter->value.second;
//                }
//            }
//        }
        }
        /**
         * behave like at() throw index_out_of_bound if such key does not exist.
         */
        const T & operator[](const Key &key) const {
            rbtreenode *findp=head;
            iterator iter;
            Compare cmp;
            if(head== nullptr){
                throw index_out_of_bound();

            }
            while(1){
                if(!cmp(key,findp->value.first)&&!cmp(findp->value.first,key)){
                    iter.iter=findp;
                    return findp->value.second;
                }

                if(cmp(key,findp->value.first)){
                    if(findp->left){
                        findp=findp->left;
                    }
                    else{
                        throw index_out_of_bound();
                        return iter.iter->value.second;
                    }
                }
                else{
                    if(findp->right){
                        findp=findp->right;
                    }
                    else{throw index_out_of_bound();
                        return iter.iter->value.second;
                    }
                }
            }
        }
        /**
         * return a iterator to the beginning
         */
        iterator begin() {
            iterator tmp;tmp.iterroot=root;
            rbtreenode *searchless=head;
            if(head== nullptr){
                tmp.isend=1;

                return tmp;
            }
            while(searchless->left){
                searchless=searchless->left;
            }
            tmp.iter=searchless;
            tmp.iterhead=head;
            return tmp;
        }
        const_iterator cbegin() const {
            const_iterator tmp;tmp.iterroot=root;
            rbtreenode *searchless=head;
            if(head== nullptr){
                tmp.isend=1;
                return tmp;
            }
            while(searchless->left){
                searchless=searchless->left;
            }
            tmp.iter=searchless;
            tmp.iterhead=head;
            return tmp;
        }
        /**
         * return a iterator to the end
         * in fact, it returns past-the-end.
         */
        iterator end() {
            iterator iter;iter.iterroot=root;iter.iterhead=head;
            iter.isend=1;
            return iter;
        }
        const_iterator cend() const {
            const_iterator iter;iter.iterroot=root;
            iter.iterhead=head;
            iter.isend=1;
            return iter;
        }
        /**
         * checks whether the container is empty
         * return true if empty, otherwise false.
         */
        bool empty() const {
            if(head)return false;
            return true;
        }
        /**
         * returns the number of elements.
         */
        size_t size() const {return sizeofmap;}
        /**
         * clears the contents
         */
        void clear() {
            deleteall(head);
            head= nullptr;
            sizeofmap=0;
        }
        /**
         * insert an element.
         * return a pair, the first of the pair is
         *   the iterator to the new element (or the element that prevented the insertion),
         *   the second one is true if insert successfully, or false.
         */
        pair<iterator, bool> insert(const value_type &value) {
            if(head== nullptr){
                sizeofmap++;
                head=new rbtreenode (value);
                iterator itertmp;
                itertmp.iter=head;
                itertmp.iterroot=head;
                head->col=black;
                return pair<iterator,bool>(itertmp,true);
            }
//            if(head== nullptr){
//                head=new rbtreenode (value);
//                head->col=black;
//                sizeofmap++;
//                iterator itertmp;
//                itertmp.iter=head;
//                itertmp.iterhead=head;
//                return pair<iterator,bool>(itertmp,true);
//            }
            iterator itertmp=begin();
            rbtreenode *insert=head,*parent= nullptr;
            Compare cmp;
            while(insert) {
                parent=insert;
                if (!cmp(insert->value.first, value.first) && !cmp(value.first, insert->value.first)) {
                    itertmp.iter = insert;
                    return pair<iterator, bool>(itertmp, false);
                } else {
                    if (cmp(insert->value.first, value.first)) {
                        insert = insert->right;
                    } else {
                        insert = insert->left;
                    }
                }
            }

            insert=new rbtreenode(value);
            rbtreenode *tmp=insert;

            if(cmp(value.first,parent->value.first)){
                parent->left=tmp;
                tmp->father=parent;
            }
            else{
                parent->right=tmp;
                tmp->father=parent;
            }
            rbtreenode *grapa=parent;
            rbtreenode *uncle=parent;
            while(parent&&parent->col==red){
                grapa=parent->father;
                if(parent==grapa->left){
                    uncle=grapa->right;
                    if(uncle== nullptr){
                        if(insert==parent->left) {
                            Rightspan(grapa);
                            grapa->col = red;
                            parent->col = black;
                            insert->col = red;
                            insert = parent;
                            break;
                        }
                        else{
                            LR(grapa);
                            grapa->col = red;
                            parent->col = red;
                            insert->col = black;
                            break;
                        }

                    }
                    else if(uncle->col==red){
                        parent->col=black;
                        grapa->col=red;
                        uncle->col=black;
                        insert=grapa;
                    }
                    else {
                        if(insert==parent->left) {
                            Rightspan(grapa);
                            grapa->col = red;
                            parent->col = black;
                            insert = parent;
                            break;
                        }
                        else{
                            LR(grapa);
                            grapa->col = red;
                            insert->col = black;
                            break;
                        }
                    }

                }
                else{
                    uncle=grapa->left;
                    if(uncle== nullptr){
                        if(insert==parent->right) {
                            Leftspan(grapa);
                            grapa->col = red;
                            parent->col = black;
                            insert->col = red;
                            break;
                        }
                        else{
                            RL(grapa);
                            grapa->col = red;
                            parent->col =red ;
                            insert->col =black;
                            break;
                        }
                    }
                    else if(uncle->col==red){
                        parent->col=black;
                        grapa->col=red;
                        uncle->col=black;
                        insert=grapa;
                    }
                    else {
                        if(insert==parent->right) {
                            Leftspan(grapa);
                            grapa->col = red;
                            parent->col = black;
                            insert = parent;
                            break;
                        }
                        else{
                            RL(grapa);
                            grapa->col = red;insert->col = black;break;
                        }
                    }
                }
                parent=insert->father;
            }

            head->col=black;
            sizeofmap++;
            itertmp.iter=tmp;
            return pair<iterator,bool>(itertmp,true);
        }
        /**
         * erase the element at pos.
         *
         * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
         */
        void erase(iterator pos) {
            if(pos.iterroot!=root){
                throw index_out_of_bound();

            }
            if(pos.isend) {
                throw index_out_of_bound();
            }
            pos.iterhead=head;
            sizeofmap--;
            rbtreenode* delPos = nullptr;        rbtreenode* delfather = nullptr;
            rbtreenode * cur=pos.iter;
            rbtreenode *parent= cur->father;

            if(cur==head){
                if(head->left== nullptr&&head->right== nullptr) { delete head;head= nullptr;
                    return;}
                else{
                    if(head->left== nullptr){
                        head=head->right;
                        delete head->father;
                        head->father= nullptr;
                        head->col=black;
                        return;
                    }
                    else if(head->right==nullptr){
                        head=head->left;
                        delete head->father;
                        head->father= nullptr;
                        head->col=black;
                        return;
                    }
                }
            }
            if (cur->left == nullptr)
            {
                delfather = parent;
                delPos = cur;
            }
            else if (cur->right == nullptr)
            {
                delfather =parent;
                delPos = cur;
            }
            else
            {
                //两节点不为空
                rbtreenode* minParent = cur;
                rbtreenode* minRight = cur->right;
                while (minRight->left)
                {
                    minRight = minRight->left;
                }
                minParent = minRight->father;
                rbtreenode* d=minRight;
                if(cur==head)head=minRight;
                d=new rbtreenode(cur->value);
                d->father= nullptr;
                d->left= nullptr;
                d->right= nullptr;
                d->col=minRight->col;
                if(minRight->father) {
                    d->father = minRight->father;
                    if (d->father->left == minRight)d->father->left = d;
                    else d->father->right = d;
                }
                if(minRight->left){
                    d->left=minRight->left;
                    minRight->left->father=d;
                }if(minRight->right){
                    d->right=minRight->right;
                    minRight->right->father=d;
                }
                minRight->father= nullptr;
                minRight->left= nullptr;
                minRight->right= nullptr;
                minRight->col=cur->col;
                if(cur->father){
                    minRight->father=cur->father;
                    if(cur->father->left==cur)cur->father->left=minRight;
                    else{
                        cur->father->right=minRight;
                    }
                }
                if(cur->right){
                    minRight->right=cur->right;
                    minRight->right->father=minRight;
                }
                if(cur->left){
                    minRight->left=cur->left;
                    minRight->left->father=minRight;
                }
                cur->father= nullptr;
                cur->left= nullptr;
                cur->right= nullptr;
                delete cur;
                parent=minRight->father;
                minRight=d;
                minParent=minRight->father;

                delfather = minParent;
                delPos = minRight;

            }
            rbtreenode* del = delPos;
            rbtreenode* delP = delfather;




            //erase   begin!!
            if(del->col==red){
                if(del->left== nullptr&&del->right== nullptr){
                    if(del==delP->left)delP->left= nullptr;
                    else delP->right= nullptr;
                    delete del;
                }
                else{
                    if(del->left== nullptr){
                        if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                        else{delP->right = del->right; del->right->father=delP; }
                    }
                    else{
                        if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                        else{delP->right = del->left; del->left->father=delP; }
                    }
                    delete del;
                }
                return;
            }


            else
            {
                //黑节点调整
                if (del->left!= nullptr)
                {
                    del->left->col = black;
                    if (delP->left==del){
                        delP->left=del->left;
                        del->left->father=delP;
                        delete del;
                    }
                    else {
                        delP->right = del->left;
                        del->left->father = delP;
                        delete del;
                    }
                    return;

                }
                else if (delPos->right!= nullptr)
                {

                    del->right->col = black;
                    if (delP->left==del){
                        delP->left=del->right;
                        del->right->father=delP;
                        delete del;
                    }
                    else {
                        delP->right = del->right;
                        del->right->father = delP;
                        delete del;
                    }
                    return;
                }
                else //待删除结点的左右均为空
                {
                    rbtreenode *brother=del;
                    while (delPos != head){
                        if (delPos == delfather->left)
                        {
                            brother = delfather->right;
                            if (brother->col == red)
                            {
                                delfather->col=red;
                                Leftspan(delfather);
                                brother->col=black;
                                brother=delfather->right;
                            }

                            if (((brother->left == nullptr) || (brother->left->col ==black)) && ((brother->right == nullptr) || (brother->right->col == black)))
                            {
                                brother->col = red;
                                if (delfather->col == red)
                                {
                                    delfather->col = black;
                                    if(del->left== nullptr&&del->right== nullptr){
                                        if(del==delP->left)delP->left= nullptr;
                                        else delP->right= nullptr;
                                        delete del;
                                    }
                                    else{
                                        if(del->left== nullptr){
                                            if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                                            else{delP->right = del->right; del->right->father=delP; }
                                        }
                                        else{
                                            if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                                            else{delP->right = del->left; del->left->father=delP; }
                                        }
                                        delete del;
                                    }
                                    return;
                                }
                                else {
                                    delPos = delfather;
                                    delfather = delPos->father;
                                }
                            }
                            else
                            {

                                if ((brother->right == nullptr) || (brother->right->col ==black)&&brother->left->col==red)
                                {
                                    Rightspan(brother);
                                    brother->col =red;
                                    brother->father->col = black;
                                    brother =brother->father;
                                    Leftspan(delfather);
                                    delfather->father->col=delfather->col;
                                    delfather->col=black;
                                    brother->right->col=black;
                                    if(del->left== nullptr&&del->right== nullptr){
                                        if(del==delP->left)delP->left= nullptr;
                                        else delP->right= nullptr;
                                        delete del;
                                    }
                                    else{
                                        if(del->left== nullptr){
                                            if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                                            else{delP->right = del->right; del->right->father=delP; }
                                        }
                                        else{
                                            if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                                            else{delP->right = del->left; del->left->father=delP; }
                                        }
                                        delete del;
                                    }
                                    return;
                                }
                                else {
                                    Leftspan(delfather);
                                    delfather->father->col=delfather->col;
                                    delfather->col=black;
                                    brother->right->col=black;
                                    if(del->left== nullptr&&del->right== nullptr){
                                        if(del==delP->left)delP->left= nullptr;
                                        else delP->right= nullptr;
                                        delete del;
                                    }
                                    else{
                                        if(del->left== nullptr){
                                            if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                                            else{delP->right = del->right; del->right->father=delP; }
                                        }
                                        else{
                                            if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                                            else{delP->right = del->left; del->left->father=delP; }
                                        }
                                        delete del;
                                    }
                                    return;
                                }
                            }
                        }
                        else
                        {
                            brother = delfather->left;
                            if (brother->col == red)
                            {
                                delfather->col=red;
                                Rightspan(delfather);
                                brother->col=black;
                                brother=delfather->left;
                            }

                            if (((brother->right == nullptr) || (brother->right->col ==black)) && ((brother->left == nullptr) || (brother->left->col == black)))
                            {
                                brother->col = red;
                                if (delfather->col == red)
                                {
                                    delfather->col = black;
                                    if(del->right== nullptr&&del->left== nullptr){
                                        if(del==delP->left)delP->left= nullptr;
                                        else delP->right= nullptr;
                                        delete del;
                                    }
                                    else{
                                        if(del->left== nullptr){
                                            if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                                            else{delP->right = del->right; del->right->father=delP; }
                                        }
                                        else{
                                            if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                                            else{delP->right = del->left; del->left->father=delP; }
                                        }
                                        delete del;
                                    }
                                    return;
                                }
                                else {
                                    delPos = delfather;
                                    delfather = delPos->father;
                                }
                            }
                            else
                            {
                                if ((brother->left == nullptr) || (brother->left->col ==black)&&brother->right->col==red)
                                {
                                    Leftspan(brother);
                                    brother->col =red;
                                    brother->father->col = black;
                                    brother =brother->father;
                                    Rightspan(delfather);
                                    delfather->father->col=delfather->col;
                                    delfather->col=black;
                                    brother->left->col=black;
                                    if(del->left== nullptr&&del->right== nullptr){
                                        if(del==delP->left)delP->left= nullptr;
                                        else delP->right= nullptr;
                                        delete del;
                                    }
                                    else{
                                        if(del->left== nullptr){
                                            if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                                            else{delP->right = del->right; del->right->father=delP; }
                                        }
                                        else{
                                            if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                                            else{delP->right = del->left; del->left->father=delP; }
                                        }
                                        delete del;
                                    }
                                    return;

                                }
                                else {
                                    Rightspan(delfather);
                                    delfather->father->col=delfather->col;
                                    delfather->col=black;
                                    brother->left->col=black;
                                    if(del->left== nullptr&&del->right== nullptr){
                                        if(del==delP->left)delP->left= nullptr;
                                        else delP->right= nullptr;
                                        delete del;
                                    }
                                    else{
                                        if(del->left== nullptr){
                                            if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                                            else{delP->right = del->right; del->right->father=delP; }
                                        }
                                        else{
                                            if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                                            else{delP->right = del->left; del->left->father=delP; }
                                        }
                                        delete del;
                                    }
                                    return;
                                }
                            }
                        }
                    }
                }
            }

            if(del->left== nullptr&&del->right== nullptr){
                if(del==delP->left)delP->left= nullptr;
                else delP->right= nullptr;
                delete del;
            }
            else{
                if(del->left== nullptr){
                    if(del==delP->left) { delP->left = del->right; del->right->father=delP;}
                    else{delP->right = del->right; del->right->father=delP; }
                }
                else{
                    if(del==delP->left) { delP->left = del->left; del->left->father=delP;}
                    else{delP->right = del->left; del->left->father=delP; }
                }
                delete del;
            }

        }


        /**
         * Returns the number of elements with key
         *   that compares equivalent to the specified argument,
         *   which is either 1 or 0
         *     since this container does not allow duplicates.
         * The default method of check the equivalence is !(a < b || b > a)
         */
        size_t count(const Key &key) const {
            rbtreenode *findp=head;
            if(head== nullptr)return 0;
            Compare cmp;
            while(1){
                if(!cmp(key,findp->value.first)&&!cmp(findp->value.first,key)){
                    return 1;
                }

                if(cmp(key,findp->value.first)){
                    if(findp->left){
                        findp=findp->left;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    if(findp->right){
                        findp=findp->right;
                    }
                    else{
                        return 0;
                    }
                }
            }
        }
        /**
         * Finds an element with key equivalent to key.
         * key value of the element to search for.
         * Iterator to an element with key equivalent to key.
         *   If no such element is found, past-the-end (see end()) iterator is returned.
         */
        iterator find(const Key &key) {
            if(head== nullptr)return end();
            rbtreenode *findp=head;
            iterator iter;
            iter.iterroot=root;
            Compare cmp;
            while(1){
                if(!cmp(key,findp->value.first)&&!cmp(findp->value.first,key)){
                    iter.iter=findp;

                    return iter;
                }

                if(cmp(key,findp->value.first)){
                    if(findp->left){
                        findp=findp->left;
                    }
                    else{
                        return end();
                    }
                }
                else{
                    if(findp->right){
                        findp=findp->right;
                    }
                    else{
                        return end();
                    }
                }
            }
        }
        const_iterator find(const Key &key) const {
            if(head== nullptr)return cend();
            rbtreenode *findp=head;
            const_iterator iter;Compare cmp;
            while(1){
                if(!cmp(key,findp->value.first)&&!cmp(findp->value.first,key)){
                    iter.iter=findp;
                    return iter;
                }

                if(cmp(key,findp->value.first)){
                    if(findp->left){
                        findp=findp->left;
                    }
                    else{
                        return cend();
                    }
                }
                else{
                    if(findp->right){
                        findp=findp->right;
                    }
                    else{
                        return cend();
                    }
                }
            }
        }
    };
    template<typename Map1, typename Map2>
    struct maps_have_same_key_type : std::false_type {};

    template<typename Key1, typename T1, typename Compare1,
            typename Key2, typename T2, typename Compare2>
    struct maps_have_same_key_type<map<Key1, T1, Compare1>,
            map<Key2, T2, Compare2>> :
            std::is_same<Key1, Key2>::type {};

    template<typename Map1, typename Map2>
    inline constexpr bool maps_have_same_key_type_v = maps_have_same_key_type<Map1, Map2>::value;


    template<typename Map1, typename Map2>
    struct maps_have_same_value_type : std::false_type {};

    template<typename Key1, typename T1, typename Compare1,
            typename Key2, typename T2, typename Compare2>
    struct maps_have_same_value_type<map<Key1, T1, Compare1>,
            map<Key2, T2, Compare2>> :
            std::is_same<T1, T2>::type {};

    template<typename Map1, typename Map2>
    inline constexpr bool maps_have_same_value_type_v = maps_have_same_value_type<Map1, Map2>::value;
    template<typename Map1, typename Map2>
    struct maps_have_same_key_compare_type : std::false_type {};
    template<typename Key1, typename T1, typename Compare1,
            typename Key2, typename T2, typename Compare2>
    struct maps_have_same_key_compare_type<map<Key1, T1, Compare1>,
            map<Key2, T2, Compare2>> :
            std::is_same<Compare1, Compare2>::type {};
    template<typename Map1, typename Map2>
    inline constexpr bool maps_have_same_key_compare_type_v = maps_have_same_value_type<Map1, Map2>::value;
}

#endif
#endif //STRAIN_MAP_H
