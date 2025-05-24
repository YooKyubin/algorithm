#include <iostream>

using namespace std;

int GCD(int a, int b)
{
    while (0 != b)
    {
        int temp = a;
        a = b;
        b = temp % b;
    }

    return a;
}

long long solution(int w,int h) {
    long long answer = 1;

    int gcd = GCD(w, h);
    int tileW = w / gcd;
    int tileH = h / gcd;

    int blankSumInTile = tileW * tileH - (tileW - 1) * (tileH - 1);

    long long blankSum = blankSumInTile * gcd;

    answer = (long long)w * (long long)h - blankSum;
    return answer;
}

int main()
{
    int w = 10;
    int h = 7;
    cout << solution(w, h) << endl;
}