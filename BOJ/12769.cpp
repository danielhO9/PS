#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

// b가 커지면 b진법으로 표현한 수도 작아질 것이다.
// b가 10이면 y, b가 y면 10이 됨. (b >= 10)
// b가 10에서 증가할수록 해당 값은 빠른 속도로 감소.
// b가 y에 가까워지면 감소 속도가 감소한다.
// 10진법 -> 19자리
// 100진법 -> 10자리
// 1000진법 -> 7자리
// 10000진법 -> 5자리
// 100000진법 -> 4자리 -> 10^5 * 60번
// 1000000진법보다 큼. -> 3자리 -> 10^4 * 60
// 10000000진법 -> 3자리

ll y, l; ll answer = 10;

ll answer_accep, times_accep;
ll acceptable(ll y, ll x) {
    answer_accep = 0; times_accep = 1;
    while (y > 0) {
        if (y % x > 9) return 0;
        answer_accep += times_accep * (y % x);
        times_accep *= 10;
        y /= x;
    }
    return answer_accep;
}

ll start, stop, mid; ll value;
ll getting_b(ll x) {
    start = 10, stop = 1e18;
    while (start < stop) {
        mid = (start + stop) / 2;
        if (x >= 100) {
            if (mid > 1e9) stop = mid - 1;
            else {
                value = mid * mid * (x / 100) + mid * ((x / 10) - (x / 100) * 10) + (x % 10);
                if (value == y) return mid;
                else if (value > y) stop = mid - 1;
                else start = mid + 1; 
            }
        } else {
            value = mid * (x / 10) + (x % 10);
            if (value == y) return mid;
            else if (value > y) stop = mid - 1;
            else start = mid + 1; 
        }
    }
    mid = (start + stop) / 2;
    if (x >= 100) {
        if (mid > 1e9) return 0;
        else {
            value = mid * mid * (x / 100) + mid * ((x / 10) - (x / 100) * 10) + (x % 10);
            if (value == y) return mid;
            else return 0;
        }
    } else {
        value = mid * (x / 10) + (x % 10);
        if (value == y) return mid;
        return 0;
    }
}

int main() {
    cin >> y >> l;
    for (ll i = 10; i <= 1e6; ++i) {
        if (acceptable(y, i)) {
            if (acceptable(y, i) < l) break;
            answer = max(answer, i);
        }
    }
    if (l < 1e4) {
        for (ll i = 999; i >= l; --i) {
            answer = max(answer, getting_b(i));
        }
    }
    cout << answer;
    return 0;
}