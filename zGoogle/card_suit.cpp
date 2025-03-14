
/*
Given a deck of cards of X suits and Y ranks (e.g., normal decks have 4 suits and 13 ranks),

How do you find the highest (if any) five straight flush (i.e., five cards of the same suit
with contiguous/consecutive numbers)?

** Examples: **
Given a card of suit "1" rank "0" --> we write it as S1R0

Example:
INPUT 2: S0R7, S2R0, S0R1, S2R1, S2R2, S2R3, S2R5, S2R4
SOLUTION 2 -->S2R1-S2R5
  
INPUT 1: S1R2, S1R0, S1R1, S0R1, S1R3, S0R7, S1R4
SOLUTION 1 --> S1R0-S1R4 would be a solution

The card class can be something like:


int MaxSuit = 4;
int MaxRank = 13;
int MatchStraightFlushCards = 5;

class Card {
 int suit; // eg. 0-3.
 int rank; // eg. 0-12
}

Please write the function:
vector<Card> findHighestStraightFlush(vector<Card> arr);
*/

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

const int MatchStraightFlushCards = 5;

struct Card {
    int suit;
    int rank;
};



vector<Card> findHighestStraightFlush(vector<Card> arr) {
    unordered_map<int, vector<Card>> suitGroups;
    
    // Group cards by suit
    for (const auto& card : arr) {
        suitGroups[card.suit].push_back(card);
    }
    
    vector<Card> bestStraightFlush;
    
    // Iterate over each suit
    for (auto& [suit, cards] : suitGroups) {
        sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
            return a.rank < b.rank;
        }); // Sort cards by rank using a lambda function
        
        vector<Card> currentStraight;
        
        for (size_t i = 0; i < cards.size(); ++i) {
            if (currentStraight.empty() || cards[i].rank == currentStraight.back().rank + 1) {
                currentStraight.push_back(cards[i]);
            } else if (cards[i].rank != currentStraight.back().rank) { // Reset if not consecutive
                currentStraight = {cards[i]};
            }
            
            if (currentStraight.size() > MatchStraightFlushCards) {
                currentStraight.erase(currentStraight.begin()); // Keep only last MatchStraightFlushCards
            }
            
            if (currentStraight.size() == MatchStraightFlushCards && (bestStraightFlush.empty() || currentStraight.back().rank > bestStraightFlush.back().rank)) {
                bestStraightFlush = currentStraight;
            }
        }
    }
    
    return bestStraightFlush;
}


int main() {
    vector<Card> cards = {{0,7}, {2,0}, {0,1}, {2,1}, {2,2}, {2,3}, {2,5}, {2,4}};
    vector<Card> result = findHighestStraightFlush(cards);
    
    for (const auto& card : result) {
        cout << "S" << card.suit << "R" << card.rank << " ";
    }
    cout << endl;
    
    return 0;
}
