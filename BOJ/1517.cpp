#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 해당 수보다 작은 수가 오른쪽에 있는 만큼
ll N; vector<ll> A(1000001); ll answer = 0;
vector<ll> ret(1000001);

void conquer(ll left, ll right) {
    ll mid = (left + right) / 2;
    ll i = left, j = mid + 1, now = left;
    while (i <= mid || j <= right) {
        if (i <= mid && (j > right || A[i] <= A[j])) {
            ret[now] = A[i]; ++i; ++now;
        } else {
            ret[now] = A[j]; ++j; ++ now;
            answer += mid - i + 1;
        }
    }
    for (ll k = left; k <= right; ++k) A[k] = ret[k];
}

void divide(ll left, ll right) {
    if (left == right) return;
    ll mid = (left + right) / 2;
    divide(left, mid); divide(mid + 1, right);
    conquer(left, right);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; ++i) cin >> A[i];
    divide(0, N - 1);
    // for (ll i = 0; i < N; ++i) cout << A[i] << " ";
    cout << answer;
    return 0;
}