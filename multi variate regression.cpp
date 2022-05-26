#include<bits/stdc++.h>
using namespace std;

//B=(X'X)^(-1)X'Y

void transpose(int row, int column,double m1[5000][5000],double m2[5000][5000]);
void inverse(int n,double m1[5000][5000],double m2[5000][5000]);
void multiplication(int row1,int column1,int row2,int column2,double matrix1[5000][5000],
                    double matrix2[5000][5000],double mul[5000][5000]);


int main()
{
    int row,column,i,j,k;

    freopen("output.txt", "r", stdin);
    cin>>row>>column;

    static double matrix[5000][5000],transposeMatrix[5000][5000],mul[5000][5000],mul2[5000][5000],inverseMatrix[5000][5000],y[5000][5000];


    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            cin>>matrix[i][j];
        }
        cin>>y[i][0];
    }


    for(i=0;i<row;i++)
        matrix[i][0]=1;


//Formula implementation:

    transpose(row,column,matrix,transposeMatrix);
 //   cout<<"Multiplication: X'X"<<endl;
    multiplication(column,row,row,column,transposeMatrix,matrix,mul);
  //  cout<<"Inverse Matrix: (X'X)^(-1)"<<endl;
    inverse(column,mul,inverseMatrix);
  //  cout<<"Multiplication: (X'X)^(-1)X'"<<endl;
    multiplication(column,column,column,row,inverseMatrix,transposeMatrix,mul);
  //  cout<<"Multiplication: (X'X)^(-1)X'Y"<<endl;
    multiplication(column,row,row,1,mul,y,mul2);

     //write on a file
    ofstream file("value.txt");

    for(i=0;i<12;i++)
        file<<mul2[i][0]<<" ";

    file.close();


    cout<<"The equation is:"<<endl<<"Y= B0";
    for(i=1;i<column;i++)
        cout<<" +B"<<i<<"X"<<i;


    cout<<"\n\nThe final equation is:"<<endl<<mul2[0][0];
    for(i=1;i<column;i++)
        cout<<" +("<<mul2[i][0]<<")X"<<i;
    cout<<endl;


    return 0;

}



void transpose(int row,int column,double m1[5000][5000],double m2[5000][5000])
{
    int i,j;

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            m2[j][i]=m1[i][j];
        }
    }
//    cout<<"\nTranspose Matrix:\n";
//    for(i=0;i<column;i++){
//        for(j=0;j<row;j++){
//            cout<<setw(8)<<m2[i][j];
//        }
//        cout<<endl;
//    }
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

//
//    cout<<"\nInverse matrix: "<<endl;
//    for(i=0;i<n;i++){
//        for(j=0;j<n;j++)
//            cout<<setw(15)<<m2[i][j];
//        cout<<endl;
//    }
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
//
//   // cout<<"The multiplication of the matrix is:\n";
//    for(i=0;i<row1;i++){
//        for(j=0;j<column2;j++){
//            cout<<setw(15)<<mul[i][j];
//        }
//        cout<<endl;
//    }
}
