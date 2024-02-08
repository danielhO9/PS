#include <bits/stdc++.h>
using namespace std;

int table[3], ans[3][2], N, temp[3];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < 3; ++j) cin >> table[j];
		temp[0] = max(ans[0][0], ans[1][0]);
		temp[2] = max(ans[1][0], ans[2][0]);
		temp[1] = max(temp[0], temp[2]);
		for (int j = 0; j < 3; ++j) ans[j][0] = temp[j] + table[j];
		temp[0] = min(ans[0][1], ans[1][1]);
		temp[2] = min(ans[1][1], ans[2][01]);
		temp[1] = min(temp[0], temp[2]);
		for (int j = 0; j < 3; ++j) ans[j][1] = temp[j] + table[j];
	}
	cout << max({ans[0][0], ans[1][0], ans[2][0]}) << " " << min({ans[0][1], ans[1][1], ans[2][1]});
}