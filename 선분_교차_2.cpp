#include <iostream>
#include <vector>

using namespace std;

struct Pos
{
    int64_t x;
    int64_t y;

    Pos operator-(Pos input)
    {
        Pos ret;
        ret.x = this->x - input.x;
        ret.y = this->y - input.y;
        return ret;
    }

    bool operator>(Pos input)
    {
        if (this->x == input.x)
            return this->y > input.y;

        return this->x > input.x;
    }

    bool operator>=(Pos input)
    {
        if (this->x == input.x)
            return this->y >= input.y;

        return this->x >= input.x;
    }
    
};

// int abs(int a) { return a > 0 ? a : -a; }

int CCW(Pos a, Pos b, Pos c)
{
    Pos AB = b - a;
    Pos AC = c - a;

    int64_t cross = AB.x * AC.y - AB.y * AC.x;

    if (cross == 0)
        return 0;

    else if (cross < 0)
        return -1;

    else
        return 1;
}

int main()
{
    vector<Pos> p(4);
    for(int i=0; i<4; ++i)
    {
        cin >> p[i].x >> p[i].y;
    }

    int basedOn0 = CCW(p[0], p[1], p[2]) * CCW(p[0], p[1], p[3]);
    int basedOn2 = CCW(p[2], p[3], p[0]) * CCW(p[2], p[3], p[1]);

    if (basedOn0 == 0 && basedOn2 == 0)
    {
        if (p[0] > p[1]) 
            swap(p[0], p[1]);
        if (p[2] > p[3])
            swap(p[2], p[3]);

        if (p[0] > p[3] || p[2] > p[1])
            cout << 0 << endl;
        else
            cout << 1 << endl;
    }
    else
    {
        if (basedOn0 <= 0 && basedOn2 <= 0)
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    
    return 0;
}