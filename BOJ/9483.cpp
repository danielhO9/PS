#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool radixSort(vector<int>& rk, int k) {
    const int n = rk.size();
    int m = *max_element(rk.begin(), rk.end());
    if (n == m) return false;
    vector<int> sr(n), srk(n);
    vector<int> cnt(m + 1);

    vector<int> rkk(n);
    for (int i = 0; i < n; ++i) {
        if (i + k < n) rkk[i] = rk[i + k];
        else rkk[i] = 0;
    }

    for (auto i: rkk) ++cnt[i];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) srk[--cnt[rkk[i]]] = i;
    reverse(srk.begin(), srk.end());

    for (auto& i: cnt) i = 0;
    for (auto i: rk) ++cnt[i];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) {
        int j = srk[i];
        sr[--cnt[rk[j]]] = j;
    }

    vector<int> nrk(n);
    m = 1; nrk[sr[0]] = m;
    for (int i = 1; i < n; ++i) {
        int cur = sr[i], prv = sr[i - 1];
        if (rk[cur] != rk[prv] || rkk[cur] != rkk[prv]) ++m;
        nrk[cur] = m;
    }
    swap(nrk, rk);
    return true;
}

vector<int> getSuffixArray(const string& s) {
    const int n = s.size();
    const int m = 255;
    vector<int> cnt(m);
    for (auto i: s) cnt[i] = 1;
    for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];

    vector<int> rk(n);
    for (int i = 0; i < n; ++i) rk[i] = cnt[s[i]];
    int k = 1;
    while (radixSort(rk, k)) k *= 2;

    vector<int> sfx(n);
    for (int i = 0; i < n; ++i) sfx[rk[i] - 1] = i;
    return sfx;
}

vector<ll> getLcp(const string& s, const vector<int>& sfx) {
	const int n = s.size();
	vector<ll> inv(n), lcp(n);
	for (int i = 0; i < n; ++i) inv[sfx[i]] = i;
	int h = 0;
	for(int i = 0; i < n; ++i) if (inv[i]) {
		int prv = sfx[inv[i] - 1];
		while (s[prv + h] == s[i + h]) ++h;
		lcp[inv[i]] = h;
		h = max(h - 1, 0);
	}
	return lcp;
}

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	const ll dValue = LLONG_MAX; // TODO
	int sz;

	ll merge(ll a, ll b) { return min(a, b); }
	SegmentTree(int sz) : SegmentTree(vector<ll>(sz, dValue)) {}
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val;
			tree[node] += val;
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return dValue;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

string S;
ll n;

ll query(SegmentTree& seg, vector<int>& inv, int i, int j, bool rev = false) {
    if (rev) {
        i = n - 1 - i;
        j = n - 1 - j;
    }
    i = inv[i]; j = inv[j];
    if (i > j) swap(i, j);
    return seg.query(i + 1, j);
}

void solve() {
    n = S.size();
    vector<int> sfx = getSuffixArray(S);
    vector<ll> lcp = getLcp(S, sfx);
    vector<int> inv(n); for (int i = 0; i < n; ++i) inv[sfx[i]] = i;
    SegmentTree seg {lcp};

    string rS = S;
    reverse(rS.begin(), rS.end());
    vector<int> rsfx = getSuffixArray(rS);
    vector<ll> rlcp = getLcp(rS, rsfx);
    vector<int> rinv(n); for (int i = 0; i < n; ++i) rinv[rsfx[i]] = i;
    SegmentTree rseg {rlcp};

    ll ans = 0;
    for (ll len = 1; len <= n; ++len) {
        vector<pair<ll, ll>> v;
        for (ll i = 0; i < n; i += len) v.push_back(make_pair(i, min(i + len - 1, n - 1)));
        for (int i = 1; i < v.size(); ++i) {
            ll lcl = query(rseg, rinv, v[i].second, v[i - 1].second, true);
            lcl = min(lcl, v[i].second - v[i].first + 1);
            if (lcl == len) {
                // cout << v[i].first << ' ' << len << '\n';
                ++ans;
            }
            if (i + 1 < v.size()) {
                ll lcr = query(seg, inv, v[i].first, v[i + 1].first);
                lcr = min(lcr, v[i + 1].second - v[i + 1].first + 1);
                ll l = len - lcl;
                ll r = min(lcr, len - 2);
                if (l <= r) ans += (r - l + 1);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> S;
        if (S[0] == '0') break;
        solve();
    }
}