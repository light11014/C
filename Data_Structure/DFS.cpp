#include <iostream>
using namespace std;

// Stack 구현
const int N = 10000;
int Stack[N];
int SP;

void init() {
	SP = 0;
}

bool isEmpty() {
	return (SP == 0);
}

void Push(int x) {
	Stack[SP++] = x;
}

int Pop() {
	if (SP == 0) return -1;
	return Stack[--SP];
}

// DFS 명시적 Stack 미로찾기
int find(char** (&Map), int row, int col) {
	int i = 0, j = 0;
	Map[i][j] = '*';
	cout << "\n\n경로: ";

	int ip, jp;
	while (true) {
		cout << "(" << i << ", " << j << ") ";
		if (i == row - 1 && j == col - 1) return 1; // 도착

		ip = -100;
		jp = -100;
		if ((j < col - 1) && Map[i][j + 1] == '0') { // 오른쪽
			ip = i;
			jp = j + 1;
		}
		else if ((i < row - 1 && j < col - 1) && Map[i + 1][j + 1] == '0') { // 대각선 오른쪽 아래
			ip = i + 1;
			jp = j + 1;
		}
		else if ((i < row - 1) && Map[i + 1][j] == '0') { // 아래
			ip = i + 1;
			jp = j;
		}
		else if ((i < row - 1 && j > 0) && Map[i + 1][j - 1] == '0') { // 대각선 왼쪽 아래
			ip = i + 1;
			jp = j - 1;
		}
		else if ((j > 0) && Map[i][j - 1] == '0') { // 왼쪽
			ip = i;
			jp = j - 1;
		}
		else if ((i > 0 && j > 0) && Map[i - 1][j - 1] == '0') { // 대각선 왼쪽 위
			ip = i - 1;
			jp = j - 1;
		}
		else if ((i > 0) && Map[i - 1][j] == '0') { // 위
			ip = i - 1;
			jp = j;
		}
		else if ((i > 0 && j < col - 1) && Map[i - 1][j + 1] == '0') { // 대각선 오른쪽 위
			ip = i - 1;
			jp = j + 1;
		}

		if (ip != -100) { // 전진
			Push(i); 
			Push(j);
			i = ip; 
			j = jp;
			Map[i][j] = '*';
		}
		else { // 후진
			if (isEmpty()) return -1;
			Map[i][j] = 'X';
			j = Pop();
			i = Pop();
		}
	}	
}

void printMap(char** (&Map), int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << Map[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	init();

	// 입력받기
	int row, col;
	cin >> row >> col;

	// 2차원 배열 동적할당
	char* (*Map) = new char* [row];
	for (int i = 0; i < row; i++)
		Map[i] = new char[col];

	// 사용자 입력 Map 배열에 저장
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int temp;
			cin >> temp;
			Map[i][j] = (temp == 0) ? '0' : '1';
		}
	}

	int result = find(Map, row, col);
	
	if (result == 1) {
		cout << "\n\nDFS 미로 찾기 성공" << endl;
		printMap(Map, row, col);
	}
	else {	
		cout << "\n\nDFS 미로 찾기 실패" << endl;
		printMap(Map, row, col);
	}

	for (int i = 0; i < col; i++)
		delete[] Map[i];
	delete[] Map;
	Map = nullptr;
	return 0;
}

