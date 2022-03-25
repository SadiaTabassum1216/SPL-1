#include<bits/stdc++.h>
using namespace std;

int main()
{
    int i,j,k,n;
    float a[100][100],d;
    cout<<"Enter order of matrix: ";
    cin>>n;

    cout<<"Enter the matrix: "<<endl;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin>>a[i][j];

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

    cout<<"Inverse matrix: "<<endl;
    for(i=1;i<=n;i++){
        for(j=n+1;j<=n*2;j++)
            cout<<setw(15)<<a[i][j];
        cout<<endl;
    }
    return 0;
}
