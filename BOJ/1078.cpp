#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll D, inf = 1e14; ll answer = inf;

// 가장 처음과 가장 마지막의 차이의 값을 최대 6개까지 시도해본다.
// 차이의 값이 n개라면, 2n자리, 2n + 1자리를 계산한다.
// 111,111

vector<ll> times = {1, 10, 100, 1000, 10000, 100000};
vector<vector<ll>> memo(12);

ll answer_temp;
ll answerCal(const vector<ll>& dif, ll answer_len) {
    answer_temp = 0;
    for (ll i = 0; i < (answer_len + 1) / 2; ++i) {
        if (i == 0) {
            if (dif[i] == 0) answer_temp += times[answer_len] + times[0];
            else answer_temp += times[answer_len] * dif[i];
        } else {
            if (dif[i] >= 0) answer_temp += times[answer_len - i] * dif[i];
            else answer_temp += times[i] * (-dif[i]);
        }
    }
    return answer_temp;
}

ll leng, value;
void solution(vector<ll>& dif) {
    value = 0; leng = dif.size();
    for (ll i = 0; i < leng; ++i) value += memo[leng * 2 - 1][i] * dif[i];
    if (value * 9 == D) { answer = min(answer, answerCal(dif, leng * 2 - 1)); return; }
    if (leng != 6) {
        value = 0;
        for (ll i = 0; i < leng; ++i) value += memo[leng * 2][i] * dif[i];
        if (value * 9 == D) { answer = min(answer, answerCal(dif, leng * 2)); return; }
    }
    if (leng == 6) { return; }
    for (ll i = -9; i < 10; ++i) {
        dif.push_back(i);
        solution(dif);
        dif.pop_back();
    }
    return;
}

int main() {
    cin >> D;
    for (ll i = 0; i < 10; ++i) times.push_back(times.back() * 10);

    memo[1].push_back(1);
    for (ll i = 2; i <= 11; ++i) memo[i].push_back(memo[i - 1].front() * 10 + 1);
    for (ll i = 3; i <= 11; ++i) {
        for (ll j = 0; j < (i + 1) / 2 - 1; ++j) {
            memo[i].push_back(memo[i].back() / 100);
        }
    }
    for (ll i = 0; i <= 11; ++i) {
        for (ll j = 0; j < memo[i].size(); ++j) memo[i][j] *= times[j];
    }

    for (ll i = 0; i < 10; ++i) {
        vector<ll> temp = {i};
        solution(temp);
    }
    if (answer == inf) cout << -1;
    else cout << answer;
    return 0;
}