#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }
int n, d, k, c;
vector<int> sushis;

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> d >> k >> c;
    sushis.resize(n);
    for (int i=0; i<n; ++i)
    {
        cin >> sushis[i];
    }

    vector<int> sushiNum(d+1, 0);
    int answer = 0;
    // init
    for (int i=0; i<k; ++i)
    {
        int sushi = sushis[i];
        if (sushiNum[sushi] == 0)
            ++answer;

        ++sushiNum[sushi];
    }
    if (sushiNum[c] == 0)
        ++answer;
    ++sushiNum[c];

    int cnt = answer;
    for (int i=0; i<n; ++i)
    {
        int j = (i + k) % n;

        int Isushi = sushis[i];
        int Jsushi = sushis[j];

        --sushiNum[Isushi];
        if (sushiNum[Isushi] == 0)
            --cnt;

        if (sushiNum[Jsushi] == 0)
            ++cnt;
        ++sushiNum[Jsushi];
        
        answer = max(answer, cnt);

    }

    cout << answer << endl;
    return 0;
}