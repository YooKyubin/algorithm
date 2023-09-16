#include <iostream>
#include <vector>
#include <queue>
#include <string>

#define MAXNUM 10000

using namespace std;

vector<char> seq {'D', 'S', 'L', 'R'};

string bfs(int a, int b)
{
    bool find = false;
    vector<string> commands(MAXNUM, "");
    queue<int> q;
    q.push(a);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        vector<int> dslr;
        dslr.push_back(cur * 2 % MAXNUM);
        dslr.push_back((cur + MAXNUM - 1) % MAXNUM);
        dslr.push_back((cur % 1000) * 10 + (cur / 1000));
        dslr.push_back(cur / 10 + (cur % 10) * 1000);

        for (int i=0; i<4; ++i)
        {
            int next = dslr[i];

            if (!commands[next].empty() || next == a) // 더 깔끔하게 처리할 수 있을거같은데..
                continue;
            
            commands[next] = commands[cur] + seq[i];
            if (next == b)
            {
                find = true;
                break;
            }
            q.push(next);
        }

        if (find)
            break;
    }

    return commands[b];
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        int a, b;
        cin >> a >> b;

        cout << bfs(a, b) << "\n";
    }
    return 0;
}