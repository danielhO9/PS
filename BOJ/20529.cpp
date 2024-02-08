#include <bits/stdc++.h>
using namespace std;
int answer;

int cal(vector<string>& MBTI, vector<int>& picked) {
    int ret = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (MBTI[picked[i]][k] != MBTI[picked[j]][k]) ++ret;
            }
        }
    }
    return ret;
}

void pick3(vector<string>& MBTI, vector<int>& picked) {
    if (picked.size() == 3) { answer = min(answer, cal(MBTI, picked)); return; }
    int last = picked.empty() ? 0 : picked.back() + 1;
    for (int i = last; i < MBTI.size(); ++i) {
        picked.push_back(i);
        pick3(MBTI, picked);
        picked.pop_back();
    }
}

int solution() {
    map<string, int> table;
    answer = 12;
    int N; cin >> N;
    vector<string> MBTI;
    string temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        table[temp] += 1;
        if (table[temp] <= 3) MBTI.push_back(temp);
    }
    vector<int> picked = {};
    pick3(MBTI, picked);
    return answer;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        cout << solution() << "\n";
    }
    return 0;
}
/*
3
3
ENTJ INTP ESFJ
4
ESFP ESFP ESFP ESFP
5
INFP INFP ESTP ESTJ ISTJ
*/