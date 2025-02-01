#include <bits/stdc++.h>
using namespace std;

int N, Q;
double x[200001];
double y[200001];
double dis[200001];
double idis[200001];
double sm[200001];
double ism[200001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> Q;
	for (int i = 1; i <= N; ++i) cin >> x[i];
	for (int i = 1; i <= N; ++i) cin >> y[i];
	for (int i = 1; i < N; ++i) {
		dis[i] = hypot(x[i + 1] - x[i], y[i + 1] - y[i]);
		idis[i] = dis[i];
		if (abs(y[i] - y[i + 1]) < 1e-4) {
			dis[i] *= 2;
			idis[i] *= 2;
		}
		else if (y[i] < y[i + 1]) dis[i] *= 3;
		else idis[i] *= 3;
	}
	for (int i = 1; i < N; ++i) sm[i] = dis[i] + sm[i - 1];
	for (int i = 1; i < N; ++i) ism[i] = idis[i] + ism[i - 1];
	cout.precision(5);
	cout << fixed;
	while (Q--) {
		int i, j; cin >> i >> j;
		if (i <= j) cout << sm[j - 1] - sm[i - 1] << '\n';
		else cout << ism[i - 1] - ism[j - 1] << '\n';
	}
}