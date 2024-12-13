//
// Created by Kuba on 14/11/2024.
//

#include "usunWspolne.h"

void usunWspolne(vector<pair<Node*,int>>& A, vector<Node*>& B) {
    unordered_set<int> values;
    for(const auto& p: B){
        values.insert(p->get_value());
    }
    A.erase(remove_if(A.begin(), A.end(),
                      [&values](const pair<Node*,int>& p) {
                          return p.first && values.count(p.first->get_value()) > 0;
                      }),
            A.end());
}