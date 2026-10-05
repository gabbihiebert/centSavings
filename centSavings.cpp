#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    int n, d;
    cin >> n >> d;
    vector<int> price(n + 1);
    vector<int> prefix(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> price[i];
        prefix[i] = prefix[i - 1] + price[i];
    }

    const int INF = 1000000000;
    vector<int> prev(n + 1, INF);
    vector<int> curr(n + 1, INF);
    prev[0] = 0;
    int best = INF;   

    for (int k = 1; k <= d + 1; k++) {
        fill(curr.begin(), curr.end(), INF);
        curr[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (prev[j] < INF) {
                    int cost = ((prefix[i] - prefix[j] + 5) / 10) * 10;
                    curr[i] = min(curr[i], prev[j] + cost);
                }
            }
        }
        prev = curr;
    }

    cout << prev[n] << endl;
    return 0;
}