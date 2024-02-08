#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Line {
    long long slope;
    long long y_value;
    double intersection;
};

double meetPoint(const Line& line1, const Line& line2) {
    return (line2.y_value - line1.y_value) / (line1.slope - line2.slope);
}

void solution(const vector<pair<long long, long long>>& product, vector<Line>& graph) {
    long long x = 0;
    graph.clear();
    int index = 0;

    for (int count = 1; count <= product.size(); ++count) {
        long long slope = 2 * product[count - 1].second;
        long long y_value = x + product[count - 1].second * product[count - 1].second;

        while (!graph.empty() && graph.back().intersection >= meetPoint(graph.back(), {slope, y_value})) {
            if (index == graph.size() - 1) {
                index -= 1;
            }
            graph.pop_back();
        }

        if (!graph.empty()) {
            graph.push_back({slope, y_value, meetPoint(graph.back(), {slope, y_value})});
        } else {
            graph.push_back({slope, y_value, 1e8 * (-1)});
        }

        while (index != graph.size() - 1 && graph[index + 1].intersection <= product[count - 1].first) {
            index += 1;
        }

        x = graph[index].slope * product[count - 1].first + graph[index].y_value + product[count - 1].first * product[count - 1].first;

        if (count == product.size()) {
            cout << x / 2;
               if (x % 2 == 0) cout << ".0";
               else cout << ".5";
            cout << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int _ = 0; _ < t; ++_) {
        long n;
        cin >> n;

        vector<pair<long long, long long>> arr1(n);
        vector<pair<long long, long long>> arr2(n);

        for (long i = 0; i < n; ++i) {
            cin >> arr1[i].first >> arr1[i].second;
            if (arr1[i].second < 0) arr1[i].second *= -1;
            arr1[i].first += 1000001;
            arr2[i].first = arr1[i].second - arr1[i].first;
            arr2[i].second = arr1[i].first + arr1[i].second;
        }

        sort(arr2.begin(), arr2.end());

        vector<pair<long long, long long>> product;
        product.push_back(arr2[0]);

        for (long i = 1; i < n; ++i) {
            while (!product.empty() && product.back().second <= arr2[i].second) {
                product.pop_back();
            }
            product.push_back(arr2[i]);
        }

        vector<Line> graph;
        solution(product, graph);
    }

    return 0;
}
