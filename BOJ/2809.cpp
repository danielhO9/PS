#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
	unordered_map<char, TrieNode*> children;
	TrieNode* failure;
	int terminal;
	TrieNode(): terminal(0) {
		
	}
	~TrieNode() {
		for (auto [i, _]: children) delete children[i];
	}
	void insert(const char* key, int sz) {
		if (*key == 0) terminal = sz;
		else {
			char next = *key;
			if (children.find(next) == children.end()) children[next] = new TrieNode();
			children[next]->insert(key + 1, sz);
		}
	}
};

void getFailure(TrieNode* trie) {
	queue<TrieNode*> Q;
	trie->failure = trie;
	for (auto [_, there]: trie->children) {
		there->failure = trie;
		Q.push(there);
	}
	while(!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop();
		for (auto [i, there]: here->children) {
			TrieNode* p = here->failure;
			while (p != trie && p->children.find(i) == p->children.end()) p = p->failure;
			if (p->children.find(i) != p->children.end()) p = p->children[i];
			else p = trie;
			there->failure = p;
			if (p->terminal) there->terminal = max(p->terminal, there->terminal);
			Q.push(there);
		}
	}
}

void query(string& s, TrieNode* trie, vector<bool>& vis) {
	int last = -1;
	vector<pair<int, int>> V;
	TrieNode* p = trie;
	for (int i = 0; i < s.size(); ++i) {
		while (p != trie && p->children.find(s[i]) == p->children.end()) p = p->failure;
		if (p->children.find(s[i]) != p->children.end()) p = p->children[s[i]];
		else p = trie;
		if (p->terminal) {
			V.push_back({i - p->terminal + 1, i});
		}
	}
	sort(V.begin(), V.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		if (a.first == b.first) return a.second > b.second;
		return a.first < b.first;
	});
	for (auto [l, r]: V) {
		if (r <= last) continue;
		if (l <= last) for (int i = last + 1; i <= r; ++i) vis[i] = 0;
		else for (int i = l; i <= r; ++i) vis[i] = 0;
		last = r;
	}
}

void solve() {
	TrieNode* trie = NULL;
	int N; cin >> N;
	string tile; cin >> tile;
	vector<bool> vis(N, 1);
	int M; cin >> M; int cnt = 0;
	while (M--) {
		if (cnt % 300 == 0) {
			if (trie) {
				getFailure(trie);
				query(tile, trie, vis);
				delete trie;
			}
			trie = new TrieNode();
		}
		string L; cin >> L;
		trie->insert(L.c_str(), L.size());
		++cnt;
	}
	getFailure(trie);
	query(tile, trie, vis);
	delete trie;
	int ans = 0;
	for (int i = 0; i < N; ++i) if (vis[i]) ++ans;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}