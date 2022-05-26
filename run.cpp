#include<bits/stdc++.h>
#include <iostream>
#define column 12
#define row 50
using namespace std;

int main()
{

    float coeffecient[column],user[row][column],ans[row],y[row],match=0;
    int i,j,temp;

    freopen("value.txt", "r", stdin);
    for(i=0;i<column;i++){
            cin>>coeffecient[i];
    }

    freopen("output.txt", "r", stdin);
    cin>>temp>>temp;

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            cin>>user[i][j];
        }
        cin>>y[i];
    }

    for(j=0;j<row;j++){
        ans[j]=coeffecient[0];
        for(i=1;i<column;i++)
            ans[j]+=coeffecient[i]*user[j][i];

    if(ans[j]>0.5)
        ans[j]=1;
    else
        ans[j]=0;
    }


    for(i=0;i<row;i++){
        if(ans[i]==y[i]){
            match++;
        }
    }
    double rate=(match*100)/row;
    cout<<"Number of test users: "<<row<<endl;
    cout<<"Accuracy: "<<rate<<"%"<<endl;

}

