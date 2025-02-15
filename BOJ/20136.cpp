#include <bits/stdc++.h>
using namespace std;

int N, K;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	vector<int> arr(K);
	for (int i = 0; i < K; ++i) cin >> arr[i];
	deque<int> pos[K + 1];
	for (int i = 0; i < K; ++i) pos[arr[i]].push_back(i);
	bool inQ[K + 1]; memset(inQ, 0, sizeof(inQ));
	int cnt = 0;
	int ans = 0;
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < K; ++i) {
		if (!inQ[arr[i]] && cnt == N) {
			while (!pq.empty()) {
				if (pq.top().first == INT32_MAX || pq.top().first == pos[pq.top().second].front()) {
					int j = pq.top().second;
					inQ[j] = false; --cnt;
					++ans;
					pq.pop();
					break;
				}
				pq.pop();
			}
		}
		if (!inQ[arr[i]]) {
			++cnt;
			inQ[arr[i]] = true;
		}
		pos[arr[i]].pop_front();
		if (pos[arr[i]].empty()) pq.push({INT32_MAX, arr[i]});
		else pq.push({pos[arr[i]].front(), arr[i]});
	}
	cout << ans;
}