#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> arr;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> n >> k;
    arr.reserve(n);
    for(int i=0; i<n; ++i)
    {
        int temp;
        cin >> temp;
        arr.push_back(temp);
    }

    vector<int> intervals;
    intervals.reserve(n-1);
    for (int i=1; i<n; ++i)
        intervals.push_back(arr[i] - arr[i-1]);

    sort(intervals.begin(), intervals.end());

    for (int i=0; i<k-1; ++i) // k개의 조를 나누기 위해서 k-1개의 칸막이가 필요하다.
        intervals.pop_back();

    int cost = 0;
    for (int interval : intervals)
        cost += interval;

    cout << cost << endl;
    return 0;
}