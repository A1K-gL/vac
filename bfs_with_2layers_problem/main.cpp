#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>

using namespace std;


int main() {
    const size_t size_t_max = 0 - 1;
    size_t k, h, r, s, t;
    cin >> k >> h >> r;
    vector< pair <size_t, size_t> > mountainRoads;
    vector< pair <size_t, size_t> > riverRoads;
    unordered_map< size_t, pair< size_t, vector<size_t> > > nodes = unordered_map<size_t, pair<size_t, vector<size_t> > >();
    for(size_t i = 1; i <= k; i++)
        nodes[i] = {size_t_max, {}};
    for(size_t i = 0; i < h; i++){
        pair<size_t, size_t> tmp;
        cin >> tmp.first >> tmp.second;
        mountainRoads.push_back(tmp);
        mountainRoads.push_back({tmp.second, tmp.first});
    }
    for(size_t i = 0; i < r; i++){
        pair<size_t, size_t> tmp;
        cin >> tmp.first >> tmp.second;
        riverRoads.push_back(tmp);
        riverRoads.push_back({tmp.second, tmp.first});
    }
    cin >> s >> t;
    deque<pair<pair<size_t, size_t>, pair<size_t, vector<size_t>>>> Q = { {{s, 0}, {0, {s}}}};
    while (!Q.empty()){
        auto tmp = Q.front();
        Q.pop_front();
        if(nodes[tmp.first.first].first > tmp.first.second){
            if(tmp.first.first != t || tmp.second.first == 2){
                nodes[tmp.first.first] = {tmp.first.second, tmp.second.second};
                if(tmp.second.first == 0){
                    for(size_t i = 0; i < mountainRoads.size(); i++){
                        if(mountainRoads[i].first == tmp.first.first){
                            auto tmp_vector = tmp.second.second;
                            tmp_vector.push_back(mountainRoads[i].second);
                            Q.push_back({{mountainRoads[i].second, tmp.first.second + 1}, {1, tmp_vector}});
                        }
                    }
                }else if(tmp.second.first == 1){
                    for(size_t i = 0; i < mountainRoads.size(); i++){
                        if(mountainRoads[i].first == tmp.first.first){
                            auto tmp_vector = tmp.second.second;
                            tmp_vector.push_back(mountainRoads[i].second);
                            Q.push_back({{mountainRoads[i].second, tmp.first.second + 1}, {1, tmp_vector}});
                        }
                    }
                    for(size_t i = 0; i < riverRoads.size(); i++){
                        if(riverRoads[i].first == tmp.first.first){
                            auto tmp_vector = tmp.second.second;
                            tmp_vector.push_back(riverRoads[i].second);
                            Q.push_back({{riverRoads[i].second, tmp.first.second + 1}, {2, tmp_vector}});
                        }
                    }
                }else{
                    for(size_t i = 0; i < riverRoads.size(); i++){
                        if(riverRoads[i].first == tmp.first.first){
                            auto tmp_vector = tmp.second.second;
                            tmp_vector.push_back(riverRoads[i].second);
                            Q.push_back({{riverRoads[i].second, tmp.first.second + 1}, {2, tmp_vector}});
                        }
                    }
                }
            }
        }

    }
    if(nodes[t].first != size_t_max){
        cout << nodes[t].first << endl;
        for(size_t i : nodes[t].second) {
            cout << i;
            if(i != (nodes[t].second.at(nodes[t].second.size() - 1)))
                cout << " ";
        }
    }else{
        cout << -1;
    }
    cout << endl;
    return 0;
}
