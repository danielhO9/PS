#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int x; cin >> x;
	if (x % 4 != 0) cout << 365;
	else if (x % 4 == 0 && x % 100 != 0) cout << 366;
	else if (x % 100 == 0 && x % 400 != 0) cout << 365;
	else if (x % 400 == 0) cout << 366;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}