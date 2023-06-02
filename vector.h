#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.h"

#include <climits>
#include <cstddef>
#define MAXINITIAL 128
namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector
    {
    public:
        T *index;
        int memnum;
        int maxnum;
        void Double(){
            maxnum*=2;
        }
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */

        class const_iterator;
        class iterator
        {
//	 The following code is written for the C++ type_traits library.
//	 Type traits is a C++ feature for describing certain properties of a type.
//	 For instance, for an iterator, iterator::value_type is the type that the
//	 iterator points to.
//	 STL algorithms and containers may use these type_traits (e.g. the following
//	 typedef) to work properly. In particular, without the following code,
//	 @code{std::sort(iter, iter1);} would not compile.
//	 See these websites for more information:
//	 https://en.cppreference.com/w/cpp/header/type_traits
//	 About value_type: https://blog.csdn.net/u014299153/article/details/72419713
//	 About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

            /**
    * TODO add data members
    *   just add whatever you want.
    */
            T *iter;

        public:
            int nownum;
            iterator(){
                iter= nullptr;
                nownum=0;
            }

            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const
            {
                iterator temp;
                temp.iter=iter;
                temp.nownum=nownum+n;

                return temp;
                //TODO
            }
            iterator operator-(const int &n) const
            {
                if(nownum-n<0){
                    throw runtime_error();
                }
                iterator temp;
                temp.iter=iter;
                temp.nownum=nownum-n;
                return temp;
                //TODO
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {
                return nownum-rhs.nownum;
                //TODO
            }
            iterator& operator+=(const int &n)
            {
                nownum+=n;
                return *this;
                //TODO
            }
            iterator& operator-=(const int &n)
            {
                if(nownum-n<0)throw runtime_error();
                nownum-=n;
                return *this;
                //TODO
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator temp;
                temp.iter=iter;
                temp.nownum=nownum;
                nownum++;
                return temp;
            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
                nownum++;
                return  *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                if(nownum==0)throw runtime_error();
                iterator temp;
                temp.iter=iter;
                temp.nownum=nownum;
                nownum--;
                return temp;
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
                if(nownum==0)throw runtime_error();
                nownum--;
                return  *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const{

                return iter[nownum];
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                if(iter!=rhs.iter)return false;
                if(nownum!=rhs.nownum)return false;
                return true;
            }
            bool operator==(const const_iterator &rhs) const {
                if(iter!=rhs.iter)return false;
                if(nownum!=rhs.nownum)return false;
                return true;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if(iter!=rhs.iter)return true;
                if(nownum!=rhs.nownum)return true;
                return false;
            }
            bool operator!=(const const_iterator &rhs) const {
                if(iter!=rhs.iter)return true;
                if(nownum!=rhs.nownum)return true;
                return false;
            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator
        {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:
            /*TODO*/

        public:T *iter;
            int nownum;
            const_iterator(){
                iter= nullptr;
                nownum=0;
            }
        public:

            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */

            const_iterator operator+(const int &n) const
            {
                const_iterator temp;
                temp.iter=iter;
                temp.nownum=nownum+n;
                return temp;
                //TODO
            }
            const_iterator operator-(const int &n) const
            {
                if(nownum-n<0){
                    throw runtime_error();
                }
                const_iterator temp;
                temp.iter=iter;
                temp.nownum=nownum-n;
                return temp;
                //TODO
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const
            {
                return nownum-rhs.nownum;
                //TODO
            }
            const_iterator& operator+=(const int &n)
            {
                nownum+=n;
                return *this;
                //TODO
            }
            const_iterator& operator-=(const int &n)
            {
                if(nownum-n<0)throw runtime_error();

                nownum-=n;
                return *this;
                //TODO
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                const_iterator temp;
                temp.iter=iter;
                temp.nownum=nownum;
                nownum++;
                return temp;
            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++() {
                nownum++;
                return  *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                if(nownum==0)throw runtime_error();
                const_iterator temp;
                temp.iter=iter;
                temp.nownum=nownum;
                nownum--;
                return temp;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                if(nownum==0)throw runtime_error();
                nownum--;
                return  *this;
            }
            /**
             * TODO *it
             */
            const T& operator*() const{
                return iter[nownum];
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                if(iter!=rhs.iter)return false;
                if(nownum!=rhs.nownum)return false;
                return true;
            }
            bool operator==(const const_iterator &rhs) const {
                if(iter!=rhs.iter)return false;
                if(nownum!=rhs.nownum)return false;
                return true;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if(iter!=rhs.iter)return true;
                if(nownum!=rhs.nownum)return true;
                return false;
            }
            bool operator!=(const const_iterator &rhs) const {
                if(iter!=rhs.iter)return true;
                if(nownum!=rhs.nownum)return true;
                return false;
            }

        };
        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */
        vector(): memnum(0), maxnum(MAXINITIAL) {
            index=(T*)malloc(MAXINITIAL*sizeof (T));
        }
        vector(const vector &other) : memnum(other.memnum), maxnum(other.maxnum){
            if(other.index== nullptr)index= nullptr;
            else{
                index=(T*)malloc(maxnum*sizeof (T));
                for(int i=0;i<memnum;i++){
                    index[i]=other.index[i];
                }
            }
        }
        /**
         * TODO Destructor
         */
        ~vector() {
            for(int i=0; i<memnum; ++i) {
                index[i].~T();
            }
            free(index);
        }
        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (this != &other) {
                maxnum = other.maxnum;
                memnum = other.memnum;
                std::free(index);
                index = (T *) malloc(maxnum * sizeof(T));
                for (int i = 0; i < memnum; i++) {
                    index[i] = other.index[i];
                }
            }
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T & at(const size_t &pos) {
            if(pos>memnum-1||pos<0)throw index_out_of_bound();
            return index[pos];
        }
        const T & at(const size_t &pos) const {
            if(pos>memnum-1||pos<0)throw index_out_of_bound();
            return index[pos];
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos) {
            if(pos>memnum-1||pos<0)throw index_out_of_bound();
            return index[pos];
        }
        const T & operator[](const size_t &pos) const {
            if(pos>memnum-1||pos<0)throw index_out_of_bound();
            return index[pos];
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T & front() const {
            if(memnum==0)throw container_is_empty();
            else return index[0];
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T & back() const {
            if(memnum==0)throw container_is_empty();
            else return index[memnum-1];
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator tmp;
            tmp.iter=index;
            return tmp;
        }
        const_iterator cbegin() const {
            const_iterator tmp;
            tmp.iter=index;
            return tmp;
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator tmp;tmp.iter=index;
//        tmp.iter= index[memnum];
            tmp.nownum=memnum;
            return tmp;
        }
        const_iterator cend() const {
            const_iterator tmp;tmp.iter=index;
//        tmp.iter= index[memnum];
            tmp.nownum=memnum;
            return tmp;
        }
        /**
         * checks whether the container is empty
         */
        bool empty() const {
            if(memnum==0)return true;
            return false;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return memnum;
        }
        /**
         * clears the contents
         */
        void clear() {
            memnum=0;
            std::free(index);
            index= nullptr;
        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            if(memnum>=maxnum-1){
                Double();
                T *tmp=(T*)malloc(maxnum*sizeof(T));
                for(int i=0;i<memnum;i++){
                    new(tmp+i)T(index[i]);
                }
                for(int i=0;i<memnum;i++){
                    index[i].~T();
                }
                free(index);
                index=tmp;
            }
            memnum++;
            new(index+memnum-1)T(index[memnum-2]);
            iterator iter=this->begin();
            int now=pos.nownum;
            iter.nownum=now;
            for(int i=memnum-2;i>now;i--){
                index[i]=index[i-1];
            }
            index[now]=value;
            return iter;

        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(ind>memnum){
                throw index_out_of_bound();
            }
            if(memnum>=maxnum-1){
                Double();
                T *tmp=(T*)malloc(maxnum*sizeof(T));
                for(int i=0;i<memnum;i++){
                    new(tmp+i)T(index[i]);
                }
                for(int i=0;i<memnum;i++){
                    index[i].~T();
                }
                free(index);
                index=tmp;
            }
            memnum++;
            new(index+memnum-1)T(index[memnum-2]);
            iterator iter=this->begin();
            iter.nownum=ind;
            for(int i=memnum-2;i>ind;i--){
                index[i]=index[i-1];
            }
            index[ind]=value;
            return iter;

        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            iterator iter=this->begin();
            int now = pos.nownum;
            iter.nownum=now;
            memnum--;
            index[memnum].~T();
            for(int i=now;i<memnum;i++){
                index[i]=index[i+1];
            }
            return iter;
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if(ind>=memnum){
                throw index_out_of_bound();
            }
            iterator iter=this->begin();
            iter.nownum=ind;
            memnum--;
            index[memnum].~T();
            for(int i=ind;i<memnum;i++){
                index[i]=index[i+1];
            }

            return iter;

        }
        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if(memnum>=maxnum-1){
                Double();
                T *tmp=(T*)malloc(maxnum*sizeof(T));
                for(int i=0;i<memnum;i++){
                    new(tmp+i)T(index[i]);
                }
                for(int i=0;i<memnum;i++){
                    index[i].~T();
                }
                free(index);
                index=tmp;
            }
            memnum++;
            new(index+memnum-1)T(value);

        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if(memnum==0)throw container_is_empty();
            else {
                index[memnum-1].~T();
                memnum--;
            }
        }
    };


}

#endif
