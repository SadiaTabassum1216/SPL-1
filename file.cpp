#include<bits/stdc++.h>
using namespace std;

struct user
{
    string loan_ID;
    string gender;
    string married;
    string dependent;
    string education;
    string employment;
    string applicantIncome;
    string coApplicantIncome;
    string amount;
    string loanTerm;
    string credit_History;
    string area;
    string status;
}users[1000];


//main
int main()
{
    ifstream fp("Train Dataset.txt");
    int i=0,j,k,n=0;

    string line,temp="";
    getline(fp,line);   //first line

    for(i=0;;++i)
        {
            getline(fp,line,',');
            users[i].loan_ID=line;

            getline(fp,line,',');
            users[i].gender=line;

            getline(fp,line,',');
            users[i].married=line;

            getline(fp,line,',');
            users[i].dependent=line;

            getline(fp,line,',');
            users[i].education=line;

            getline(fp,line,',');
            users[i].employment=line;

            getline(fp,line,',');
            users[i].applicantIncome=line;

            getline(fp,line,',');
            users[i].coApplicantIncome=line;

            getline(fp,line,',');
            users[i].amount=line;

            getline(fp,line,',');
            users[i].loanTerm=line;

            getline(fp,line,',');
            users[i].credit_History=line;

            getline(fp,line,',');
            users[i].area=line;

            getline(fp,line,'\n');
            users[i].status=line;

            if(!fp)
                break;
            cout <<i+1<<"\t"<<users[i].loan_ID<<"\t"<<users[i].gender<<"\t"<<users[i].married<<"\t"
            <<users[i].dependent<<"\t"<<users[i].education<<"\t"<<users[i].employment<<"\t"
            <<users[i].applicantIncome<<"\t"<<users[i].coApplicantIncome<<"\t"
            <<users[i].amount<<"\t"<<users[i].loanTerm<<"\t"
            <<users[i].credit_History<< setw (20)<<users[i].area<< setw (10)<<users[i].status <<endl;
            ++n;


            }

    fp.close();
    cout<<"Total customer is: "<<n<<endl;
}
