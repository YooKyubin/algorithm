#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> arr;

int max(int a, int b) { return a > b ? a : b; }

// 최대값이 입력으로 들어오면, 최대값이 넘지 않도록 구슬들을 합친 뒤 그 구슬의 개수를 리턴한다.
int countGroup(int mid)
{
    int temp = 0;
    int cnt = 0;
    for (int i=0; i<n; ++i)
    {
        if (temp + arr[i] > mid)
        {
            temp = arr[i];
            ++cnt;
        }
        else
        {
            temp += arr[i];
        }
    }

    if (temp > 0)
        cnt += 1;

    return cnt;
}

int main()
{
    cin >> n >> m;
    arr.resize(n);
    for (int i=0; i<n; ++i)
        cin >> arr[i];
    
    int lo = 0;
    int hi = 30001;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        int groupCnt = countGroup(mid);
        
        if (m >= groupCnt)
        {
            hi = mid - 1;
        }
        else 
        {
            lo = mid + 1;
        }
    }
    int target = lo;
    for (int i=0; i<n; ++i)
    {
        target = max(target, arr[i]);
    }
    cout << target << endl;
    
    int temp = 0;
    int cnt = 0;
    int groupCnt = 0;
    for (int i=0; i<n; ++i)
    {
        if (n-(i-1) + groupCnt == m)
        {
            cout << cnt << " ";
            for (int j=i; j<n; ++j)
            {
                cout << 1 << " ";
            }
            cout << endl;
            return 0;
        }
        
        if (temp + arr[i] > target)
        {
            temp = arr[i];
            cout << cnt << " ";
            ++groupCnt;
            cnt = 0;
            ++cnt;
        }
        else
        {
            temp += arr[i];
            ++cnt;
        }
    }

    if (temp > 0)
        cout << cnt << endl;

    return 0;
}