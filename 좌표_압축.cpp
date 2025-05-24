#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i=0; i<n; ++i)
    {
        cin >> arr[i];
    }
    vector<int> arrDeduplicated = arr;
    sort(arrDeduplicated.begin(), arrDeduplicated.end());
    arrDeduplicated.erase(unique(arrDeduplicated.begin(), arrDeduplicated.end()), arrDeduplicated.end());
    
    int rank = 0;
    unordered_map<int, int> ranks;
    for (auto& i : arrDeduplicated)
    {
        ranks[i] = rank;
        ++rank;
    }

    for (auto& i : arr)
    {
        cout << ranks[i] << " ";
    }
    cout << endl;

    return 0;
}

/*
    std::set 사용보다 직접 std::vector 에서 정렬 후 중복 제거하는 게 더 빨랐다.
    std::map 보다 std::unordered_map 사용이 더 빨랐다.
*/