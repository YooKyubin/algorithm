#include <iostream>
#include <vector>

using namespace std;

struct Coord
{
    Coord() = default;
    Coord(int _x, int _y)
    : x(_x)
    , y(_y)
    {}
    
    int x;
    int y;
    
    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }
    
    Coord operator-(const Coord& other) const
    {
        return Coord(x - other.x, y - other.y);
    }
    
    Coord operator*(int i) const
    {
        return Coord(x * i, y * i);
    }
    
    Coord operator*(const Coord& other) const
    {
        return Coord(x * other.x, y * other.y);
    }
    
    bool operator==(const Coord& other) const
    {
        return x == other.x && y == other.y;
    }
};

static const vector<Coord> dirs { {0, 0}, {1, 0}, {-1, 0}, {0, -1}, {0, 1} };

Coord MovePoint(const Coord& startPoint, int dir, int dist)
{
    return startPoint + (dirs[dir] * dist);
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int numKoreanMelon;
    cin >> numKoreanMelon;

    Coord point = Coord(0, 0);
    vector<Coord> points;
    points.reserve(6);
    points.push_back(point);
    vector<int> dirCounts(5, 0);
    for (int i=0; i<6; ++i)
    {
        int dir;
        int dist;
        cin >> dir >> dist;
        
        point = MovePoint(point, dir, dist);
        points.push_back(point);

        ++dirCounts[dir];
    }

    Coord minPoint { 500, 500 };
    Coord maxPoint { -500, -500 };
    for (const Coord& point : points)
    {
        minPoint.x = min(point.x, minPoint.x);
        minPoint.y = min(point.y, minPoint.y);

        maxPoint.x = max(point.x, maxPoint.x);
        maxPoint.y = max(point.y, maxPoint.y);
    }

    Coord centerPoint {0, 0};
    for (const Coord& point : points)
    {   
        bool isSame = false;

        isSame |= point.x == minPoint.x;
        isSame |= point.y == minPoint.y;
        isSame |= point.x == maxPoint.x;
        isSame |= point.y == maxPoint.y;

        if (false == isSame)
        {
            centerPoint = point;
            break;
        }
    }

    vector<Coord> duplicatedDirs;
    duplicatedDirs.reserve(2);
    for (int i=1; i<dirCounts.size(); ++i)
    {
        if (dirCounts[i] == 2)
        {
            duplicatedDirs.push_back(dirs[i]);
        }
    }
    //rotate cw 90
    for (Coord& dir : duplicatedDirs)
    {
        dir = Coord(dir.y, - dir.x);
    }
    vector<Coord> bigRectVertices = {minPoint, maxPoint};
    bigRectVertices.emplace_back(minPoint.x, maxPoint.y);
    bigRectVertices.emplace_back(maxPoint.x, minPoint.y);

    Coord emptyPoint = {};
    for (const Coord& vertex : bigRectVertices)
    {
        bool isEmptyPoint = false;
        for (const Coord& point : points)
        {
            if (vertex == point)
            {
                isEmptyPoint = true;
                break;
            }
        }
        
        if (false == isEmptyPoint)
        {
            emptyPoint = vertex;
            break;
        }
    }


    int bigRectSize = (maxPoint.x - minPoint.x) * (maxPoint.y - minPoint.y);
    int smallRectSize = abs(centerPoint.x - emptyPoint.x) * (abs(centerPoint.y - emptyPoint.y));

    cout << (bigRectSize - smallRectSize) * numKoreanMelon << endl;

    return 0;
}