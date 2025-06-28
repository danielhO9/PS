#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://casterian.net
// return {gcd, x, y}, ax + by = gcd
tuple<ll, ll, ll> extended_euclidean(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x, y] = extended_euclidean(b, a % b);
    return {g, y, x - (a / b) * y};
}