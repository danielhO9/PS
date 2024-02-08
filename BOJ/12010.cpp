#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

deque<int> L, R;
int N, X, Y, Z;
LL ans;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> X >> Y >> Z; int a, b;
	for (int i = 0; i < N; ++i) {
		cin >> a >> b;
		for (int j = 0; j < abs(a - b); ++j) {
			if (a > b) {
				if (L.empty()) {
					ans -= -Y;
					R.push_front(-Y - Z * i);
				} else {
					ans -= max(-Y, L.back() - Z * i);
					R.push_front(max(-Y, L.back() - Z * i) - Z * i);
					L.pop_back();
				}
			} else {
				if (R.empty()) {
					ans += X;
					L.push_back(X + Z * i);
				} else {
					ans += min(X, R.front() + Z * i);
					L.push_back(min(X, R.front() + Z * i) + Z * i);
					R.pop_front();
				}
			}
		}
	}
	cout << ans;
}