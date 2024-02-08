#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N; vector<ll> A(100000);

ll solution(vector<ll>& A, ll left, ll right) {
    if (left == right) return A[left] * A[left];
    ll mid = (left + right) / 2;
    ll ret = max(solution(A, left, mid), solution(A, mid + 1, right));
    ll lo = mid, hi = mid + 1;
    ll mini = min(A[lo], A[hi]), sum = A[lo] + A[hi];
    ret = max(ret, sum * mini);
    while (left < lo || hi < right) {
        if (hi < right && (left == lo || A[lo - 1] < A[hi + 1])) {
            ++hi;
            mini = min(mini, A[hi]);
            sum += A[hi];
        } else {
            --lo;
            mini = min(mini, A[lo]);
            sum += A[lo];
        }
        ret = max(ret, mini * sum);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    cout << solution(A, 0, N - 1);
    return 0;
}