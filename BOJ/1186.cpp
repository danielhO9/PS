#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
	int x1, y1, x2, y2;
};

int K, N;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	vector<Rectangle> v;
	set<int> xs, ys;
	for (int i = 0; i < N; ++i) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		v.push_back({x1, y1, x2, y2});
		xs.insert(x1); xs.insert(x2);
		ys.insert(y1); ys.insert(y2);
	}
	vector<int> xv, yv;
	for (auto i: xs) xv.push_back(i);
	for (auto i: ys) yv.push_back(i);
	
	unordered_map<int, int> xm, ym;
	int xcnt = 0;
	for (auto i: xv) xm[i] = xcnt++;
	int ycnt = 0;
	for (auto i: yv) ym[i] = ycnt++;
	int val[xcnt - 1][ycnt - 1];
	for (int i = 0; i < xcnt - 1; ++i) for (int j = 0; j < ycnt - 1; ++j) {
		val[i][j] = (xv[i + 1] - xv[i]) * (yv[j + 1] - yv[j]);
	}
	reverse(v.begin(), v.end());
	priority_queue<pair<int, int>> pq;
	int cnt = N;
	for (auto& r: v) {
		int c = 0;
		for (int i = xm[r.x1]; i < xm[r.x2]; ++i) for (int j = ym[r.y1]; j < ym[r.y2]; ++j) {
			c += val[i][j];
			val[i][j] = 0;
		}
		pq.push({c, -cnt}); --cnt;
	}
	vector<int> ans;
	while (K--) {
		auto cur = pq.top(); pq.pop();
		ans.push_back(-cur.second);
	}
	sort(ans.begin(), ans.end());
	for (auto i: ans) cout << i << ' ';
	


}

