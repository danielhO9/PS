#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M, K;
ll dis[3000][3000];
char board[3000][3000];
ll deg[3000][3000];
ll MAX = 987654321;

ll dy[4] = {0, 0, 1, -1};
ll dx[4] = {1, -1, 0, 0};

void solve() {
	cin >> N >> M >> K;
	memset(dis, -1, sizeof(dis));
	for (ll i = 0; i < N; ++i) for (ll j = 0; j < M; ++j) deg[i][j] = 2;
    for (ll i = 0; i < K; ++i) {
        ll R, C; cin >> R >> C; --R; --C;
        board[R][C] = 'G';
    }
	queue<pair<ll, ll>> q;

	for (ll i = 0; i < N; ++i) for (ll j = 0; j < M; ++j) {
		if (board[i][j] == 'G') {
			dis[i][j] = 0;
			deg[i][j] = 0;
		}
	}
	
	for (ll i = 0; i < N; ++i) for (ll j = 0; j < M; ++j) {
		if (board[i][j] == 'G') {
			for (ll k = 0; k < 4; ++k) {
				ll ni = i + dy[k], nj = j + dx[k];
				if (0 <= ni && ni < N && 0 <= nj && nj < M) --deg[ni][nj];
				if (0 <= ni && ni < N && 0 <= nj && nj < M && dis[ni][nj] == -1 && deg[ni][nj] == 0) q.push({ni, nj});
			}
		}
	}

	while (!q.empty()) {
		ll y = q.front().first, x = q.front().second; q.pop();
		ll f = MAX, s = MAX;
		for (ll i = 0; i < 4; ++i) {
			ll ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < N && 0 <= nx && nx < M && dis[ny][nx] != -1) {
				if (f >= dis[ny][nx] + 1) {
					s = f;
					f = dis[ny][nx] + 1;
				} else if (s >= dis[ny][nx] + 1) {
					s = dis[ny][nx] + 1;
				}
			}
		}
		dis[y][x] = s;
		for (ll i = 0; i < 4; ++i) {
			ll ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < N && 0 <= nx && nx < M && dis[ny][nx] == -1) {
				--deg[ny][nx];
				if (deg[ny][nx] == 0) {
					q.push({ny, nx});
				}
			}
		}
		
	}
    ll ans = 0;
    for (ll i = 0; i < N; ++i) for (ll j = 0; j < M; ++j) if (dis[i][j] != -1) ans += dis[i][j];
    cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}