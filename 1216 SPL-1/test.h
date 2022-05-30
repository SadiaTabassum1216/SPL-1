#include<bits/stdc++.h>
#include <iostream>

using namespace std;

float validation(float *value, string input)
{

    int i,j,row,column;

     ifstream cin(input);
        cin>>row>>column;

    float user[row][column],y[row];

        for(i=0;i<row;i++){
            for(j=0;j<column;j++){
                cin>>user[i][j];
            }
        cin>>y[i];
        }


    float coeffecient[column],ans[row],match=0;

    for(i=0;i<column;i++){
        coeffecient[i]=value[i];
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
   // cout<<"Number of test users: "<<row<<endl;
   // cout<<"Accuracy: "<<rate<<"%"<<endl;

    return rate;

}

