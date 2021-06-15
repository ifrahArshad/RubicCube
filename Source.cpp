#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

//Front-0
//Back-1
//Up-2
//Down-3
//Left-4
//Right-5


class Cube{
private:
	int cube[6][3][3];
public:
	Cube() {
		cube[6][3][3];
	}
	void readFromFile(ifstream& fin) {
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++) {
					fin >> cube[i][j][k];
				}
	}
	void p() {
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					cout << cube[i][j][k];
	}
	void print() {

		for (int j = 0; j < 3; j++) {
			cout << "      ";
			for (int k = 0; k < 3; k++) {
				cout << cube[2][j][k] << " ";
			}
			cout << endl;
		}

		for (int j = 0; j < 3; j++) {
			//cout << "   ";
			for (int k = 0; k < 3; k++) {
				cout << cube[4][j][k] << " ";
			}
			for (int k = 0; k < 3; k++) {
				cout << cube[0][j][k] << " ";
			}
			for (int k = 0; k < 3; k++) {
				cout << cube[5][j][k] << " ";
			}
			for (int k = 0; k < 3; k++) {
				cout << cube[1][j][k] << " ";
			}
			cout << endl;
		}


		for (int j = 0; j < 3; j++) {
			cout << "      ";
			for (int k = 0; k < 3; k++) {
				cout << cube[3][j][k] << " ";
			}
			cout << endl;
		}

		cout << endl;
	}

	int heuristic(Cube &target) {
		//return 0;
		int count=0;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					if (this->cube[i][j][k] != target.cube[i][j][k])
						count++;
		return count/12;
	}

	void clockwise(int phase) {
		int temp1 = cube[phase][0][0];
		int temp2 = cube[phase][1][0];
		int temp3 = cube[phase][2][0];

		cube[phase][0][0] = cube[phase][2][0];
		cube[phase][1][0] = cube[phase][2][1];
		cube[phase][2][0] = cube[phase][2][2];

		cube[phase][2][1] = cube[phase][1][2];
		cube[phase][2][2] = cube[phase][0][2];
		cube[phase][1][2] = cube[phase][0][1];

		cube[phase][0][2] = temp1;
		cube[phase][0][1] = temp2;
		cube[phase][0][0] = temp3;
	}
	void anticlockwise(int phase) {
		int temp1 = cube[phase][0][0];
		int temp2 = cube[phase][1][0];

		cube[phase][0][0] = cube[phase][0][2];
		cube[phase][1][0] = cube[phase][0][1];
		cube[phase][0][1] = cube[phase][1][2];

		cube[phase][0][2] = cube[phase][2][2];
		cube[phase][1][2] = cube[phase][2][1];
		cube[phase][2][2] = cube[phase][2][0];

		cube[phase][2][1] = temp2;
		cube[phase][2][0] = temp1;

	}
	void frontClockwise() {
		///phase itself

		clockwise(0);
		//other phases
		int temp1 = cube[4][0][2];
		int temp2 = cube[4][1][2];
		int temp3 = cube[4][2][2];

		cube[4][0][2] = cube[3][0][0];
		cube[4][1][2] = cube[3][0][1];
		cube[4][2][2] = cube[3][0][2];

		cube[3][0][0] = cube[5][2][0];
		cube[3][0][1] = cube[5][1][0];
		cube[3][0][2] = cube[5][0][0];

		cube[5][2][0] = cube[2][2][2];
		cube[5][1][0] = cube[2][2][1];
		cube[5][0][0] = cube[2][2][0];

		cube[2][2][2] = temp1;
		cube[2][2][1] = temp2;
		cube[2][2][0] = temp3;
	}
	void frontAntiClockwise() {
		///phase itself

		anticlockwise(0);
		//other phases
		int temp1 = cube[4][0][2];
		int temp2 = cube[4][1][2];
		int temp3 = cube[4][2][2];

		cube[4][0][2] = cube[2][2][2];
		cube[4][1][2] = cube[2][2][1];
		cube[4][2][2] = cube[2][2][0];

		cube[2][2][2] = cube[5][2][0];
		cube[2][2][1] = cube[5][1][0];
		cube[2][2][0] = cube[5][0][0];

		cube[5][2][0] = cube[3][0][0];
		cube[5][1][0] = cube[3][0][1];
		cube[5][0][0] = cube[3][0][2];

		cube[3][0][0] = temp1;
		cube[3][0][1] = temp2;
		cube[3][0][2] = temp3;
	}
	void backClockwise() {///phase itself

		clockwise(1);
		//other phases
		int temp1 = cube[5][0][2];
		int temp2 = cube[5][1][2];
		int temp3 = cube[5][2][2];

		cube[5][0][2] = cube[3][2][2];
		cube[5][1][2] = cube[3][2][1];
		cube[5][2][2] = cube[3][2][0];

		cube[3][2][2] = cube[4][2][0];
		cube[3][2][1] = cube[4][1][0];
		cube[3][2][0] = cube[4][0][0];

		cube[4][2][0] = cube[2][0][0];
		cube[4][1][0] = cube[2][0][1];
		cube[4][0][0] = cube[2][0][2];

		cube[2][0][0] = temp1;
		cube[2][0][1] = temp2;
		cube[2][0][2] = temp3;
	}
	void backAntiClockwise() {
		///phase itself

		anticlockwise(1);
		//other phases
		int temp1 = cube[5][0][2];
		int temp2 = cube[5][1][2];
		int temp3 = cube[5][2][2];

		cube[5][0][2] = cube[2][0][0];
		cube[5][1][2] = cube[2][0][1];
		cube[5][2][2] = cube[2][0][2];

		cube[2][0][0] = cube[4][2][0];
		cube[2][0][1] = cube[4][1][0];
		cube[2][0][2] = cube[4][0][0];

		cube[4][2][0] = cube[3][2][2];
		cube[4][1][0] = cube[3][2][1];
		cube[4][0][0] = cube[3][2][0];

		cube[3][2][2] = temp1;
		cube[3][2][1] = temp2;
		cube[3][2][0] = temp3;
	}
	void rightClockwise() {
		///phase itself

		clockwise(5);
		//other phases
		int temp1 = cube[0][0][2];
		int temp2 = cube[0][1][2];
		int temp3 = cube[0][2][2];

		cube[0][0][2] = cube[3][0][2];
		cube[0][1][2] = cube[3][1][2];
		cube[0][2][2] = cube[3][2][2];

		cube[3][0][2] = cube[1][2][0];
		cube[3][1][2] = cube[1][1][0];
		cube[3][2][2] = cube[1][0][0];

		cube[1][2][0] = cube[2][0][2];
		cube[1][1][0] = cube[2][1][2];
		cube[1][0][0] = cube[2][2][2];

		cube[2][0][2] = temp1;
		cube[2][1][2] = temp2;
		cube[2][2][2] = temp3;
	}
	void rightAntiClockwise() {
		///phase itself

		anticlockwise(5);
		//other phases
		int temp1 = cube[0][0][2];
		int temp2 = cube[0][1][2];
		int temp3 = cube[0][2][2];

		cube[0][0][2] = cube[2][0][2];
		cube[0][1][2] = cube[2][1][2];
		cube[0][2][2] = cube[2][2][2];

		cube[2][0][2] = cube[1][2][0];
		cube[2][1][2] = cube[1][1][0];
		cube[2][2][2] = cube[1][0][0];

		cube[1][2][0] = cube[3][0][2];
		cube[1][1][0] = cube[3][1][2];
		cube[1][0][0] = cube[3][2][2];

		cube[3][0][2] = temp1;
		cube[3][1][2] = temp2;
		cube[3][2][2] = temp3;
	}
	void leftClockwise() {

		clockwise(4);
		//other phases
		int temp1 = cube[1][0][2];
		int temp2 = cube[1][1][2];
		int temp3 = cube[1][2][2];

		cube[1][0][2] = cube[3][2][0];
		cube[1][1][2] = cube[3][1][0];
		cube[1][2][2] = cube[3][0][0];

		cube[3][2][0] = cube[0][2][0];
		cube[3][1][0] = cube[0][1][0];
		cube[3][0][0] = cube[0][0][0];

		cube[0][2][0] = cube[2][2][0];
		cube[0][1][0] = cube[2][1][0];
		cube[0][0][0] = cube[2][0][0];

		cube[2][2][0] = temp1;
		cube[2][1][0] = temp2;
		cube[2][0][0] = temp3;
	}
	void leftAntiClockwise() {
		anticlockwise(4);
		//other phases
		int temp1 = cube[1][0][2];
		int temp2 = cube[1][1][2];
		int temp3 = cube[1][2][2];

		cube[1][0][2] = cube[2][2][0];
		cube[1][1][2] = cube[2][1][0];
		cube[1][2][2] = cube[2][0][0];

		cube[2][2][0] = cube[0][2][0];
		cube[2][1][0] = cube[0][1][0];
		cube[2][0][0] = cube[0][0][0];

		cube[0][2][0] = cube[3][2][0];
		cube[0][1][0] = cube[3][1][0];
		cube[0][0][0] = cube[3][0][0];

		cube[3][2][0] = temp1;
		cube[3][1][0] = temp2;
		cube[3
		][0][0] = temp3;
	}
	void upClockwise() {

		clockwise(2);
		//other phases
		int temp1 = cube[4][0][0];
		int temp2 = cube[4][0][1];
		int temp3 = cube[4][0][2];

		cube[4][0][0] = cube[0][0][0];
		cube[4][0][1] = cube[0][0][1];
		cube[4][0][2] = cube[0][0][2];

		cube[0][0][0] = cube[5][0][0];
		cube[0][0][1] = cube[5][0][1];
		cube[0][0][2] = cube[5][0][2];

		cube[5][0][0] = cube[1][0][0];
		cube[5][0][1] = cube[1][0][1];
		cube[5][0][2] = cube[1][0][2];

		cube[1][0][0] = temp1;
		cube[1][0][1] = temp2;
		cube[1][0][2] = temp3;
	}
	void upAntiClockwise() {

		anticlockwise(2);
		//other phases
		int temp1 = cube[4][0][0];
		int temp2 = cube[4][0][1];
		int temp3 = cube[4][0][2];

		cube[4][0][0] = cube[1][0][0];
		cube[4][0][1] = cube[1][0][1];
		cube[4][0][2] = cube[1][0][2];

		cube[1][0][0] = cube[5][0][0];
		cube[1][0][1] = cube[5][0][1];
		cube[1][0][2] = cube[5][0][2];

		cube[5][0][0] = cube[0][0][0];
		cube[5][0][1] = cube[0][0][1];
		cube[5][0][2] = cube[0][0][2];

		cube[0][0][0] = temp1;
		cube[0][0][1] = temp2;
		cube[0][0][2] = temp3;
	}
	void downClockwise() {

		clockwise(3);
		//other phases
		int temp1 = cube[4][2][2];
		int temp2 = cube[4][2][1];
		int temp3 = cube[4][2][0];

		cube[4][2][2] = cube[1][2][2];
		cube[4][2][1] = cube[1][2][1];
		cube[4][2][0] = cube[1][2][0];

		cube[1][2][2] = cube[5][2][2];
		cube[1][2][1] = cube[5][2][1];
		cube[1][2][0] = cube[5][2][0];

		cube[5][2][2] = cube[0][2][2];
		cube[5][2][1] = cube[0][2][1];
		cube[5][2][0] = cube[0][2][0];

		cube[0][2][2] = temp1;
		cube[0][2][1] = temp2;
		cube[0][2][0] = temp3;
	}
	void downAntiClockwise() {

		anticlockwise(3);
		//other phases
		int temp1 = cube[4][2][2];
		int temp2 = cube[4][2][1];
		int temp3 = cube[4][2][0];

		cube[4][2][2] = cube[0][2][2];
		cube[4][2][1] = cube[0][2][1];
		cube[4][2][0] = cube[0][2][0];

		cube[0][2][2] = cube[5][2][2];
		cube[0][2][1] = cube[5][2][1];
		cube[0][2][0] = cube[5][2][0];

		cube[5][2][2] = cube[1][2][2];
		cube[5][2][1] = cube[1][2][1];
		cube[5][2][0] = cube[1][2][0];

		cube[1][2][2] = temp1;
		cube[1][2][1] = temp2;
		cube[1][2][0] = temp3;
	}
	bool compare(Cube target) {
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					if (this->cube[i][j][k] != target.cube[i][j][k])
						return false;
		return true;
	}
};

