#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int H, W; cin >> H >> W;
	cout << min(H, W) * 100 / 2;
}