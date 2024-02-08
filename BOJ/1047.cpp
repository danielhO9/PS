#include <bits/stdc++.h>
using namespace std;
// 나무들의 무리로부터 한쪽으로 많이 떨어져 있다면 잘라내는 게 유리하다
// 잘라낼 후보: 나무를 많이 주는 친구 or 한쪽으로 가장 튀어나온 친구
// 2 ^ 40 - 절대 안됨. 한 번에 하나의 나무를 자르는 식으로 가면 무슨 일이 있어도 안된다
// 울타리를 기준으로 생각해야 한다.
// 나무들 중 두 개를 골라 두 나무를 양끝으로 하는 직사각형을 만든다. 40C2
// 각 직사각형에 대해 직사각형 외부의 나무를 모두 자르고, 직사각형 내부에서 가장 많은 나무를 주는 것부터 자른다.
int N, answer = 41;
map<int, int> x, y, wood;

int solution(int x1, int y1, int x2, int y2) {
    int ret = 0; vector<int> remomoveWoods; int preparewood = 0;
    int minx = min(x1, x2), maxx = max(x1, x2);
    int miny = min(y1, y2), maxy = max(y1, y2);
    for (int i = 0; i < N; ++i) {
        if (minx <= x[i] && x[i] <= maxx && miny <= y[i] && y[i] <= maxy) {
            remomoveWoods.push_back(wood[i]);
        } else {
            ret++;
            preparewood += wood[i];
        }
    }
    sort(remomoveWoods.begin(), remomoveWoods.end());
    while (preparewood < (maxx - minx + maxy - miny) * 2 && !remomoveWoods.empty()) {
        preparewood += remomoveWoods.back();
        remomoveWoods.pop_back();
        ret++;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> wood[i];

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                for (int l = k; l < N; ++l) {
                    answer = min(answer, solution(x[i], y[k], x[j], y[l]));
                }
            }
        }
    }
    
    cout << answer;
    return 0;
}