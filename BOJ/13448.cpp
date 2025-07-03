#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Prob {
    ll M, P, R;
};

int N, T;
ll M[50], P[50], R[50];
ll cache[100001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> T;
    vector<Prob> v;
    for (int i = 0; i < N; ++i) cin >> M[i];
    for (int i = 0; i < N; ++i) cin >> P[i];
    for (int i = 0; i < N; ++i) cin >> R[i];
    for (int i = 0; i < N; ++i) v.push_back(Prob {M[i], P[i], R[i]});
    sort(v.begin(), v.end(), [](const Prob& a, const Prob& b) {
        return b.P * a.R < a.P * b.R;
    });
    for (int i = 0; i < N; ++i) {
        Prob cur = v[i];
        for (ll j = T; j >= 0; --j) {
            if (j - cur.R < 0) break;
            cache[j] = max(cache[j], cache[j - cur.R] + cur.M - j * cur.P);
        }
    }
    cout << *max_element(cache, cache + T + 1);
}