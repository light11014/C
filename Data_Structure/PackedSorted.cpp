#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

int A[100];
int S, L, R; // S:size, L:left, R:right

int srch(int x)
{
	int s, e, m;
	s = 0;
	e = S - 1;

	while (s <= e) {
		m = (s + e) / 2;
		if (A[m] == x) {
			L = R = m;
			return 1;
		}
		else if (A[m] > x) {
			e = m - 1;
		}
		else {
			s = m + 1;
		}
	}

	// A[L] < x < A[R]
	L = e;
	R = s;
	return -1;
}

void insrt(int x)
{
	S++;
	for (int i = S - 1; i >= R; i--)
		A[i + 1] = A[i];
	A[R] = x;
}

void dlte(int x)
{
	for (int i = L; i < S; i++)
		A[i] = A[i + 1];
	S--;		
}

int main()
{
	char c;
	int x, i;
	S = 0;

	while (true) {
		printf("S =  %d\n", S);
		for (i = 0; i < S; i++) {
			printf("%3d\t", i);
		}
		printf("\n");
		for (i = 0; i < S; i++) {
			printf("%3d\t", A[i]);
		}
		printf("\n\n");

		scanf(" %c", &c);
		if (c == 's') { // Search
			scanf(" %d", &x);
			if (srch(x) == -1)
				printf("%d Not Found. Should be between %d and %d\n", x, L, R);
			else
				printf("%d Found at Index %d\n", x, L);
		}
		else if (c == 'i') { // Insert
			scanf(" %d", &x);
			if (srch(x) == -1) {
				insrt(x);
			}
		}
		else if (c == 'd') { // Delete
			scanf(" %d", &x);
			if (srch(x) == 1) {
				dlte(x);
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