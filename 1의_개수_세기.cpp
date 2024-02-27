#include <iostream>
#include <vector>

using namespace std;

vector<uint64_t> psum1(64, 0);

int Log2(uint64_t x)
{
    int cnt = 0;
    while (x = x >> 1)
    {
        ++cnt;
    }

    return cnt; // 자릿수는 cnt+1;
}

uint64_t Pow(int x)
{
    // uint64_t ret = 1;
    // return ret << x;
    return 1ULL << x;
}

uint64_t getPsum1(uint64_t x)
{
    if (x == 0)
        return 0;

    int logX = Log2(x);
    uint64_t ret = 0;
    ret += psum1[logX];
    
    x = x - Pow(Log2(x));
    ret += getPsum1(x) + x;

    return ret;
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    uint64_t a, b;
    cin >> a >> b;
    
    for (int i=1; i<64; ++i)
    {
        psum1[i] = psum1[i-1] * 2 + Pow(i-1);
    }

    cout << getPsum1(b+1) - getPsum1(a) << endl;
        
    return 0;
}