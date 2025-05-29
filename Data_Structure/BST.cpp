#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

class Node {
public:
	int a;
	Node* L, * R;
};

class BST {
public:
	BST();
	Node* Search(int x);
	Node* SearchP(Node* N, int x);
	void Insert(int x);
	void InsertP(Node* N, int x, Node** RP);
	void Delete(int x);
	void Print();
	void PrintP(Node* N, int d, int LR);
	Node* Root;
	Node* Prt;
};

BST::BST()
{
	Root = new Node;
	Root->a = 999;
	Root->L = NULL;
	Root->R = NULL;
}

Node* BST::Search(int x)
{
	Prt = Root;
	return SearchP(Root->L, x);
}

Node* BST::SearchP(Node* N, int x)
{
	Node* NN;
	if (N == NULL) return NULL;
	else {
		if (N->a < x) {
			Prt = N;
			SearchP(N->R, x);
		}	
		else if (N->a > x) {
			Prt = N;
			SearchP(N->L, x);
		}	
		else {
			printf("Found!!\n");
			return N;
		}		
	}
}

void BST::Insert(int x)
{
	InsertP(Root->L, x, &(Root->L));
}

void BST::InsertP(Node* N, int x, Node** RP)
{
	Node* NN;
	if (N == NULL) {
		NN = new Node;
		NN->a = x;
		NN->L = NN->R = NULL;
		*RP = NN;
	} 
	else {
		if (N->a < x)
			InsertP(N->R, x, &(N->R));
		else if (N->a > x)
			InsertP(N->L, x, &(N->L));
		else
			return;
	}
}


void BST::Delete(int x)
{
	Node* NN, * PP, * MD, * MDP;
	NN = Search(x);
	PP = Prt;
	if (NN == NULL) return;
	if (NN->L == NULL && NN->R == NULL) {
		if (PP->L == NN)
			PP->L = NULL;
		else
			PP->R = NULL;
		delete NN;
	}
	else if (NN->L != NULL && NN->R == NULL) {
		if (PP->L == NN)
			PP->L = NN->L;
		else
			PP->R = NN->L;
		delete NN;
	}
	else if (NN->L == NULL && NN->R != NULL) {
		if (PP->L == NN)
			PP->L = NN->R;
		else
			PP->R = NN->R;
		delete NN;
	}
	else {
		MD = NN->R;
		MDP = NN;
		while (MD->L != NULL) {
			MDP = MD;
			MD = MD->L;
		}	
		NN->a = MD->a;

		if (MD->L == NULL && MD->R == NULL) {
			if (MDP->L == MD)
				MDP->L = NULL;
			else
				MDP->R = NULL;
			delete MD;
		}
		else if (MD->L == NULL && MD->R != NULL) {
			if (MDP->L == MD)
				MDP->L = MD->R;
			else
				MDP->R = MD->R;
			delete MD;
		}
	}
}

void BST::Print()
{
	PrintP(Root, 0, 0);
}

void BST::PrintP(Node* N, int d, int LR)
{
	if (LR == 1)
		for (int i = 0; i < d; i++)
			printf("        ");
	printf("%8d", N->a);

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
	BST T;
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
		else if (c == 'd') { // Delete
			scanf(" %d", &x);
			T.Delete(x);
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


