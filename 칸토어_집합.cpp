#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void FillBar(string& bar, int startIndex, int length)
{
    if (1 == length)
    {
        bar[startIndex] = '-';
        return;
    }

    int splitedLength = length / 3;

    int secondIndex = startIndex + splitedLength;
    int thirdIndex = secondIndex + splitedLength;

    FillBar(bar, startIndex, splitedLength);
    FillBar(bar, thirdIndex, splitedLength);
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        int length = pow(3, n);
        string bar(length, ' ');
        FillBar(bar, 0, length);
        
        cout << bar << endl;
    }

    return 0;
}