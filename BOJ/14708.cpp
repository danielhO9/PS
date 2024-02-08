#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll K, k, z;
ll answer; vector<ll> answer_vector = {0, 0, 0};

ll zCreater(ll x, ll y) { return K / (x * y); }

void solution(ll x) {
    ll y = x;
    while (true) {
        z = zCreater(x, y);
        if (x * y * z < K) ++z;
        if (y > z) break;
        if (answer > x*y + y*z + z*x) {
            answer = x*y + y*z + z*x; answer_vector = {x, y, z};
        }
        ++y;
    }
}

int main() {
    cin >> K;
    k = static_cast<ll>(ceil(cbrt(K)));
    answer = LLONG_MAX;
    for (ll i = max(1LL, k - 3000); i <= k; ++i) {
        solution(i);
    }
    cout << answer_vector[0] << " " << answer_vector[1] << " " << answer_vector[2];
    return 0;
}