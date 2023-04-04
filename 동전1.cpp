#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    vector<int> coins;
    vector<int> tabular(k+1, 0);

    for (int i=0; i < n; i++){
        int coin;
        cin >> coin;
        coins.push_back(coin);
    }

    // sort(coins.begin(), coins.end()); 정렬 왜 안해도 되지?

    tabular[0] = 1;
    for(auto coin: coins){
        for (int i=1; i<k+1; i++){
            if ( i >= coin ){
                tabular[i] += tabular[i-coin];
            }
        }
    }

    cout << tabular[k] << endl;

    return 0;
}