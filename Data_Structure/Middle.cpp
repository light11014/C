#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

class PQMin {
public:
	PQMin();
	int Size();
	int Top();
	void Insert(int x);
	void Delete();
	int a[1000];
	int n;
};

PQMin::PQMin()
{
	n = 0;
}

int PQMin::Size()
{
	return n;
}

int PQMin::Top()
{
	return a[1];
}

void PQMin::Insert(int x) 
{
	int i;
	n++;
	a[n] = x;
	i = n;
	while (i != 1) {
		if (a[i / 2] <= a[i]) 
			break;
		swap(a[i / 2], a[i]);
		i = i / 2;
	}
}

void PQMin::Delete()
{
	int i, j;
	a[1] = a[n];
	n--;
	i = 1;
	while (true) {
		if (i * 2 > n) break;
		if (i * 2 == n) {
			if (a[i] <= a[i * 2]) break;
			else {
				swap(a[i], a[i * 2]);
				i = i * 2;
			}
		}
		else {
			j = (a[i * 2] < a[i * 2 + 1]) ? i * 2 : i * 2 + 1;

			if (a[i] <= a[j]) break;
			else {
				swap(a[i], a[j]);
				i = j;
			}
		}
	}
}

class PQMax {
public:
	PQMax();
	int Size();
	int Top();
	void Insert(int x);
	void Delete();
	int a[1000];
	int n;
};

PQMax::PQMax()
{
	n = 0;
}

int PQMax::Size()
{
	return n;
}

int PQMax::Top()
{
	return a[1];
}

void PQMax::Insert(int x)
{
	int i;
	n++;
	a[n] = x;
	i = n;
	while (i != 1) {
		if (a[i / 2] >= a[i]) break;
		swap(a[i / 2], a[i]);
		i = i / 2;
	}
}

void PQMax::Delete()
{
	int i, j;
	a[1] = a[n];
	n--;
	i = 1;
	while (true) {
		if (i * 2 > n) break;
		if (i * 2 == n) {
			if (a[i] >= a[i * 2]) break;
			else {
				swap(a[i], a[i * 2]);
				i = i * 2;
			}
		}
		else {
			j = (a[i * 2] > a[i * 2 + 1]) ? i * 2 : i * 2 + 1;

			if (a[i] >= a[j]) break;
			else {
				swap(a[i], a[j]);
				i = j;
			}
		}
	}
}


int main()
{
	char c;
	int x, y, i, lcnt, rcnt;
	PQMax Left;
	PQMin Right;
	lcnt = rcnt = 0;

	while (true) {
		scanf(" %c", &c);
		if (c == 'p') { // Middle Value Print
			if (Left.Size() == 0)
				printf("No entry.\n");
			else
				printf("Middle member = %d\n", Left.Top());
		}
		else if (c == 'i') { // Insert
			scanf(" %d", &x);

			if (lcnt == 0) {
				Left.Insert(x);
				lcnt = 1;
			}
			else if (lcnt == rcnt) {
				if (x <= Right.Top()) {
					Left.Insert(x);
				}
				else {
					y = Right.Top();
					Right.Delete();
					Left.Insert(y);
					Right.Insert(x);
				}
				lcnt++;
			}
			else { // lcnt == rcnt + 1;
				if (x >= Left.Top()) {
					Right.Insert(x);
				}
				else {
					y = Left.Top();
					Left.Delete();
					Right.Insert(y);
					Left.Insert(x);
				}
				rcnt++;
			}
		}
		else if (c == 'd') { // Middle Value Delete
			if (Left.Size() == 0)
				printf("No entry to delete.\n");
			else {
				y = Left.Top(); 
				Left.Delete();
				if (lcnt == rcnt) {
					x = Right.Top();
					Right.Delete();
					Left.Insert(x);
					rcnt--;
				}
				else {
					lcnt--;
				}
				printf("Middle member = %d, has been deleted\n", y);
			}		
		}
		else if (c == 'q') { // Quit
			break;
		}
		else {
			printf("???\n");
		}
	}
	return 0;
}


