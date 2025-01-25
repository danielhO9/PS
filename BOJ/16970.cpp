#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

int N, M, K;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;
	int ans = 0;
	for (int x1 = 0; x1 <= N; ++x1) for (int x2 = 0; x2 <= N; ++x2) {
		for (int y1 = 0; y1 <= M; ++y1) for (int y2 = 0; y2 <= M; ++y2) {
			int cnt;
			int xdif = abs(x2 - x1), ydif = abs(y2 - y1);
			if (x1 == x2 || y1 == y2) cnt = xdif + ydif + 1;
			else {	
				int g = gcd(xdif, ydif);
				cnt = g + 1;
			}
			if (cnt == K) ++ans;
		}
	}
	cout << ans / 2;
}