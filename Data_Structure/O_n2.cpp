#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

int n, m;

int MAP[1000][1000];

int Stack[10000];
int SP;

void Push(int x)
{
	Stack[SP++] = x;
	return;
}

int Pop()
{
	return Stack[--SP];
}

int IsEmpty()
{
	return (SP == 0);
}

void SetLink(int x, int y)
{
	MAP[x][y] = 1;
	return;
}

int LastForward[1000];

int NextForward(int x)
{
	LastForward[x]++;
	while (LastForward[x] <= n) {
		if (MAP[x][LastForward[x]] == 1)
			return LastForward[x];
		else
			LastForward[x]++;
	}
	return -1;
}

int Visited[1000];
int LastStart = 0;

int IsMarked(int x)
{
	return Visited[x];
}

void Mark(int x)
{
	Visited[x] = 1;
}

int NextStart() 
{
	LastStart++;
	while (LastStart <= n) {
		if (IsMarked(LastStart) == 0)
			return LastStart;
		else
			LastStart++;
	}
	return -1;
}

int main() 
{
	int x, y, cur, s;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		SetLink(x, y);
		SetLink(y, x);
	}

	printf("***** O(N2) Result *****\n");

	while ((cur = NextStart()) != -1) {
		printf("%d", cur);
		Mark(cur);
		while (1) {
			if ((s = NextForward(cur)) != -1) {
				if (IsMarked(s) == 0) {
					printf(" %d", s);
					Mark(s);
					Push(cur);
					cur = s;
				}
			}
			else {
				if (IsEmpty() == 1)
					break;
				else {
					cur = Pop();
				}
			}
		}
		printf("\n");
	}
	return 0;
}

/*
10 7
1 3
3 9
6 2
5 10
7 3
4 9
8 10
*/