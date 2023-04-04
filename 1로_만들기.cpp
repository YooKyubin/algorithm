#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> memo(1000001, 0);

int dp(int x){
    // cout << x << endl;
    if (x == 1) return 0;
    else if(memo[x] != 0) return memo[x];
    else{
        memo[x] = dp(x-1) + 1;      
        if (x % 2 == 0) memo[x] = min(memo[x], dp(x / 2)+1);
        if (x % 3 == 0) memo[x] = min(memo[x], dp(x / 3)+1);
        return memo[x];
    }
}

int main(){
    int x;
    cin >> x;
    cout << dp(x) << endl;
    return 0;
}