#include <bits/stdc++.h>
using namespace std;

int N, s;

bool query(char t1, int num1, char t2, int num2) {
	cout << "? " << t1 << ' ' << num1 << ' ' << t2 << ' ' << num2 << '\n';
	cout << flush;
	bool ret; cin >> ret;
	return ret;
}

void solve() {
	cin >> N >> s;
	if (s == 1) {
		for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
			if (query('A', i, 'B', j)) {
				cout << "! 1\n";
				cout << flush;
				return;
			}
		}
		cout << "! 0\n";
		return;
	}
	
	vector<int> v;
	for (int i = 1; i <= N; ++i) v.push_back(i);
	shuffle(v.begin(), v.end(), default_random_engine());

	vector<int> Aidx;
	for (int i = 0; i < N; ++i) {
		if (Aidx.size() == 26) {
			cout << "! 1\n";
			cout << flush;
			return;
		}
		if (Aidx.empty()) {
			Aidx.push_back(v[i]);
			continue;
		}
		bool flag = false;
		for (int j: Aidx) {
			if (query('A', j, 'A', v[i])) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			Aidx.push_back(v[i]);
		}
	}

	shuffle(v.begin(), v.end(), default_random_engine());
	vector<int> Bidx;
	for (int i = 0; i < N; ++i) {
		if (Aidx.size() + Bidx.size() > 26) {
			cout << "! 1\n";
			cout << flush;
			return;
		}
		if (Bidx.empty()) {
			Bidx.push_back(v[i]);
			continue;
		}
		bool flag = false;
		for (int j: Bidx) {
			if (query('B', j, 'B', v[i])) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			Bidx.push_back(v[i]);
		}
	}
	for (auto i: Aidx) for (auto j: Bidx) {
		if (query('A', i, 'B', j)) {
			cout << "! 1\n";
			cout << flush;
			return;
		}
	}
	cout << "! 0\n";
	cout << flush;
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}