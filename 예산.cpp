#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int ComputeBudget(int maximum, const vector<int>& requests)
{
    int sum = 0;

    for (int i : requests)
    {
        sum += min(maximum, i);
    }

    return sum;
}


int BinarySearch(int totalBudget, const vector<int>& requests)
{
    int left = -1;
    int right = 1'000'000'000 + 1;
    
    while (left + 1 < right)
    {
        int mid = (left + right) >> 1;
    
        if (ComputeBudget(mid, requests) > totalBudget)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    
    return left;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    
    vector<int> requests(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> requests[i];
    }

    int totalBudget;
    cin >> totalBudget;

    int totalRequest = 0;
    for (int i = 0; i < n; ++i)
    {
        totalRequest += requests[i];
    }

    if (totalRequest > totalBudget)
    {
        cout << BinarySearch(totalBudget, requests) << endl;
    }
    else
    {
        cout << *max_element(requests.begin(), requests.end()) << endl;
    }

    return 0;
}