void readData(Cube &input, Cube &output, string file) {
	ifstream fin;
	fin.open(file.c_str());
	input.readFromFile(fin);
//	fin.close();
	//fin.open(file.c_str());
	output.readFromFile(fin);
	fin.close();
}

bool DFS(Cube cube, Cube target, int depth, vector<string> &moves) {
	//checking function
	if (cube.compare(target))
		return true;
	if (depth <= 0)
		return false;
	Cube c = cube;
	c.frontClockwise();
	if (DFS(c, target, depth - 1, moves)){
		moves.push_back("F");
		return true;
	}
	c = cube;
	c.frontAntiClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("F'");
		return true;
	}
	c = cube;
	c.backClockwise();
	if (DFS(c , target, depth - 1, moves)) {
		moves.push_back("B");
		return true;
	}
	c = cube;
	c.backAntiClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("B'");
		return true;
	}
	c = cube;
	c.upClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("U");
		return true;
	}
	c = cube;
	c.upAntiClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("U'");
		return true;
	}
	c = cube;
	c.downClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("D");
		return true;
	}
	c = cube;
	c.downAntiClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("D'");
		return true;
	}
	c = cube;
	c.leftClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("L");
		return true;
	}
	c = cube;
	c.leftAntiClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("L'");
		return true;
	}
	c = cube;
	c.rightClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("R");
		return true;
	}
	c = cube;
	c.rightAntiClockwise();
	if (DFS(c, target, depth - 1, moves)) {
		moves.push_back("R'");
		return true;
	}
	return false;
}
bool IDFS(Cube cube, Cube target,int limit,vector<string> &moves) {
	//vector<string> moves;
	for (int i = 1; i <= limit; i++) {
		if (DFS(cube, target, i,moves))
			return true;
	}
	return false;
}


