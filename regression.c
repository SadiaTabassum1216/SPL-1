#include<stdio.h>

//B=(X'X)^(-1)X'Y

float determinant(int row, float matrix[row][row]);
void transpose(int row,int column,float matrix1[row][column],float matrix2[column][row]);
void coFactor(int row, float matrix[row][row],float output[row][row]);
void multiplication(int row1,int column1,int row2,int column2,float matrix1[row1][column1],float matrix2[row2][column2],float mul[row1][column2]);
void inverse(int row, float input[row][row],float inverseMatrix[row][row]);


int main()
{
int row,column,i,j,k;
printf("Enter the row and column number:");
scanf("%d %d",&row,&column);

float m1[row][column],m2[column][row],mul[row][row],det;
float inverseMatrix[row][row];

printf("Enter the matrix:\n");
for(i=0;i<row;i++){
    for(j=0;j<column;j++){
        scanf("%f",&m1[i][j]);
    }
}

//    transpose(row,column,m1,m2);
//    multiplication(row,column,column,row,m1,m2,mul);
    det= determinant(row,m1);
    printf("\nDeterminant= %.2f",det);

inverse(row,m1,inverseMatrix);


printf("\nInverse Matrix:\n");
    for(i=0;i<row;i++){
        for(j=0;j<row;j++){
            printf("%.4f ",inverseMatrix[i][j]);
        }
        printf("\n");
    }


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
//printf("\nTranspose Matrix:\n");
//    for(i=0;i<column;i++){
//        for(j=0;j<row;j++){
//            printf("%.2f ",m2[i][j]);
//        }
//        printf("\n");
//    }
}


float determinant(int row, float matrix[row][row])
{
    int i,j,k,m,n,sign=1;

    float det=0, b[row][row];
    if(row==1)
        return matrix[0][0];

    det=0;
    for(k=0;k<row;k++){
            m=0;
            n=0;
        for(i=0;i<row;i++){
            for(j=0;j<row;j++){
                if(i!=0 && j!=k){
                    b[m][n]=matrix[i][j];
                    n++;
                    if(n>=row-2)
                    {
                        n=0;
                        m++;
                    }
//                if (n<(row-2))
//                    n++;
//                   else
//                    {
//                     n=0;
//                     m++;
//                     }
                }
            }
        }
        det=det+sign*(matrix[0][k]*determinant(row-1,b));
        //printf("\n** %.2lf",det);
        sign=-1*sign;
    }
return det;
}


void coFactor(int row, float matrix[row][row],float output[row][row])
{
    int i,j,k,l,m,n,sign=1;
for(l=0;l<row;l++){
    for(k=0;k<row;k++){
            m=0;
            n=0;
        for(i=0;i<row;i++){
            for(j=0;j<row;j++){
                if(i!=l && j!=k){
                    output[m][n]=matrix[i][j];
                    n++;
                    if(n==row-2)
                    {
                        n=0;
                        m++;
                    }
                }

            }
        }
    }
}
}


void inverse(int row, float input[row][row],float inverseMatrix[row][row]){

float cofactors[row][row],transposeMatrix[row][row];
int i,j;
coFactor(row,input,cofactors);

printf("\nCofactor:\n");
    for(i=0;i<row;i++){
        for(j=0;j<row;j++){
            printf("%.4f ",cofactors[i][j]);
        }
        printf("\n");
    }

transpose(row,row,cofactors,transposeMatrix);

printf("\nTranspose Matrix:\n");
    for(i=0;i<row;i++){
        for(j=0;j<row;j++){
            printf("%.4f ",transposeMatrix[i][j]);
        }
        printf("\n");
    }

float d=determinant(row,input);


for(i=0;i<row;i++){
    for(j=0;j<row;j++){
        inverseMatrix[i][j]=transposeMatrix[i][j]/d;
    }
}

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
