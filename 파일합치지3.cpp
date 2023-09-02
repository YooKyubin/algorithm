#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() 
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        int n;
        cin >> n;
        priority_queue<int64_t> pq;
        for (int i=0; i<n; i++)
        {
            int64_t temp;
            cin >> temp;
            pq.push(-i);
        }
        
        int64_t answer = 0;
        while (pq.size() > 1)
        {
            int64_t a = pq.top();
            pq.pop();
            int64_t b = pq.top();
            pq.pop();
            
            answer += a + b;
            pq.push(a + b);

        }
        cout << -answer << "\n";

    }
    return 0;
}