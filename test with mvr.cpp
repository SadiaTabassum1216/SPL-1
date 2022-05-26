#include<bits/stdc++.h>
#include <iostream>
#include<string.h>
#define column 12
using namespace std;

int main()
{

    float coeffecient[column],user[column],ans;
    int i;

    ifstream fp { "value.txt" };
    for(i=0;i<column;i++){
            fp>>coeffecient[i];
    }
//
//    freopen("userInput.txt", "r", stdin);
//    for(i=0;i<column;i++){
//        cin>>user[i];
//    }
    cout<<"\tWelcome! please fill up the form."<<endl;
    string name,temp;
    cout<<"\nName: ";
    cin>>name;
    cout<<"Gender (male/female): ";
    cin>>temp;
    if(temp=="male")
            user[1]=1;
        else if(temp=="female")
            user[1]=0;
        else
            user[1]=-1;


    cout<<"Marital status (yes/no): ";
    cin>>temp;
        if(temp=="yes")
            user[2]=1;
        else if(temp=="no")
            user[2]=0;
        else
            user[2]=-1;


    cout<<"Number of dependents: ";
    cin>>user[3];
        if(user[3]>3)
            user[3]=4;



    cout<<"Education status:\n\t1. Graduate(yes)\n\t2. Non graduate(no)\n\t";
    cin>>temp;
        if(temp=="yes")
            user[4]=1;
        else if(temp=="no")
            user[4]=0;
        else
            user[4]=-1;

    cout<<"Employment status (yes/ no): ";
    cin>>temp;
        if(temp=="yes")
            user[5]=1;
        else if(temp=="no")
            user[5]=0;
        else
            user[5]=-1;

    cout<<"Applicant income ($): ";
    cin>>user[6];

    cout<<"Co-Applicant income ($): ";
    cin>>user[7];

    cout<<"Loan amount ($): ";
    cin>>user[8];

    cout<<"Loan amount term(in month): ";
    cin>>user[9];

    cout<<"Credit history (yes/ no): ";
    cin>>temp;
        if(temp=="yes")
            user[10]=1;
        else if(temp=="no")
            user[10]=0;
        else
            user[10]=-1;


     cout<<"Property Area (Urban/ SemiUrban/ Rural): ";
    cin>>temp;
        if(temp=="Urban")
            user[11]=2;
        else if(temp=="SemiUrban")
            user[11]=1;
        else if(temp=="Rural")
            user[11]=0;
        else
            user[5]=-1;

            for(i=0;i<column;i++){
                if(user[i]==-1){
                    cout<<"wrong input"<<endl;
                    return 0;
                }
            }


   cout<<"The final equation is:"<<endl<<coeffecient[0];

    for(i=1;i<column;i++)
        cout<<" +("<<coeffecient[i]<<")("<<user[i]<<")";

    ans=coeffecient[0];
    for(i=1;i<column;i++)
        ans+=coeffecient[i]*user[i];

    cout<<"\n\nThe value is: "<<ans<<endl;
    if(ans>0.5)
        cout<<"\nAccepted."<<endl;
    else
        cout<<"\nRejected."<<endl;

}
