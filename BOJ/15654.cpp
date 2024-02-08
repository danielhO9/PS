#include <bits/stdc++.h>
using namespace std;

int N, M, arr[8];
vector<int> Q;

void solution(int l) {
	if (Q.size() == M) {
		for (auto i: Q) cout << i << " ";
		cout << "\n";
		return;
	}
	if (l >= N) return;
	bool switc = false;
	for (int i = 0; i < N; ++i) {
		switc = false;
		for (auto j: Q) if (j == arr[i]) {
			switc = true;
			break;
		}
		if (!switc) {
			Q.push_back(arr[i]);
			solution(i);
			Q.pop_back();
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> arr[i];
	sort(arr, arr + N);
	for (int i = 0; i < N; ++i) {
		Q.push_back(arr[i]);
		solution(i);
		Q.pop_back();
	}
}