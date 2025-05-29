#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

class Node {
public:
	int a;
	int LLen, RLen;
	Node* L, * R;
};

class AVL {
public:
	AVL();
	Node* Search(int x);
	Node* SearchP(Node* N, int x);
	void Insert(int x);
	int InsertP(Node* N, int x, Node** RP);
	void Print();
	void PrintP(Node* N, int d, int LR);
	Node* Root = nullptr;
};

AVL::AVL()
{
	Root = new Node;
	Root->a = 999;
	Root->LLen = 0;
	Root->RLen = 0;
	Root->L = NULL;
	Root->R = NULL;
}

Node* AVL::Search(int x)
{
	return SearchP(Root->L, x);
}

Node* AVL::SearchP(Node* N, int x)
{
	Node* NN;
	if (N == NULL) return NULL;
	else {
		if (N->a < x) {
			return SearchP(N->R, x);
		}	
		else if (N->a > x) {
			return SearchP(N->L, x);
		}	
		else {
			printf("Found!!\n");
			return N;
		}		
	}
}

void AVL::Insert(int x)
{
	int Len = InsertP(Root->L, x, &(Root->L));
	Root->LLen = Len + 1;
}

int AVL::InsertP(Node* N, int x, Node** RP)
{
	Node* NN, *A, *B, *C, *T1, *T2;
	int Len;
	if (N == NULL) {
		NN = new Node;
		NN->a = x;
		NN->L = NN->R = NULL;
		NN->LLen = NN->RLen = 0;
		*RP = NN;
		return 0;
	} 
	else {
		if (N->a < x) {
			Len = InsertP(N->R, x, &(N->R));
			N->RLen = Len + 1;
		}
		else if (N->a > x) {
			Len = InsertP(N->L, x, &(N->L));
			N->LLen = Len + 1;
		}
	}

	if (N->LLen > N->RLen + 1 || N->RLen > N->LLen + 1) {
		if (N->a > x && (N->L)->a > x) { // case LL
			A = N; 
			B = N->L; 

			T1 = B->R;
			B->R = A;
			A->L = T1;
			
			if (A->L == NULL)
				A->LLen = 0;
			else
				A->LLen = max((A->L)->LLen, (A->L)->RLen) + 1;
			B->LLen = max((B->L)->LLen, (B->L)->RLen) + 1;
			B->RLen = max((B->R)->LLen, (B->R)->RLen) + 1;
			*RP = B;
			return max(B->LLen, B->RLen);
		}
		else if (N->a > x && (N->L)->a < x) { // case LR
			A = N;
			B = A->L;
			C = B->R;

			T1 = C->L;
			T2 = C->R;
			C->L = B;
			C->R = A;
			B->R = T1;
			A->L = T2;

			if (B->R == NULL) B->RLen = 0;
			else B->RLen = max((B->R)->LLen, (B->R)->RLen) + 1;

			if (A->L == NULL) A->LLen = 0;
			else A->LLen = max((A->L)->LLen, (A->L)->RLen) + 1;

			C->LLen = max((C->L)->LLen, (C->L)->RLen) + 1;
			C->RLen = max((C->R)->LLen, (C->R)->RLen) + 1;
			*RP = C;
			return max(C->LLen, C->RLen);
		}
		else if (N->a < x && (N->R)->a < x) { // case RR
			A = N;
			B = N->R;

			T1 = B->L;
			B->L = A;
			A->R = T1;

			if (A->R == NULL)
				A->RLen = 0;
			else
				A->RLen = max((A->R)->LLen, (A->R)->RLen) + 1;
			B->LLen = max((B->L)->LLen, (B->L)->RLen) + 1;
			B->RLen = max((B->R)->LLen, (B->R)->RLen) + 1;
			*RP = B;
			return max(B->LLen, B->RLen);
		}
		else if (N->a > x && (N->L)->a < x) { // case RL
			A = N;
			B = A->R;
			C = B->L;

			T1 = C->L;
			T2 = C->R;
			C->L = A;
			C->R = B;
			A->R = T1;
			B->L = T2;

			if (A->R == NULL) A->RLen = 0;
			else A->RLen = max((A->R)->LLen, (A->R)->RLen) + 1;

			if (B->L == NULL) B->LLen = 0;
			else B->LLen = max((B->L)->LLen, (B->L)->RLen) + 1;

			C->LLen = max((C->L)->LLen, (C->L)->RLen) + 1;
			C->RLen = max((C->R)->LLen, (C->R)->RLen) + 1;
			*RP = C;
			return max(C->LLen, C->RLen);
		}
	}
	return max(N->LLen, N->RLen);
}

void AVL::Print()
{
	PrintP(Root, 0, 0);
}

void AVL::PrintP(Node* N, int d, int LR)
{
	if (LR == 1) {
		for (int i = 0; i < d; i++)
			printf("              ");
	}	
	printf(" [%2d|%4d|%2d] ", N->LLen, N->a, N->RLen);

	if (N->L == NULL)
		printf("\n");
	else
		PrintP(N->L, d + 1, 0);

	if (N->R != NULL)
		PrintP(N->R, d + 1, 1);
}

int main()
{
	char c;
	int x, i;
	AVL T;
	Node* RR;

	while (true) {
		T.Print();
		scanf(" %c", &c);
		if (c == 's') { // Search
			scanf(" %d", &x);
			if ((RR = T.Search(x)) == NULL)
				printf("%d Not Found.\n", x);
			else
				printf("%d Found at Address %d\n", x, RR);
		}
		else if (c == 'i') { // Insert
			scanf(" %d", &x);
			T.Insert(x);
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


