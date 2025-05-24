#include <iostream>
#include <vector>
// #include <unordered_map>
#include <map>

using namespace std;

struct Coord
{
    Coord() = default;
    Coord(int _x, int _y)
        : x(_x)
        , y(_y)
    {}
    Coord(const vector<int>& coord)
        : x(coord[0])
        , y(coord[1])
    {}

    int x;
    int y;

    bool operator==(const Coord& other) const
    {
        return x == other.x && y == other.y;
    }

    // map 사용을 위한 연산자 오버로딩
    bool operator<(const Coord& other) const
    {
        if (x == other.x)
        {
            return y < other.y;
        }
        return x < other.x;
    }

    vector<Coord> GetDetailPathTo(const Coord& other)
    {
        vector<Coord> detailPath;

        Coord coord = *this;
    
        // x 움직이기
        while (coord.x != other.x)
        {
            if (this->x < other.x)
            {
                ++coord.x;
            }
            else
            {
                --coord.x;
            }
            detailPath.push_back(coord);
        }

        // y 움직이기
        while(coord.y != other.y)
        {
            if (this->y < other.y)
            {
                ++coord.y;
            }
            else
            {
                --coord.y;
            }
            detailPath.push_back(coord);
        }
        return detailPath;
    }
};

vector<Coord> ComputeFullDetailPath(const vector<int>& route, const vector<vector<int>>& points)
{
    vector<Coord> fullDefailPath;
    fullDefailPath.push_back( Coord( points[route.front() - 1] ) );

    for (size_t i = 1; i < route.size(); ++i)
    {
        // K번째는 [K-1]로 접근해야함
        Coord from = Coord(points[route[i-1] - 1]);
        Coord to = Coord(points[route[i] - 1]);

        // 성능을 최대화 한다고 reserve 도 하고 make move iter도 사용했지만 실제 제출 했을 때 큰 차이가 없었다.
        vector<Coord> detailPath = from.GetDetailPathTo(to);
        fullDefailPath.reserve(fullDefailPath.size() + detailPath.size());
        fullDefailPath.insert(
            fullDefailPath.end(),
            make_move_iterator(detailPath.begin()), 
            make_move_iterator(detailPath.end()));
    }

    return fullDefailPath;
}

int CountCollision(const vector<vector<Coord>>& positionsBytime)
{
    int maxDuration = 0;
    for (auto positions : positionsBytime)
    {
        maxDuration = std::max(maxDuration, (int)positions.size());
    }

    int collisionCount = 0;
    for (int i=0; i<maxDuration; ++i)
    {
        map<Coord, int> positionsInSameTime;
        for (const vector<Coord>& positions : positionsBytime)
        {
            if (positions.size() <= i)
            {
                continue;
            }

            const Coord& position = positions[i];
            if (positionsInSameTime.end() == positionsInSameTime.find(position))
            {
                positionsInSameTime[position] = 1;
            }
            else
            {
                ++positionsInSameTime[position];

                if (2 == positionsInSameTime[position])
                {
                    ++collisionCount;
                }
            }
        }
    }

    return collisionCount;
}

int solution(vector<vector<int>> points, vector<vector<int>> routes) {
    int answer = 0;

    vector<vector<Coord>> positionsBytime;
    positionsBytime.reserve(routes.size());
    for (const vector<int>& route : routes)
    {
        positionsBytime.push_back(ComputeFullDetailPath(route, points));
    }

    answer = CountCollision(positionsBytime);

    return answer;
}

int main()
{
    vector<vector<int>> points =
    {{2, 2}, {2, 3}, {2, 7}, {6, 6}, {5, 2}};
    // vector<vector<int>> routes;
    vector<vector<int>> routes 
    {{2, 3, 4, 5}, {1, 3, 4, 5}};
    cout << solution(points, routes) << endl;

    return 0;
}