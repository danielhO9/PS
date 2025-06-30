#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int ALPHABETS = 2;
int toNumber(char ch) { return ch - 'A'; };

struct TrieNode {
	TrieNode* children[ALPHABETS];
	int cnt;

	TrieNode(): cnt(0) { memset(children, 0, sizeof(children)); }
	~TrieNode() { for (int i = 0; i < ALPHABETS; ++i) if (children[i]) delete children[i]; }
	void insert(const ll& s, int idx = 0) {
		++cnt;
		if (idx == 60) return;
		else {
			int next = ((s >> idx) & 1);
			if (children[next] == nullptr) children[next] = new TrieNode();
			children[next]->insert(s, idx + 1);
		}
	}
};

int N;
ll X[200000];
int ans;

void dfs(TrieNode* trie, int used, int cnt) {
	if (trie->cnt < used) return;
	ans = max(ans, cnt);
	bool flag = false;
	for (int i = 0; i < 2; ++i) if (trie->children[i]) {
		flag = true;
		int nused = used;
		int left = trie->cnt - trie->children[i]->cnt;
		nused = max(0, nused - left);
		dfs(trie->children[i], nused + 1, cnt + 1);
	}
	if (!flag) ans = max(ans, cnt + trie->cnt - used);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
	for (int i = 0; i < N; ++i) cin >> X[i];
	TrieNode* trie = new TrieNode{};
	for (int i = 0; i < N; ++i) trie->insert(X[i]);
	dfs(trie, 0, 0);
	cout << ans;
}

/*
000101
100111
010011
011011
001011

*/