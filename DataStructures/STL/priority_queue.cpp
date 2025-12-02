// Note that by default C++ creates a max-heap for priority queue
#include <iostream>
#include <queue>
#define pii pair<int, int>

using namespace std;

void showpq(priority_queue<pair<int, int>> gq)
{
	cout << "priority queue: ";
	priority_queue<pair<int, int>> g = gq;
	while (!g.empty()) {
		cout << g.top().first << " : " << g.top().second << endl;
		g.pop();
	}
	cout << '\n';
}

int main()
{
	priority_queue<pair<int, int>> gquiz; //based on pair key: 50 30 30 20 5 1
	priority_queue<pii, vector<pii>,greater<pii>> quize1; //based on pair key: 1 5 20 30 30 50
	gquiz.push({30, 10});
	gquiz.push({50, 20});
	gquiz.push({30, 30});
	gquiz.push({20, 40});
	gquiz.push({5, 4});
	gquiz.push({1, 2});

	cout << "The priority queue gquiz is : ";
	showpq(gquiz);

	cout << "\ngquiz.size() : " << gquiz.size();
	cout << "\ngquiz.top() : " << gquiz.top().first << " " << gquiz.top().second;

	cout << "\ngquiz.pop() : " << endl;
	gquiz.pop();
	showpq(gquiz);

	return 0;
}
