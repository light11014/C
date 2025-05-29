#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

int A[100], B[100];
int S, L, R;

int srch(int x) // S:size, L:left, R:right
{
	int s, e, m;
	s = 0;
	e = S - 1;
	while (s <= e) {
		m = (s + e) / 2;
		if (A[m] == x) {
			L = R = m;
			if (B[m] == 1)
				return 1;
			else
				return -1;
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
	int i, j;
	if (L == R)
		B[L] = 1;
	else if (L == -1) { // R == 0, x는 A내에서 가장 작은수
		i = R;
		while (B[i] == 1 && i < S) // 오른쪽 빈 공간 탐색
			i++;
		if (i == S) { // A[0] ~ A[S-1]: 빈 공간 존재X
			for (j = S - 1; j >= R; j--) { // 오른쪽으로 이동
				A[j + 1] = A[j];
				B[j + 1] = B[j];
			}
			A[R] = x;
			B[R] = 1;
			S++;
		}
		else { // A[0] ~ A[S-1]: 빈 공간 존재O -> A[i]
			for (j = i - 1; j >= R; j--) { // A[0] ~ A[i-1]: 오른쪽으로 한 칸 이동
				A[j + 1] = A[j];
				B[j + 1] = B[j];
			}
			A[R] = x;
			B[R] = 1;
		}
	}
	else if (R == S) { // L == S-1, x는 A내에서 가장 큰 수
		i = L;
		while (B[i] == 1 && i >= 0) // 왼쪽 빈 공간 탐색
			i--;
		if (i == -1) { // A[0] ~ A[S-1]: 빈 공간 존재X
			A[S] = x; 
			B[S] = 1;	
			S++;
		}
		else { // A[0] ~ A[S-1]: 빈 공간 존재O -> A[i]
			for (j = i; j < L; j++) { // A[i+1] ~ A[S-1]: 왼쪽으로 한 칸 이동
				A[j] = A[j + 1];
				B[j] = B[j + 1];
			}
			A[L] = x;
			B[L] = 1;
		}
	}
	else { // x가 A내에서 가장 큰 수도 작은 수도 아님
		i = L;
		while (B[i] == 1 && i >= 0)
			i--;
		if (i != -1) { // A[0] ~ A[L]: 빈 공간 존재O -> A[i]
			for (j = i; j < L; j++) { // A[i+1] ~ A[L]: 왼쪽으로 한 칸 이동
				A[j] = A[j + 1];
				B[j] = B[j + 1];
			}
			A[L] = x;
			B[L] = 1;
		} 
		else { // A[0] ~ A[L]: 빈 공간 존재X
			i = R;
			while (B[i] == 1 && i < S)
				i++;
			if (i != S) { // A[R] ~ A[S-1]: 빈 공간 존재O -> A[i]
				for (j = i - 1; j >= R; j--) { // A[R] ~ A[i-1]: 오른쪽으로 한 칸 이동
					A[j + 1] = A[j];
					B[j + 1] = B[j];
				}
				A[R] = x;
				B[R] = 1;
			}
			else { // A[R] ~ A[S-1]: 빈 공간 존재X
				for (j = S - 1; j >= R; j--) { // A[R] ~ A[S-1]: 오른쪽으로 한 칸 이동
					A[j + 1] = A[j];
					B[j + 1] = B[j];
				}
				A[R] = x;
				B[R] = 1;
				S++;
			}
		}
	}
}

void dlte(int x)
{
	B[L] = 0;
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
		printf("\n");
		for (i = 0; i < S; i++) {
			printf("%3d\t", B[i]);
		}
		printf("\n\n");

		scanf(" %c", &c);
		if (c == 's') {
			scanf(" %d", &x);
			if (srch(x) == -1 && L != R)
				printf("%d Not Found. Should be between %d and %d\n", x, L, R);
			else if (srch(x) == -1 && L == R)
				printf("%d Not Found. Stored as deleted value at %d\n", x, L);
			else
				printf("%d Found at Index %d\n", x, L);
		}
		else if (c == 'i') {
			scanf(" %d", &x);
			if (srch(x) == -1) {
				insrt(x);
			}
		}
		else if (c == 'd') {
			scanf(" %d", &x);
			if (srch(x) == 1) {
				dlte(x);
			}
		}
		else if (c == 'q') {
			break;
		}
		else {
			printf("???\n");
		}
	}
	return 0;
}