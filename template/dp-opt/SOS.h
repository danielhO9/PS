/**
 * Description: Sum over Subsets (SOS) DP.
 *  Computes $F[mask] = \sum_{submask \subseteq mask} a[submask]$ for all masks.
 *  The input array `a` does not need to have a size that is a power of two.
 * Time: $O(N \log N)$ where $N$ is the smallest power of two greater than or equal to the size of `a`.
 */
vector<ll> sosDP(const vector<ll>& a) {
    int sz = a.size();
    int n = (sz == 0) ? 0 : (int)ceil(log2(sz));
    vector<ll> ret(1 << n);
    for (int i = 0; i < sz; ++i) ret[i] = a[i];
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < (1 << n); ++x) {
            if (x & (1 << i)) ret[x] += ret[x ^ (1 << i)];
        }
    }
    return ret;
}

