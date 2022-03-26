#include<bits/stdc++.h>
using namespace std;

//B=(X'X)^(-1)X'Y

void transpose(int n,float m1[50][50],float m2[50][50]);
void inverse(int n,float m1[50][50],float m2[50][50]);
void multiplication(int row1,int column1,int row2,int column2,float matrix1[50][50],
                    float matrix2[50][50],float mul[50][50]);


int main()
{
int N,i,j,k;

cout<<"Enter order of matrix: ";
cin>>N;

float matrix[50][50],transposeMatrix[50][50],mul[50][50],mul2[50][50],inverseMatrix[50][50],y[50][50];

printf("Enter matrix x:\n");
for(i=0;i<N;i++){
    for(j=0;j<N;j++){
        cin>>matrix[i][j];
    }
}

printf("Enter matrix y:\n");
for(i=0;i<N;i++){
    for(j=0;j<1;j++){
        cin>>y[i][j];
    }
}

transpose(N,matrix,transposeMatrix);
cout<<"Multiplication: XX'"<<endl;
multiplication(N,N,N,N,matrix,transposeMatrix,mul);
inverse(N,mul,inverseMatrix);
cout<<"Multiplication: (XX')^(-1)X'"<<endl;
multiplication(N,N,N,N,inverseMatrix,transposeMatrix,mul);
cout<<"Multiplication: (XX')^(-1)X'Y"<<endl;
multiplication(N,N,N,1,mul,y,mul2);


//    cout<<"\nInverse matrix: "<<endl;
//    for(i=0;i<N;i++){
//        for(j=0;j<N;j++)
//            cout<<setw(15)<<inverseMatrix[i][j];
//        cout<<endl;
//    }

return 0;
}

void transpose(int n,float m1[50][50],float m2[50][50])
{
    int i,j;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            m2[j][i]=m1[i][j];
        }
    }
cout<<"\nTranspose Matrix:\n";
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cout<<setw(20)<<m2[i][j]<<" ";
        }
        cout<<endl;
    }
}

void inverse(int n,float m1[50][50],float m2[50][50])
{
    int i,j,k;
    float d,a[500][500];

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            a[i][j]=m1[i-1][j-1];
        }
    }

    //Augmenting Identity Matrix of Order N
    for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
				   if(i==j)
				    	a[i][j+n] = 1;
				   else
				    	a[i][j+n] = 0;
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


    cout<<"\nInverse matrix: "<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            cout<<setw(20)<<m2[i][j];
        cout<<endl;
    }
}

void multiplication(int row1,int column1,int row2,int column2,float matrix1[50][50],
                    float matrix2[50][50],float mul[50][50])
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

   // cout<<"The multiplication of the matrix is:\n";
    for(i=0;i<row1;i++){
        for(j=0;j<column2;j++){
            cout<<setw(20)<<mul[i][j]<<" ";
        }
        cout<<endl;
    }
}
