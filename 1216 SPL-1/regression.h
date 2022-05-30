#pragma once

#include<bits/stdc++.h>
using namespace std;

//B=(X'X)^(-1)X'Y

void transpose(int row, int column,double m1[5000][5000],double m2[5000][5000]);
void inverse(int n,double m1[5000][5000],double m2[5000][5000]);
void multiplication(int row1,int column1,int row2,int column2,double matrix1[5000][5000],
                    double matrix2[5000][5000],double mul[5000][5000]);


float* regressionFunc(string input)
{
    int row,column,i,j,k;
     static double matrix[5000][5000],transposeMatrix[5000][5000],mul[5000][5000],mul2[5000][5000],
     inverseMatrix[5000][5000],y[5000][5000];

   {
     ifstream cin(input);
        cin>>row>>column;

        for(i=0;i<row;i++){
            for(j=0;j<column;j++){
                cin>>matrix[i][j];
            }
        cin>>y[i][0];
        }

   }




    for(i=0;i<row;i++)
        matrix[i][0]=1;


//Formula implementation:

    transpose(row,column,matrix,transposeMatrix);   //transpose
    multiplication(column,row,row,column,transposeMatrix,matrix,mul);   //X'X"
    inverse(column,mul,inverseMatrix);  //(X'X)^(-1)
    multiplication(column,column,column,row,inverseMatrix,transposeMatrix,mul); //(X'X)^(-1)X'
    multiplication(column,row,row,1,mul,y,mul2);    //(X'X)^(-1)X'Y



    float *output=new float[12];

    for(i=0;i<12;i++)
        output[i]=mul2[i][0];


//    cout<<"The equation is:"<<endl<<"Y= B0";
//    for(i=1;i<column;i++)
//        cout<<" +B"<<i<<"X"<<i;


    cout<<"\nEquation: "<<mul2[0][0];
    for(i=1;i<column;i++)
        cout<<" +("<<mul2[i][0]<<")X"<<i;
    cout<<endl;

    return output;

}

void transpose(int row,int column,double m1[5000][5000],double m2[5000][5000])
{
    int i,j;

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            m2[j][i]=m1[i][j];
        }
    }
}



void inverse(int n,double m1[5000][5000],double m2[5000][5000])
{
    int i,j,k;
    static double d,a[5000][10000];

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            a[i][j]=m1[i-1][j-1];
        }
    }

    //Augmenting Identity Matrix of Order N
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j)
                a[i][j+n]=1;
            else
                a[i][j+n]=0;
        }
    }

    //Reducing to diagonal  matrix
    for(i=1;i<=n;i++){
        for(j=1;j<=n*2;j++)
            if(j!=i){
                d=a[j][i]/a[i][i];
                for(k=1;k<=n*2;k++)
                    a[j][k]=a[j][k]-a[i][k]*d;
            }
    }

    //Reducing to unit matrix
    for(i=1;i<=n;i++){
        d=a[i][i];
        for(j=1;j<=n*2;j++)
            a[i][j]=a[i][j]/d;
    }

     for(i=1;i<=n;i++){
        for(j=n+1;j<=n*2;j++)
            m2[i-1][j-n-1]=a[i][j];
     }
}



void multiplication(int row1,int column1,int row2,int column2,double matrix1[5000][5000],
                    double matrix2[5000][5000],double mul[5000][5000])
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
}
