#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> minHeap;
    priority_queue<int, vector<int>, less<int>> maxHeap;

    int middle = 10000;

    for (int i=0; i<n; ++i)
    {
        int input;
        cin >> input;

        if (middle < input)
        {
            minHeap.push(input);
        }
        else
        {
            maxHeap.push(input);
        }

        // maxHeap.size()가 0~1개 더 많도록 유지
        if (minHeap.size() > maxHeap.size())
        {
            int temp = minHeap.top();
            maxHeap.push(temp);
            minHeap.pop();
        }
        else if(maxHeap.size() - minHeap.size() >= 2) 
        {
            int temp = maxHeap.top();
            minHeap.push(temp);
            maxHeap.pop();
        }
        
        middle = maxHeap.top();
        cout << maxHeap.top() << "\n";

    }
    return 0;
}