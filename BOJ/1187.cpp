#include <bits/stdc++.h>
using namespace std;
// k번째는 k-1번째 * 2 + 1로 구성된다.
// 각각은 N / 2의 배수, N/2(a+b), a+b가 2의 배수여야함

int N;
vector<int> arr(2048);
vector<int> visited(2048, 0);
vector<int> inde = {0};

void solution(vector<int>& ind, int left, int right, int num) {
    vector<int> send;
    // for (int i = 1; i <= 2 * N - 1; ++i) { cout << visited[i] << " "; }
    // cout << endl;
    // (right - left + 2) / 2
    if (right - left + 1 == 3) {
        if (arr[ind[left]] % 2 == arr[ind[left + 1]] % 2)  { visited[ind[left]] = num; visited[ind[left + 1]] = num; return; }
        if (arr[ind[left]] % 2 == arr[ind[left + 2]] % 2) { visited[ind[left]] = num; visited[ind[left + 2]] = num; return; }
        visited[ind[left + 1]] = num; visited[ind[left + 2]] = num; return;
    }
    solution(ind, left, (left + right) / 2 - 1, 1);
    solution(ind, (left + right) / 2, right - 1, 2);

    int sum1 = 0, sum2 = 0, sum3 = 0;
    for (int i = left; i <= right; ++i) {
        if (visited[ind[i]] == 0) send.push_back(ind[i]);
    }
    // cout << "send" << endl;
    // for (int i: send) cout << i << " ";
    // cout << endl;
    solution(send, 0, (right - left) / 2 - 1, 3);
    // for (int i = 1; i <= 2 * N - 1; ++i) { cout << visited[i] << " "; }
    // cout << endl;
    for (int i = left; i <= right; ++i) {
        if (visited[ind[i]] == 1) sum1 += arr[ind[i]];
        else if (visited[ind[i]] == 2) sum2 += arr[ind[i]];
        else if (visited[ind[i]] == 3) sum3 += arr[ind[i]];
    }
    if (sum1 % ((right - left + 2) / 2) == sum2 % ((right - left + 2) / 2)) {
        for (int i = left; i <= right; ++i) {
            if (visited[ind[i]] == 1 || visited[ind[i]] == 2) visited[ind[i]] = num;
            else visited[ind[i]] = 0;
        }
        return;
    }
    if (sum1 % ((right - left + 2) / 2) == sum3 % ((right - left + 2) / 2)) {
        for (int i = left; i <= right; ++i) {
            if (visited[ind[i]] == 1 || visited[ind[i]] == 3) visited[ind[i]] = num;
            else visited[ind[i]] = 0;
        }
        return;
    }
    if (sum3 % ((right - left + 2) / 2) == sum2 % ((right - left + 2) / 2)) {
        for (int i = left; i <= right; ++i) {
            if (visited[ind[i]] == 3 || visited[ind[i]] == 2) visited[ind[i]] = num;
            else visited[ind[i]] = 0;
        }
        return;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 1; i <= 2 * N - 1; ++i) { cin >> arr[i]; inde.push_back(i); }
    solution(inde, 1, 2 * N - 1, 1);
    for (int i = 1; i <= 2 * N - 1; ++i) if (visited[i] == 1) cout << arr[i] << " ";
    return 0;
}