//
// Created by felix on 1/29/24.
//

#ifndef RULES_H
#define RULES_H
#include <map>
#include <utility>


class Rules {
public:
    std::map<int,int> rules;
    Rules(std::map<int,int> rules) {
        this->rules = std::move(rules);
    }
    Rules() {

    }
    Rules(
        int s0,int s1,int s2,int s3,int s4,int s5,int s6,int s7,int s8) {
        changeRule(0,s0);changeRule(1,s1);changeRule(2,s2);
        changeRule(3,s3);changeRule(4,s4);changeRule(5,s5);
        changeRule(6,s6);changeRule(7,s7);changeRule(8,s8);
    }
    bool getAlive(int nNeighbors, bool cellState) {
        return rules[nNeighbors] == 2 || (rules[nNeighbors] == 1 && cellState == 1);
    }
    void changeRule(int ruleI, int lds) {//lds: livesdiessurvives
        rules[ruleI] = lds;
    }
};



#endif //RULES_H
