#include <vector>
#include <queue>
#include <map>
#include <iostream>
using namespace std;

struct Coord
{
    Coord() = default;
    Coord(int _x, int _y)
        : x(_x)
        , y(_y)
    {}
    int x = -1;
    int y = -1;

    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    bool CheckOOB(const int depth, const int width) const
    {
        return x < 0 || x >= depth || y < 0 || y >= width;
    }
};

static const vector<Coord> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void FloodFill(
    vector<vector<int>> &area,
    const vector<vector<int>> &land,
    const int height, const int depth, const int width,
    const int areaNumber,
    const Coord& start)
{
    queue<Coord> q;
    q.push(start);
    area[start.x][start.y] = areaNumber;

    while (!q.empty())
    {
        Coord curr = q.front();
        q.pop();

        int currHeight = land[curr.x][curr.y];

        for (const Coord& dir : dirs)
        {
            Coord next = curr + dir;
            if (next.CheckOOB(depth, width))
            {
                continue;
            }
           
            int nextHeight = land[next.x][next.y];
            if (abs(nextHeight - currHeight) > height)
            {
                continue;   
            }

            if (area[next.x][next.y] != -1)
            {
                continue;
            }
            area[next.x][next.y] = areaNumber;
            q.push(next);
        }
    }
}

int FillArea(
    vector<vector<int>>& outArea,
    const vector<vector<int>>& land, const int height, const int depth, const int width)
{
    outArea.assign(depth, vector<int>(width, -1));

    int areaNumber = 0;
    for (int i=0; i<depth; ++i)
    {
        for (int j=0; j<width; ++j)
        {
            if (outArea[i][j] == -1)
            {
                FloodFill(outArea, land, height, depth, width, areaNumber, Coord(i, j));
                ++areaNumber;
            }
        }
    } 

    return areaNumber;
}

vector<map<int, int>> MakeGraph(
    const vector<vector<int>>& area, 
    const int numAreas,
    const vector<vector<int>>& land, 
    const int height, const int depth, const int width)
{
    vector<map<int, int>> graph(numAreas);
    vector<vector<bool>> isVisited(depth, vector<bool>(width, false));

    for (int i =0; i < depth; ++i)
    {
        for (int j=0; j<width; ++j)
        {
            if (isVisited[i][j])
            {
                continue;
            }
            
            queue<Coord> q;
            q.emplace(i, j);
            isVisited[i][j] = true;
            int targetArea = area[i][j];
            while (!q.empty())
            {
                Coord curr = q.front();
                q.pop();

                for (auto& dir : dirs)
                {
                    Coord next = dir + curr;

                    if (next.CheckOOB(depth, width))
                    {
                        continue; 
                    }

                    int nextArea = area[next.x][next.y];
                    if (targetArea != nextArea)
                    {
                        int interval = abs(land[curr.x][curr.y] - land[next.x][next.y]);
                        auto iter = graph[targetArea].find(nextArea);
                        if (iter == graph[targetArea].end())
                        {
                            graph[targetArea].emplace(nextArea, interval);
                        }
                        else
                        {
                            iter->second = min(iter->second, interval);
                        }
                        continue;
                    }
                    if (isVisited[next.x][next.y])
                    {
                        continue;
                    }

                    isVisited[next.x][next.y] = true;
                    q.push(next);
                }
            }
        }
    }

    return graph;
}

int ComputeMSTEdgeSum(const vector<map<int, int>>& graph)
{
    struct Edge
    {
        Edge() = default;
        Edge(int _to, int _weight)
            : to(_to)
            , weight(_weight)
        {}
        int to;
        int weight;

        bool operator>(const Edge& other) const
        {
            return weight > other.weight;
        }
        bool operator<(const Edge& other) const
        {
            return weight < other.weight;
        }
    };
    vector<Edge> mst;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<bool> isVisited(graph.size(), false);
    pq.push(Edge(0, 0));

    while (!pq.empty())
    {
        Edge curr = pq.top();
        pq.pop();

        if (isVisited[curr.to])
        {
            continue;
        }

        isVisited[curr.to] = true;
        mst.push_back(curr);
        
        if (mst.size() == graph.size())
        {
            break;
        }

        for (const pair<int, int>& edge : graph[curr.to])
        {
            if (isVisited[edge.first])
            {
                continue;
            }

            pq.push(Edge(edge.first, edge.second));
        }
    }

    int sumEdgeWeight = 0;
    for (Edge edge : mst)
    {
        sumEdgeWeight += edge.weight;
    }
    return sumEdgeWeight;
}

int solution(vector<vector<int>> land, int height) {
    int answer = 0;

    const int depth = (int)land.size();
    const int width = (int)land.front().size();

    // 사다리 없이 돌아다닐 수 있는 영역
    vector<vector<int>> area;
    int numAreas = FillArea(area, land, height, depth, width);

    vector<map<int, int>> graph = MakeGraph(area, numAreas, land, height, depth, width);

    answer = ComputeMSTEdgeSum(graph);
    
    return answer;
}

int main()
{
    // vector<vector<int>> land = 
    // {
    //     {10, 12, 14, 16},
    //     {24, 22, 20, 18},
    //     {26, 28, 30, 32},
    //     {40, 38, 36, 34},
    // };
    vector<vector<int>> land = 
    {
        {1, 4, 8, 10}, {5, 5, 5, 5}, {10, 10, 10, 10}, {10, 10, 10, 20},
    };
    int height = 3;

    cout << solution(land, height) << endl;
    return 0;
}