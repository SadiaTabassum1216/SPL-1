#include<bits/stdc++.h>
using namespace std;

struct user
{
    string loan_ID;
    string gender;
    bool married;
    int dependent;
    string education;
    string employment;
    int applicantIncome;
    int coApplicantIncome;
    int amount;
    int loanTerm;
    int credit_History;
    string area;
    bool status;
}users[1000];
//main
int main()
{
    ifstream fp("Train Dataset.txt");
    int i=1,c;
    string line;
    getline(fp,line);

        while(getline(fp,line))
              {
            cout <<i<<" "<< line<<endl;
            i++;
              }

    fp.close();
}
