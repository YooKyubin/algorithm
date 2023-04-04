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
    vector<int> tabular(k+1, k+1);

    for (int i=0; i < n; i++){
        int coin;
        cin >> coin;
        coins.push_back(coin);
    }

    sort(coins.begin(), coins.end()); 

    tabular[0] = 0;
    for(auto coin: coins){
        for (int i=1; i<k+1; i++){
            if ( i - coin >= 0 ) tabular[i] = min(tabular[i], tabular[i-coin] + 1);
        }
    }
    
    if ( tabular[k]  == k+1) cout << -1 << endl;
    else cout << tabular[k] << endl;

    return 0;
}