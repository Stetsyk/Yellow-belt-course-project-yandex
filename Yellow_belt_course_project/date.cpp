//
//  date.cpp
//  Yellow_belt_course_project
//
//  Created by Oleksii Stetsyk on 10/19/19.
//  Copyright © 2019 Oleksii Stetsyk. All rights reserved.
//
#pragma once
#include "date.h"

int Date::GetYear() const{
    return year;
}
int Date::GetMonth() const{
    return month;
}
int Date::GetDay() const{
    return day;
}
Date::Date(int year, int month, int day){
    if(!(month >= 1 && month <= 12)){
        throw logic_error("Month value is invalid: " + to_string(month));
    }
    if(!(day >= 1 && day <= 31)){
        throw logic_error("Day value is invalid: " + to_string(day));
    }
    this->year = year;
    this->month = month;
    this->day = day;
}
Date::Date(tuple<int, int, int> date){
    Date(get<0>(date), get<1>(date), get<2>(date));
}
Date::Date(const string & s){
    std::istringstream stream(s);
    bool myFlag = true;
    myFlag = myFlag && (stream >> year);
    myFlag &= (stream.peek() == '-');
    stream.ignore(1);
    myFlag = myFlag && (stream >> month);
    myFlag &= (stream.peek() == '-');
    stream.ignore(1);
    myFlag = myFlag && (stream >> day);
    myFlag = myFlag && stream.eof();
    if (!myFlag)
    {
        throw std::logic_error("Wrong date format: " + s);
    }
    Date(year, month, day);
}
ostream& operator<<(ostream & stream, const Date & date){
    stream << setfill('0');
    stream << setw(4) << date.GetYear();
    stream << "-";
    stream << setw(2) << date.GetMonth();
    stream << "-";
    stream << setw(2) << date.GetDay();
    return stream;
}
bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() != rhs.GetYear()) return lhs.GetYear() < rhs.GetYear();
    if(lhs.GetMonth() != rhs.GetMonth()) return lhs.GetMonth() < rhs.GetMonth();
    return lhs.GetDay() < rhs.GetDay();
}
bool operator>(const Date & lhs, const Date & rhs){
    return rhs < lhs;
}
bool operator==(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() != rhs.GetYear()) return false;
    if(lhs.GetMonth() != rhs.GetMonth()) return false;
    if(lhs.GetDay() != rhs.GetDay()) return false;
    return true;
}
bool operator!=(const Date & lhs, const Date & rhs){
    if(lhs.GetYear() != rhs.GetYear()) return true;
    if(lhs.GetMonth() != rhs.GetMonth()) return true;
    if(lhs.GetDay() != rhs.GetDay()) return true;
    return false;
}
bool operator<=(const Date & lhs, const Date & rhs){
    return !(lhs > rhs);
}
bool operator>=(const Date & lhs, const Date & rhs){
    return !(lhs < rhs);
}

Date ParseDate(istream &is) {
    int year;
    is >> year;
    is.ignore();
    int month;
    is >> month;
    is.ignore();
    int day;
    is >> day;
    return {year, month, day};
}
