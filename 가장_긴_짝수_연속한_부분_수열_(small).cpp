#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<pair<bool, int>> odd;
vector<int> input;

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    cin >> n >> k;

    input.resize(n);
    for (int i=0; i<n; ++i)
    {
        cin >> input[i];
    }

    bool pre = input[0] % 2;
    int  cnt = 0;
    for (int i=0; i<n; ++i)
    {
        if (pre == input[i] % 2)
        {
            ++cnt;
        }
        else
        {
            pair<bool, int> temp;
            temp.first = pre;
            temp.second = cnt;
            odd.push_back(temp);

            cnt = 1;
            pre = input[i] % 2;
        }
    }
    odd.push_back({pre, cnt});

    int oddCnt = 0;
    int evenCnt = 0;
    int maxVal = 0;
    int right = 0;
    int left = 0;
    while (right < odd.size())
    {
        if (odd[right].first)
            oddCnt += odd[right].second;
        else
            evenCnt += odd[right].second;
        
        while (oddCnt > k)
        {
            if (odd[left].first)
                oddCnt -= odd[left].second;
            else
                evenCnt -= odd[left].second;
            ++left;
        }
        
        maxVal = max(maxVal, evenCnt);
        ++right;
    }
    
    cout << maxVal << endl;
    return 0;
}