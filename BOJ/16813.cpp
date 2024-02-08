#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct song {
    int t; ll p, f;

    bool operator < (const song& var) const {
        return f < var.f;
    }
};

struct Line {
    ll slope, y_value;
    mutable double meet;

    bool operator < (const Line& var) const {
        if (slope == var.slope) {return y_value > var.y_value;}
		return slope < var.slope;
	}

    bool operator < (ll x) const {return meet < x;}
};

struct LineContainer: set<Line, less<>> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        if (next(a) == end()) { a->meet = 10001.0; return false; }
        if (a->slope == next(a)->slope) a->meet = a->y_value >= next(a)->y_value ? 10001.0 : 0.0;
        else a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(ll slope, ll y_value) {
        auto ite = insert({slope, y_value, 0}).first;
        while (removeNext(ite)) {erase(next(ite)); removeNext(ite); } //ite의 meet값 조정됨
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, T; cin >> N >> T;
    vector<song> songs;
    int t; ll p, f;
    songs.push_back({0, 0, 0});
    for (int i = 0; i < N; ++ i) {
        cin >> t >> p >> f;
        songs.push_back({t, p, f});
    }
    sort(songs.begin(), songs.end());

    vector<vector<ll>> dp(N + 1, vector<ll>(T + 1, 0));
    vector<LineContainer> graph(T + 1);
    vector<ll> answer;
    for (int i = 1; i <= N; ++i) {
        if (i == 1) {
            for (int j = 1; j <= T; ++j) {
                if (songs[i].t <= j) {
                    dp[i][j] = songs[i].p;
                    graph[j].add(2 * songs[i].f, dp[i][j] - songs[i].f * songs[i].f);
                    if (j == T) answer.push_back(dp[i][j]);
                }
            }
        } else {
            for (int j = 1; j <= T; ++j) {
                if (songs[i].t <= j) {
                    if (graph[j - songs[i].t].empty()) dp[i][j] = songs[i].p;
                    else {
                        Line line = *graph[j - songs[i].t].lower_bound(songs[i].f);
                        dp[i][j] = max(songs[i].p, line.slope * songs[i].f + line.y_value - songs[i].f * songs[i].f + songs[i].p);
                    }
                    if (j == T) answer.push_back(dp[i][j]);
                }
            }

            for (int j = 1; j <= T; ++j) {
                if (songs[i].t <= j) {
                    graph[j].add(2 * songs[i].f, dp[i][j] - songs[i].f * songs[i].f);
                }
            }
        }
    }
    cout << *max_element(answer.begin(), answer.end());

    return 0;
}