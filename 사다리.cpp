#include <iostream>
#include <cmath>
using namespace std;

double GetC(double x, double y, double w)
{
    double h1 = sqrt(x * x - w * w);
    double h2 = sqrt(y * y - w * w);

    return h1 * h2 / (h1 + h2);
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    double x, y, c;
    cin >> x >> y >> c;

    double low = 0.0;
    double high = max(x, y);

    while ( low + 0.001 < high)
    {
        double mid = (low + high) * 0.5;

        if (c < GetC(x, y, mid))
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }

    cout << high << endl;
    return 0;
}