#include<bits/stdc++.h>
using namespace std;

//B=(X'X)^(-1)X'Y

void transpose(int row, int column,float m1[700][700],float m2[700][700]);
void inverse(int n,float m1[700][700],float m2[700][700]);
void multiplication(int row1,int column1,int row2,int column2,float matrix1[700][700],
                    float matrix2[700][700],float mul[700][700]);


int main()
{
int row,column,n,i,j,k;

freopen("output.txt", "r", stdin);
//cout<<"Enter order of matrix: ";
cin>>row>>n;
column=n+1;

static float matrix[700][700],transposeMatrix[700][700],mul[700][700],mul2[700][700],inverseMatrix[700][700],y[700][700],user[700],ans=0;


//cout<<"Enter matrix x:"<<endl;
for(i=0;i<row;i++){
    for(j=1;j<column;j++){
        cin>>matrix[i][j];
    }
    cin>>y[i][0];
}

for(i=0;i<row;i++)
    matrix[i][0]=1;

//cout<<"Enter matrix y:"<<endl;
//for(i=0;i<row;i++){
//    for(j=0;j<1;j++){
//        cin>>y[i][j];
//    }
//}

//cout<<"User input:"<<endl;
for(i=0;i<n;i++)
    cin>>user[i];


cout<<"\nInput Matrix:\n";
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            cout<<setw(8)<<matrix[i][j];
        }
        cout<<endl;
    }
cout<<"Y matrix:\n";
for(i=0;i<row;i++)
    cout<<y[i][0]<<endl;

transpose(row,column,matrix,transposeMatrix);
cout<<"Multiplication: X'X"<<endl;
multiplication(column,row,row,column,transposeMatrix,matrix,mul);
cout<<"Inverse Matrix: (X'X)^(-1)"<<endl;
inverse(column,mul,inverseMatrix);
cout<<"Multiplication: (X'X)^(-1)X'"<<endl;
multiplication(column,column,column,row,inverseMatrix,transposeMatrix,mul);
cout<<"Multiplication: (X'X)^(-1)X'Y"<<endl;
multiplication(column,row,row,1,mul,y,mul2);

ans=mul2[0][0];
for(i=1;i<=n;i++)
ans+=mul2[i][0]*user[i-1];

cout<<"\nThe value is: "<<ans;

return 0;
}

void transpose(int row,int column,float m1[700][700],float m2[700][700])
{
    int i,j;

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            m2[j][i]=m1[i][j];
        }
    }
cout<<"\nTranspose Matrix:\n";
    for(i=0;i<column;i++){
        for(j=0;j<row;j++){
            cout<<setw(8)<<m2[i][j];
        }
        cout<<endl;
    }
}

void inverse(int n,float m1[700][700],float m2[700][700])
{
    int i,j,k;
    float d,a[700][700];

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


    cout<<"\nInverse matrix: "<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            cout<<setw(15)<<m2[i][j];
        cout<<endl;
    }
}

void multiplication(int row1,int column1,int row2,int column2,float matrix1[700][700],
                    float matrix2[700][700],float mul[700][700])
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
            cout<<setw(15)<<mul[i][j];
        }
        cout<<endl;
    }
}
