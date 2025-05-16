#include <string>
#include <vector>
#include <queue>

#include <iostream>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int s : scoville)
        minHeap.push(s);

    while (2 <= minHeap.size() && minHeap.top() < K)
    {
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();
        
        minHeap.push(first + second * 2);
        
        ++answer;
    }
    
    if (minHeap.top() < K)
        return -1;
        
    return answer;
}