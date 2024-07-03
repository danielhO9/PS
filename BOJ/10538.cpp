#include <bits/stdc++.h>
using namespace std;

string draw[2000];
int cnt[2000][2000];
vector<int> pi;

int toNumber(char x) {
	if (x == 'x') return 1;
	else return 0;
};

struct TrieNode {
	TrieNode* children[2];
	TrieNode* failure;
	int terminal;
	TrieNode() {
		terminal = 0;
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < 2; ++i) if (children[i]) delete children[i];
	}
	void insert(const char* key, int type) {
		if (*key == 0) terminal = type;
		else {
			int next = toNumber(*key);
			if (children[next] == NULL) children[next] = new TrieNode();
			children[next]->insert(key + 1, type);
		}
	}
};

void getFailure(TrieNode* trie) {
	queue<TrieNode*> Q;
	trie->failure = trie;
	for (int i = 0; i < 2; ++i) if (trie->children[i]) {
		trie->children[i]->failure = trie;
		Q.push(trie->children[i]);
	}
	while(!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop();
		for (int i = 0; i < 2; ++i) if (here->children[i]) {
			TrieNode* there = here->children[i];
			TrieNode* p = here->failure;
			while (p != trie && p->children[i] == NULL) p = p->failure;
			if (p->children[i]) p = p->children[i];
			else p = trie;
			there->failure = p;
			if (p->terminal) there->terminal = p->terminal;
			Q.push(there);
		}
	}
}

// N[...i] 접두사와 접미사가 같은 최대 길이(본인 제외)
vector<int> getPartialMatch(const string& N) {
	int m = N.size(); 
	vector<int> pi(m, 0);
	int begin = 1, matched = 0;
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

// 짚더미 H의 부분 문자열이 바늘 N인 index
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) ret.push_back(begin);
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

int query(string& s, TrieNode* trie) {
	TrieNode* p = trie;
	for (int i = 0; i < s.size(); ++i) {
		int next = toNumber(s[i]);
		while (p != trie && p->children[next] == NULL) p = p->failure;
		if (p->children[next]) p = p->children[next];
		else p = trie;
		if (p->terminal) return p->terminal;
	}
	return 0;
}

void solve() {
	int hp, wp, hm, wm; cin >> hp >> wp >> hm >> wm;
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < hp; ++i) {
		cin >> draw[i];
		trie->insert(draw[i].c_str(), i + 1);
	}
	getFailure(trie);
	string H;
	for (int i = 0; i < hm; ++i) for (int j = 0; j < wm; ++j) {
		char tmp; cin >> tmp;
		H += tmp;
	}
	TrieNode* p = trie;
	for (int i = 0; i < H.size(); ++i) {
		int next = toNumber(H[i]);
		while (p != trie && p->children[next] == NULL) p = p->failure;
		if (p->children[next]) p = p->children[next];
		else p = trie;
		int y = i / wm, x = i % wm;
		cnt[y][x] = p->terminal;
	}
	// for (int i = 0; i < hm; ++i) {
	// 	for (int j = 0; j < wm; ++j) cout << cnt[i][j] << ' ';
	// 	cout << '\n';
	// }
	string N = "";
	for (int i = 0; i < hp; ++i) {
		N += query(draw[i], trie) + '0';
	}
	pi = getPartialMatch(N);
	// cout << N;
	int ans = 0;
	for (int i = wp - 1; i < wm; ++i) {
		string H;
		for (int j = 0; j < hm; ++j) H += cnt[j][i] + '0';
		ans += kmpSearch(H, N).size();
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}