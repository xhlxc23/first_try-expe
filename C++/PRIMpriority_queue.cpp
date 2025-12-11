#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include<climits>
#include<queue> 
#include <algorithm>
#include <string.h>
using namespace std;
struct edge {
	int to;
	int value;
	bool operator>(const edge& other) const {
		return value > other.value;
	}
};
struct point {
	int si;
	list<edge> ed;
};

bool operator < (const edge& a, const edge& b) {
	return a.to < b.to;
}
int findMinPrice(vector<point>& points, vector<bool>& belong) {
    int n = points.size();
    if (n == 0) return 0;
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    int totalPrice = 0;
    belong[0] = true;
    for (const auto& e : points[0].ed) {
        if (!belong[e.to]) {
            pq.push(e);
        }
    }
    for (int i = 1; i < n; i++) {
        while (!pq.empty()) {
            edge minEdge = pq.top();
            pq.pop();
            if (!belong[minEdge.to]) {
                totalPrice += minEdge.value;
                belong[minEdge.to] = true;
                for (const auto& e : points[minEdge.to].ed) {
                    if (!belong[e.to]) {
                        pq.push(e);
                    }
                }
                break;
            }
        }
    }

    return totalPrice;
}