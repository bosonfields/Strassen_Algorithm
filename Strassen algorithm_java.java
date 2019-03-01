//Strassen Algorithm
package strassen.multiplicate;

import java.util.*;

public class Strassen {
	public static void main(String[] args){
		int[][] arrA={{1,3,5},
			          {2,4,6},
			          {3,5,7},};
	    int[][] arrB={{1,2,7},
			          {8,3,4},
			          {2,13,5}};
	    Matrix A = new Matrix(arrA);
	    Matrix B = new Matrix(arrB);
	    
	    int finalRow = B.row;
	    int finalColumn = A.column;
	    
	    int sNum = squareNum(A, B);
	    A.square(sNum);
	    B.square(sNum);
	    System.out.println();

	    Matrix C = Strassen_algorithm(A, B);
	    C.de_square(finalRow, finalColumn);
	    Read(C);
	    
	}
	static Matrix Strassen_algorithm(Matrix A, Matrix B){
		Matrix C = new Matrix(A.size);
		if(A.size == 1){
			C.setValue(0, 0, A.element(0, 0)*B.element(0, 0));
		}
		else{
			int size = A.size/2;
			Matrix A11 = A.split(11);
			Matrix A12 = A.split(12);
			Matrix A21 = A.split(21);
			Matrix A22 = A.split(22);
			
			Matrix B11 = B.split(11);
			Matrix B12 = B.split(12);
			Matrix B21 = B.split(21);
			Matrix B22 = B.split(22);
			
			Matrix S1, S2, S3, S4, S5, S6, S7, S8, S9, S10;
			Matrix P1, P2, P3, P4, P5, P6, P7;
		
			S1 = addtion(B12, B22.add_coeficient(-1));
			S2 = addtion(A11, A12);
			S3 = addtion(A21, A22);
			S4 = addtion(B21, B11.add_coeficient(-1));
			S5 = addtion(A11, A22);
			S6 = addtion(B11, B22);
			S7 = addtion(A12, A22.add_coeficient(-1));
			S8 = addtion(B21, B22);
			S9 = addtion(A11, A21.add_coeficient(-1));
			S10 = addtion(B11, B12);
			
			P1 = Strassen_algorithm(A11, S1);
			P2 = Strassen_algorithm(S2, B22);
			P3 = Strassen_algorithm(S3, B11);
			P4 = Strassen_algorithm(A22, S4);
			P5 = Strassen_algorithm(S5, S6);
			P6 = Strassen_algorithm(S7, S8);
			P7 = Strassen_algorithm(S9, S10);
			
			Matrix C11 = new Matrix(size);
			Matrix C12 = new Matrix(size);
			Matrix C21 = new Matrix(size);
			Matrix C22 = new Matrix(size);
			
			C11 = addtion4(P5,P4,P2.add_coeficient(-1),P6);
			C12 = addtion(P1,P2);
			C21 = addtion(P3,P4);
			C22 = addtion4(P5, P1, P3.add_coeficient(-1), P7.add_coeficient(-1));
			
			C.merge(C11, C12, C21, C22);
		}
		return C;
	}
	
	static void Read(Matrix M){
		System.out.println("Print Strassen Result:");
		int size = M.matrix.size();
		for(int i=0; i<size; i++){
			System.out.println(M.matrix.get(i));
		}
	}
    static Matrix addtion(Matrix A, Matrix B){
    	int size = A.size;
    	Matrix add = new Matrix(size);
    	for(int i=0; i<size; i++){
    		for(int j=0; j<size; j++){
    			add.setValue(i, j, A.element(i, j) + B.element(i, j));
    		}
    	}
    	return add;
    }
    static Matrix addtion4(Matrix A, Matrix B, Matrix C, Matrix D){
    	int size = A.size;
    	Matrix add4 = new Matrix(size);
    	for(int i=0; i<size; i++){
    		for(int j=0; j<size; j++){
    			add4.setValue(i, j, A.element(i, j) + B.element(i, j) + C.element(i, j) + D.element(i, j));
    		}
    	}
    	return add4;
    }
    static int squareNum(Matrix A, Matrix B){
    	Integer sizeArr[] = {A.column, A.row, B.column, B.row};
    	int max = (int) Collections.max(Arrays.asList(sizeArr));
    	int sNum = 1;
    	while(sNum<max){
    		sNum = sNum * 2;
    	}
    	return sNum;
    }
}