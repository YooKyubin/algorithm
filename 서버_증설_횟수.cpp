#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(vector<int> players, int m, int k) {
    int answer = 0;

    vector<int> numServers(24, 0);

    for (int i=0; i<24; ++i)
    {
        int numPlayers = players[i];
        int numRequiredServers = numPlayers / m;

        int numMissingServer = numRequiredServers - numServers[i];
        if (numMissingServer > 0)
        {
            // numServers[i + k] -= numMissingServer;
            for (int j=0; j<k; ++j)
            {
                if (i + j >= 24)
                {
                    break;
                }
                numServers[i + j] += numMissingServer;
            }

            answer += numMissingServer;
        }
    }

    return answer;
}


int main()
{
    vector<int> players =  
    {0, 0, 0, 10, 0, 12, 0, 15, 0, 1, 0, 1, 0, 0, 0, 5, 0, 0, 11, 0, 8, 0, 0, 0};

    int m = 5;
    int k = 1;

    cout << solution(players, m, k) << endl;

    return 0;
}