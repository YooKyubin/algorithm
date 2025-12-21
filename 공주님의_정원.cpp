#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const static int MtoD[13] = 
{
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
};

int monthAcc[13] {};

struct Date
{
    Date(int month, int day)
    : value( monthAcc[month - 1] + day)
    {}

    bool operator==(const Date& other) const
    {
        return value == other.value;
    }
    bool operator<(const Date& other) const
    {
        return value < other.value;
    }
    bool operator<=(const Date& other) const
    {
        return value <= other.value;
    }
    bool operator>(const Date& other) const
    {
        return value > other.value;
    }

    int value;
};

struct Flower
{
    Flower(Date start, Date end)
    : start(start)
    , end(end)
    {}

    Date start;
    Date end;
};

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    for (int i = 1; i < 13; ++i)
    {
        monthAcc[i] = monthAcc[i-1] + MtoD[i];
    }

    int n;
    cin >> n;

    vector<Flower> flowers;
    flowers.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        int sm, sd, em, ed;
        cin >> sm >> sd >> em >> ed;
        flowers.push_back({ Date(sm, sd), Date(em, ed) });
    }

    sort(flowers.begin(),flowers.end(), 
        [](auto& src, auto& dst)->bool
        {
            if (src.start == dst.start)
            {
                return src.end < dst.end;
            }
            return src.start < dst.start;
        });


    const Date targetStart { 3, 1 };
    const Date targetEnd   { 11, 30 };

    Date currEnd = targetStart;
    int currID = 0;
    int answer = 0;

    while (currEnd <=targetEnd)
    {
        Date farthestEnd = currEnd;
        while (currID < n)
        {
            Flower currFlower = flowers[currID];
            if (currEnd < currFlower.start)
            {
                break;
            }
            farthestEnd = max(farthestEnd, currFlower.end);
            ++currID;
        }
        
        if (farthestEnd == currEnd)
        {
            break;
        }
        currEnd = farthestEnd;
        ++answer;
    }

    if (currEnd <= targetEnd)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << answer << endl;
    }
    
    return 0;
}

/*
    시작 날짤르 기준으로 정렬
    가능한 꽃 후보 선정, 후보 꽃은 시작날짜가 이전 꽃보다 앞선 꽃들
    꽃 후보들 중 끝날짜가 가장 먼 꽃 선택
    반복.
*/