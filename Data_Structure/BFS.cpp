#include<iostream>
using namespace std;

// Queue ����
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

// BFS ����� Queue �̷� ã��
int find(char** (&Map), int row, int col) {
	int i = 0, j = 0;
	cout << "\n\n���: ";
	
	while (true) {
		if (i == row - 1 && j == col - 1) {
			Map[i][j] = '*';
			cout << "(" << i << ", " << j << ") ";
			return 1; // ����
		}

		// Queue�� �ִ� ��ǥ�� �̹� �� �����϶�
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
		if ((j < col - 1) && Map[i][j + 1] == '0') { // ������
			Insert(i);
			Insert(j + 1);
		}
		if ((i < row - 1 && j < col - 1) && Map[i + 1][j + 1] == '0') { // �밢�� ������ �Ʒ�
			Insert(i + 1);
			Insert(j + 1);
		}
		if ((i < row - 1) && Map[i + 1][j] == '0') { // �Ʒ�
			Insert(i + 1);
			Insert(j);
		}
		if ((i < row - 1 && j > 0) && Map[i + 1][j - 1] == '0') { // �밢�� ���� �Ʒ�
			Insert(i + 1);
			Insert(j - 1);
		}
		if ((j > 0) && Map[i][j - 1] == '0') { // ����
			Insert(i);
			Insert(j - 1);
		}
		if ((i > 0 && j > 0) && Map[i - 1][j - 1] == '0') { // �밢�� ���� ��
			Insert(i - 1);
			Insert(j - 1);
		}
		if ((i > 0) && Map[i - 1][j] == '0') { // ��
			Insert(i - 1);
			Insert(j);
		}
		if ((i > 0 && j < col - 1) && Map[i - 1][j + 1] == '0') { // �밢�� ������ ��
			Insert(i - 1);
			Insert(j + 1);
		}

		if (isEmpty()) return -1; // ���̻� �� ���� ����. ����

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

	// �Է¹ޱ�
	int row, col;
	cin >> row >> col;

	// 2���� �迭 �����Ҵ�
	char* (*Map) = new char* [row];
	for (int i = 0; i < row; i++)
		Map[i] = new char[col];

	// ����� �Է� Map �迭�� ����
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int temp;
			cin >> temp;
			Map[i][j] = (temp == 0) ? '0' : '1';
		}
	}

	int result = find(Map, row, col);

	if (result == 1) {
		cout << "\n\nBFS �̷� ã�� ����" << endl;
		printMap(Map, row, col);
	}
	else {
		cout << "\n\nBFS �̷� ã�� ����" << endl;
		printMap(Map, row, col);
	}

	for (int i = 0; i < col; i++)
		delete[] Map[i];
	delete[] Map;
	Map = nullptr;
	return 0;
}