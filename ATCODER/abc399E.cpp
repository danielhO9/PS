#include <bits/stdc++.h>
using namespace std;

int N;
string S, T;
bool rem = false;
set<int> adj[26];
set<int> iadj[26];
int deg[26];

int dfs(int v, vector<int>& sccNum, stack<int>& S, vector<vector<int>>& scc, vector<int>& ord, int& cnt) {
	ord[v] = ++cnt; S.push(v);
	int result = ord[v];
	for (int u: adj[v]) {
		if (ord[u] == -1) result = min(result, dfs(u, sccNum, S, scc, ord, cnt));
		else if (sccNum[u] == -1) result = min(result, ord[u]);
	}
	if (result == ord[v]) {
		vector<int> temp;
		while (true) {
			int t = S.top(); S.pop();
			temp.push_back(t);
			sccNum[t] = scc.size();
			if (t == v) break;
		}
		sort(temp.begin(), temp.end());
		scc.push_back(temp);
	}
	return result;
}

void getSCC(vector<vector<int>>& scc, vector<int>& sccNum) {
	stack<int> S; vector<int> ord(26, -1); int cnt = -1;
	for (int i = 0; i < 26; ++i) if (ord[i] == -1) dfs(i, sccNum, S, scc, ord, cnt);
}

void solve() {
    cin >> N;
    cin >> S >> T;
    for (int i = 0; i < N; ++i) adj[S[i] - 'a'].insert(T[i] - 'a'), iadj[T[i] - 'a'].insert(S[i] - 'a');
    for (int i = 0; i < 26; ++i) for (auto j: adj[i]) ++deg[j];
    for (int i = 0; i < 26; ++i) if (adj[i].size() > 1) {
        cout << -1;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        if (adj[i].empty()) rem = true;
    }
    
    vector<vector<int>> scc;
	vector<int> sccNum(26, -1);
	getSCC(scc, sccNum);

    int ans = 0;
    for (int i = 0; i < 26; ++i) if (!adj[i].empty() && *adj[i].begin() != i) ++ans;
    if (rem == false) {
        for (auto g: scc) if (g.size() != 1) {
            for (auto i: g) if (deg[i] != 1) rem = true;
        }
        for (int i = 0; i < 26; ++i) {
            if (deg[i] != 1) rem= true;
        }
    }
    for (auto g: scc) {
        if (g.size() == 1) continue;
        bool flag = false;
        for (auto i: g) if (deg[i] != 1) flag = true;
        if (!flag && rem == 0) {
            cout << -1;
            return;
        }
        if (!flag) ++ans;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}