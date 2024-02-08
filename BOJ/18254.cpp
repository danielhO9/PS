#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int N, M, Q;

struct sweeping {
	int p; LL x; int ind;
	bool operator < (const sweeping& o) const { return p < o.p; }
};

LL sum(vector<LL> &tree, int i) {
    LL ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}
void update(vector<LL> &tree, int i, LL diff) {
    while (i < tree.size()) {
        tree[i] += diff;
        i += (i & -i);
    }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> Q;
	vector<LL> A(N + 1);
	// A[i] = A[0] ^ A[1] ... ^ A[i]
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
		A[i] ^= A[i - 1];
	}
    vector<LL> fstTree(N + 1), conTree(N + 1);
	// M번 연산
	vector<LL> prefixA(N + 1);
	vector<pair<int, int>> upd; upd.push_back({1, 1});
	for (int i = 0; i < M; ++i) {
		int l, r; LL x; cin >> l >> r >> x;
		upd.push_back({l, r});
		prefixA[l] ^= x;
		if (r != N) prefixA[r + 1] ^= x;
	}
	vector<LL> xorA(N + 1);
	for (int i = 1; i <= N; ++i) xorA[i] = prefixA[i] ^ xorA[i - 1];
	for (int i = 1; i <= N; ++i) xorA[i] ^= xorA[i - 1];
	for (int i = 1; i <= N; ++i) A[i] ^= xorA[i];
	// 1번 쿼리(구간별)
	vector<deque<sweeping>> B(Q / 100 + 1);
	// 2번 쿼리
	vector<pair<int, int>> two;
	// 1번 쿼리에 속한 2번쿼리들
	// 구간합이 짝수라면 xor
	vector<vector<int>> one;
	// 2번 쿼리의 정답
	vector<LL> ans;
	for (int i = 0; i <= N; ++i) prefixA[i] = 0, xorA[i] = 0;
	int index = 0, cnt = -1, first = 0;
	vector<LL> prefixB(M + 1);
	for (LL j = 0; j < Q; ++j) {
		if (j != 0 && j % 100 == 0) {
			++index; first = cnt + 1;
			for (int i = 0; i <= N; ++i) prefixA[i] = 0, xorA[i] = 0;
			LL tB = 0;
			for (int i = 0; i <= M; ++i) {
				// tB: i번째 연산에 적용될 수
				tB ^= prefixB[i];
				auto l = upd[i].first, r = upd[i].second;
				prefixA[l] ^= tB;
				if (r != N) prefixA[r + 1] ^= tB;
			}
			for (int i = 1; i <= N; ++i) xorA[i] = prefixA[i] ^ xorA[i - 1];
			for (int i = 1; i <= N; ++i) xorA[i] ^= xorA[i - 1];
			for (int i = 1; i <= N; ++i) A[i] ^= xorA[i];
			for (int i = 0; i <= M; ++i) prefixB[i] = 0;
		}
		int what; cin >> what;
		if (what == 1) {
			int L, R; LL v; cin >> L >> R >> v;
			++cnt;
			B[index].push_back({L - 1, v, cnt});
			B[index].push_back({R, v, cnt});
			one.push_back({});

			prefixB[L] ^= v;
			if (R != M) prefixB[R + 1] ^= v;
		} else {
			int s, e; cin >> s >> e;
			ans.push_back(A[e] ^ A[s - 1]);
			if (cnt != -1) {
				for (auto j = first; j <= cnt; ++j) one[j].push_back(two.size());
			}
			two.push_back({s, e});
		}
	}
	// for (auto i: ans) cout << i << ' ';
	for (int i = 0; i < (Q / 100 + 1); ++i) sort(B[i].begin(), B[i].end());
	for (int i = 0; i <= M; ++i) {
		auto l = upd[i].first, r = upd[i].second;
		update(fstTree, l, 1);
		if (r != N) update(fstTree, r + 1, -1);
		update(conTree, l, -l + 1);
		if (r != N) update(conTree, r + 1, -r);
		for (int b = 0; b < (Q / 100 + 1); ++b) {
			while (!B[b].empty() && B[b].front().p == i) {
				LL x = B[b].front().x; int ind = B[b].front().ind; B[b].pop_front();
				for (auto j: one[ind]) {
					// cout << j << ' ';
					int s = two[j].first, e = two[j].second;
					LL value = (sum(fstTree, e) * e + sum(conTree, e)) - (sum(fstTree, s - 1) * (s - 1) + sum(conTree, s - 1));
					if (value % 2 == 0) ans[j] ^= x;
				}
			}
		}
	}
	for (auto i: ans) cout << i << '\n';
}