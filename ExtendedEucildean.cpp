#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// it returns {g, {x,y}}, ax+by=g
pair<ll, pair<ll, ll>> exEucild(ll a, ll b) {
	bool inv = a < b;
	if (inv) swap(a, b);
    if (b == 0) return {a, {1, 0}};
    pair<ll, pair<ll, ll>> ret = exEucild(b, a % b);
    ll g, x, y;
    g = ret.first;
    x = ret.second.first, y = ret.second.second;
    if (inv) return {g, {x - (a / b) * y, y}};
	else return {g, {y, x - (a / b) * y}};
}