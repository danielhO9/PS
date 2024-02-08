#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct Line {
    LL slope, y_value;
    mutable double meet;

    bool operator < (const Line& var) const {
		return slope < var.slope;
	}

    bool operator < (LL x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = static_cast<double>(45 * 1e6); return false; }
        a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(LL slope, LL y_value) {
        auto ite = insert({slope, y_value, 0}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }
};

vector<LineContainer> lines(305);
LL dp[305][305];
bool visited[305][305];
LL q[305][305][305];
LL S[305][305];
LL SS[305][305];

void dfs(LL i, LL j) {
    visited[i][j] = true;
    LL answer = -(1e16);
    for (LL k = i; k <= j; ++k) {
        if (i <= k - 1 && !visited[i][k - 1]) dfs(i, k - 1);
        if (k + 1 <= j && !visited[k + 1][j]) dfs(k + 1, j);
        Line line = *lines[k].lower_bound(q[i][j][k]);
        answer = max(answer, dp[i][k - 1] + dp[k + 1][j] + line.slope * q[i][j][k] + line.y_value);
    }
    dp[i][j] = answer;
    // cout << i << " " << j << "->" << answer << endl;
}

int main() {
    LL N; cin >> N;
    // q[쿼리 시작점][쿼리 끝점][해당 위치]
    // S[i][j] = Q[i][i] + ... + Q[i][j]
    // SS[i][j] = S[1][j] + ... + S[i][j]
    LL temp;
    for (LL i = 1; i < N + 1; ++i) {
        for (LL j = i; j < N + 1; ++j) {
            cin >> temp;
            S[i][j] = S[i][j - 1] + temp;
        }
    }
    for (LL i = 1; i < N + 1; ++i) {
        for (LL j = 1; j < N + 1; ++j) SS[j][i] = SS[j - 1][i] + S[j][i];
    }
    for (LL i = 1; i < N + 1; ++i) {
        for (LL j = i; j < N + 1; ++j) {
            for (LL k = i; k <= j; ++k) q[i][j][k] = SS[k][j] - SS[i - 1][j] + SS[i - 1][k - 1] - SS[k][k - 1];
        }
    }
    LL K, V, C;
    for (LL i = 1; i < N + 1; ++i) {
        cin >> K;
        for (LL j = 0; j < K; ++j) {
            cin >> V >> C;
            lines[i].add(V, -C);
        }
    }
    for (LL i = 1; i < N + 1; ++i) {
        // cout << i << endl;
        // for (Line element: lines[i]) {
        //     cout << element.slope << " " << element.y_value << " " << element.meet << endl;
        // }
    }
    dfs(1, N);
    cout << dp[1][N] << "\n";
    return 0;
}