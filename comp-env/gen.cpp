#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
	//rand() inbyggd returnar val från 0 to randmax -> vill hamna i range [a,b]
	return a + rand() % (b - a + 1); //inklusive b-a s.a. inte mod ger 0 då
}

//nr of arguments
//array of array of chars argv[n] är det n:te cmd arg med 0 ./file
int main(int argc, char* argv[]) {
	//srand sätter seed till random generator func, different seed different nums
	srand(atoi(argv[1])); //skapa seed from cmd arg converted to int
    //måste ha arg till nu tho
	int n = rand(4, 20);
	printf("%d\n", n);
	//set<int> used; //distinct
	for (int i = 0; i < n; ++i) {
		int x;
		x = rand(1, 1222);
		/*
		do {
			x = rand(1, 10);
		} while (used.count(x));
		*/
		printf("%d ", x);
	}
	puts("");
}