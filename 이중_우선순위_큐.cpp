#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("../../input.txt", "r", stdin);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        int k;
        cin >> k;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> maxHeap;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        vector<bool> visited (k, false);
        for (int i=0; i<k; ++i)
        {
            char c;
            int n;
            cin >> c >> n;

            if (c == 'I')
            {
                maxHeap.push({n, i});
                minHeap.push({n, i});
            }
            else if (n == -1)
            {
                while (!minHeap.empty() && visited[minHeap.top().second])
                {
                    minHeap.pop();
                }

                if (minHeap.empty())
                    continue;

                int target = minHeap.top().first;
                int idx = minHeap.top().second;
                visited[idx] = true;
            }
            else if (n == 1)
            {
                while (!maxHeap.empty() && visited[maxHeap.top().second])
                {
                    maxHeap.pop();
                }

                if (maxHeap.empty())
                    continue;

                int target = maxHeap.top().first;
                int idx = maxHeap.top().second;
                visited[idx] = true;
            }
        }
        
        while (!maxHeap.empty() && visited[maxHeap.top().second]) 
        {
            maxHeap.pop();
        }
        while (!minHeap.empty() && visited[minHeap.top().second]) 
        {
            minHeap.pop();
        }

        if (minHeap.empty() || maxHeap.empty())
        {
            cout << "EMPTY" << endl;
        }
        else
        {
            cout << maxHeap.top().first << " " << minHeap.top().second << endl;
        }
    }

    return 0;
}