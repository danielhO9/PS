#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n1, n2; cin >> n1 >> n2;
	cout << (n2 - n1) * (n2 - n1 + 1) /2;
}