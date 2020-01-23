#pragma once
#include "date.h"
#include <sstream>
#include <vector>
using namespace std;
template<typename T1, typename T2>
void clearIfNeed(map<T1, T2> & mp, const T1 & key){
    if(static_cast<int>(mp[key].size()) == 0)
        mp.erase(key);
    return;
}

class Database {
public:
    void Add(const Date& date, const string& event){
        if(!event.empty() && !dateMapUnique[date].count(event)){
            dateMapUnique[date].insert(event);
            dateMap[date].push_back(event);
        }
    }
    string Last(const Date & date) const{
        auto it = dateMap.upper_bound(date);
        if(it == begin(dateMap)){
            throw invalid_argument("There is no event whith value not bigger than current");
        }
        --it;
        ostringstream stream;
        stream << it->first << " " << it->second.back();
        return (stream.str());
    }
    template<class T>
    int RemoveIf(const T & predicate){
        vector<pair<Date, string> > resultVector = FindIf(predicate);
        for(const auto & [date, event] : resultVector){
            dateMapUnique.at(date).erase(event);
            clearIfNeed(dateMapUnique, date);
            
            vector<string> & vecAtDate = dateMap.at(date);
            vecAtDate.erase(find(vecAtDate.begin(), vecAtDate.end(), event));
            clearIfNeed(dateMap, date);
        }
        return static_cast<int>(resultVector.size());
    }
    
    template<class T>
    vector<pair<Date, string> > FindIf(const T & predicate) const {
        vector<pair<Date, string> > resultVector;
        for(const auto & [date, eventsVector] : dateMap){
            for(const auto & event : eventsVector){
                if(predicate(date, event)){
                    resultVector.push_back({date, event});
                }
            }
        }
        return resultVector;
    }
    void Print(ostream & stream) const{
        for(const auto & [key, value] : dateMap){
            for(const auto & str: value){
                stream << key << " " << str << endl;
            }
        }
    };
private:
    map<Date, set<string> > dateMapUnique;
    map<Date, vector<string> > dateMap;
};
