#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    // Initializes variables, reads number of items and dividers
    int n, d;
    cin >> n >> d;

    // Initiailizes arrays of size n + 1, so that the numbers are 1 to n, and index 0 is a dummy
    vector<int> price(n + 1);
    vector<int> prefix(n + 1, 0);

    // Reads the prices of each item
    // prefix[i] is the sum of prices from item 1 to item i
    // So any group j + 1 costs prefix[i] - prefix[j]

    for (int i = 1; i <= n; i++) {
        cin >> price[i];
        prefix[i] = prefix[i - 1] + price[i];
    }

    // The impossible variable
    const int INF = 1000000000;

    // Initializes the dynamic programming arrays
    // prev is the previous row in the DP table
    // curr is the current row in the DP table being built
    vector<int> prev(n + 1, INF);
    vector<int> curr(n + 1, INF);
    prev[0] = 0; 

    // Each pass of the for loops represents a new divider, and therefore a new layer
    // The fill resets each layer 
    // curr[0] makes it clear that 0 items cost 0 dollars, regardless of the number of dividers/groups
    // This means prev[0] = 0, so a group can start at j = 0 and cover all items up to i
        // This is how we use few dividers 

    for (int k = 1; k <= d + 1; k++) {
        fill(curr.begin(), curr.end(), INF);
        curr[0] = 0;

        // For each item i, calculate the minimum cost to form a group ending at i
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                // Check if the previous state is valid, it cannot be < INF
                if (prev[j] < INF) {
                    // Calculate the cost of forming a group from item j + 1 to item i
                    // Cost is the rounded price of the last group, with the rounding logic using 5 and 10
                    int cost = ((prefix[i] - prefix[j] + 5) / 10) * 10;
                    // This is the recursive relationship for the dynamic programming solution.
                    // The total is the best cost for the first j items using at most k - 1 dividers
                    curr[i] = min(curr[i], prev[j] + cost);
                }
            }
        }
        // Copies the finished layer into previous to continue
        prev = curr;
    }

    // Outputs the minimum cost to group all items with at most d dividers
    cout << prev[n] << endl;
    return 0;
}