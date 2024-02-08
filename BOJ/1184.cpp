#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N;
vector<vector<ll>> A(51, vector<ll>(51, 0));
vector<vector<ll>> S(51, vector<ll>(51, 0));
map<ll, ll> valuecnt;

ll solution(int y, int x) {
    ll ret = 0;
    valuecnt.clear();
    for (int i = 1; i <= y; ++i) {
        for (int j = 1; j <= x; ++j) {
            valuecnt[S[y][x] - S[y][j - 1] - S[i - 1][x] + S[i - 1][j - 1]]++;
        }
    }
    for (int i = y + 1; i <= N; ++i) {
        for (int j = x + 1; j <= N; ++j) {
            ret += valuecnt[S[i][j] - S[y][j] - S[i][x] + S[y][x]];
        }
    }
    valuecnt.clear();
    for (int i = 1; i <= y; ++i) {
        for (int j = x + 1; j <= N; ++j) {
            valuecnt[S[y][j] - S[y][x] - S[i - 1][j] + S[i - 1][x]]++;
        }
    }
    for (int i = y + 1; i <= N; ++i) {
        for (int j = 1; j <= x; ++j) {
            ret += valuecnt[S[i][x] - S[i][j - 1] - S[y][x] + S[y][j - 1]];
        }
    }
    return ret;
} 


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    ll answer = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> A[i][j];
            S[i][j] = S[i - 1][j] + S[i][j - 1] + A[i][j] - S[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= N - 1; ++i) {
        for (int j = 1; j <= N - 1; ++j) {
            answer += solution(i, j);
        }
    }
    cout << answer;
    return 0;
}