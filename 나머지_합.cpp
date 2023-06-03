#include <iostream>
#include <vector>

using namespace std;

int n, m;
// vector<long long> sequence;
vector<int> count;

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    long long res = 0;
    // sequence.push_back(0);
    count.assign(m, 0);
    count[0] += 1;
    long long input, pre = 0, now;
    for (int i=0; i < n; i++){
        cin >> input;
        // pre = sequence.back();
        now = (pre + input) % m;
        count[now] += 1;
        // sequence.push_back( now );
        pre = now;
    }
    for (int cnt : count){ 
        if ( cnt != 0 ) res += (long long)cnt * (cnt - 1) / 2;
    }
    cout << res << endl;
    return 0;
}