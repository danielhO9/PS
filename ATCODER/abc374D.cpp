#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, S, T;
int A[6], B[6], C[6], D[6];
vector<int> ord;
double ans = 987654321.0;
bool used[6];

double dist(int a, int b, int c, int d) {
	
	double tmp = (a - c) * (a - c) + (b - d) * (b - d);
	return sqrt(tmp);
}

void calc() {
	for (int i = 0; i < (1 << N); ++i) {
		// cout << i << '\n';
		for (int j = 0; j < N; ++j) if ((i >> j) & 1) {
			swap(A[j], C[j]); swap(B[j], D[j]);
		}

		int a = 0, b = 0;
		double cnt = 0.0;
		for (int k = 0; k < N; ++k) {
			cnt += (double)  dist(a, b, A[ord[k]], B[ord[k]]) / S;
			cnt += (double) dist(A[ord[k]], B[ord[k]], C[ord[k]], D[ord[k]]) / T;
			a = C[ord[k]]; b = D[ord[k]];
		}
		ans = min(ans, cnt);

		for (int j = 0; j < N; ++j) if ((i >> j) & 1) {
			swap(A[j], C[j]); swap(B[j], D[j]);
		}
	}
	
}

void getOrd() {
	if (ord.size() == N) {
		calc();
		return;
	}
	for (int i = 0; i < N; ++i) if (!used[i]) {
		used[i] = true;
		ord.push_back(i);
		getOrd();
		used[i] = false;
		ord.pop_back();
	}
}

void solve() {
	cin >> N >> S >> T;
	for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i] >> D[i];
	getOrd();
	cout << fixed;
	cout.precision(10);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}