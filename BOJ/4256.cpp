#include <bits/stdc++.h>
using namespace std;
vector<int> preorder(1001), inorder(1001), postorder(1001), pre(1001), ino(1001);

void solution(int prel, int prer, int inl, int inr, int p) {
    // prel, prel + 1 ~ prel + in_root - inl, prel + in_root - inl + 1 ~ prer
    // inl ~ in_root - 1, in_root, in_root + 1, inr
    int in_root = ino[preorder[prel]];
    if (in_root > inl) solution(prel + 1, prel + in_root - inl, inl, in_root - 1, p);
    if (in_root < inr) solution(prel + in_root - inl + 1, prer, in_root + 1, inr, p + in_root - inl);
    postorder[p + prer - prel] = preorder[prel];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        int n; cin >> n;
        for (int j = 1; j <= n; ++j) {
            cin >> preorder[j];
            pre[preorder[j]] = j;
        }
        for (int j = 1; j <= n; ++j) {
            cin >> inorder[j];
            ino[inorder[j]] = j;
        }
        solution(1, n, 1, n, 1);
        for (int j = 1; j <= n; ++j) cout << postorder[j] << " ";
        cout << "\n";
    }

    return 0;
}