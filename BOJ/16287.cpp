#include <bits/stdc++.h>
using namespace std;

int w, n, a[5000];
bool visited[800000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> w >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (a[i] + a[j] < w && visited[w - a[i] - a[j]]) {
				cout << "YES";
				return 0;
			}
		}
		for (int j = 0; j < i; ++j) {
			if (a[i] + a[j] < w) visited[a[i] + a[j]] = 1;
		}
	}
	cout << "NO";
	return 0;
}