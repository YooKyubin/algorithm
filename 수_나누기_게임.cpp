#include <iostream>
#include <vector>

#define MAXNUM 1000000

using namespace std;

int n;
vector<int> arr;
vector<bool> nums(MAXNUM + 1, false);
vector<int> score(MAXNUM + 1, 0);

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> n;
    arr.reserve(n);
    for (int i=0; i<n; ++i)
    {
        int input;
        cin >> input;
        nums[input] = true;
        arr.push_back(input);
    }

    for (int i : arr)
    {
        for (int j = i+i; j <= MAXNUM; j += i)
        {
            score[i] += nums[j]; 
            --score[j];
        }
    }

    for (int i=0; i<n; ++i)
    {
        cout << score[arr[i]] << " ";
    }
    cout << endl;
    
    return 0;
}