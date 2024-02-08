#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N; vector<ll> A(100000);
pair<ll, ll> panswer = {0, 0};
ll answer = -1;

void solution(vector<ll>& A, ll left, ll right) {
    if (left == right) {
        if (answer < A[left] * A[left]) {
            answer = A[left] * A[left];
            panswer = {left, left};
        }
        return;
    }
    ll mid = (left + right) / 2;
    solution(A, left, mid); solution(A, mid + 1, right);
    ll lo = mid, hi = mid + 1;
    ll mini = min(A[lo], A[hi]), sum = A[lo] + A[hi];
    if (answer < sum * mini) {
        answer = sum * mini;
        panswer = {lo, hi};
    }
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
        if (answer < mini * sum) {
            answer = mini * sum;
            panswer = {lo, hi};
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    solution(A, 0, N - 1);
    cout << answer << "\n";
    cout << panswer.first + 1 << " " << panswer.second + 1;
    return 0;
}