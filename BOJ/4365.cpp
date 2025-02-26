#include <bits/stdc++.h>
using namespace std;

vector<int> cur;

string toCard(int x) {
	string ret;
	if (x % 13 <= 8) ret += to_string((x % 13) + 2);
	else if (x % 13 == 9) ret += "Jack";
	else if (x % 13 == 10) ret += "Queen";
	else if (x % 13 == 11) ret += "King";
	else ret += "Ace";
	ret += " of ";
	if (x / 13 == 0) ret += "Clubs";
	else if (x / 13 == 1) ret += "Diamonds";
	else if (x / 13 == 2) ret += "Hearts";
	else ret += "Spades";
	return ret; 
}

void read() {
	for (auto i: cur) cout << toCard(i) << '\n';
	cout << '\n';
}

int n;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < 52; ++i) cur.push_back(i);
	int q[52][n];
	for (int i = 0; i < n; ++i) for (int j = 0; j < 52; ++j) {
		cin >> q[j][i];
		--q[j][i];
	}
	int k;
	while (cin >> k) {
		--k;
		vector<int> ncur(52);
		for (int i = 0; i < 52; ++i) ncur[i] = cur[q[i][k]];
		cur = ncur;
		// for (auto i: cur) cout << i << ' ';
		// cout << '\n';
		read();
	}
}