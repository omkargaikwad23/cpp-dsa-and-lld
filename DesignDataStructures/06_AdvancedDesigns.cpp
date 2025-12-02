/*
================================================================================
                    DESIGN - ADVANCED DATA STRUCTURES
================================================================================

Complex designs combining multiple data structures.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Design Twitter (LeetCode 355) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────
postTweet, getNewsFeed (10 most recent), follow, unfollow

Design: HashMap for followers, HashMap for tweets, merge K sorted feeds.

Time: O(n log k) for getNewsFeed | Space: O(users * tweets)
*/
class Twitter {
    int timestamp;
    unordered_map<int, vector<pair<int, int>>> tweets;  // userId → [(time, tweetId)]
    unordered_map<int, unordered_set<int>> following;   // userId → set of followed users
    
public:
    Twitter() : timestamp(0) {}
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timestamp++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        // Merge tweets from user and followed users
        auto cmp = [](auto& a, auto& b) { return a.first < b.first; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        
        // Add user's own tweets
        for (auto& [time, id] : tweets[userId]) {
            pq.push({time, id});
        }
        
        // Add followed users' tweets
        for (int followee : following[userId]) {
            for (auto& [time, id] : tweets[followee]) {
                pq.push({time, id});
            }
        }
        
        vector<int> feed;
        while (!pq.empty() && feed.size() < 10) {
            feed.push_back(pq.top().second);
            pq.pop();
        }
        
        return feed;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            following[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};


/*
PROBLEM 2: Design Browser History (LeetCode 1472)
─────────────────────────────────────────────────
visit(url), back(steps), forward(steps)

Time: O(1) | Space: O(n)
*/
class BrowserHistory {
    vector<string> history;
    int current;
    
public:
    BrowserHistory(string homepage) {
        history.push_back(homepage);
        current = 0;
    }
    
    void visit(string url) {
        history.resize(current + 1);  // Clear forward history
        history.push_back(url);
        current++;
    }
    
    string back(int steps) {
        current = max(0, current - steps);
        return history[current];
    }
    
    string forward(int steps) {
        current = min((int)history.size() - 1, current + steps);
        return history[current];
    }
};


/*
PROBLEM 3: Design Search Autocomplete System (LeetCode 642)
───────────────────────────────────────────────────────────
input(c): Return top 3 suggestions for prefix.

Design: Trie + priority queue

Time: O(p + n log n) per query | Space: O(total chars)
*/
class AutocompleteSystem {
    struct TrieNode {
        TrieNode* children[27] = {};  // 26 letters + space
        unordered_map<string, int> counts;  // sentences with this prefix → count
    };
    
    TrieNode* root;
    TrieNode* curr;
    string prefix;
    
    int charToIdx(char c) {
        return c == ' ' ? 26 : c - 'a';
    }
    
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new TrieNode();
        curr = root;
        
        for (int i = 0; i < sentences.size(); i++) {
            addSentence(sentences[i], times[i]);
        }
    }
    
    void addSentence(const string& sentence, int count) {
        TrieNode* node = root;
        for (char c : sentence) {
            int idx = charToIdx(c);
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->counts[sentence] += count;
        }
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            addSentence(prefix, 1);
            prefix = "";
            curr = root;
            return {};
        }
        
        prefix += c;
        int idx = charToIdx(c);
        
        if (!curr || !curr->children[idx]) {
            curr = nullptr;
            return {};
        }
        
        curr = curr->children[idx];
        
        // Get top 3
        auto cmp = [](auto& a, auto& b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first > b.first;
        };
        
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
        
        for (auto& [sentence, count] : curr->counts) {
            pq.push({sentence, count});
        }
        
        vector<string> result;
        for (int i = 0; i < 3 && !pq.empty(); i++) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        
        return result;
    }
};


/*
PROBLEM 4: Design Excel Sum Formula (LeetCode 631)
──────────────────────────────────────────────────
set(r, c, v), get(r, c), sum(r, c, numbers): numbers like "A1:B2"

Time: O(cells) for sum | Space: O(n * m)
*/
class Excel {
    vector<vector<int>> grid;
    vector<vector<vector<pair<int,int>>>> formulas;  // Store sum dependencies
    int H, W;
    
    pair<int, int> parseCell(const string& s) {
        int col = s[0] - 'A';
        int row = stoi(s.substr(1)) - 1;
        return {row, col};
    }
    
    int calculateSum(int row, int col) {
        int sum = 0;
        for (auto& [r, c] : formulas[row][col]) {
            sum += grid[r][c];
        }
        return sum;
    }
    
public:
    Excel(int height, char width) : H(height), W(width - 'A' + 1) {
        grid.assign(H, vector<int>(W, 0));
        formulas.assign(H, vector<vector<pair<int,int>>>(W));
    }
    
    void set(int row, char column, int val) {
        int r = row - 1, c = column - 'A';
        formulas[r][c].clear();
        grid[r][c] = val;
    }
    
    int get(int row, char column) {
        int r = row - 1, c = column - 'A';
        if (formulas[r][c].empty()) return grid[r][c];
        return calculateSum(r, c);
    }
    
