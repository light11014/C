#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

int n, m;

class Node {
public:
	int a;
	Node* n;
};

class List {
public:
	List();
	void Insert(int x);
	int NextForward();
	Node* head;
	Node* LastForward;
};

List::List() 
{ 
	head = NULL; 
	LastForward = NULL;
}

void List::Insert(int x) 
{
	Node* c;
	c = new Node;
	c->n = head;
	c->a = x;
	head = c;
}

int List::NextForward()
{
	if (head == NULL)
		return -1;
	if (LastForward == NULL)
		LastForward = head;
	else
		LastForward = LastForward->n;
	if (LastForward == NULL)
		return -1;
	else
		return LastForward->a;
}

List MAP[1000];

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
	MAP[x].Insert(y);
	return;
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

	printf("***** LinkedList Result *****\n");

	while ((cur = NextStart()) != -1) {
		printf("%d", cur);
		Mark(cur);
		while (1) {
			if ((s = MAP[cur].NextForward()) != -1) {
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


20 20
13 17
1 5
1 13
13 1
5 6
6 5
7 7
19 20
18 19
19 4
15 16
16 2
4 8
8 10
9 15
19 11
7 17
8 19
19 20
1 19
*/