struct State {
	Cube cube;
	State *parent;
	int cost;
	int heuristic;
	string move;
	State(Cube _cube, State *parent, int cost, int heuristic, string move) {
		this->cube = _cube;
		this->parent = parent;
		this->cost = cost;
		this->heuristic = heuristic;
		this->move = move;
	}

};

class Compare
{
public:
	bool operator() (State *s, State *t)
	{
		return ((s->cost + s->heuristic) > (t->cost + t->heuristic));
	}
};

void printBFSPath(State *s) {
	cout << endl;
	vector<string> moves;
	while (s != nullptr) {
		//cout << s->move << " ";
		moves.push_back(s->move);
		s = s->parent;
	}
	for (int i = moves.size() - 1; i >= 0; i--) {
		cout << moves[i] << " ";
	}
}

void printIDFSPath(vector<string> moves) {
	for (int i = moves.size() - 1; i >= 0; i--) {
		cout << moves[i] << " ";
	}
}
bool BFS(Cube cube, Cube target) {

	priority_queue<State*, vector<State*>, Compare> queue;
	queue.push(new State(cube, nullptr, 0, cube.heuristic(target), " "));
	while (!queue.empty()) {
		State *s = queue.top();
		queue.pop();
		Cube c = s->cube;
		Cube temp;

		cout << s->cost << " " << s->heuristic << endl;
		if (c.compare(target)) {
			printBFSPath(s);
			cout << "FOUND\n";
			return true;
		}

		temp = c;
		temp.frontClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "F"));

		temp = c;
		temp.frontAntiClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "F'"));

		temp = c;
		temp.backClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "B"));

		temp = c;
		temp.backAntiClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "B'"));

		temp = c;
		temp.upClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "U"));

		temp = c;
		temp.upAntiClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "U'"));

		temp = c;
		temp.downClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "D"));

		temp = c;
		temp.downAntiClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "D'"));

		temp = c;
		temp.leftClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "L"));

		temp = c;
		temp.leftAntiClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "L'"));

		temp = c;
		temp.rightClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "R"));

		temp = c;
		temp.rightAntiClockwise();
		queue.push(new State(temp, s, s->cost + 1, temp.heuristic(target), "R'"));
	}
	return false;
}

int main() {

	Cube cube;
	Cube output;

	readData(cube, output, "output.txt");

	cout << "--------------Original--------------------" << endl;
//	cube.p();
	cube.print();
	cout << endl;
	output.print();
	cout << endl;

	cube.frontClockwise();
	cube.upAntiClockwise();
	cube.frontClockwise();
	cube.upAntiClockwise();


	vector<string> moves;
	cout << "-------------IDFS------------" << endl;
	if (IDFS(cube, output, 20, moves)) {
		printIDFSPath(moves);
	}
	cout << endl<<"-------------A*------------" << endl;
	BFS(cube, output);
	

	system("pause");
	return 0;
}