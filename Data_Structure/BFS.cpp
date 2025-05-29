#include<iostream>
using namespace std;

// Queue 구현
const int N = 10000;
int Queue[N];
int Head, Tail;

void init() {
	Head = 0;
	Tail = 0;
}

bool isEmpty() {
	return (Head == Tail);
}

void Insert(int x) {
	Queue[Tail] = x;
	Tail = (Tail + 1) % N;
}

int Delete() {
	int RetVal;
	RetVal = Queue[Head];
	Head = (Head + 1) % N;
	return RetVal;
}

// BFS 명시적 Queue 미로 찾기
int find(char** (&Map), int row, int col) {
	int i = 0, j = 0;
	cout << "\n\n경로: ";
	
	while (true) {
		if (i == row - 1 && j == col - 1) {
			Map[i][j] = '*';
			cout << "(" << i << ", " << j << ") ";
			return 1; // 도착
		}

		// Queue에 있던 좌표가 이미 간 지점일때
		if (Map[i][j] == '*') { 
			if (isEmpty()) 
				return -1;
			else {
				i = Delete();
				j = Delete();
				continue;
			}
		}

		Map[i][j] = '*';
		cout << "(" << i << ", " << j << ") ";
		if ((j < col - 1) && Map[i][j + 1] == '0') { // 오른쪽
			Insert(i);
			Insert(j + 1);
		}
		if ((i < row - 1 && j < col - 1) && Map[i + 1][j + 1] == '0') { // 대각선 오른쪽 아래
			Insert(i + 1);
			Insert(j + 1);
		}
		if ((i < row - 1) && Map[i + 1][j] == '0') { // 아래
			Insert(i + 1);
			Insert(j);
		}
		if ((i < row - 1 && j > 0) && Map[i + 1][j - 1] == '0') { // 대각선 왼쪽 아래
			Insert(i + 1);
			Insert(j - 1);
		}
		if ((j > 0) && Map[i][j - 1] == '0') { // 왼쪽
			Insert(i);
			Insert(j - 1);
		}
		if ((i > 0 && j > 0) && Map[i - 1][j - 1] == '0') { // 대각선 왼쪽 위
			Insert(i - 1);
			Insert(j - 1);
		}
		if ((i > 0) && Map[i - 1][j] == '0') { // 위
			Insert(i - 1);
			Insert(j);
		}
		if ((i > 0 && j < col - 1) && Map[i - 1][j + 1] == '0') { // 대각선 오른쪽 위
			Insert(i - 1);
			Insert(j + 1);
		}

		if (isEmpty()) return -1; // 더이상 갈 곳이 없음. 포기

		i = Delete();
		j = Delete();
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
		cout << "\n\nBFS 미로 찾기 성공" << endl;
		printMap(Map, row, col);
	}
	else {
		cout << "\n\nBFS 미로 찾기 실패" << endl;
		printMap(Map, row, col);
	}

	for (int i = 0; i < col; i++)
		delete[] Map[i];
	delete[] Map;
	Map = nullptr;
	return 0;
}