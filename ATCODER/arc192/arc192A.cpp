#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int A[200000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	if (N % 4 == 0) cout << "Yes";
	else if (N % 4 == 1 || N % 4 == 3) {
		bool flag = false;
		for (int i = 0; i < N; ++i) if (A[i]) flag = true;
		if (flag) cout << "Yes";
		else cout << "No";
	} else {
		vector<int> tmp;
		for (int i = 0; i < N; ++i) if (A[i]) tmp.push_back(i);
		if (tmp.size() < 2) cout << "Yes";
		else {
			for (int i = 0; i + 1 < tmp.size(); ++i) {
				int cur = tmp[i], nxt = tmp[i + 1];
				if ((nxt - cur) % 2) {
					cout << "Yes";
					return;
				}
			}
			cout << "No";
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}