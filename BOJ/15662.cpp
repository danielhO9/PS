#include <bits/stdc++.h>
using namespace std;

int T;
deque<int> wheel[1000];
int way[1000];

void query(int num, int type) {
	memset(way, 0, sizeof(way));
	way[num] = type;
	for (int i = num + 1; i < T; ++i) {
		if (wheel[i - 1][2] == wheel[i][6]) break;
		way[i] = (-1) * way[i - 1];
	}
	for (int i = num - 1; i >= 0; --i) {
		if (wheel[i + 1][6] == wheel[i][2]) break;
		way[i] = (-1) * way[i + 1];
	}
	for (int i = 0; i < T; ++i) {
		if (way[i] == 1) {
			wheel[i].push_front(wheel[i].back());
			wheel[i].pop_back();
		} else if (way[i] == -1) {
			wheel[i].push_back(wheel[i].front());
			wheel[i].pop_front();
		}
	}
}

void solve() {
	cin >> T;
	for (int i = 0; i < T; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < 8; ++j) {
			wheel[i].push_back(tmp[j] - '0');
		}
	}
	int K; cin >> K;
	for (int i = 0; i < K; ++i) {
		int num, type; cin >> num >> type; --num;
		query(num, type);
	}
	int ret = 0;
	for (int i = 0; i < T; ++i) if (wheel[i][0] == 1) ++ret;
	cout << ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}