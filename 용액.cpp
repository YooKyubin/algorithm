#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n;
    vector<int> nums;

    cin >> n;
    for (int i=0; i<n; i++){
        int temp; cin >> temp;
        nums.push_back(temp);
    }
    int i=0;
    int j = n-1;
    int minVal = 1e9 * 2 + 1;
    pair<int, int> answer = { nums[i], nums[j] };
    while(i < j){
        int lo = nums[i];
        int hi = nums[j];
        int mix = hi + lo;
        if (abs(minVal) > abs(mix)){
            // 갱신
            minVal = mix;
            answer.first = lo;
            answer.second = hi;
        }
        if (mix > 0){
            --j;
        }
        else{
            ++i;
        }
    }

    cout << answer.first << " " <<  answer.second << endl;
    return 0;
}