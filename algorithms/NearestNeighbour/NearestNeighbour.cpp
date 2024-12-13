#include "NearestNeighbour.h"

void NearestNeighbour::nearestNeighbour(Node *start, int size, vector<Node*> visited, int actualCost,Node *con, int c) {
    int sum = actualCost;
    int count = c;

    visited.push_back(con);
    Node* current_Node = con;
    while (count != size){
        vector<pair<Node*, int>> nodes = current_Node->getVectorOfNodes();
        usunWspolne(nodes,visited);

        std::sort(nodes.begin(), nodes.end(), [](const std::pair<Node*, int>& a, const std::pair<Node*, int>& b) {
            return a.second < b.second;
        });

        for(int x = 1; x< nodes.size(); x++){
            if(nodes[x].second == nodes[0].second){
                nearestNeighbour(start,size,visited,sum+nodes[x].second,nodes[x].first,count+1);
            }
            else{
                break;
            }
        }

        visited.push_back(nodes[0].first);
        sum += nodes[0].second;
        current_Node = nodes[0].first;
        count += 1;
    }
    bool flag = false;
    int x = 0;
    for(x = 0; x < current_Node->getVectorOfNodes().size(); x++){
        if(current_Node->getVectorOfNodes()[x].first->get_value() == start->get_value()){
            flag = true;
            break;
        }
    }


    if (flag) {
        visited.push_back(start);
        sum += current_Node->getVectorOfNodes()[x].second;
        if(sum < result){
            result = sum;
            best_way.clear();
            for(Node* n: visited) best_way.push_back(n->get_value());
        }
    }
}

void NearestNeighbour::findBestWay(vector<Node> nodes) {
    vector<int> best_scores = vector<int>();
    vector<vector<int> > best_ways = vector<vector<int> >();
    for(int x = 0; x < nodes.size(); x++){
        vector<Node*> visited = vector<Node*>();
        nearestNeighbour(&nodes[x], nodes.size(),visited,0,&nodes[x],1);
        best_scores.push_back(result);
        best_ways.push_back(best_way);
        result = INT_MAX;
        best_way.clear();
    }
    auto min_it = std::min_element(best_scores.begin(), best_scores.end());
    result = *min_it;
    auto it = std::find(best_scores.begin(), best_scores.end(),*min_it);
    int index = distance(best_scores.begin(),it);
    best_way = best_ways[index];
}
