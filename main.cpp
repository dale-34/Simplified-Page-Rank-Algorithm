#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <iomanip>
using namespace std;

class AdjacencyList {
    private:
        map<string, vector<pair<string, double>>> graph;  // matrix list
        map<string, vector<pair<string, double>>> temp;  // temp matrix for calculation
        map<string, double> result;  // resulting matrix after calculations (also used for multiplication)
    public:
        void pageRank(int p);
        void insertEdge(string from, string to);
        double getWeight(string from);
        void calculateRank(string from);
};

void AdjacencyList::pageRank(int p) {
    for (auto &key: graph) {  // initialize list
        result[key.first] = 1.00 / (graph.size());
    }
    int i = 1;
    while (i < p) {
        if (i == p) {  // prints r(0)
            break;
        }
        for (auto& graphPair : graph) {
            const string& key = graphPair.first;  // name of key
            if (graphPair.second.empty()) {
                temp[key].emplace_back(make_pair("", 0.00)); // rank is 0 if no out degrees
            }
            else {
                auto iter = result.find(key);
                if (iter != result.end()) {
                    for (auto& pair : graphPair.second) {  // list multiplication
                        double resultValue = 0.00;
                        resultValue = pair.second * iter->second;
                        temp[key].emplace_back(make_pair(pair.first, resultValue));  // store in temp
                    }
                }
            }
        }
        for (auto& key : temp) {
            calculateRank(key.first);
        }
        for (auto& key: temp) {  // clear temp after calculations
            temp[key.first].clear();
        }
        i++;
    }
    for (const auto& pair : result) {  // display ranks
        cout << pair.first << " ";
        cout << fixed << setprecision(2) << pair.second << endl;
    }
}

void AdjacencyList::calculateRank(string from) {
    double sum = 0.00;
    for (auto& key : temp) {  // iterates through graph and compares key to "from"
        if (key.first != from) {  // skip "from" key's iteration
            for (auto &innerPair: key.second) {  // sum in degree values
                if (innerPair.first == from) {
                    sum += innerPair.second;
                    result[from] = sum;
                    break;
                } else {
                    result[from] = sum;
                }
            }
        }
    }
}

void AdjacencyList::insertEdge(string from, string to) {
    double weight = getWeight(from);
    graph[from].emplace_back(make_pair(to, weight));  // assigns initial weight to "from"
    if (graph.find(to) == graph.end()) {  // set to empty if vertex does not exist
        graph[to] = {};
    }
    if (graph.find(from) != graph.end()) {  // updates weight for added vertices for same key
        for (int i = 0; i < graph[from].size(); i++) {
            graph[from][i].second = getWeight(from);
        }
    }
}

double AdjacencyList::getWeight(string from) {
    if (graph[from].empty()) {
        return 0.00;
    }
    else {
        return 1.00/(graph[from].size());
    }
}

int main() {
    int no_of_lines, power_iterations;
    string from, to;
    AdjacencyList graph;
    cin >> no_of_lines;
    cin >> power_iterations;
    for (int i = 0; i < no_of_lines; i++) {
        cin >> from >> to;
        graph.insertEdge(from, to);
    }
    graph.pageRank(power_iterations);
}