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


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    vector<int> LIS;
    LIS.reserve(n);
    LIS.push_back(arr.front());
    
    vector<int> tracking(n, -1);
    tracking[0] = 0;

    for (int i = 1; i < n; ++i)
    {
        int curr = arr[i];
        if (LIS.back() < curr)
        {
            tracking[i] = (int)LIS.size();
            LIS.push_back(curr);
        }
        else
        {
            int low = -1;
            int high = (int)LIS.size();
            
            while (low + 1 < high)
            {
                int mid = ( low + high ) >> 1;
                
                if ( curr <= LIS[mid] )
                {
                    high = mid; 
                }
                else
                {
                    low = mid;
                }
            }
            LIS[high] = curr;
            tracking[i] = high;
        }
    }

    vector<int> answer;
    int lastIndex = (int)LIS.size()-1;
    for (int i = n-1; i >= 0; --i)
    {
        int id = tracking[i];

        if (id == lastIndex)
        {
            answer.push_back(arr[i]);
            --lastIndex;
        }
    }

    cout << answer.size() << endl;
    for (int i = (int)LIS.size() -1; i >= 0; --i)
    {
        cout << answer[i] << " ";
    }
    cout << endl;
        
    return 0;
}