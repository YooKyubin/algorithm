#include <iostream>
#include <vector>

using namespace std;

void DP(vector<vector<bool>>& memo, int currWeight, int id, const vector<int>& weights)
{
    if (weights.size() + 1 == id)
    {
        return;
    }

    int currWeightIndex = abs(currWeight);
    if (currWeightIndex < memo[0].size())
    {
        if (memo[id][currWeightIndex])
        {
            return;
        }
        memo[id][currWeightIndex] = true;
    }
    
    DP(memo, currWeight + weights[i], id + 1, weights);
    DP(memo, currWeight,              id + 1, weights);
    DP(memo, currWeight - weights[i], id + 1, weights);
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int numWeights;
    cin >> numWeights;

    vector<int> weights(numWeights);
    for (int i = 0; i < numWeights; ++i)
    {
        cin >> weights[i];
    }

    int numBeads;
    cin >> numBeads;

    vector<int> beads(numBeads);
    for (int i = 0; i < numBeads; ++i)
    {
        cin >> beads[i];
    }

    vector<vector<bool>> memo(numWeights + 1, vector<bool>(max(40'001, numWeights * 500 + 1)));
    DP(memo, 0, 0, weights);

    for (int bead : beads)
    {
        bool result = false;

        for (auto& line : memo)
        {
            
            if (line[bead])
            {
                result = true;
                break;
            }
            
        }
        cout << (result ? 'Y' : 'N') << " ";
    }
    cout << endl;
        
    return 0;
}