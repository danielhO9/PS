#include <bits/stdc++.h>
using namespace std;

int N, S;
vector<int> arr[26];
vector<string> input[26];
vector<int> adj[26];
int deg[26];

void parse(string s) {
    vector<string> v;
    s += ' ';
    int l = -1;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') {
            if (l != -1) {
                v.push_back(s.substr(l, i - l));
                l = -1;
            }
        } else {
            if (l == -1) l = i;
        }
    }
    input[v[0][0] - 'A'] = v;

    if (v[1] == "%") {
        for (int i = 2; i < v.size(); ++i) {
            arr[v[0][0] - 'A'].push_back(stoi(v[i]));
        }
    } else {
        for (int i = 1; i < v.size(); ++i) {
            if ('A' <= v[i][0] && v[i][0] <= 'Z') {
                adj[v[i][0] - 'A'].push_back(v[0][0] - 'A');
                ++deg[v[0][0] - 'A'];
            }
        }
    }
}

int calc(const vector<string>& v) {
    double val = 0.0;
    double last = stod(v[0]);
    for (int i = 1; i < v.size(); i += 2) {
        if (v[i] == "+") {
            val += last;
            last = stod(v[i + 1]);
        } else if (v[i] == "-") {
            val += last;
            last = -stod(v[i + 1]);
        } else {
            assert(v[i] == "*");
            last *= stod(v[i + 1]);
        }
    }
    val += last;
    val = max(0.001, min(255.001, val));
    return val;
}

string read(const string& s, int idx) {
    if ('A' <= s[0] && s[0] <= 'Z') {
        int iidx = idx + stoi(s.substr(2, (int)s.size() - 3));
        if (0 <= iidx && iidx < S) return to_string(arr[s[0] - 'A'][iidx]);
        else return "0";
    }
    else return s;
}

string f_rec(int c, int& idx, int iidx) {
    assert(input[c][idx] == "(");
    ++idx;
    vector<string> v;
    while (true) {
        if (input[c][idx] == ")") break;
        if (input[c][idx] == "(") v.push_back(f_rec(c, idx, iidx));
        else if (input[c][idx].size() == 1) v.push_back(input[c][idx]);
        else v.push_back(read(input[c][idx], iidx));
        ++idx;
    }
    return to_string(calc(v));
}

void f(int c) {
    if (input[c][1] == "%") return;
    arr[c].resize(S);
    for (int i = 0; i < S; ++i) {
        int idx = 1;
        input[c][1] = "(";
        input[c].push_back(")");
        auto ret = f_rec(c, idx, i);
        arr[c][i] = stoi(ret);
    }
}

void solve() {
    cin >> N >> S;
    cin.ignore();
    for (int i = 0; i < 26; ++i) arr[i].clear();
    for (int i = 0; i < 26; ++i) input[i].clear();
    for (int i = 0; i < 26; ++i) adj[i].clear();
    for (int i = 0; i < 26; ++i) deg[i] = 0;
    for (int i = 0; i < N; ++i) {
        string s; getline(cin, s);
        parse(s);
    }
    queue<int> q;
    for (int i = 0; i < 26; ++i) if (!input[i].empty() && deg[i] == 0) q.push(i);
    while (!q.empty()) {
        int c = q.front(); q.pop();
        f(c);
        for (auto i: adj[c]) {
            --deg[i];
            if (deg[i] == 0) q.push(i);
        }
    }
    for (int i = 0; i < 26; ++i) if (!arr[i].empty() && input[i][1] != "%") {
        cout << (char)('A' + i) << " % ";
        for (auto j: arr[i]) cout << j << ' ';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int D; cin >> D;
    for (int i = 1; i <= D; ++i) {
        cout << "DATA SET #" << i << '\n';
        solve();
    }
}