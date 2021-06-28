
#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;
#endif

//following suit https://www.youtube.com/watch?v=Xu8jjJnwvxE

class Edge {
public:
    int from, to;
    Edge* residual;
    long flow = 0;
    long capacity;

    Edge() {

    }

    Edge(int from, int to, int capacity) {
        this->from = from;
        this->to = to;
        this->capacity = capacity;
    }

    bool isResidual() {
        return this->capacity == 0;
    }

    // viktigt att ha just denna def om residual tänk ska funger
    long remainingCapacity() {
        return capacity - flow;
    }

    //uppdatera hur graf ser ut efter funnan path
    void augument(long bottleNeck) {
        flow += bottleNeck;
        (*residual).flow -= bottleNeck;
    }
};

class FordFulkersonDfsSolver {
public:
    static const long INF = LONG_MAX / 2;

    // n = number of nodes, source and sink node
    int n, s, t;

    // Smart sätt att undvika behöva sätta varje cell ill false efter iter om bara 0 1 då
    // vi kör dfs flera ggr
    int visitedToken = 1;
    vector<int> visited;

    long maxFlow = 0;

    vector<vector<Edge*>> graph;


    //funktioner är stackallokerad och allt därtill -> så obj som skapas ligger på stack addresser
    //skapar pointers till stackaddreesser -> sen blir kiko. Heap memory med new eller malloc
    void addEdge(int from, int to, int capacity) {

        //Edge forward(); != Edge* forward = new Edge();
        Edge* forward = new Edge();
        Edge* backward = new Edge();
        forward->from = from;
        forward->to = to;
        forward->capacity = capacity;
        backward->from = to;
        backward->to = from;
        backward->capacity = 0;

        forward->residual = backward;
        backward->residual = forward;

        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    void solve() {
        //finding all augmeting paths - initially bottleneck flow INF
        for (long f = dfs(s, INF); f != 0; f = dfs(s, INF)) {
            //next iter with dfs - when no paths left to be found returns 0
            visitedToken++;
            maxFlow += f;
        }
    }

    long dfs(int node, long flow) {
        //reached sink - actual path so return bottleneck flow found
        if (node == t) return flow;

        visited[node] = visitedToken; //Avoid cycling


        //för edges till en nod
        for (Edge* e : graph[node]) {
            if (e->remainingCapacity() > 0 && visited[e->to] != visitedToken) {

                long bottleNeck = dfs(e->to, min(flow, e->remainingCapacity()));

                if (bottleNeck > 0) {
                    //if found path - traceback - notera att residual edges som använts tas ut
                    e->augument(bottleNeck);
                    return bottleNeck;
                }
            }
        }

        return 0;
    }

    FordFulkersonDfsSolver(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        visited = vector<int>(n, 0);
        graph = vector<vector<Edge*>>(n); //0 indexerad
    }
};


/*
Ex:
number_of_nodes = 12;
start = number_of_nodes - 1;
sink = number_of_nodes - 2;
FordFulkersonDfsSolver plzwork(number_of_nodes,start,sink);

plzwork.addEdge(from,to,capacity) ->
(start,0,3) osv.

plzwork.solve()
plzwork.maxFlow <- AND
*/

