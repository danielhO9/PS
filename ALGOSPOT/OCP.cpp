#include <bits/stdc++.h>
using namespace std;

int q, m, R[100], choice[101][501], n;
double T[500][500], M[500][500], cache[101][501], B[500];
unordered_map<string, int> dict;
string corpus[500];

double recognize(int segment, int previousMatch) {
	if (segment == n) return 0;
	double& ret = cache[segment + 1][previousMatch + 1];
	if (ret != 1.0) return ret;
	ret = -1e200;
	int& choose = choice[segment + 1][previousMatch + 1];
	for (int thisMatch = 0; thisMatch < m; ++thisMatch) {
		double cand = M[thisMatch][R[segment]] + recognize(segment + 1, thisMatch);
		if (previousMatch != -1) cand += T[previousMatch][thisMatch];
		else cand += B[thisMatch];
		if (ret < cand) { ret = cand; choose = thisMatch; }
	}
	return ret;
}

string reconstruct(int segment, int previousMatch) {
	int choose = choice[segment + 1][previousMatch + 1];
	string ret = corpus[choose];
	if (segment < n - 1) ret = ret + " " + reconstruct(segment + 1, choose);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> m >> q;
	string word;
	for (int i = 0; i < m; ++i) {
		cin >> word;
		dict[word] = i;
		corpus[i] = word;
	}
	double temp;
	for (int i = 0; i < m; ++i) {
		cin >> temp;
		B[i] = log(temp);
	}
	for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) {
		cin >> temp;
		T[i][j] = log(temp);
	}
	for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) {
		cin >> temp;
		M[i][j] = log(temp);
	}
	for (int i = 0; i < q; ++i) {
		cin >> n;
		for (int j = 0; j < n; ++j) {
			cin >> word;
			R[j] = dict[word];
		}
		for (int i = 0; i < n + 1; ++i) for (int j = 0; j < m + 1; ++j) cache[i][j] = 1.0;
		recognize(0, -1); cout << reconstruct(0, -1) << "\n";
	}
}