    int sum(int row, char column, vector<string> numbers) {
        int r = row - 1, c = column - 'A';
        formulas[r][c].clear();
        
        for (const string& s : numbers) {
            size_t colon = s.find(':');
            if (colon == string::npos) {
                auto [pr, pc] = parseCell(s);
                formulas[r][c].push_back({pr, pc});
            } else {
                auto [r1, c1] = parseCell(s.substr(0, colon));
                auto [r2, c2] = parseCell(s.substr(colon + 1));
                for (int i = r1; i <= r2; i++) {
                    for (int j = c1; j <= c2; j++) {
                        formulas[r][c].push_back({i, j});
                    }
                }
            }
        }
        
        grid[r][c] = calculateSum(r, c);
        return grid[r][c];
    }
};


/*
PROBLEM 5: Design Skiplist (LeetCode 1206)
──────────────────────────────────────────
Probabilistic data structure with O(log n) search, insert, delete.

Time: O(log n) average | Space: O(n)
*/
class Skiplist {
    struct Node {
        int val;
        vector<Node*> next;
        Node(int v, int level) : val(v), next(level, nullptr) {}
    };
    
    Node* head;
    int maxLevel;
    float probability;
    
    int randomLevel() {
        int level = 1;
        while ((float)rand() / RAND_MAX < probability && level < maxLevel) {
            level++;
        }
        return level;
    }
    
public:
    Skiplist() : maxLevel(16), probability(0.5) {
        head = new Node(-1, maxLevel);
    }
    
    bool search(int target) {
        Node* curr = head;
        for (int i = maxLevel - 1; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->val < target) {
                curr = curr->next[i];
            }
        }
        curr = curr->next[0];
        return curr && curr->val == target;
    }
    
    void add(int num) {
        vector<Node*> update(maxLevel, head);
        Node* curr = head;
        
        for (int i = maxLevel - 1; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->val < num) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        
        int level = randomLevel();
        Node* newNode = new Node(num, level);
        
        for (int i = 0; i < level; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    
    bool erase(int num) {
        vector<Node*> update(maxLevel, head);
        Node* curr = head;
        
        for (int i = maxLevel - 1; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->val < num) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        
        curr = curr->next[0];
        if (!curr || curr->val != num) return false;
        
        for (int i = 0; i < curr->next.size(); i++) {
            update[i]->next[i] = curr->next[i];
        }
        
        delete curr;
        return true;
    }
};


/*
PROBLEM 6: Text Editor (LeetCode 2296)
──────────────────────────────────────
Cursor at end. addText, deleteText, cursorLeft, cursorRight.

Design: Two stacks (left and right of cursor)

Time: O(k) | Space: O(n)
*/
class TextEditor {
    string left, right;
    
public:
    void addText(string text) {
        left += text;
    }
    
    int deleteText(int k) {
        int deleted = min(k, (int)left.size());
        left.resize(left.size() - deleted);
        return deleted;
    }
    
    string cursorLeft(int k) {
        while (k-- > 0 && !left.empty()) {
            right += left.back();
            left.pop_back();
        }
        return left.substr(max(0, (int)left.size() - 10));
    }
    
    string cursorRight(int k) {
        while (k-- > 0 && !right.empty()) {
            left += right.back();
            right.pop_back();
        }
        return left.substr(max(0, (int)left.size() - 10));
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Advanced Designs ===\n\n";
    
    // 1. Twitter
    Twitter twitter;
    twitter.postTweet(1, 5);
    auto feed = twitter.getNewsFeed(1);
    cout << "1. Twitter feed: ";
    for (int id : feed) cout << id << " ";
    cout << "\n";
    
    // 2. Browser History
    BrowserHistory browser("google.com");
    browser.visit("facebook.com");
    browser.visit("youtube.com");
    cout << "2. Browser back(1): " << browser.back(1) << "\n";
    cout << "   Browser forward(1): " << browser.forward(1) << "\n";
    
    // 5. Skiplist
    Skiplist sl;
    sl.add(1);
    sl.add(2);
    sl.add(3);
    cout << "5. Skiplist search(1): " << (sl.search(1) ? "true" : "false") << "\n";
    sl.erase(2);
    cout << "   Skiplist search(2): " << (sl.search(2) ? "true" : "false") << "\n";
    
    // 6. Text Editor
    TextEditor te;
    te.addText("leetcode");
    cout << "6. Text Editor delete(4): " << te.deleteText(4) << "\n";
    te.addText("practice");
    cout << "   Left(3): " << te.cursorLeft(3) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Design                        | Key Data Structures                            |
+───────────────────────────────+────────────────────────────────────────────────+
| Twitter                       | HashMap + HashMap + merge K sorted             |
| Browser History               | Vector with current pointer                    |
| Autocomplete                  | Trie + counts at each node                     |
| Excel                         | Grid + formula dependencies                    |
| Skiplist                      | Multi-level linked list                        |
| Text Editor                   | Two stacks (left and right of cursor)          |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

