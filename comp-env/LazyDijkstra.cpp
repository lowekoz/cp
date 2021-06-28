

#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;
#endif

//ej verifierad tho - för ints
//lazy dijkstra - https://www.youtube.com/watch?v=pSqmAO-m7Lk

/*
Dijkstra : utvärdera src (iter 0) s.a. nya kanter tillkommer, dessa edges är till noder vi "kan se".
Bland noder vi kan se är det lätt att avgöra vilken den billigaste vi kan ta oss till ifrån src.
Då graph har non-negative EW, kan vi vara säkra på att bland alla noder vi inte kan
se har de distans från src >= kortaste vi kan se. Ergo, vi kan gå till den billigaste
vi kan se och vara säkra på att ingen annan nod har en billigare väg från src. Nu tillkommer nya
edges som vi kan se (dynamiskt ackumulerade om vi går igenom andra noder än src för att beräkna dist från
src), med dessa inkluderat kan vi återigen se en billigaste väg från src till ngn nod, återigen eftersom
det är den billigaste vägen vi kan se och alla andra edges har vikt >= 0, så finns ingen billigare. osv.
... med upprepat resonemang.
Sammanfattningsvis, vi kan arbeta av noder från billigaste från source uppåt. Basically, vi kan alltid
säkert plocka bort den billigaste utav noder från src!
*/

struct Dijkstra {
	int n; //num of nodes
	vector<vector<pair<int,int>>> adjList; //[from] -> {{w, to}, ...}
	vector<int> prev;
	vector<int> dist; //dist from src
	Dijkstra(int n) {
		this->n = n;
		this->dist = vector<int>(n, INT32_MAX);
		this->prev = vector<int>(n, -1);
		this->adjList = vector<vector<pair<int,int>>>(n);
	}

	void addEdge(int from, int to, int weight) {
		this->adjList[from].push_back({weight,to});
	}

	void solve(int src) {
		vector<bool> vis(n, 0);
		this->dist[src] = 0;
		//för pair int ges deafult.first comparator i heap, så min_heap för först el
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
		pq.push({ 0,src }); //bara för att starta igng process
		while (!pq.empty()) {
			pair<int, int> current = pq.top();
			pq.pop();
			//{minVal (ackumlativ), at} i heap tsk. w, to som i adj list
			int minVal = current.first;
			int at = current.second;
			vis[at] = true; //klar med denna nod!
			if (dist[at] < minVal) continue; // tänk {10,X} pushas före {4,X}. Conveniant att då skippa {10,X} sen
			for (auto& nxt : adjList[at]) {
				if (vis[nxt.second]) continue; //skippa alla vi redan utvärderat
				int newDist = dist[at] + nxt.first; //potential
				if (newDist < dist[nxt.second]) {
					//found better alt.
					prev[nxt.second] = at;
					dist[nxt.second] = newDist;
					pq.push({ newDist,nxt.second });
				}
			}
		}
	}

	vector<int> reconstructPath(int src, int goal) {
		//vi har prev pekar var vi kom ifrån till nod X
		vector<int> path;
		path.push_back(goal);
		int tmp = goal;
		while (prev[tmp] != -1) {
			tmp = prev[tmp];
			path.push_back(tmp);
		}
		reverse(path.begin(), path.end());
		return path;

	}
};

int main() {
	Dijkstra obj(7);
	int src = 0; //Home = 0
	obj.addEdge(0, 1, 5);
	obj.addEdge(1, 0, 5);
	obj.addEdge(1, 3, 3);
	obj.addEdge(3, 1, 3);
	obj.addEdge(2, 1, 9);
	obj.addEdge(1, 2, 9);
	obj.addEdge(3, 2, 5);
	obj.addEdge(2, 3, 5);
	obj.addEdge(0, 4, 8);
	obj.addEdge(4, 0, 8);
	obj.addEdge(4, 3, 4);
	obj.addEdge(3, 4, 4);
	obj.addEdge(5, 4, 6);
	obj.addEdge(4, 5, 6);
	obj.addEdge(5, 3, 2);
	obj.addEdge(3, 5, 2);
	obj.addEdge(2, 6, 7);
	obj.addEdge(6, 2, 7);
	obj.addEdge(5, 6, 4);
	obj.addEdge(6, 5, 4);

	obj.solve(src); //Terminater inte early vid visited Goal, utan löser hela graf
	vector<int> path = obj.reconstructPath(0,6); //from to

	int i = 0;
	for (auto& el : obj.dist) {
		cout << "from " << src << " to node :" << (char)(i+96) << " we have minimal distance " << el << endl;
		i++;
	}
	for (auto& el : path) {
		cout << (char)(el+96) << " ";
	}cout << endl;
}
