#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Resource
{
    Resource() = default;
    Resource(int _gold, int _silver, int _switchingVolume)
        : gold(_gold)
        , silver(_silver)
        , switchingVolume(_switchingVolume)
    {}

    int gold = 0;
    int silver = 0;
    int switchingVolume = 0;

    Resource& operator+=(const Resource& other)
    {
        gold += other.gold;
        silver += other.silver;
        switchingVolume += other.switchingVolume;

        return *this;
    }
};

Resource ComputeTransportVolume(int g, int s, int w, int t, long long time)
{
    // 주어진 시간에 도시가 운송할 수 있는 최대량
    long long totalTransportableVolume = ((time + t) / (2 * t)) * w;

    int transportableGold = (int)min((long long)g, totalTransportableVolume);

    totalTransportableVolume -= transportableGold;

    int transportableSilver = (int)min((long long)s, totalTransportableVolume);

    int leftSilver = max(s - transportableSilver, 0);
    int switchingVolume = min(leftSilver, transportableGold);

    return Resource{ transportableGold, transportableSilver, switchingVolume };
}

pair<int, int> ComputeTransportVolume(
    int b,
    const vector<int>& g, const vector<int>& s, 
    const vector<int>& w, const vector<int>& t, long long time)
{
    int numCities = (int)g.size();
    Resource transportableResource;

    for (int i=0; i<numCities; ++i)
    {
        transportableResource += ComputeTransportVolume(g[i], s[i], w[i], t[i], time);
    }

    if (transportableResource.silver < b)
    {
        // 모자란 은
        int requiredSilver = b - transportableResource.silver;
        // 은으로 변환할 금
        int switchingVolume = min(transportableResource.switchingVolume, requiredSilver);

        transportableResource.gold -= switchingVolume;
        transportableResource.silver += switchingVolume;
    }

    return { transportableResource.gold, transportableResource.silver };
}

long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    long long answer = -1;

    long long low = 0;
    // (g[i] 최대 + s[i] 최대) / w 최소 * (t 왕복 최대) 
    long long high = 2 * 1e9 / 1 * 2 * 1e5 + 1;
    // check(low) => false, check(high) => true

    while (low + 1LL < high)
    {
        long long mid = (low + high) >> 1;

        pair<int, int> transportableVolume = ComputeTransportVolume(b, g, s, w, t, mid);
        int gold = transportableVolume.first;
        int silver = transportableVolume.second;

        if (gold >= a && silver >= b)
        {
            high = mid;
        }   
        else
        {
            low = mid;
        }
    }
    answer = high;

    return answer;
}

/*
    주어진 시간에 할당량을 만족할 수 있는가 확인하는 함수
    주어진 시간에 각 도시별 최대 할당량
    금 먼저 채울 수 있으면 채우고 난 뒤에 남은 걸로 은을 채운다.
    (금으로 채워졌지만 은으로 바꿀 수 있는 양)
*/
#include <iostream>

int main()
{
    int a = 90;
    int b = 500;
    vector<int> g = {70, 70, 0};
    vector<int> s = {0, 0, 500};
    vector<int> w = {100, 100, 2};
    vector<int> t = {4, 8, 1};

    cout << solution(a, b, g, s, w, t) << endl;
    return 0;
}