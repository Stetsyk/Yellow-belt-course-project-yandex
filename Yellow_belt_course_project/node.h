//
//  node.hpp
//  Yellow_belt_course_project
//
//  Created by Oleksii Stetsyk on 10/19/19.
//  Copyright © 2019 Oleksii Stetsyk. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <memory>
#include "date.h"
using std::string;

enum class LogicalOperation{
    And,
    Or,
};

enum class Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

template<typename T, typename P>
bool comp(Comparison operator_, T a, P b){
    if(operator_ == Comparison::Less){
        return a < b;
    }
    else if(operator_ == Comparison::LessOrEqual){
        return a <= b;
    }
    else if(operator_ == Comparison::Greater){
        return a > b;
    }
    else if(operator_ == Comparison::GreaterOrEqual){
        return a >= b;
    }
    else if(operator_ == Comparison::Equal){
        return a == b;
    }
    else{
        return a != b;
    }
}

class Node{
public:
    virtual bool Evaluate(const Date & date, const string & event) const = 0;
};

class EmptyNode : public Node{
public:
    bool Evaluate(const Date & date, const string & event) const override{
        return true;
    }
};

class DateComparisonNode : public Node{
public:
    DateComparisonNode(const Comparison & cmp, const Date & date) : cmp_(cmp), date_(date) {}
    bool Evaluate(const Date & date, const string & event) const override{
        return comp(cmp_, date, date_);
    }
private:
    Comparison cmp_;
    Date date_;
};

class EventComparisonNode : public Node{
public:
    EventComparisonNode(const Comparison & cmp, const string & event) : cmp_(cmp), event_(event){}
    bool Evaluate(const Date & date, const string & event) const override{
        return comp(cmp_, event, event_);
    }
private:
    Comparison cmp_;
    string event_;
};

class LogicalOperationNode : public Node{
public:
    LogicalOperationNode(LogicalOperation logical_operation, const shared_ptr<Node> a, const shared_ptr<Node> b) : logical_operation_(logical_operation), a_(a), b_(b)  {}
    bool Evaluate(const Date & date, const string & event) const override{
        bool left = a_->Evaluate(date, event);
        bool right = b_->Evaluate(date, event);
        if(logical_operation_ == LogicalOperation::And) return (left && right);
        return (left || right);
    }
private:
    LogicalOperation logical_operation_;
    shared_ptr<Node> a_, b_;
};
