#include<bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

struct user
{
    string loan_ID;             //key
    string gender;              //categorical
    string married;             //categorical
    string dependent;           //ordinal
    string education;           //ordinal
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

int standardDeviation(int a[],int n)
{
    int i,square=0,var;

    for(i=0;i<n;i++)
        square+=a[i]*a[i];

    int avg=mean(a,n);

    var=(square/n)-avg*avg;

return sqrt(var);
}

void boxPlot(int a[],int n, int q[4])
{
    int x,y,z;

    //data must be sorted
    x=n/4;
    y=n/2;
    z=3*n/4;

    q[0]=a[x];
    q[1]=a[y];
    q[2]=a[z];
    q[3]=q[2]-q[0]; //IQR
}


void sorting(int a[],int n)
{
    int i,j,temp;

    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(a[i]>a[j]){
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}

//main
int main()
{

    //read train file
    ifstream fp("Train Dataset.txt");
    int i=0,n=0,j;

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
    int x=0;
    float rate;
    for(i=0;i<n;i++){
        if(users[i].status=="Y")
            x++;
    }
    rate=(float)x/(float)n*100.00;

    cout<<"Approved loan: "<<x<<endl;
    cout<<"Approval rate:"<< rate<<"%"<<endl;


    //Univariate data analysis (Categorical)

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
    cout<<"Re-payed doubt applicant:"<< rate<<"%"<<endl;

    //convert into a 2D array
    float data[n][13];
    for(i=0;i<n;i++){
        data[i][0]=stof(users[i].loan_ID);
        if(users[i].gender=="Male")
            data[i][1]=1;
        else
            data[i][1]=0;

        if(users[i].married=="Yes")
            data[i][2]=1;
        else
            data[i][2]=0;

        if(users[i].dependent=="3+")
            data[i][3]=4;
        else
            data[i][3]=stof(users[i].dependent);

        if(users[i].education=="Graduate")
            data[i][4]=1;
        else
            data[i][4]=0;

        if(users[i].employment=="Yes")
            data[i][5]=1;
        else
            data[i][5]=0;

        data[i][6]=stof(users[i].applicantIncome);
        data[i][7]=stof(users[i].coApplicantIncome);
        data[i][8]=stof(users[i].amount);
        data[i][9]=stof(users[i].loanTerm);
        data[i][10]=stof(users[i].credit_History);

        if(users[i].area=="Urban")
            data[i][11]=2;
        else if(users[i].area=="Semiurban")
            data[i][11]=1;
        else
            data[i][11]=0;

        if(users[i].status=="Y")
            data[i][12]=1;
        else
            data[i][12]=0;

    for(i=0;i<n;i++){
        for(j=0;j<13;j++){
            cout<<data[i][j]<<" ";
        }
        cout<<"\n";
    }
    }




    //removing missing values:
        //we'll use the prior one from univariate analysis
}
