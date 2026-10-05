#include <iostream>
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
}