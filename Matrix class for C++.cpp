// Matrix class for square

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Matrix {
public:
	vector<vector<int>> value;
	Matrix(int nums) {
		int i;
		for (i = 0; i < nums; i++) {
			vector<int> vec_tmp(nums, 0);
			value.push_back(vec_tmp);
		}
	}
	int getRowsize() {
		return int(value.size());
	}
	int getColsize() {
		return int(value[0].size());
	}

	void initial_zero(vector<vector<int>> & vec, int n) {
		int k;
		for (k = 0; k < n; k++) {
			vector<int> vec_tmp(n, 0);
			vec.push_back(vec_tmp);
		}
	}

	void besquare(int n) {
		vector<vector<int>> square;
		initial_zero(square, n);

		int i,j;
		int rlen = getRowsize();
		int clen = getColsize();

		for (i = 0; i < rlen; i++) {
			for (j = 0; j < clen; j++) {
				square[i][j] = value[i][j];
			}
		}
		value = square;
	}
	void split(int r, int c) {
		vector<vector<int>> splitTemp;
		int i, j;
		for (i = 0; i < r; i++) {
			vector<int> vecTemp;
			for (j = 0; j < c; j++) {
				vecTemp.push_back(value[i][j]);
			}
			splitTemp.push_back(vecTemp);
		}
		value = splitTemp;
	}

	void besquared2(int n) {
		int i;
		vector<vector<int>> squared2;
		for (i = 0; i < n; i++) {
			if (i < getRowsize()) {
				vector<int> vecTemp(value[i].begin(), value[i].end());
				vector<int> zeroSome(n - getColsize(), 0);
				vecTemp.insert(vecTemp.end(), zeroSome.begin(), zeroSome.end());
				squared2.push_back(vecTemp);
			}
			else {
				vector<int> zeroWhole(n, 0);
				squared2.push_back(zeroWhole);
			}
		}
		value = squared2;
	}
};

int square_size(Matrix &A, Matrix &B);

int main() {
	Matrix A(3);
	Matrix B(3);
	A.value = { {1,3,5},{6,6,7},{3,7,8} };
	B.value = { {1,5,8,0,1,3} ,{3,6,7,3,2,1}, {4,3,7,5,9,1} };

	int n = square_size(A, B);
	
	B.besquared2(n);

	//B.besquare(n);

	//B.split(3, 6);


	for (vector<vector<int>>::iterator it = B.value.begin(); it != B.value.end(); it++) {
		vector<int> vec_temp = *it;
		for (vector<int>::iterator iter = vec_temp.begin(); iter != vec_temp.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}
	std::cin.get();
}

int square_size(Matrix &A, Matrix &B) {
	int max = 0;
	int arr[] = { A.getColsize(), A.getRowsize(), B.getColsize(), B.getRowsize() };
	for (int i = 0; i < 4; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	int n = 1;
	while (n < max) {
		n = n * 2;
	}
	return n;
}