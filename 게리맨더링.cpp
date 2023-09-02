#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> population;
vector<vector<int>> graph;
unsigned int red = 0;
unsigned int visited = 1;
int answer = INT32_MAX;

int sumVec(vector<int>& input)
{
    int ret = 0;
    for (auto i: input)
        ret += i;
    return ret;
}

int min(int a, int b) { return a < b ? a : b; }
int abs(int a) { return a < 0 ? -a : a; }

int findBlue(int v)
{
    int ret = population[v];
    for (int next : graph[v])
    {
        if (red & 1 << next)
            continue;
        if (visited & 1 << next)
            continue;

        visited = visited | 1 << next;
        ret += findBlue(next);
    }
    return ret;
}

int findRed(int v)
{
    int ret = population[v];
    for (int next : graph[v])
    {
        if (!(red & 1 << next))
            continue;
        if (visited & 1 << next)
            continue;

        visited = visited | 1 << next;
        ret += findRed(next);
    }
    return ret;
}

int main() 
{
    cin >> n;
    population.resize(n); 
    graph.resize(n);

    for (int i=0; i<n; ++i)
        cin >> population[i];
    
    for (int i=0; i<n; ++i)
    {
        int cnt;
        cin >> cnt;
        while (cnt--)
        {
            int dest;
            cin >> dest;
            graph[i].push_back(dest-1);
        }
    }

    int totalPo = sumVec(population);

    while (red != 1 << n)
    {
        ++red;
        int redPopulation;
        int bluePopulation;

        // 파란색 시작점 찾기
        int blueStart;
        for (int i=0; i<n; ++i)
        {
            if (red & 1 << i)
                continue;
            blueStart = i;
            break;
        }
        // 파란색 탐색
        visited = 0 | 1 << blueStart;
        bluePopulation = findBlue(blueStart);
        if (visited != ~( (~0 << n) ^ red))
            continue;

        // 빨간색 시작점은 항상 1, 빨간색 탐색
        visited = 1;
        redPopulation = findRed(0);
        
        if (visited != red)
            continue;
        
        answer = min(answer, abs(bluePopulation - redPopulation));
        
    }

    if (answer == INT32_MAX)
        answer = -1;
    cout << answer << endl;
    return 0;
}