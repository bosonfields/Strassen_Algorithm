# Strassen for py

import math
import numpy as np

def squareMatrix(A, B):
    M_len = np.array([len(A), len(A[0]), len(B), len(B[0])])
    lMax = np.max(M_len)
    sNum = 1
    while sNum<lMax:
        sNum = sNum * 2
    Aup = np.hstack((A,np.zeros((len(A),sNum - len(A[0])))))
    A = np.vstack((Aup, np.zeros((sNum-len(A),sNum))))
    Bup = np.hstack((B, np.zeros((len(B), sNum - len(B[0])))))
    B = np.vstack((Bup, np.zeros((sNum - len(B), sNum))))
    return A, B

def strassen(A, B):
    n= len(A[0])
    C=np.array(np.zeros((n, n)))
    if n==1:
        C[0][0]=A[0][0]*B[0][0]
    else:
        (A1,A2)=np.split(A,2,axis=0)
        (B1,B2)=np.split(B,2,axis=0)
        (A11,A12,A21,A22)=(np.split(A1, 2, axis=1) + np.split(A2, 2, axis=1))
        (B11,B12,B21,B22)=(np.split(B1, 2, axis=1) + np.split(B2, 2, axis=1))
        S1 = B12 - B22
        S2 = A11 + A12
        S3 = A21 + A22
        S4 = B21 - B11
        S5 = A11 + A22
        S6 = B11 + B22
        S7 = A12 - A22
        S8 = B21 + B22
        S9 = A11 - A21
        S10= B11 + B12
        P1 = strassen(A11, S1)
        P2 = strassen(S2, B22)
        P3 = strassen(S3, B11)
        P4 = strassen(A22, S4)
        P5 = strassen(S5, S6)
        P6 = strassen(S7, S8)
        P7 = strassen(S9, S10)
        C11 = P5 + P4 - P2 + P6
        C12 = P1 + P2
        C21 = P3 + P4
        C22 = P5 + P1 - P3 - P7
        C = np.vstack((np.hstack((C11, C12)),np.hstack((C21, C22))))
    return C

A = np.array([[1, 3, 8], [7, 5, 2]])
B = np.array([[6, 8], [4, 2],[5, 3]])

row = len(B[0])
column = len(A)

A, B = squareMatrix(A,B)

C = strassen(A, B)

C = C[:column,:row]

print(C)