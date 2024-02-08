#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N; vector<ll> light(18, 1<<18);
int ret = 400;

vector<int> dy = {0, 0, 1, -1, 0};
vector<int> dx = {1, -1, 0, 0, 0};

void do_switch(int y, int x) {
    for (int i = 0; i < 5; ++i) {
        if (0 <= y + dy[i] && y + dy[i] < N && 0<= x + dx[i] && x + dx[i] < N) {
            light[y + dy[i]] ^= 1<<(x + dx[i]);
        }
    }
}


int switching(int x) {
    // if (x == 2) cout << light[0] - 262144 << endl;
    if (x == N) {
        for (int i = 0; i < N; ++i) {
            if (light[N - 1] == (light[N - 1] | 1 << i)) return 400;
        }
        return 0;
    }
    int cnt = 0;
    vector<int> push_temp;
    for (int i = 0; i < N; ++i) {
        if (light[x - 1] == (light[x - 1] | 1 << i)) {
            cnt += 1;
            do_switch(x, i);
            push_temp.push_back(i);
        }
    }
    int ret_temp = cnt + switching(x + 1);
    for (int i: push_temp) {
        do_switch(x, i);
    }
    return ret_temp;
}

void solution(int x, int cnt_temp) {
    if (x == N) {
        ret = min(ret, cnt_temp + switching(1));
        return;
    }
    solution(x + 1, cnt_temp);
    do_switch(0, x);
    solution(x + 1, cnt_temp + 1);
    do_switch(0, x);
}


int main() {
    cin >> N;
    int temp;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> temp;
            if (temp == 1) light[i] |= 1 << j;
        }
    }
    solution(0, 0);
    if (ret >= 400) cout << -1;
    else cout << ret;
    return 0;
}
// 1 0 0