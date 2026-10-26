#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 200001 * 2;
 
int A[MAXN];

string s;
int n;

bool palin(int l, int r) {
	++l; ++r;
	l *= 2; r *= 2; --l; --r;
	int mid = (l + r) / 2;
	if (A[mid] >= mid - l) return true;
	return false;
}

void manachers(string S, int N)
{
    int r = 0, p = 0;
    for (int i = 0; i < N; i++)
    {
        if (i <= r)
            A[i] = min(A[2 * p - i], r - i);
        else
            A[i] = 0;
 
        while (i - A[i] - 1 >= 0 && i + A[i] + 1 < N && S[i - A[i] - 1] == S[i + A[i] + 1])
            A[i]++;
 
        if (r < i + A[i])
        {
            r = i + A[i];
            p = i;
        }
    }
}


void solve() {
	cin >> n;
	int q; cin >> q;
	cin >> s;
	vector<int> same(n), isame(n);

	string str;
    int len = s.size();
    for (int i = 0; i < len; i++)
    {
        str += '#';
        str += s[i];
    }
    str += '#';
    manachers(str, str.size());


	for (int i = 0; i < n; ++i) { same[i] = i; isame[i] = min(i + 1, n - 1); }
	for (int i = 0; i < n; ++i) {
		if (i != 0 && same[i - 1] >= same[i]) {
			same[i] = same[i - 1]; continue;
		}
		int x = i;
		while (x + 1 < n && s[x + 1] == s[i]) ++x;
		same[i] = x;
	}
	// for (int i = 0; i < n; ++i) cout << same[i] << ' ';
	for (int i = 0; i < n; ++i) {
		if (i != 0 && isame[i - 1] >= isame[i]) {
			isame[i] = isame[i - 1]; continue;
		}
		if (i >= n - 2) continue;
		char a = s[i], b = s[i + 1];
		int x = i;
		while (x + 1 < n){
			if ((x + 1) % 2 == i % 2 && s[x + 1] == a) {
				++x; continue;
			}
			if ((x + 1) % 2 != i % 2 && s[x + 1] == b) {
				++x; continue;
			}
			break;
		}
		isame[i] = x;
	}
	// for (int i = 0; i < n; ++i) cout << isame[i] << ' ';
	while (q--) {
		int l, r; cin >> l >> r; --l; --r;
		ll len = r - l + 1; 
		ll ans = 0;
		bool doit = false;
		if (same[l] < r) {
			ll temp = len / 2;
			ans += temp * (temp + 1);
			if (len % 2 == 0) doit = true;
		}
		if (isame[l] < r) {
			ll temp = (len - 1) / 2;
			ans += temp * (temp + 1);
			ans += temp;
			if (len % 2 != 0) doit = true;
		}
		if (doit && palin(l, r)) {	
			ans -= len;
		}

		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}