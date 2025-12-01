/*
You have a circular garland (necklace) containing n gems. Each gem is either a Diamond (D) or a Ruby (R). The garland contains exactly d diamonds and r rubies, where both d and r are even numbers.
You can make at most 2 cuts on the garland. After cutting, group the resulting pieces into two parts such that each part contains exactly half the diamonds (d/2) and half the rubies (r/2).
Determine if such a division is possible, and if so, return the cut positions.

Example:
Input: n = 8, gems = [D, R, D, R, D, R, D, R]
Output: [2, 6]
Explanation: We can make two cuts at positions 2 and 6 to divide the garland into two parts:
[D, R, D, R] and [D, R, D, R]
Each part contains exactly half the diamonds and half the rubies.

Example:
Input: n = 6, gems = [D, R, D, R, D, R]
Output: []
Explanation: It is not possible to make two cuts to divide the garland into two parts such that each part contains exactly half the diamonds and half the rubies.
*/