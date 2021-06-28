
#ifndef __SKELETON
#include<bits/stdc++.h>
using namespace std;
#endif

struct UF {
 
	vector<int> component_size;
	vector<int> repr;
	vector<pair<int,int>> additionalInfo; //ex. på hur man kan spara mer max / min each of each set
 
	UF(int number_of_elements) {
		/*Skapar representanter från 0 - sig själv repr, samt size 1 initiallly*/
		for(int i = 0; i < number_of_elements; i++) {
			repr.push_back(i);
			component_size.push_back(1);
			additionalInfo.push_back({ i,i }); //self is max and min initially
		}
	}

	int size(int a) {
		/*returnar storlek på komponent mer repr a. */
		a = find(a); //det är repr som innehåller all info! - hitta repr!
		return component_size[a];
	}
 
	int find(int a) {
		/*hitta representant till a samt uppdatera trasitivitet in the go, (snabbare nästa gång)*/
 
		//fallet då sig själv är repr
		if (repr[a] == a) {
			return a;
		}
 
		//fallet då a pekar på en annan repr, som i sin tur eventuellt pekar vidare, uppdatera in the run ->
		repr[a] = find(repr[a]);
		//return vad som hittades! - alla transitivt uppdateras
		return repr[a];
	}
 
	void merge(int gravity, int pebble) {
		/*merge:a två komponenter givet två godtyckliga noder*/
        //Tricket är att bara merga representanter för respektive mängd!
		
        //ändra till deras repr
		gravity = find(gravity);
		pebble = find(pebble);
 
		//om dom redan är samma komponent
		if (gravity == pebble) {
			return;
		}
 
		//om pebble representerar ett större kluster. Bättre att låta färre gå längre, än fler gå längre! (path compression)
		if (component_size[pebble] > component_size[gravity]) {
			swap(pebble, gravity);
		}
 
		repr[pebble] = gravity; //ändra repr för pebbles mängd
		component_size[gravity] += component_size[pebble];
		component_size[pebble] = 0; //konsistent i att det är repr som innehar all info
 
		//additional info - [min,max]
		additionalInfo[gravity].first = min(additionalInfo[gravity].first, additionalInfo[pebble].first);
		additionalInfo[gravity].second = max(additionalInfo[gravity].second, additionalInfo[pebble].second);
		return;
	}
 
	int count_islands() {
		/*count number of disjoint components by counting number of non-zero sizes. Oxå anledning att cleara non repr*/
		int count = 0;
		for (auto el : component_size) {
			if (el > 0) {
				count += 1;
			}
		}
		return count;
	}
 
	bool get(int u, int v) {
		/*check if two elements u and v belong to the same set.*/
		u = find(u);
		v = find(v);
		if (u == v) {
			return true;
		}
		return false;
	}
};