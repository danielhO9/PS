#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		double a, b; cin >> a >> b;
		int dif = b - a;
		vector<int> tmp = {50, 20, 10, 5, 1};
		for (auto i: tmp) {
			cout << dif / i << "-$" << i;
			if (i == 1) cout << "\n";
			else cout << ", ";
			dif %= i;
		}
	}	
}