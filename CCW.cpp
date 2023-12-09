#include <iostream>

using namespace std;

int abs(int a) { return a > 0 ? a : -a; }

struct Pos
{
    int x, y, z;
};

Pos cross(Pos a, Pos b)
{
    return {
        (a.y * b.z - a.z * b.y),
        - (a.x * b.z - a.z * b.x),
        (a.x * b.y - a.y * b.x)
    };
}

int main()
{
    pair<int, int> a, b, c;
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
    cin >> c.first >> c.second;

    Pos vec1, vec2;
    vec1 = {b.first - a.first, b.second - a.second, 0};
    vec2 = {c.first - a.first, c.second - a.second, 0};
    
    Pos result = cross(vec1, vec2);
    if (result.z == 0)
        cout << 0 << endl;
    else
        cout << result.z / abs(result.z) << endl;

    return 0;
}