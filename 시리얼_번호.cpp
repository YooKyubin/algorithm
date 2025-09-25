#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Serial
{
    Serial(const string& arg)
    : str(arg)
    , length(arg.size())
    , integerSum(0)
    {
        for (const char& ch : arg)
        {
            int charToInt = ch - '0';
            if (0 <= charToInt && charToInt <= 9)
            {
                integerSum += charToInt;
            }
        }
    }

    string str;
    int length;
    int integerSum;

    bool operator<(const Serial& rhs) const
    {
        if (str.length() == rhs.str.length())
        {
            if (integerSum == rhs.integerSum)
            {
                return str < rhs.str;
            }

            return integerSum < rhs.integerSum;
        }

        return str.length() < rhs.str.size();
    }
};

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<Serial> serials;
    serials.reserve(n);
    for (int i = 0; i< n; ++i)
    {
        string serial;
        cin >> serial;
        serials.push_back(Serial(serial));
    }

    sort(serials.begin(), serials.end());

    for (auto& serial : serials)
    {
        cout << serial.str << endl;
    }
    return 0;
}