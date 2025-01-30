#include <bits/stdc++.h>
using namespace std;

int N, M;
int arr[9][9];
unordered_map<int, int> cache[9][9];
int pow_10[9];
int tmp[10], cnt;
const int MAX = 987654321;

int getDigit(int num, int i) {
	int ret = num / pow_10[i];
	return ret % 10;
}

int normalize(int state) {
	memset(tmp, 0, sizeof(tmp));
	cnt = 0;
	int nstate = 0;
	for (int i = 0; i < M; ++i) {
		int cur = getDigit(state, i);
		if (cur != 0 && tmp[cur] == 0) tmp[cur] = ++cnt;
	}
	for (int i = 0; i < M; ++i) {
		int cur = getDigit(state, i);
		nstate += pow_10[i] * tmp[cur];
	}
	// cout << state << ' ' << nstate << '\n';
	return nstate;
}

int matchCache(int y, int x, int state) {
	if (y == N) {
		bool flag = true;
		for (int i = 0; i < M; ++i) if (getDigit(state, i) >= 2) flag = false;
		if (flag) return 0;
		return MAX;
	}
	if (cache[y][x].find(state) != cache[y][x].end()) return cache[y][x][state];
	int& ret = cache[y][x][state];
	int nx = (x + 1) % M;
	int ny = nx == 0 ? y + 1 : y;
	ret = MAX;

	bool flag = false;
	for (int i = 0; i <= M - 2; ++i) if (getDigit(state, M - 1) == getDigit(state, i)) {
		flag = true;
		break;
	}
	if (getDigit(state, M - 1) == 0 || flag) {
		int nstate = state - pow_10[M - 1] * getDigit(state, M - 1);
		nstate *= 10;
		nstate = normalize(nstate);
		ret = min(ret, matchCache(ny, nx, nstate));
	}

	int nstate;
	if (getDigit(state, M - 1) == 0 && (x == 0 || getDigit(state, 0) == 0)) {
		nstate = state * 10 + 9;
	} else if (getDigit(state, M - 1) != 0 && x != 0 && getDigit(state, 0) != 0) {
		int f = getDigit(state, M - 1);
		int s = getDigit(state, 0);
		nstate = state - pow_10[M - 1] * f;
		nstate *= 10;
		nstate += s;
		for (int i = 0; i < M; ++i) if (getDigit(nstate, i) == f) {
			nstate -= pow_10[i] * getDigit(nstate, i);
			nstate += pow_10[i] * s;
		}
	} else {
		nstate = state - pow_10[M - 1] * getDigit(state, M - 1);
		nstate *= 10;
		if (getDigit(state, M - 1) != 0) nstate += getDigit(state, M - 1);
		else nstate += getDigit(state, 0);
	}
	nstate = normalize(nstate);
	ret = min(ret, arr[y][x] + matchCache(ny, nx, nstate));

	flag = true;
	for (int i = 0; i < M; ++i) if (getDigit(state, i) >= 2) flag = false;
	if (flag) ret = min(ret, 0);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> arr[i][j];
	pow_10[0] = 1;
	for (int i = 1; i < 9; ++i) pow_10[i] = pow_10[i - 1] * 10;
	cout << matchCache(0, 0, 0) << "\n";
}