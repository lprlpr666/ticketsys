#ifndef SJTU_UTILITY_HPP
#define SJTU_UTILITY_HPP

#include <utility>
#include <iostream>
#include <sstream>
#include <iomanip>
namespace sjtu {

    template<class T>
    T *upper_bound(T *first, T *last, T key) {
        if (first == last)return first;
        last--;
        if (key >= *last)return last + 1;
        while (first < last) {
            T *mid = first + (last - first) / 2;
            if (key < *mid) {
                last = mid;
            } else {
                first = mid + 1;
            }
        }
        return first;
    }

    template<class T>
    T *lower_bound(T *first, T *last, T key) {
        if (first == last)return first;
        last--;
        if (key > *last)return last + 1;
        while (first < last) {
            T *mid = first + (last - first) / 2;
            if (*mid < key) {
                first = mid + 1;
            } else {
                last = mid;
            }
        }
        return first;
    }

    template<typename T>
    void merge_sort(T *left, T *right) {
        if (left >= right) return;

        T *middle = left + (right - left) / 2;

        merge_sort(left, middle);
        merge_sort(middle + 1, right);

        T *temp = new T[right - left + 1];
        T *p1 = left, *p2 = middle + 1, *p3 = temp;
        while (p1 <= middle && p2 <= right) {
            if (*p1 < *p2) {
                *p3++ = *p1++;
            } else {
                *p3++ = *p2++;
            }
        }
        while (p1 <= middle) {
            *p3++ = *p1++;
        }
        while (p2 <= right) {
            *p3++ = *p2++;
        }
        for (T *p = temp, *q = left; p3-- != temp;) {
            *q++ = *p++;
        }
        delete[] temp;
    }


    template<class T1, class T2>
    class pair {
    public:
        T1 first;
        T2 second;

        constexpr pair() : first(), second() {}

        pair(const pair &other) = default;

        pair(pair &&other) = default;

        pair(const T1 &x, const T2 &y) : first(x), second(y) {}

        template<class U1, class U2>
        pair(U1 &&x, U2 &&y) : first(x), second(y) {}

        template<class U1, class U2>
        pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}

        template<class U1, class U2>
        pair(pair<U1, U2> &&other) : first(other.first), second(other.second) {}
    };

}
int getmonday(int month) {
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else if(month==2){
        return 28;
    }
    else return 31;
}

#endif
