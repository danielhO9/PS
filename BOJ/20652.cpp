#include <bits/stdc++.h>
using namespace std;

int N;
char dir[50];
int x[50], y[50];
int ans[50];

struct Meet {
    int t, i, j;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> dir[i] >> x[i] >> y[i];
    vector<Meet> v;
    for (int i = 0; i < N; ++i) ans[i] = INT32_MAX;
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
        if (dir[i] == dir[j]) {
            if (dir[i] == 'N' && x[i] == x[j]) v.push_back({abs(y[i] - y[j]), i, j});
            if (dir[i] == 'E' && y[i] == y[j]) v.push_back({abs(x[i] - x[j]), i, j});
        } else {
            if (dir[i] == 'N' && x[j] <= x[i] && y[j] >= y[i]) v.push_back({max(abs(y[i] - y[j]), abs(x[i] - x[j])), i, j});
            if (dir[i] == 'E' && x[i] <= x[j] && y[i] >= y[j]) v.push_back({max(abs(y[i] - y[j]), abs(x[i] - x[j])), i, j});
        }
    }
    sort(v.begin(), v.end(), [](const Meet& a, const Meet& b) {
        return a.t < b.t;
    });
    for (auto i: v) {
        int a = i.i, b = i.j;
		int ta, tb;
		if (dir[a] == dir[b]) {
			if (dir[a] == 'N') {
				ta = (y[a] < y[b] ? y[b] - y[a] : 0);
				tb = (y[a] < y[b] ? 0 : y[a] - y[b]);
			} else {
				ta = (x[a] < x[b] ? x[b] - x[a] : 0);
				tb = (x[a] < x[b] ? 0 : x[a] - x[b]);
			}
		} else {
			if (dir[a] == 'N') ta = y[b] - y[a], tb = x[a] - x[b];
			else ta = x[b] - x[a], tb = y[a] - y[b];
		}
		if (ta == tb) continue;
		if (ta < tb) {
			if (ans[a] < ta) continue;
			ans[b] = min(ans[b], tb);
		} else {
			if (ans[b] < tb) continue;
			ans[a] = min(ans[a], ta);
		}
    }
	for (int i = 0; i < N; ++i) {
		if (ans[i] == INT32_MAX) cout << "Infinity\n";
		else cout << ans[i] << '\n';
	}

}