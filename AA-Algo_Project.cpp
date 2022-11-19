#include<iostream>
#include<utility>
#include<bits/stdc++.h>
using namespace std;

void subMatrix(float** mat, float** temp, int p, int q, int n) {
   int i = 0;
   int j = 0;
   // filling the sub matrix
   for (int row = 0; row < n; row++) {
      for (int col = 0; col < n; col++) {
         // skipping if the current row or column is not equal to the current
         // element row and column
         if (row != p && col != q) {
            temp[i][j++] = mat[row][col];
            if (j == n - 1) {
               j = 0;
               i++;
            }
         }
      }
   }
}

//Function to find the determinant of a matrix
float FindDet(float** A, int n)
{
    float determinant = 0;
    if (n == 1) {
        return A[0][0];
        }
   if (n == 2) {
      return (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
   }
   //int temp[5][5], sign = 1;
   int sign = 1;
   float** temp = (float**)new float[1000];
   for(int e = 0;e<n;e++)
   {
    temp[e] = new float[1000];
   }
   for (int i = 0; i < n; i++) {
      subMatrix(A, temp, 0, i, n);
      determinant += sign * A[0][i] * FindDet(temp, n - 1);
      sign = -sign;
   }
   return determinant;
}

//Function to get the cofactor of every elemnet in the matrix
void getCofactor(float** A, float** temp, int p, int q,int n)
{
    int i = 0, j = 0;
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those elements which are not in the given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
                // Row is filled, so increase row index and and reset column index 
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(float** A, float adj[1000][1000],int n)
{
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }
    // temp is used to store cofactors of A[][]
    int sign = 1;
    float** temp = (float**)new float[1000][1000];
    for(int e = 0;e<n;e++)
    {
        temp[e] = new float[1000];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, n);
            // sign of adj[j][i] is positive if sum of row and column index is divisible by 2(or even)
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            // Interchanging rows and columns to get the transpose of the matrix
            adj[j][i] = (sign) * (FindDet(temp, n - 1));
        }
    }
}

float** InverseMatrix(float** A,int n)
{
    float det = FindDet(A, n);
    //adj stores the adjoint of every element of the matrix
    float adj[1000][1000];
    adjoint(A, adj, n);
    //inverse stores the final inverse of the matrix
    float **inverse = (float**)new float[1000];
    for(int q = 0;q<1000;q++)
    {
        inverse[q] = new float[1000];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inverse[i][j] = adj[i][j] / det;
        }
    }
    return inverse;
}

bool FindMatrix(float **A, float* B, int m)
{
    float inv = 0;
    int invalid = 0;
    float **p = (float**)new float[1000];
    float *x = (float*)new float[1000];
    for(int q = 0;q<1000;q++)
    {
        p[q] = new float[1000];
    }
    for(int i = 0;i < m;i++)
    {
        invalid = 0;
        for(int j = 0;j < m;j++)
        {
            if(A[i][j] == 0)
            {
                invalid += 1;
            }
        }
        if((invalid == m) && (B[i] > 0))
        {
            return false;//Because 0 multiplied with any number cannot be greater than any positive number
        }
    }
    //inv holds the determinant of the matrix to check if the matrix is invertible or not
    inv = FindDet(A,m);
    if(inv == 0)
    {
        //Here we subtract or add the diagonal elements by 1(Identity Matrix) to make sure the matrix is invvertible
        for(int k = 0;k<m;k++)
        {
            if(((A[k][k] > 0) && (B[k] > 0)) || ((A[k][k] <= 0) && (B[k] <= 0)))
            {
                A[k][k] = A[k][k] - 1;
            }
            else if(((A[k][k] >= 0) && (B[k] < 0)) || ((A[k][k] < 0) && (B[k] >= 0)))
            {
                A[k][k] = A[k][k] + 1;
            }
        }
    }
    //p stores the inverse of the matrix A
    p = InverseMatrix(A,m);
    /*for(int z = 0;z<m;z++)
    {
	for(int h = 0;h<m;h++)
	{
		cout << p[z][h];
	}
	cout << '\n';
    }*/
    for(int l = 0;l<m;l++)
    {
        for(int r = 0;r<m;r++)
        {
            x[l] += p[l][r] * B[r];
        }
        //x[l] = x[l]*2;
        //cout << fixed << setprecision(1) << x[l];
        //cout<<x[l];
        //cout <<'\n';
    }
    if(inv != 0)
    {
    	cout <<"The values for x is: \n";
    	for(int g = 0;g<m;g++)
    	{
		cout<< x[g]<<'\n';
	}
    }
    else
    {
    	cout <<"Possible values of x are: \n";
    	for(int a1 = 0;a1<m;a1++)
    	{
    		x[a1] = x[a1]*2;
    		cout<< x[a1]<<'\n';
    	}
    	cout <<"or\n";
    	for(int a2 = 0;a2<m;a2++)
    	{
		x[a2] = x[a2]/4;
		cout<< x[a2]<<'\n';
	}
     }
     return true;
}

int main()
{
    float** A = (float**)new float[1000];
    float* B = (float*)new float[1000];
    int m;
    for(int w = 0;w<1000;w++)
    {
        A[w] = new float[1000];
    }
    //Accepting the number of rows and the elements of the matrix
    cout <<"Enter the number of rows in the matrix: ";
    cin >> m;
    cout <<"Enter the Matrix A: ";
    for(int e = 0;e<m;e++)
    {
        for(int r = 0;r<m;r++)
        {
            cin >> A[e][r];
        }
    }
    cout <<"Enter the Matrix B: ";
    for(int t = 0 ;t<m;t++)
    {
        cin >> B[t];
    }
    //bool res = FindMatrix(A,B,m);
    if(FindMatrix(A,B,m))
        cout <<"It is possible to get a matrix X\n";
    else
        cout <<"It is not possible to get a matrix X\n";
    return 0;
}
