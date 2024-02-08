#include <bits/stdc++.h>
using namespace std;

int n, a[100000], d[100000];
string s;
bool isOn[100000];
vector<int> ans;

void solution() {
	ans.clear();
	cin >> n;
	cin >> s;
	for (int i = 0; i < n; ++i) isOn[i] = (s[i] == '1');
	for (int i = 0; i < n; ++i) { cin >> a[i]; --a[i]; }
	for (int i = 0; i < n; ++i) d[i] = 0;
	for (int i = 0; i < n; ++i) ++d[a[i]];
	vector<int> Q;
	for (int i = 0; i < n; ++i) if (d[i] == 0) Q.push_back(i);
	while (!Q.empty()) {
		int ba = Q.back();
		Q.pop_back();
		if (isOn[ba]) {
			ans.push_back(ba);
			isOn[ba] = 0;
			isOn[a[ba]] = (isOn[a[ba]] == 0);
		}
		--d[a[ba]];
		if (d[a[ba]] == 0) Q.push_back(a[ba]);
	}
	for (int i = 0; i < n; ++i) if (isOn[i]) {
		Q.clear();
		int index = i;
		int onSum = 0;
		while (true) {
			if (isOn[index]) ++onSum;
			Q.push_back(index);
			index = a[index];
			if (index == i) break;
		}
		if (onSum % 2 == 1) {
			cout << -1 << '\n';
			return;
		}
		vector<int> v1, v2;
		while (true) {
			if (index == i) {
				isOn[index] = 0;
				v1.push_back(index);
				index = a[index];
				if (index == i) break;
				continue;
			}
			if ((isOn[index] && (v1.empty() || a[v1.back()] != index)
			|| (!isOn[index] && !v1.empty() && a[v1.back()] == index))) v1.push_back(index);
			if ((isOn[index] && (v2.empty() || a[v2.back()] != index)
			|| (!isOn[index] && !v2.empty() && a[v2.back()] == index))) v2.push_back(index);
			isOn[index] = 0;
			index = a[index];
			if (index == i) break;
		}
		if (v1.size() > v2.size()) for (auto i: v2) ans.push_back(i);
		else for (auto i: v1) ans.push_back(i);
	}
	cout << ans.size() << '\n';
	for (auto i: ans) cout << i + 1 << " ";
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) solution();
}

/*
8
5
11101
4 3 4 2 2
2
10
2 1
10
0000000011
9 10 10 7 10 9 9 9 10 2
10
1000111101
9 3 8 9 2 1 3 7 2 7
10
0001101010
5 7 6 10 8 3 6 6 2 2
10
0101100010
8 7 7 9 9 4 1 4 2 7
10
1010111010
7 9 10 7 7 2 8 6 10 4
10
1110000001
3 10 10 1 10 8 6 3 2 1
*/