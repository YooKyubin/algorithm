#include <iostream>
#include <vector>

using namespace std;

int64_t n;
int64_t k;

int64_t min(int64_t a, int64_t b) { return a > b ? b : a; }

int64_t calRank(int64_t num){ // 작거나 같은 값의 개수
    int64_t ret = 0;
    for (int i=1; i<=n; i++){
        ret += min(num / i, n);
    }
    return ret;
}

int main() {
    cin >> n;
    cin >> k;
    
    int64_t lo = 0;
    int64_t hi = n*n;
    while (lo <= hi) {
        int64_t mid = (lo + hi) / 2;

        if (k <= calRank(mid) )
        // if ( calRank(mid) < k)
            hi = mid - 1;

        else 
            lo = mid + 1;

    }
    cout << lo << endl;
    return 0;
}