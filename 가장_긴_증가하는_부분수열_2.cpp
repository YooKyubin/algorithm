#include <iostream>
#include <vector>

using namespace std;


int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> arr;
    for (int i=0; i<n; ++i)
    {
        int input;
        cin >> input;
        
        if (arr.empty() || arr.back() < input)
        {
            arr.push_back(input);
            continue;
        }

        // binary search
        int lo = 0; 
        int hi = arr.size()-1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (arr[mid] < input) // input 보다 크거나 같은 수가 처음 나오는 경우를 찾는다.
                lo = mid + 1;
            
            else
                hi = mid - 1;
            
        }
        
        arr[lo] = input;
    }

    cout << arr.size() << endl;
    return 0;
}