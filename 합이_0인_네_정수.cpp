#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;

int binSearchLow(int64_t target, vector<int64_t>& arr){
    int lo = 0;
    int hi = arr.size()-1;

    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        if (target <= arr[mid]) 
            hi = mid - 1;
        else 
            lo = mid + 1;
    }
    return lo;
}

int binSearchHigh(int64_t target, vector<int64_t>& arr){
    int lo = 0;
    int hi = arr.size()-1;

    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        if (target < arr[mid]) 
            hi = mid - 1;
        else {
            lo = mid + 1;
        }
    }
    return lo;
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vector<int> A(n);
    vector<int> B(n);
    vector<int> C(n);
    vector<int> D(n);
    for (int i=0; i<n; i++){
        int a, b, c, d;
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }
    vector<int64_t> ab;
    vector<int64_t> cd;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            ab.push_back(A[i] + B[j]);
            cd.push_back(C[i] + D[j]);
        }
    }
    sort(ab.begin(), ab.end());
    sort(cd.begin(), cd.end());
    
    int64_t answer = 0;
    for (int i=0; i<ab.size(); i++){
        // int hi = binSearchHigh(-ab[i], cd);
        // int lo = binSearchLow(-ab[i], cd);
        // int ret = hi - lo;
        // answer += ret;
        answer += binSearchHigh(-ab[i], cd) - binSearchLow(-ab[i], cd);
    }
    cout << answer << endl;
    return 0;
}