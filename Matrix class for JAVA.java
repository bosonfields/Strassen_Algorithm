//Matrix class for JAVA

package strassen.multiplicate;

import java.util.*;

public class Matrix {

	int size = 0;
	int row = 0;
	int column = 0;
	List<List<Integer>> matrix = new ArrayList<>();
	
	public Matrix(int n){
		this.row = n;
		this.column = n;
		this.size = n;
		List<Integer> rows = new ArrayList<Integer>();
		for(int i=0;i<n;i++){
			rows.add(0);
		}
		for(int i=0; i<n; i++){
			List<Integer> temp = new ArrayList<Integer>(rows);
			this.matrix.add(temp);
		}
	}
	
	public Matrix(int row, int column){
		this.row = row;
		this.column = column;
		List<Integer> rows = new ArrayList<Integer>();
		for(int i=0;i<row;i++){
			rows.add(0);
		}
		for(int i=0; i<column; i++){
			List<Integer> temp = new ArrayList<Integer>(rows);
			this.matrix.add(temp);
		}
	}
	
	public Matrix(int[][] arr){
		this.row = arr[0].length;
		this.column = arr.length;
		for (int[] array : arr) {
			 List<Integer> rows = new ArrayList<Integer>();
			 for(int s : array){
				 rows.add(s);
			 }
			 this.matrix.add(rows);
		 }      
	}
	
	public List<List<Integer>> read(){
		return this.matrix;
	}
	
	public int element(int i, int j){
		return this.matrix.get(i).get(j);
	}
	
    public void setValue(int i, int j, int value){
    	this.matrix.get(i).set(j, value);
    }
    
    public void square(int sNum){
    	this.size = sNum;
    	int rowDiff = this.size - this.row;
    	
    	for(int i = 0; i<this.column; i++){
        	Integer zeroDiff[] = new Integer[rowDiff];
        	Arrays.fill(zeroDiff, 0);
        	this.matrix.get(i).addAll(Arrays.asList(zeroDiff));
    	}
    	for(int j = 0; j<sNum - this.column; j++){
    		Integer zeroSquare[] = new Integer[sNum];
    		Arrays.fill(zeroSquare, 0);
    		this.matrix.add(Arrays.asList(zeroSquare));
    	}
    }
    
    public Matrix add_coeficient(int c){
    	Matrix coe_product = new Matrix(this.size);
    	for(int i=0; i<this.size; i++){
    		for(int j=0; j<this.size; j++){
    			coe_product.setValue(i, j, this.element(i, j)*c);
    		}
    	}
    	return coe_product;
    }
    
    public Matrix split(int mark){
    	int size=this.size/2;
    	Matrix split_matrix = new Matrix(size);
    		for(int i=0; i<size; i++){
        		for(int j=0; j<size; j++){
        			if(mark==11){
        				split_matrix.setValue(i, j, this.element(i, j));
        			}
        			else if(mark==12){
        				split_matrix.setValue(i, j, this.element(i, size+j));
        			}
        			else if(mark==21){
        				split_matrix.setValue(i, j, this.element(size+i, j));
        			}
        			else{
        				split_matrix.setValue(i, j, this.element(size+i, size+j));
        			}
        		}
    	    }
    		return split_matrix;
    }
    
    public void merge(Matrix M11, Matrix M12, Matrix M21, Matrix M22){
    	int size=this.size/2;
    	for(int i=0; i<this.size; i++){
    		for(int j=0; j<this.size; j++){
    			if(i<size && j<size){
    				this.setValue(i, j, M11.element(i, j));
    			}
    			else if(i<size && j>=size){
    				this.setValue(i, j, M12.element(i, j-size));
    			}
    			else if(i>=size && j<size){
    				this.setValue(i, j, M21.element(i-size, j));
    			}
    			else{
    				this.setValue(i, j, M22.element(i-size, j-size));
    			}
    		}
    	}
    }
    public void de_square(int row, int column){
    	for(int i = 0; i<column; i++){
    		if(row < this.size){this.matrix.get(i).subList(row, this.size).clear();}
    	}
    	if(column< this.size){this.matrix.subList(column, this.size).clear();}
    	this.size = 0;
    }
}