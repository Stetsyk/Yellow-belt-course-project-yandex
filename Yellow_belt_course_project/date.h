//
//  date.hpp
//  Yellow_belt_course_project
//
//  Created by Oleksii Stetsyk on 10/19/19.
//  Copyright © 2019 Oleksii Stetsyk. All rights reserved.
//
#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

class Date {
public:
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    Date(int year, int month, int day);
    Date(tuple<int, int, int> date);
    Date(const string & s);
private:
    int year;
    int month;
    int day;
};
ostream& operator<<(ostream & stream, const Date & date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date & lhs, const Date & rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date & lhs, const Date & rhs);
bool operator<=(const Date & lhs, const Date & rhs);
bool operator>=(const Date & lhs, const Date & rhs);

Date ParseDate(istream & is);
