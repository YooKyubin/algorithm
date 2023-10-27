#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int w, h;
vector<vector<char>> board;
vector<vector<int>> graph;
vector<pair<int, int>> nodePos;
int nodeCnt = 1;
vector<vector<int>> memo;

bool OOB(int x, int y)
{
    return x < 0 || x >= h || y < 0 || y >= w;
}

int min(int a, int b) { return a < b ? a : b; }

bool input()
{
    cin >> w >> h;
    board.assign(h, vector<char>(w));
    nodePos.resize(1);
    
    if (w == 0 && h == 0)
        return false;

    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            cin >> board[i][j];
            if (board[i][j] == 'o')
            {
                nodePos[0] = {i, j};
            }

            else if (board[i][j] == '*')
            {
                nodePos.push_back({i, j});
            }
        }
    }
    nodeCnt = nodePos.size();
    graph.assign(nodeCnt, vector<int>(nodeCnt, -1));
    memo.assign(nodeCnt, vector<int>(1 << nodeCnt, INT32_MAX));

    // for (auto i : nodePos)
    // {
    //     cout << i.first << ", " << i.second << "\t";
    // }cout << endl;

    return true;
}

void bfs(int start)
{
    pair<int, int> startNode = nodePos[start];
    struct Params
    {
        int x;
        int y;
        int dist;
    };
    vector<pair<int, int>> dir { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
    
    queue<Params> q;
    vector<vector<bool>> visited(h, vector<bool>(w, false));
    q.push({startNode.first, startNode.second, 0});
    visited[startNode.first][startNode.second] = true;
    
    while(!q.empty())
    {
        int x = q.front().x;
        int y = q.front().y;
        int dist = q.front().dist;
        q.pop();


        if(board[x][y] == '*' || board[x][y] == 'o') 
        {
            for (int i=0; i<nodeCnt; ++i)
            {
                if (nodePos[i].first == x && nodePos[i].second == y)
                {
                    graph[start][i] = dist;
                }
            }
        }

        for (auto d : dir)
        {
            int nx = x + d.first;
            int ny = y + d.second;

            if (OOB(nx, ny))
                continue;

            if (board[nx][ny] == 'x')
                continue;
            
            if (visited[nx][ny])
                continue;

            visited[nx][ny] = true;
            q.push({nx, ny, dist+1});

        }
    }
}

bool makeGraph()
{
    for (int i=0; i<nodePos.size(); ++i)
    {
        bfs(i);
    }

    for (auto node : graph)
    {
        for (auto edge : node)
        {
            if (edge == -1)
                return false;
        }
    }

    return true;
}

int TSP(int cur, int visited)
{
    if (visited == (1 << nodeCnt) - 1)
    {
        return 0;
    }

    if (memo[cur][visited] != INT32_MAX)
    {
        return memo[cur][visited];
    }

    for (int i=0; i<nodeCnt; ++i)
    {
        if (visited & 1 << i)
            continue;

        int dist = TSP(i, visited | (1 << i));
        memo[cur][visited] = min(memo[cur][visited], dist + graph[cur][i]);
    }

    return memo[cur][visited];
}

int graphBFS()
{
    struct Params
    {
        int idx;
        int dist;
        int visited;
    };

    struct cmp
    {
        bool operator()(Params a, Params b)
        {
            return a.dist > b.dist;
        }
    };
    priority_queue<Params, vector<Params>, cmp> pq;

    pq.push({0, 0, 1});
    int answer = -1;
    
    while(!pq.empty())
    {
        // cout << "bfs" << endl;
        int cur = pq.top().idx;
        int dist = pq.top().dist;
        int state = pq.top().visited;
        pq.pop();

        // cout << "cur : " << cur << ", dist : " << dist << ", state : " << state << "\n";

        if (state ==((1 << nodeCnt) - 1))// && visited[cur][(1 << nodeCnt) - 1])
        {
            answer = dist;
            return answer;
        }

        for (int i=1; i<nodeCnt; ++i)
        {
            if (graph[cur][i] <= 0)
                continue;

            if (state & 1 << i)
                continue;

            int nextDist = dist + graph[cur][i];
            int nextState = state | 1 << i;
            pq.push({i, nextDist, nextState});
        }
        
    }

    return answer;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    while (input())
    {
        int ans = -1;
        if (makeGraph())
        {
            // ans = TSP(0, 1);
            ans = graphBFS();
        }

        cout << ans << "\n";
        graph.clear();
    }
    return 0;
}

// bfs + 비트마스킹DP


// for (int i=0; i<nodeCnt; ++i)
// {
//     cout << i << " : \t";
//     for (int j=0; j<nodeCnt; ++j)
//     {
//         cout << graph[i][j] << "\t";
//     }
//     cout << endl;
// }


//https://www.acmicpc.net/board/view/86028