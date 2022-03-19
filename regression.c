#include<stdio.h>

//B=(X'X)^(-1)X'Y

float determinant(int row, float matrix[row][row]);
void transpose(int row,int column,float matrix1[row][column],float matrix2[column][row]);
void multiplication(int row1,int column1,int row2,int column2,float matrix1[row1][column1],float matrix2[row2][column2],float mul[row1][column2]);

int main()
{
int row,column,i,j,k;
printf("Enter the row and column number:");
scanf("%d %d",&row,&column);

float m1[row][column],m2[column][row],mul[row][row],det;

printf("Enter the matrix:\n");
for(i=0;i<row;i++){
    for(j=0;j<column;j++){
        scanf("%f",&m1[i][j]);
    }
}

    transpose(row,column,m1,m2);
    multiplication(row,column,column,row,m1,m2,mul);


    det= determinant(row,mul);
    printf("\nDeterminant= %.2f",det);
return 0;
}


void transpose(int row,int column,float m1[row][column],float m2[column][row])
{
    int i,j;

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            m2[j][i]=m1[i][j];
        }
    }
printf("\nTranspose Matrix:\n");
    for(i=0;i<column;i++){
        for(j=0;j<row;j++){
            printf("%.2f ",m2[i][j]);
        }
        printf("\n");
    }
}


float determinant(int row, float matrix[row][row])
{
    int i,j,k,m,n,sign=1;
    if(row==1)
        return matrix[0][0];

    float det=0, b[row][row];
    for(k=0;k<row;k++){
            m=0;
            n=0;
        for(i=0;i<row;i++){
            for(j=0;j<row;j++){
                if(i!=0 && j!=k){
                    b[m][n]=matrix[i][j];
                    n++;
                    if(n==row-1)
                    {
                        n=0;
                        m++;
                    }
                }
            }
        }
        det=det+sign*(matrix[0][k]*determinant(row-1,b));
        sign=sign*(-1);
    }
return det;
}

void multiplication(int row1,int column1,int row2,int column2,float matrix1[row1][column1],float matrix2[row2][column2],float mul[row1][column2])
{
    int i,j,k;
    for(i=0;i<row1;i++){
        for(j=0;j<column2;j++){
            mul[i][j]=0;
                for(k=0;k<row2;k++){
                    mul[i][j]=mul[i][j]+matrix1[i][k]*matrix2[k][j];
                }
        }
    }

    printf("The multiplication of the matrix is:\n");
    for(i=0;i<row1;i++){
        for(j=0;j<column2;j++){
            printf("%.2f ",mul[i][j]);
        }
        printf("\n");
    }
}
