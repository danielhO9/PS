#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    sort(A.begin(), A.end());
    int start, end;
    int answer = 0;
    for (int i = 0; i < N; ++i) {
        start = 0; end = N - 1;
        while (start < end) {
            if (start == i) { start++; continue;}
            else if (end == i) { end--; continue; }
            if (A[start] + A[end] > A[i]) end--;
            else if (A[start] + A[end] < A[i]) start++;
            else {answer ++; break;}
        }
    }
    cout << answer;
    return 0;
}