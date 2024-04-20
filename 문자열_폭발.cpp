#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // freopen("../../input.txt", "r", stdin);

    string input;
    string key;
    cin >> input;
    cin >> key;

    string answer;
    // answer.reserve(input.size());

    for (int i=0; i<input.size(); ++i)
    {
        answer.push_back(input[i]);

        if (answer.size() < key.size())
            continue;

        if (answer.back() == key.back())
        {
            if ( key.compare( answer.substr(answer.size() - key.size(), key.size())) == 0 )
            {
                for (int j=0; j<key.size(); ++j)
                {
                    answer.pop_back();
                }
            }
        }
    }

    if (answer.empty())
        answer = "FRULA";

    cout << answer << endl;

    return 0;
}