#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void initial_zero(vector<vector<int>> &vec, int nums);
void strassen_algorithm(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int n);
void split_matrix(vector<vector<int>> &A, vector<vector<int>> &A11, vector<vector<int>> &A12, vector<vector<int>> &A21, vector<vector<int>> &A22, int n2);
void addition_matrix(vector<vector<int>> &result,vector<vector<int>> vec1, vector<vector<int>> vec2, vector<vector<int>> vec3, vector<vector<int>> vec4, int nums);
vector<vector<int>> negative_matrix(vector<vector<int>> A, int nums);
void merge_matrix(vector<vector<int>> &C, vector<vector<int>> C11, vector<vector<int>> C12, vector<vector<int>> C21, vector<vector<int>> C22, int nums);

int main() {
	
	int n = 2;
	
	vector<vector<int>> vecA= { {1,3},{7,5} };
	vector<vector<int>> vecB= { {6,8},{4,2} };
	vector<vector<int>> vecC;
	
	initial_zero(vecC, n);
	strassen_algorithm(vecA, vecB, vecC, n);

	for (vector<vector<int>>::iterator it = vecC.begin(); it != vecC.end(); it++) {
		vector<int> vec_temp = *it;
		for (vector<int>::iterator iter = vec_temp.begin(); iter != vec_temp.end(); iter++) {
			cout << *iter << " ";
		} 
		cout<<endl;
	}
	std::cin.get();
}

void strassen_algorithm(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int n) {
	if (n == 1) {
		C[0][0] = A[0][0] * B[0][0];
	}
	else {
		int n2 = n / 2;
		//initial subset
		vector<vector<int>> vecZero;
		vector<vector<int>> A11, A12, A21, A22;
		vector<vector<int>> B11, B12, B21, B22;
		vector<vector<int>> C11, C12, C21, C22;
		vector<vector<int>> S1, S2, S3, S4, S5, S6, S7, S8, S9, S10;
		vector<vector<int>> P1, P2, P3, P4, P5, P6, P7;

		for (auto s : { &vecZero,&A11,&A12,&A21,&A22, &B11, &B12, &B21, &B22, &C11, &C12, &C21, &C22,
			&S1, &S2, &S3, &S4, &S5, &S6, &S7, &S8, &S9, &S10, &P1, &P2, &P3, &P4, &P5, &P6, &P7 }) {
			initial_zero(*s, n2);
		}
		//Split into subset
		split_matrix(A, A11, A12, A21, A22, n2);
		split_matrix(B, B11, B12, B21, B22, n2);

		addition_matrix(S1, B12, negative_matrix(B22,n2), vecZero, vecZero, n2);
		addition_matrix(S2, A11, A12, vecZero, vecZero, n2);
		addition_matrix(S3, A21, A22, vecZero, vecZero, n2);
		addition_matrix(S4, B21, negative_matrix(B11, n2), vecZero, vecZero, n2);
		addition_matrix(S5, A11, A22, vecZero, vecZero, n2);
		addition_matrix(S6, B11, B22, vecZero, vecZero, n2);
		addition_matrix(S7, A12, negative_matrix(A22, n2), vecZero, vecZero, n2);
		addition_matrix(S8, B21, B22, vecZero, vecZero, n2);
		addition_matrix(S9, A11, negative_matrix(A21, n2), vecZero, vecZero, n2);
		addition_matrix(S10, B11, B12, vecZero, vecZero, n2);

		strassen_algorithm(A11, S1, P1, n2);
		strassen_algorithm(S2, B22, P2, n2);
		strassen_algorithm(S3, B11, P3, n2);
		strassen_algorithm(A22, S4, P4, n2);
		strassen_algorithm(S5, S6, P5, n2);
		strassen_algorithm(S7, S8, P6, n2);
		strassen_algorithm(S9, S10, P7, n2);

		addition_matrix(C11, P5, P4, negative_matrix(P2, n2), P6, n2);
		addition_matrix(C12, P1, P2, vecZero, vecZero, n2);
		addition_matrix(C21, P3, P4, vecZero, vecZero, n2);
		addition_matrix(C22, P5, P1, negative_matrix(P3, n2), negative_matrix(P7,n2),n2);

		merge_matrix(C, C11, C12, C21, C22, n);
	}
};

//Initial Matrixes with zero value
void initial_zero(vector<vector<int>> &vec, int nums) {
	int i;
	for (i = 0; i < nums; i++) {
		vector<int> vec_tmp(nums, 0);
		vec.push_back(vec_tmp);
	}
};

//Split matrix quaterly
void split_matrix(vector<vector<int>> &A, vector<vector<int>> &A11, vector<vector<int>> &A12, vector<vector<int>> &A21, vector<vector<int>> &A22, int n2) {
	int i = 0,j;
	for (vector<vector<int>>::iterator iti = A.begin(); iti != A.end(); iti++,i++) {
		vector<int> vec_tmp = *iti;
		j = 0;
		for (vector<int>::iterator itj = vec_tmp.begin(); itj != vec_tmp.end(); itj++,j++) {
			if (i < n2 && j < n2) {
				A11[i][j] = *itj;
			}
			else if (i >= n2 && j < n2) {
				A21[i - n2][j] = *itj;
			}
			else if (i<n2 && j>=n2) {
				A12[i][j - n2] = *itj;
			}
			else {
				A22[i - n2][j - n2] = *itj;
			}
		}
	}
};
//Matrix addition
void addition_matrix(vector<vector<int>> &result,vector<vector<int>> vec1, vector<vector<int>> vec2, vector<vector<int>> vec3, vector<vector<int>> vec4, int nums) {
	int i, j;
	for (i = 0; i < nums; i++) {
		for (j = 0; j < nums; j++) {
			result[i][j]=vec1[i][j] + vec2[i][j] + vec3[i][j] + vec4[i][j];
		}
	}
};
//Assign negative values to the matrix
vector<vector<int>> negative_matrix(vector<vector<int>> A, int nums){
	int i, j;
	vector<vector<int>> negA;
	initial_zero(negA, nums);
	for (i = 0; i < nums; i++) {
		for (j = 0; j < nums; j++) {
			negA[i][j] = 0 - A[i][j];
		}
	}
	return negA;
};
//Merge matrixes into one
void merge_matrix(vector<vector<int>> &C, vector<vector<int>> C11, vector<vector<int>>C12, vector<vector<int>> C21, vector<vector<int>> C22, int nums) {
	int i, j;
	nums = nums/2;
	for (i = 0; i < 2 * nums; i++) {
		for (j = 0; j < 2 * nums; j++) {
			if (i < nums && j < nums) {
				C[i][j] = C11[i][j];
			}
			else if (i >= nums && j < nums) {
				C[i][j] = C21[i - nums][j];
			}
			else if (i < nums && j >= nums) {
				C[i][j] = C12[i][j - nums];
			}
			else {
				C[i][j] = C22[i - nums][j - nums];
			}
		}
	}
};