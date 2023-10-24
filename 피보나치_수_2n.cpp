#include <iostream>
#include <vector>
#include <map>

#define DIVISOR 1000000

using namespace std;

int64_t n;
map<int64_t, int64_t> memo;

int64_t fibo(int64_t v) // fibo * fibo 의 값이 int32 를 넘어갈 수 있음, 타입캐스팅을 매번 사용하기 귀찮아서 그냥 int64로 퉁침
{
    if (memo.find(v) != memo.end())
        return memo[v];
    
    if (v % 2 == 0) // 2n
    {
        int64_t v2 = v / 2;
        return memo[v] = ( ( fibo(v2) * fibo(v2) ) % DIVISOR + (2 * fibo(v2) * fibo(v2-1)) % DIVISOR ) % DIVISOR;
    }
    else // 2n - 1
    {
        int64_t v2 = (v+1) / 2;
        return memo[v] = ( ( fibo(v2) * fibo(v2) ) % DIVISOR + (fibo(v2-1) * fibo(v2-1)) % DIVISOR ) % DIVISOR;
    }
}

int main()
{
    cin >> n;

    memo[0] = 0;
    memo[1] = 1;

    int answer = fibo(n);

    cout << answer << endl;
    return 0;
}