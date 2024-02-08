#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> v;
int N, K;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; string ts; vector<string> tv;
	for (int i = 0; i < N; ++i) {
		cin >> K; tv.clear();
		for (int j = 0; j < K; ++j) {
			cin >> ts;
			tv.push_back(ts);
		}
		v.push_back(tv);
	}
	sort(v.begin(), v.end());
	tv.clear();
	for (auto way: v) {
		for (int i = 0; i < way.size(); ++i) {
			if (tv.size() <= i) {
				tv.push_back(way[i]);
				for (int j = 0; j < i; ++j) cout << "--";
				cout << way[i];
				cout << '\n';
			} else if (tv[i] != way[i]) {
				while (tv.size() > i) tv.pop_back();
				tv.push_back(way[i]);
				for (int j = 0; j < i; ++j) cout << "--";
				cout << way[i];
				cout << '\n';
			}
		}
	}
}