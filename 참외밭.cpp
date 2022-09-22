#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int k;
vector<pair<int,int> > points;
//int points[7][2]; // 원점(0,0)이 두 번 생김
//int draw[5][2] = {{0,0}, {1,0}, {-1,0}, {0,-1}, {0,1}};
vector<pair<int, int> > draw;
int x[3];
int y[3];
int dir, len;
int answer=0;
vector<pair<int, int> > unsort;

bool cmp(pair<int, int> a, pair<int, int> b){
    return a.second < b.second;
}

void make_draw(){
    draw.push_back(pair<int, int> (0,0));
    draw.push_back(pair<int, int> (1,0));
    draw.push_back(pair<int, int> (-1,0));
    draw.push_back(pair<int, int> (0,-1));
    draw.push_back(pair<int, int> (0,1));
}

int main(){
    cin >> k;

    make_draw();

    points.push_back(pair<int,int>(0,0));
    for(int i=1; i < 7; i++){
        cin >> dir >> len;
        /*
        for(int j = 0; j < 2; j ++){
            points[i][j] = points[i-1][j] + draw[dir][j] * len;
        }
        */
        points.push_back(pair<int, int>(
            points[i-1].first + draw[dir].first * len, points[i-1].second + draw[dir].second * len));
    }

    for(pair<int, int> i: points){
        cout << i.first << " " << i.second << endl;
    }

    cout << endl;

    unsort = points; //같은 주소를 사용하는것이 아니고 값을 복사하는 것인가?

    sort(points.begin(),points.end());

    x[0] = points[0].first;
    x[1] = points[3].first;
    x[2] = points[6].first;

    sort(points.begin(),points.end(), cmp);

    /*
    sort(points.begin(), points.end(),
    [](pair<int, int> a, pair<int, int> b){
        return a.second < b.second;
    });
    */

    y[0] = points[0].second;
    y[1] = points[3].second;
    y[2] = points[6].second;

    for(int i=0; i < 3; i++){
        cout << x[i] << " " << y[i]<< endl;
    }

    for(int i =1; i < unsort.size(); i++){
        int a = unsort[i].first;
        int b = unsort[i].second;
        if(a == x[2] && b == y[2]){
            answer = answer + (x[2] - x[1]) * (y[2] - y[1]);
        }
        if(a == x[0] && b == y[2]){
            answer = answer + (x[1] - x[0]) * (y[2] - y[1]);
        }
        if(a == x[0] && b == y[0]){
            answer = answer + (x[1] - x[0]) * (y[1] - y[0]);
        }
        if(a == x[2] && b == y[0]){
            answer = answer + (x[2] - x[1]) * (y[1] - y[0]);
        }
    }

    for(pair<int, int> i: unsort){
        cout << i.first << " " << i.second << endl;
    }
    cout << answer * k << endl;

    return 0;
}