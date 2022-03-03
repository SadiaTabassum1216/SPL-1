#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include<cstring>
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
        data[i][0]=atof(users[i].loan_ID.c_str());
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
            data[i][3]=atof(users[i].dependent.c_str());

        if(users[i].education=="Graduate")
            data[i][4]=1;
        else
            data[i][4]=0;

        if(users[i].employment=="Yes")
            data[i][5]=1;
        else
            data[i][5]=0;

        data[i][6]=atof(users[i].applicantIncome.c_str());
        data[i][7]=atof(users[i].coApplicantIncome.c_str());
        data[i][8]=atof(users[i].amount.c_str());
        data[i][9]=atof(users[i].loanTerm.c_str());
        data[i][10]=atof(users[i].credit_History.c_str());

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


    }
    cout<<"Gender,Married,Dependents,Education,Self_Employed,ApplicantIncome,CoapplicantIncome,LoanAmount,Loan_Amount_Term,Credit_History,Property_Area,Loan_Status";
    for(i=0;i<n;i++){
        for(j=1;j<13;j++){
           cout<<data[i][j]<<"\t";
        }
        cout<<"\n";
   }


float mean[13],percentage[13],entropy[13];

//Mean
int sum;
for(j=0;j<13;j++){
        sum=0;
   // mean[i]=Mean(m,n,a,i);
    for(i=0;i<n;i++)
        sum=sum+data[i][j];

    mean[j]=sum/(float)n;
}
cout<<"Mean: ";
for(i=1;i<13;i++)
    cout<<mean[i]<<" ";
    cout<<endl;

//Percentage
int c;

for(j=0;j<13;j++){
        c=0;
    for(i=0;i<n;i++){
        if(data[i][j]<mean[j])
            c++;
    }
    percentage[j]=(float)c/(float)n;
}
cout<<"Percentage: ";
for(i=1;i<13;i++)
    cout<<percentage[i]<<" ";


    //removing missing values:
        //we'll use the prior one from univariate analysis
}
