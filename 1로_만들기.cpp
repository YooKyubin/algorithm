#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

uint32_t memo[1000001];

uint32_t dp(uint32_t x){
    // cout << x << endl;
    if (x == 1) return 0;
    else if(memo[x] != 0) return memo[x];
    else{
        uint32_t a = -1;
        uint32_t b = -1;
        uint32_t c = -1;
        if (x % 2 == 0) a = dp(x / 2);
        if (x % 3 == 0) b = dp(x / 3);
        c = dp(x-1);      
        return memo[x] = min(a, min(b, c)) + 1;
    }
}

int main(){
    uint32_t x;
    cin >> x;
    memset(memo, 0, sizeof(uint32_t) * (x+1));
    cout << dp(x) << endl;
    return 0;
}