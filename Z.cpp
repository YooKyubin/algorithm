#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, r, c;
    cin >> n >> r >> c;

    vector<int> lookupPow2(n+1, 1);
    for (int i=1; i<=n; ++i)
    {
        lookupPow2[i] *= lookupPow2[i-1] * 2;
    }

    vector<int> adress;
    for (int i = 1; i <= n ; ++i)
    {
        bool isUp = (r % lookupPow2[i]) < lookupPow2[i-1];
        bool isLeft = (c % lookupPow2[i]) < lookupPow2[i-1];

        int location = 0;
        if (isUp && isLeft)
            location = 0;

        if (isUp && !isLeft)
            location = 1;

        if (!isUp && isLeft)
            location = 2;

        if (!isUp && !isLeft)
            location = 3;

        adress.push_back(location);
    }

    int answer = 0;
    for (int i=0; i<=n; ++i)
    {
        answer += lookupPow2[i] * lookupPow2[i] * adress[i];
    }
    cout << answer << endl;
    return 0;
}