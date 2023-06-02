//
// Created by 陆鹏睿 on 2023/6/2.
//

#ifndef CODE_DAYTIME_H
#define CODE_DAYTIME_H

#include <string>
#include <iomanip>

class daytime
{
public:
    int hh,mm;
    daytime(){}
    daytime(int hh_,int mm_):hh(hh_),mm(mm_){}
    daytime(const daytime &other):hh(other.hh),mm(other.mm){}
    daytime operator=(const daytime &other){
        hh=other.hh;
        mm=other.mm;
        return *this;
    }
    ~daytime(){}
    friend bool operator<(daytime &x1,daytime&x2){
        if(x1.hh==x2.hh)return x1.mm<x2.mm;
        return x1.hh<x2.hh;
    }
};
class monthtime
{
public:
    int mm,dd;
    monthtime(){}
    monthtime(int mm_,int dd_):mm(mm_),dd(dd_){}
    monthtime(const monthtime &other):mm(other.mm),dd(other.dd){}
    monthtime operator=(const monthtime &other){
        dd=other.dd;
        mm=other.mm;
        return *this;
    }
    friend bool operator<(const monthtime &x1,const monthtime &x2){
        if(x1.mm<x2.mm)return true;
        else if(x1.mm==x2.mm && x1.dd<x2.dd)return true;
        else return false;
    }
    friend bool operator>(const monthtime &obj1,const monthtime &obj2){
        if(obj1.mm>obj2.mm)return true;
        else if(obj1.mm==obj2.mm && obj1.dd>obj2.dd)return true;
        else return false;
    }
    ~monthtime(){}
};
class Time {
public:
    int month_;int day_;int hour_;int minute_;
    int days_in_month(int month) const {
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        }
        else if(month==2){
            return 28;
        }
        else return 31;
    }
    Time(){}
    Time(int month, int day, int hour, int minute): month_(month), day_(day), hour_(hour), minute_(minute) {}
    Time(monthtime m_,daytime d_=daytime()):month_(m_.mm),day_(m_.dd),hour_(d_.hh),minute_(d_.mm){}
    std::string toString() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << month_ << "-" << std::setw(2) << std::setfill('0') << day_
            << " " << std::setw(2) << std::setfill('0') << hour_ << ":" << std::setw(2) << std::setfill('0') << minute_;
        return oss.str();
    }
    Time operator+(int minutes) const {
        Time result = *this;
        result.minute_ += minutes;
        result.hour_+=result.minute_/60;
        result.minute_ %= 60;
        if (result.hour_ >= 24) {
            result.day_+=result.hour_/24;
            result.hour_%=24;
            if (result.day_ > days_in_month(result.month_)) {
                result.day_ -= days_in_month(result.month_);
                result.month_++;
            }
        }
        return result;
    }
    Time operator-(int minutes) const {
        Time result(*this);
        int borrow_minutes = minutes % (24 * 60);
        int borrow_days = minutes / (24 * 60);
        int borrow_hour = borrow_minutes / 60;
        int borrow_minute = borrow_minutes % 60;
        result.minute_ -= borrow_minute;
        if (result.minute_ < 0) {
            result.minute_ += 60;
            borrow_hour++;
        }
        result.hour_ -= borrow_hour;
        if (result.hour_ < 0) {
            result.hour_ += 24;
            borrow_days++;
        }
        while (borrow_days > 0) {
            int days_in_prev_month = days_in_month(result.month_ - 1);
            if (result.day_ <= borrow_days) {
                borrow_days -= result.day_;
                result.month_--;
                if (result.month_ == 0) {
                    result.month_ = 12;
                    result.day_ = days_in_month(result.month_) - borrow_days % days_in_prev_month;
                } else {
                    result.day_ = days_in_month(result.month_);
                }
            } else {
                result.day_ -= borrow_days;
                borrow_days = 0;
            }
        }
        return result;
    }
    int operator-(const Time& other) const {
        int days=0;
        if(month_!=other.month_){
            for(int i=other.month_+1;i<=month_-1;i++)
                days+=days_in_month(i);
            days+=days_in_month(other.month_)-other.day_;
            days+=day_;
        }
        else days=day_-other.day_;
        int minutes = days * 24 * 60 + (hour_ - other.hour_) * 60 + (minute_ - other.minute_);
        return minutes;
    }
    int days_to(const Time& other){
        int days=0;
        if(month_!=other.month_){
            for(int i=other.month_+1;i<=month_-1;i++)
                days+=days_in_month(i);
            days+=days_in_month(other.month_)-other.day_;
            days+=day_;
        }
        else days=day_-other.day_;
        return days;
    }
    bool operator<(const Time& other) const {
        if (month_ != other.month_) {
            return month_ < other.month_;
        } else if (day_ != other.day_) {
            return day_ < other.day_;
        } else if (hour_ != other.hour_) {
            return hour_ < other.hour_;
        } else {
            return minute_ < other.minute_;
        }
    }

    bool operator>(const Time& other) const {
        return other < *this;
    }
    bool operator==(const Time& other) const {
        return month_ == other.month_ && day_ == other.day_ && hour_ == other.hour_ && minute_ == other.minute_;
    }

    bool operator<=(const Time& other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const Time& other) const {
        return *this > other || *this == other;
    }
    Time operator=(const Time &other){
        month_=other.month_;
        day_=other.day_;
        hour_=other.hour_;
        minute_=other.minute_;
        return *this;
    }


};
#endif //CODE_DAYTIME_H
