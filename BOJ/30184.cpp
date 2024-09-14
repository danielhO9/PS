#include <bits/stdc++.h>
using namespace std;

int N;
string T;
vector<int> ans;
int now = 0;

vector<char> ans;

int f(int x) {
	if (x == N) return now;
	if (T[x + 1] != T[x]) {
		ans.push_back(T[x]);
		return f(x + 2);
	}
	int pos = now;
	

}

void solve() {
	cin >> N >> T;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}