#include <iostream>

using namespace std;

int n, k;
bool odd[50000];

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    cin >> n >> k;
    for (int i=0; i<n; ++i)
    {
        int num;
        cin >> num;
        odd[i] = num % 2;
    }

    int oddCnt = 0;
    int maxVal = 0;
    int right = 0;
    int left = 0;
    while (right < n)
    {
        if (odd[right])
            ++oddCnt;
        
        while (oddCnt > k)
        {
            if (odd[left])
                --oddCnt;
            ++left;
        }
        
        maxVal = max(maxVal, right - left - oddCnt + 1);
        ++right;
    }
    
    cout << maxVal << endl;
    return 0;
}