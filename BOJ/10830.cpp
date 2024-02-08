#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N;
vector<vector<int>> arr(5, vector<int>(5));
LL B;

vector<vector<int>> time(vector<vector<int>>& arr1, vector<vector<int>>& arr2) {
	vector<vector<int>> ret(5, vector<int>(5));
	for (int i = 0; i < N; ++i) for (int j = 0; j < 5; ++j) {
		ret[i][j] = 0;
		for (int k = 0; k < N; ++k) { ret[i][j] += arr1[i][k] * arr2[k][j]; ret[i][j] %= 1000; }
	}
	return ret;
}

vector<vector<int>> solution(vector<vector<int>>& a, LL m) {
	if (m == 1) return a;
	vector<vector<int>> par = solution(a, m / 2);
	auto ret = time(par, par);
	if (m % 2 == 0) return ret;
	auto ret2 = ret;
	ret2 = time(ret, arr);
	return ret2;
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> B;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) { cin >> arr[i][j]; arr[i][j] %= 1000; }
	auto ans = solution(arr, B);
	for (int i = 0; i < N; ++i) { for (int j = 0; j < N; ++j) cout << ans[i][j] << " "; cout << "\n"; }
}

