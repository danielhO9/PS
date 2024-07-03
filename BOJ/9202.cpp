#include <bits/stdc++.h>
using namespace std;

char boggle[4][4];
bool vis[4][4];
int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int score = 0;
set<string> ans;
string word, mword;

int calc(int x) {
	if (x <= 2) return 0;
	else if (x <= 4) return 1;
	else if (x == 5) return 2;
	else if (x == 6) return 3;
	else if (x == 7) return 5;
	else return 11;
}

struct TrieNode {
	unordered_map<char, TrieNode*> children;
	bool terminal;
	TrieNode(): terminal(false) {
		
	}
	~TrieNode() {
		for (auto [i, _]: children) delete children[i];
	}
	void insert(const char* key) {
		if (*key == 0) terminal = true;
		else {
			char next = *key;
			if (children.find(next) == children.end()) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}
	bool find(const char* key) {
		if (*key == 0) return this->terminal;
		char next = *key;
		if (children.find(next) == children.end()) return false;
		return children[next]->find(key + 1);
	}
	bool remove(const char* key) {
		bool flag = true;
		if (*key == 0) {
			this->terminal = false;
			if (!children.empty()) flag = false;
			return flag;
		}
		if (this->terminal) return false;
		char next = *key;
		if (children[next]->remove(key + 1)) {
			delete children[next]; children.erase(next);
			for (auto [_, i]: children) flag = false;
			return flag;
		} else return false;
	}
	void query(int y, int x) {
		if (word.size() == 8) return;
		char next = boggle[y][x];
		if (children.find(next) == children.end()) return;
		vis[y][x] = true;
		word += next;
		if (children[next]->terminal) {
			ans.insert(word);
			if (mword.size() == word.size()) {
				mword = min(mword, word);
			} else if (mword.size() < word.size()) {
				mword = word;
			}
		}
		for (int i = 0; i < 8; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < 4 && 0 <= nx && nx < 4 && !vis[ny][nx]) children[next]->query(ny, nx);
		}
		vis[y][x] = false;
		word.pop_back();
	}
};

void solve() {
	int w; cin >> w;
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < w; ++i) {
		string s; cin >> s;
		trie->insert(s.c_str());
	}
	int b; cin >> b;
	for (int i = 0; i < b; ++i) {
		ans.clear(); score = 0; mword = "";
		for (int j = 0; j < 4; ++j) {
			string s; cin >> s;
			for (int k = 0; k < 4; ++k) boggle[j][k] = s[k];
		}
		for (int j = 0; j < 4; ++j) for (int k = 0; k < 4; ++k) {
			trie->query(j, k);
		}
		for (auto i: ans) score += calc(i.size());
		cout << score << ' ' << mword << ' ' << ans.size() << '\n';
	}
	delete trie;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}