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
    bool getAlive(int nNeighbors, bool cellState) {
        return rules[nNeighbors] == 2 || (rules[nNeighbors] == 1 && cellState == 1);
    }
    void changeRule(int ruleI, int lds) {//lds: livesdiessurvives
        rules[ruleI] = lds;
    }
};



#endif //RULES_H
