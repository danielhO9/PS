#include <bits/stdc++.h>
using namespace std;

int N, C;
int cache[301];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> C;
	cache[0] = 1;
	for (int i = 0; i < C; ++i) {
		int c; cin >> c;
		for (int j = N; j >= 0; --j) if (j >= c) {
			for (int k = 1; k <= j / c; ++k) cache[j] += cache[j - k * c];
		}
	}
	cout << cache[N];
}