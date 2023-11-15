#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

int n, k;

int max(int a, int b) { return a > b ? a : b; }

int pow(int a, int x)
{
	int ret = 1;
	for (int i = 0; i < x; ++i)
	{
		ret = ret * a;
	}
	return ret;
}

int main()
{
	cin >> n >> k;
	int length = to_string(n).length();
	//vector<int> visited(pow(10, length), false);

	int answer = -1;

    int cnt = 0;
    queue<int> curQueue;
    curQueue.push(n);
	while (cnt < k)
	{
        queue<int> nextQueue;
        vector<bool> visited(pow(10, length), false);

        while (!curQueue.empty())
        {
            int cur = curQueue.front();
            curQueue.pop();

            for (int i = 0; i < length; ++i)
            {
                for (int j = i + 1; j < length; ++j)
                {
                    int first = cur / pow(10, i) % 10;
                    int second = cur / pow(10, j) % 10;

                    if (j == length-1 && first == 0)
                        continue;

                    int next = cur - first * pow(10, i) - second * pow(10, j) + first * pow(10, j) + second * pow(10, i);
                    //cout << "i : " << i << ", j : " << j << " , next : " << next << endl;
                    if (visited[next])
                        continue;

                    visited[next] = true;
                    nextQueue.push(next);
                }
            }
        }
        curQueue = nextQueue;
        ++cnt;

        if (cnt == k)
        {
            while(!curQueue.empty())
            {
                int val = curQueue.front();
                answer = max(answer, val);
                curQueue.pop();
            }
        }
	}

	cout << answer << endl;
	return 0;
}