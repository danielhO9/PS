#include <bits/stdc++.h>
using namespace std;

const double K = 0.5;


int N, M;
vector<tuple<int, int, int>> v;
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dist(0.0, 1.0);
bool state[100];
int opt_val;
bool opt_state[100];
int score[100];

bool f(int x) {
    if (x > 0) return state[abs(x) - 1];
    else return !state[abs(x) - 1];
}

int getE() {
    int ret = 0;
    for (auto [x1, x2, x3]: v) if (f(x1) || f(x2) || f(x3)) ++ret;
    if (ret > opt_val) {
        opt_val = ret;
        for (int i = 0; i < N; ++i) opt_state[i] = state[i];
    }
    return ret;
}

void simulated_annealing() {
    for (int i = 0; i < 150000; ++i) {
        double t = (1.0 - i / 150000.0);
        int e1 = getE();
        int idx = gen() % N;
        state[idx] ^= 1;
        int e2 = getE();
        double p = exp((double)(e2 - e1) / (K * t));
        if (p < dist(gen)) state[idx] ^= 1;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int x1, x2, x3; cin >> x1 >> x2 >> x3;
        v.push_back({x1, x2, x3});
        if (x1 > 0) ++score[x1 - 1];
        else --score[-x1 - 1];
        if (x2 > 0) ++score[x2 - 1];
        else --score[-x2 - 1];
        if (x3 > 0) ++score[x3 - 1];
        else --score[-x3 - 1];
    }

    for (int i = 0; i < N; ++i) if (0.5 < dist(gen)) state[i] ^= 1;
    getE();

    simulated_annealing();

    if (opt_val == M) {
        cout << 1 << '\n';
        for (int i = 0; i < N; ++i) cout << opt_state[i] << ' ';
    } else cout << 0;
}