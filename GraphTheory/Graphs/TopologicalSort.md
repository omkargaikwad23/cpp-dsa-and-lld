
## Graph Representation and Dry Run

### Graph Representation

The graph can be represented as follows:

```
1 -> 2
1 -> 4
2 -> 5
3 -> 5
4 -> 5
```

### Dry Run

1. Initialize `visited` array to `[false, false, false, false, false, false]`.
2. Initialize `ordering` array to `[-1, -1, -1, -1, -1, -1]`.
3. Start with `i = 4` (since `n = 5`).

#### Iteration 1: src = 1
- Call `dfs(4, 1, visited, ordering)`.
- Mark `visited[1] = true`.
- Explore edge `1 -> 2`.
  - Call `dfs(4, 2, visited, ordering)`.
  - Mark `visited[2] = true`.
  - Explore edge `2 -> 5`.
    - Call `dfs(4, 5, visited, ordering)`.
    - Mark `visited[5] = true`.
    - No more edges to explore.
    - Set `ordering[4] = 5`.
    - Return `i = 3`.
  - Set `ordering[3] = 2`.
  - Return `i = 2`.
- Explore edge `1 -> 4`.
  - Call `dfs(2, 4, visited, ordering)`.
  - Mark `visited[4] = true`.
  - Explore edge `4 -> 5` (already visited).
  - Set `ordering[2] = 4`.
  - Return `i = 1`.
- Set `ordering[1] = 1`.
- Return `i = 0`.

#### Iteration 2: src = 2
- Already visited.

#### Iteration 3: src = 3
- Call `dfs(0, 3, visited, ordering)`.
- Mark `visited[3] = true`.
- Explore edge `3 -> 5` (already visited).
- Set `ordering[0] = 3`.
- Return `i = -1`.

#### Iteration 4: src = 4
- Already visited.

#### Iteration 5: src = 5
- Already visited.

### Final Ordering

The final topological ordering is: `3 1 4 2 5`.

