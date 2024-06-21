#include <bits/stdc++.h>
using namespace std;

void solve() {
	string a, b; int c;
	cin >> a >> b >> c;
	int tmp = stoi(a+b);
	cout << stoi(a) + stoi(b) - c << '\n';
	cout << stoi(a + b) - c;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}