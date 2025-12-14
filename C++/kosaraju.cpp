#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include<climits>
#include<stack> 
#include <algorithm>
#include <string.h>
#include<string>
using namespace std;
vector<int> DFS(vector<vector<int>>& pic, int n) {
	vector<int> result; 
	vector<bool>visited(n + 1, 0);
	stack<int> s; 
	vector<bool> processed(n + 1, 0); 
	for (int u = 1; u <= n; ++u) {
		if (visited[u]) continue;
		s.push(u); 
		while (!s.empty()) {
			int temp = s.top();
			s.pop();
			if (!visited[temp]) {
				visited[temp] = 1; 
				s.push(temp);
				processed[temp] = 1; 
				for (auto it = pic[temp].rbegin(); it != pic[temp].rend(); ++it) {
					int i = *it; 
					if (visited[i] == 0) { 
						s.push(i);
					}
				}
			}
			else if (processed[temp]) {
				result.push_back(temp); 
				processed[temp] = 0;
			}
		}
	}
	reverse(result.begin(), result.end());
	return result;
}
int kosaraju(vector<vector<int>>&inverseDia, int n,vector<int>topo) {
	vector<bool>visited(n + 1, 0);
	vector<int>group_belong(n+1,0);
	int count = 0;
	for (int i = 0; i < n; i++) {
		int begin = topo[i];
		if (visited[begin] == 1) continue;
		stack<int> s;
		s.push(begin);
		while (!s.empty()) {
			int temp = s.top();
			s.pop();
			group_belong[temp] = begin;
			visited[temp] = 1;
			for (auto j : inverseDia[temp]) {
				if (visited[j] == 0) {
					s.push(j);
				}
			}
		}

	}
	list<int>group_mark;
	for (int i = 1; i <= n; i++) {
		bool flag = 0;
		for(auto j:group_mark){
			if (group_belong[i] == j) {
				flag = 1;
				break;
			}
		}
		if(!flag){
			group_mark.push_back(group_belong[i]);
			count++;
		}
	}
	return count;
}