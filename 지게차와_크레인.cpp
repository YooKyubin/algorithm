#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Coord
{
    Coord() = default;

    Coord(int _x, int _y)
        : x(_x)
        , y(_y)
    {}

    int x = 0;
    int y = 0;

    Coord operator+(const Coord& other)
    {
        return Coord(x + other.x, y + other.y);
    }

    bool CheckOutOfBourdary(int height, int width)
    {
        return x < 0 || x >= height || y < 0 || y >= width;
    }
};

vector<string> CreateGround(const vector<string>& storage)
{
    const int height = storage.size();
    const int width = storage.back().size();

    vector<string> ground;
    ground.push_back( string(width + 2, ' ') );
    for (const string& line : storage)
    {
        ground.push_back( string(" ") + line + string(" ") );
    }
    ground.push_back( string(width + 2, ' ') );

    return ground;
}

vector<Coord> ComputeAcceesibleCoord(const vector<string>& ground)
{
    vector<Coord> accessibleCoords;

    const int height = ground.size();
    const int width = ground.back().size();
    static const vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };
    
    queue<Coord> q;
    vector<vector<bool>> visitedTable(height, vector<bool>(width, false));

    q.push(Coord(0, 0));
    visitedTable[0][0] = true;

    while (false == q.empty())
    {
        Coord curr = q.front();
        q.pop();

        for (const Coord& dir : dirs)
        {
            Coord next = curr + dir;

            if (true == next.CheckOutOfBourdary(height, width))
            {
                continue;
            }

            if (true == visitedTable[next.x][next.y])
            {
                continue;
            }

            visitedTable[next.x][next.y] = true;

            if (' ' == ground[next.x][next.y])
            {
                q.push(next);
            }
            else
            {
                accessibleCoords.push_back(next);
            }
        }
    }

    return accessibleCoords;
}

int PopContainerWithCraneAndCount(vector<string>& ground, char containerID)
{
    const int height = ground.size();
    const int width = ground.back().size();

    int numPopedContainers = 0;
    for (int i=0; i<height; ++i)
    {
        for (int j=0; j<width; ++j)
        {
            if (ground[i][j] == containerID)
            {
                ground[i][j] = ' ';
                ++numPopedContainers;
            }
        }
    }

    return numPopedContainers;
}

int PopContainerWithForkLiftAndCount(vector<string>& ground, char containerID)
{
    int numPopedContainers = 0;

    vector<Coord> accessibleCoords = ComputeAcceesibleCoord(ground);
    for (const Coord& accessibleCoord : accessibleCoords)
    {
        char& accessibleID = ground[accessibleCoord.x][accessibleCoord.y];
        if (containerID == accessibleID)
        {
            accessibleID = ' ';
            ++numPopedContainers;
        }
    }

    return numPopedContainers;
}

int solution(vector<string> storage, vector<string> requests) {
    int answer = 0;
    int numPopedContainers = 0;

    vector<string> ground = CreateGround(storage);

    for (const string& request : requests)
    {
        const char requestID = request.front();
        if (request.size() == 2)
        {
            numPopedContainers += PopContainerWithCraneAndCount(ground, requestID);
        }
        else
        {
            numPopedContainers += PopContainerWithForkLiftAndCount(ground, requestID);
        }
    }

    answer = storage.size() * storage.back().size() - numPopedContainers;

    return answer;
}

#include <iostream>
int main()
{
    vector<string> storage = 
    {"AZWQY", "CAABX", "BBDDA", "ACACA"};
    vector<string> requests = 
    {"A", "BB", "A"};

    cout << solution(storage, requests) << endl;
    return 0;
}

/*
방금 제거된 컨테이너 중 노출된 컨테이너만 flood fill의 queue에 추가해주면 됨
*/