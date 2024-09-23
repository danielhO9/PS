#include <bits/stdc++.h>
using namespace std;

int N, M, Q;
int cnt = 0;

bool query(int x, int y) {
	++cnt;
	cout << "? " << x << ' ' << y << '\n';
	cout << flush;
	int ret; cin >> ret;
	return ret;
}

void solve() {
	cin >> N >> M >> Q;
	N = 1000; M = 100; Q = 950;

	vector<int> v;
	for (int i = 1; i <= N; ++i) v.push_back(i);
	random_device rd;
    mt19937 g(rd());
	shuffle(v.begin(), v.end(), g);

	vector<int> ret;

	vector<int> ans;
	vector<int> nans;
	for (int i = 0; i < 50; ++i) {
		ans.clear(); nans.clear();
		if (i == 49 && ret.size() == 0) {
			for (int j = 981; j < 1000; ++j) {
				bool dif = query(v[0], v[j]);
				if (dif) ret.push_back(v[j]);
			}
			if (ret.size() < 10) ret.push_back(v[980]);
			cout << "! ";
			for (auto i: ret) cout << i << ' ';
			cout << '\n';
			cout << flush;
			return;
		}
		for (int j = i * 20 + 1; j < i * 20 + 20; ++j) {
			bool dif = query(v[i * 20], v[j]);
			if (dif) nans.push_back(v[j]);
			else ans.push_back(v[j]);
		}
		ans.push_back(v[i * 20]);
		if (ans.size() == 10) {
			int tmp = (i + 1) % 50;
			bool dif = query(ans.front(), v[tmp * 20]);
			if (dif) {
				cout << "! ";
				for (auto i: ans) cout << i << ' ';
				cout << '\n';
				cout << flush;
				return;
			} else {
				cout << "! ";
				for (auto i: nans) cout << i << ' ';
				cout << '\n';
				cout << flush;
				return;
			}
		}
		if (ans.size() > nans.size()) {
			if (!nans.empty()) for (auto j: nans) ret.push_back(j);
		} else {
			if (!ans.empty()) for (auto j: ans) ret.push_back(j);
		}
	}
	cout << "! ";
	for (auto i: ret) cout << i << ' ';
	cout << '\n';
	cout << flush;
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}