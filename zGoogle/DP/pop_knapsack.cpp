/*
The Knapsack problem is a well-known problem in the field of computer programming and problem-solving. To make it more interesting, an interviewer uses a modified version of the problem.

Given n items, where the weight of the ith item is 2^i, and the cost of the ith item is cost[i], find the minimum amount needed to purchase the items such that the combined weight of the purchased items is at least minWeight.
Example
Consider n = 5, cost = [2, 5, 7, 11, 25], min Weight = 26
One of the optimal ways to purchase the items is as follows:
• Buy 2 units of the Oth item and 3 units of the 3rd item.
• Total cost = 2 * 2 + 3 * 11 = 37.
• Total weight = (2 * 2^0) + (3 * 2^3) = 26, which is at least minWeight.
Return the total cost of the items, 37.

One of the optimal ways to purchase is
• Buy 2 units of the Oth item and 3 units of the 3rd item.
• Total cost = 2 * 2 + 3 * 11 = 37.
• Total weight = (2 * 2^0) + (3 * 2^3) = 26, which is at least minWeight.
Return the total cost of the items, 37.

Constraints
• 1<= n <= 30
• 1 ≤ cost[i] ≤ 10^9
• 1 <= minWeight ≤ 10^9
*/