# Contributing to DSA & System Design Interview Prep

Thanks for considering a contribution! This repo is meant to be a clean, pattern-first reference for interview prep, and contributions that keep that spirit are very welcome.

## Ways to Contribute

- **Add a new problem** to an existing pattern file
- **Add a new pattern/category** that isn't covered yet
- **Improve an existing solution** (better time/space complexity, cleaner code, more comments)
- **Fix bugs** in existing code
- **Improve documentation** (README, code comments, complexity notes)
- **Add a new LLD problem** under `LLD/`

## Before You Start

For anything beyond a small fix (typo, comment, minor cleanup), please open an issue first to discuss what you'd like to add. This avoids duplicate work and keeps the repo's structure consistent.

## Style Guidelines

To keep the repo consistent:

1. **File naming**: Follow the existing `NN_DescriptiveName.cpp` convention (e.g. `06_PathProblems.cpp`) within a category folder.
2. **Code style**:
   - Use clear, descriptive variable names (no single-letter names except loop counters like `i`, `j`).
   - Add a brief comment above each function/problem explaining what it solves.
   - Include time and space complexity as a comment, e.g. `// Time: O(n), Space: O(1)`.
3. **One pattern, one file**: Group problems by the technique they use, not just by topic.
4. **Test your code** before submitting — make sure it compiles and runs correctly.
5. **Keep solutions clean**: Prefer readability over cleverness. This is a learning resource first.

## Submitting a Pull Request

1. Fork the repo and create your branch from `master`:
   ```bash
   git checkout -b add-pattern-name
   ```
2. Make your changes, following the style guidelines above.
3. Commit with a clear message describing what you added/changed:
   ```bash
   git commit -m "Add: Sliding window solution for X problem"
   ```
4. Push to your fork and open a Pull Request against `master`.
5. In your PR description, briefly explain:
   - What problem/pattern you added or changed
   - Why it belongs where you placed it
   - Time/space complexity of your solution

## Code of Conduct

Be respectful and constructive in issues, PRs, and reviews. This is a learning resource for the community — let's keep it welcoming for beginners and experienced engineers alike.

## Questions?

Open an issue and tag it with `question` — happy to help clarify anything before you put in the work.

Thanks again for helping make this a better resource for everyone prepping for interviews! ⭐
