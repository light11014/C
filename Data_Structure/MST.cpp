#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

class edge {
public:
	int a, b, w;
	bool operator< (const edge& k) const 
	{
		return w < k.w;
	}
};

vector<pair<int, int>> AD[1000];

edge ED[1000];
int Used[1000];

int n, m;

int A[1000];

int Find(int a) {
	int r, p, q;
	p = a;
	while (A[p] != 0) {
		p = A[p];
	}
	r = p;
	p = a;
	while (A[p] != 0) {
		q = p;
		p = A[q];
		A[q] = r;
	}
	return p;
}

void Union(int a, int b) {
	int p, q;
	p = Find(a);
	q = Find(b);
	A[q] = p;
	return;
}

int Visited[1000];

void Print(int nd, int w, int d, int LR) {
	Visited[nd] = 1;
	if (LR == 1)
		for (int i = 0; i < d; i++)
			printf("          ");
	printf("[%3d, %3d]", w, nd);
	int first = 1;
	for (int i = 0; i < AD[nd].size(); i++) {
		if (Visited[AD[nd][i].first] == 0) {
			if (first == 1) {
				Print(AD[nd][i].first, AD[nd][i].second, d + 1, 0);
			}
			else {
				Print(AD[nd][i].first, AD[nd][i].second, d + 1, 1);
			}
			first = 0;
		}
	}
	if (first == 1) {
		printf("\n");
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf(" %d %d %d", &ED[i].a, &ED[i].b, &ED[i].w);
	}
	sort(ED + 1, ED + m + 1);
	for (int i = 1; i <= m; i++) {
		if (Find(ED[i].a) != Find(ED[i].b)) {
			Used[i] = 1;
			Union(ED[i].a, ED[i].b);
		}
	}
	int sum = 0;
	for (int i = 1; i <= m; i++) {
		if (Used[i] == 1)
			sum += ED[i].w;
	}
	printf("Weight Sum = %d\n", sum);
	for (int i = 1; i <= m; i++) {
		if (Used[i]) {
			AD[ED[i].a].push_back(make_pair(ED[i].b, ED[i].w));
			AD[ED[i].b].push_back(make_pair(ED[i].a, ED[i].w));
		}
	}
	Print(1, 0, 0, 0);
	return 0;
}

/*

5 10
1 2 10
1 4 5
1 5 6
2 3 1
2 4 3
2 4 4
3 4 9
3 5 4
3 5 6
4 5 2

*/