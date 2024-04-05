#include <bits/stdc++.h>
using namespace std;

int calc(char& i) { return i - 'A'; }

struct TrieNode {
	TrieNode* children[3];
	TrieNode* failure;
	int terminal;
	int cache[1001];
	TrieNode() {
		terminal = 0;
		for (int i = 0; i < 3; ++i) children[i] = NULL;
		for (int i = 0; i <= 1000; ++i) cache[i] = INT32_MIN;
	}
	~TrieNode() {
		for (int i = 0; i < 3; ++i) if (children[i]) delete children[i];
	}
	void insert(const char* key) {
		if (*key == 0) terminal += 1;
		else {
			char next = *key;
			if (!children[calc(next)]) children[calc(next)] = new TrieNode();
			children[calc(next)]->insert(key + 1);
		}
	}
};

void getFailure(TrieNode* trie) {
	queue<TrieNode*> Q;
	trie->failure = trie;
	for (auto there: trie->children) if (there) {
		there->failure = trie;
		Q.push(there);
	}
	while(!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop();
		for (int i = 0; i < 3; ++i) if (here->children[i]) {
			TrieNode* p = here->failure;
			while (p != trie && !p->children[i]) p = p->failure;
			if (p->children[i]) p = p->children[i];
			else p = trie;
			here->children[i]->failure = p;
			if (p->terminal) here->children[i]->terminal += p->terminal;
			Q.push(here->children[i]);
		}
	}
}

void solve() {
	TrieNode* trie = new TrieNode();
	int N, K; cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		string S; cin >> S;
		trie->insert(S.c_str());
	}
	getFailure(trie);
	int ans = -1;
	for (int i = 0; i < 3; ++i) if (trie->children[i]) {
		trie->children[i]->cache[1] = trie->children[i]->terminal;
		ans = max(ans, trie->children[i]->cache[1]);
	}
	vector<TrieNode*> V;
	queue<TrieNode*> Q;
	for (int i = 0; i < 3; ++i) if (trie->children[i]) Q.push(trie->children[i]);
	while (!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop(); V.push_back(here);
		for (int j = 0; j < 3; ++j) {
			if (here->children[j]) {
				Q.push(here->children[j]);
			}
		}
	}
	for (int i = 2; i <= K; ++i) {
		for (auto here: V) {
			if (here->cache[i - 1] == INT32_MIN) continue;
			for (int j = 0; j < 3; ++j) {
				TrieNode* p = here;
				while (p != trie && !p->children[j]) p = p->failure;
				if (p->children[j]) p = p->children[j];
				else continue;
				p->cache[i] = max(p->terminal + here->cache[i - 1], p->cache[i]);
				ans = max(ans, p->cache[i]);
			}
		}
	}
	cout << ans;
	delete trie;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}