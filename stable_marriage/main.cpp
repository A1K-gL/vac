#include <iostream>
#include <vector>

using namespace std;

bool isBetter(vector<int> a, int newI, int currentI){
    for(size_t i = 0; i < a.size(); i++){
        if(a[i] == newI)
            return true;
        if(a[i] == currentI)
            return false;
    }
    return false;
}

vector<int> stableMarriage(int n, int m, vector<vector<int>> menPrefs, vector<vector<int>> womenPrefs){
    vector<int> result(n + m, -1);
    int freeCount = n;
    while(freeCount > 0){
        vector<vector<int>> possibleConnections (m);
        for(int i = 0; i < (int)menPrefs.size(); i++){
            if(result[i] == -1 && !menPrefs[i].empty()) {
                possibleConnections[menPrefs[i].front() - n].push_back(i);
                menPrefs[i].erase(menPrefs[i].begin());
            }
        }
        for(int i = 0; i < (int)possibleConnections.size(); i++){
            for(auto j : possibleConnections[i]){
                if(result[i + n] == -1){
                    result[i + n] = j;
                    result[j] = i + n;
                    freeCount--;
                }else if(isBetter(womenPrefs[i], j, result[i+n])){
                    result[result[i+n]] = -1;
                    result[i+n] = j;
                    result[j] = i + n;
                }
            }
        }
    }
    return result;
}

int main() {
    int n = 0, m = 0;
    vector<vector<int>> menPrefs, womenPrefs;
    cin >> n >> m;
    for(int i = 0; i < (n + m); i++){
        int length = 0;
        cin >> length;
        vector<int> tmp;
        for(int j = 0; j < length; j++) {
            int tmpInt;
            cin >> tmpInt;
            tmp.push_back(tmpInt - 1);
        }
        if(i < n)
            menPrefs.push_back(tmp);
        else
            womenPrefs.push_back(tmp);
    }
    vector<int> result = stableMarriage(n, m, menPrefs, womenPrefs);
    for(auto iter : result) {
        if(iter != -1)
            iter++;
        cout << iter<< endl;
    }
    return EXIT_SUCCESS;
}
