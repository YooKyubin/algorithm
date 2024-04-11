#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// int biSearch(vector<int>& arr, int target)
// {
//     int lo = 0;
//     int hi = arr.size()-1;

//     while (lo <= hi)
//     {
//         int mid = (lo + hi) / 2;
//         if (arr[mid] < target)
//         {
//             lo = mid+1;
//         }
//         else
//         {
//             hi = mid-1;
//         }
//     }

//     return lo;
// }

int main()
{
    freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i=0; i<n; ++i)
    {
        cin >> arr[i];
    }

    vector<int> idx(n);
    for (int i=0; i<n; ++i)
    {
        idx[i] = i;
    }

    vector<int> LIS;
    LIS.reserve(n);
    LIS.push_back(arr[0]);

    for (int i=1; i<n; ++i)
    {
        if (LIS.back() < arr[i])
        {
            LIS.push_back(arr[i]);
            idx[i] = LIS.size() - 1;
        }
        else
        {
            // int idxToChange = biSearch(LIS, arr[i]);
            // LIS[idxToChange] = arr[i];
            // idx[i] = idxToChange;

            auto itorToChange = lower_bound(LIS.begin(), LIS.end(), arr[i]);
            *itorToChange = arr[i];
            idx[i] = distance(LIS.begin(), itorToChange);
        }
    }

    int lastIdx = LIS.size()-1;
    vector<int> answer;
    answer.reserve(lastIdx);
    for (int i=n-1; i >= 0; --i)
    {
        if (lastIdx == idx[i])
        {
            answer.push_back(arr[i]);
            --lastIdx;
        }
    }
    
    cout << LIS.size() << endl;
    while (!answer.empty())
    {
        cout << answer.back() << " ";
        answer.pop_back();
    }
    return 0;
}