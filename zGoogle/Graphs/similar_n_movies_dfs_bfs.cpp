
/*
You have movies with the movie name and rating. For example:

"Movie A , rating 6",
"Movie B , rating 7",
"Movie C , rating 8",
"Movie D , rating 9",
"Movie E , rating 5",

You are also given transitive relation (bi-directional), for example:
Movie A is similar to Movie B,
Movie B is similar to Movie C.
Movie C is similar to Movie D.
Movie A is similar to Movie E.

keep in mind it's bi-directional(means B is similar to A as well)

We can safely assume from above relation that :
Movie A is similar to Movie C as well

That being said you will be given input as (movieName, N), you have to find out N movies similar to the movieName with highest rating.

In this case,
A->6
B->7
C->8
D->9
E->5

input=(A,2) -> means find 2 movies with highest rating similar to movie A.
output= D,C -> as A is similar to B and B is similar to C and C is similar to D and A is similar to E means A,B,C,D,E are similar movies and among them D and C have highest rating , hence the above answer.

1. create adj list
2. perform bfs and get the connected component
3. sort the component
*/



#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Function that performs BFS to find all movies similar to the starting movie
void bfs(const unordered_map<string, unordered_set<string>>& graph,
         const string& startMovie,
         unordered_set<string>& connectedMovies) {
    queue<string> toVisit;
    toVisit.push(startMovie);
    connectedMovies.insert(startMovie);

    while (!toVisit.empty()) {
        string current = toVisit.front();
        toVisit.pop();

        for (const auto& neighbor : graph.at(current)) {
            if (connectedMovies.find(neighbor) == connectedMovies.end()) {
                connectedMovies.insert(neighbor);
                toVisit.push(neighbor);
            }
        }
    }
}

// Comparator function to sort movies by their ratings
bool compareMovies(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}

// Main function to find top N similar movies by rating
vector<string> findTopSimilarMovies(const unordered_map<string, int>& ratings,
                                              const unordered_map<string, unordered_set<string>>& graph,
                                              const string& movieName,
                                              int N) {
    unordered_set<string> connectedMovies;
    bfs(graph, movieName, connectedMovies);

    // Prepare a vector of ratings
    vector<pair<string, int>> movieRatings;
    for (const auto& movie : connectedMovies) {
        if (movie != movieName) { // Exclude the starting movie itself
            movieRatings.emplace_back(movie, ratings.at(movie));
        }
    }

    // Sort the vector by ratings in descending order
    sort(movieRatings.begin(), movieRatings.end(), compareMovies);

    // Collect top N movies
    vector<string> result;
    for (int i = 0; i < N && i < movieRatings.size(); ++i) {
        result.push_back(movieRatings[i].first);
    }

    return result;
}

int main() {
    // Movie ratings
    unordered_map<string, int> ratings = {
        {"A", 6}, {"B", 7}, {"C", 8}, {"D", 9}, {"E", 5}
    };

    // Movie similarity graph representation
    unordered_map<string, unordered_set<string>> graph = {
        {"A", {"B", "E"}},
        {"B", {"A", "C"}},
        {"C", {"B", "D"}},
        {"D", {"C"}},
        {"E", {"A"}}
    };

    string movieName = "A";
    int N = 2;

    vector<string> topMovies = findTopSimilarMovies(ratings, graph, movieName, N);

    for (const auto& movie : topMovies) {
        cout << movie << " ";
    }

    return 0;
}