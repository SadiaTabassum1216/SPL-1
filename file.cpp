#include<bits/stdc++.h>
using namespace std;

struct user
{
    string loan_ID;             //key
    string gender;              //categorical
    string married;             //categorical
    string dependent;           //ordinal
    string education;           //cordinal
    string employment;          //categorical
    string applicantIncome;     //numerical
    string coApplicantIncome;   //numerical
    string amount;              //numerical
    string loanTerm;            //numerical
    string credit_History;      //categorical
    string area;                //ordinal
    string status;              //dependent variable
}users[1000];

int mean(int a[],int n)
{
    int i,sum=0;

    for(i=0;i<n;i++)
    {
        sum=sum+a[i];
    }
return sum/n;
}


//main
int main()
{

    //read train file
    ifstream fp("Train Dataset.txt");
    int i=0,n=0;

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
            /*cout <<i+1<<"\t"<<users[i].loan_ID<<"\t"<<users[i].gender<<"\t"<<users[i].married<<"\t"
            <<users[i].dependent<<"\t"<<users[i].education<<"\t"<<users[i].employment<<"\t"
            <<users[i].applicantIncome<<"\t"<<users[i].coApplicantIncome<<"\t"
            <<users[i].amount<<"\t"<<users[i].loanTerm<<"\t"
            <<users[i].credit_History<< setw (20)<<users[i].area<< setw (10)<<users[i].status <<endl;*/
            ++n;


            }

    fp.close();
    cout<<"Total customer is: "<<n<<endl;
    int x=0;
    float rate;
    for(i=0;i<n;i++){
        if(users[i].status=="Y")
            x++;
    }
    rate=(float)x/(float)n*100.00;

    cout<<"Approved loan: "<<x<<endl;
    cout<<"Approval rate:"<< rate<<"%"<<endl;

    //Univariate data analysis (Cateorical)

   //Gender
    x=0;
    for(i=0;i<n;i++){
        if(users[i].gender=="Male")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Male applicant:"<< rate<<"%"<<endl;

    //Marital status
       x=0;
    for(i=0;i<n;i++){
        if(users[i].married=="Yes")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Married applicant:"<< rate<<"%"<<endl;

    //Employment Type
    x=0;
    for(i=0;i<n;i++){
        if(users[i].employment=="Yes")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Self Employed applicant:"<< rate<<"%"<<endl;

    //Credit history
       x=0;
    for(i=0;i<n;i++){
        if(users[i].credit_History=="1")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Repayed doubt applicant:"<< rate<<"%"<<endl;


    //removing missing values:
}
