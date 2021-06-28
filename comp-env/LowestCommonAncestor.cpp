/*
Description: 
Link: https://www.baeldung.com/cs/tree-lowest-common-ancestor
Core idea: Samma depth från root? Om inte måste vi flytta den som är djupare ner. Om ja och ej samma, fortsätt uppåt.
Extra: Det vackra med träd är att alla noder kan vara roots innan man bestämt sig!
Status: Ej vtestad

Standards:
	-> Assume only one CodeLib import
	-> TODO - left to implement
	-> mark possible changes with hint towards why like such //@size
*/
#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;
#endif

const int _N = 400005; //@size of graph
vector<int> adj[_N];
int node_depth[_N];
int parent_of[_N];

//preprocessa hela trädet från vald nod - vilken depth och föregångare en nod har. 
void DepthFirstPreparation(int nod = 0, int layer = 0,int parent = 0) { //@nod = 0 väljer root
	parent_of[nod] = parent;
	parent = nod;
	node_depth[nod] = layer;
	for (int el : adj[nod]) {
		DepthFirstPreparation(el,layer + 1,parent);
	}
}

int LCA(int nod_A, int nod_B) {
	int depth_A = node_depth[nod_A];
	int depth_B = node_depth[nod_B]; 
	while (true) {
		if (depth_A == depth_B) {
			//om samma djup - kolla om samma nod -> klar
			if (nod_A == nod_B) {
				return nod_A;
			}
			else {
				nod_A = parent_of[nod_A];
				depth_A -= 1;
			}
		} //gå alltid upp med den som är på djupare node_depth först.
		else if (depth_A < depth_B) {
			depth_B -= 1;
			nod_B = parent_of[nod_B];
		}
		else {
			depth_A -= 1;
			nod_A = parent_of[nod_A];
		}
	}
}

DepthFirstPreparation(); //HELLO! LOOK AT ME, I'M MR.MEESEEKS. @ekv. till build()