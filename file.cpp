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

float minimum(float a[],int n){
    int i;
    float m=a[1];
    for(i=1;i<n;i++){
        if(a[i]<m)
            m=a[i];
    }
return m;
}

void print(int n,float a[][13]){
int i,j;
cout<<"Gender Married Dependents Education Employed A.Income CA.Income LoanAmount Term Credit_History Area Status\n";
for(i=0;i<n;i++){
    for(j=1;j<13;j++){
        cout<<a[i][j]<<" ";
    }
    cout<<"\n";
    }
}

float mean(float a[][13],int n,int category)
{
    int i,sum=0;

    for(i=0;i<n;i++)
    {
        sum=sum+a[i][category];
    }
return sum/n;
}

float standardDeviation(float a[][13],int n,int category)
{
    int i,square=0,var;

    for(i=0;i<n;i++)
        square+=a[i][category]*a[i][category];

    float avg=mean(a,n,category);

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
    ifstream fp("Train-Dataset.txt");
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
    float missingData[13];

   //Gender
    x=0;
    for(i=0;i<n;i++){
        if(users[i].gender=="Male")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Male applicant:"<< rate<<"%"<<endl;
    if(rate>50)
        missingData[1]=1;
    else
        missingData[1]=0;



    //Marital status
    x=0;
    for(i=0;i<n;i++){
        if(users[i].married=="Yes")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Married applicant:"<< rate<<"%"<<endl;
    if(rate>50)
        missingData[2]=1;
    else
        missingData[2]=0;


         //Graduate
    x=0;
    for(i=0;i<n;i++){
        if(users[i].education=="Graduate")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Graduate applicant:"<< rate<<"%"<<endl;
    if(rate>50)
        missingData[4]=1;
    else
        missingData[4]=0;



    //Employment Type
    x=0;
    for(i=0;i<n;i++){
        if(users[i].employment=="Yes")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Self Employed applicant:"<< rate<<"%"<<endl;
    if(rate>50)
        missingData[5]=1;
    else
        missingData[5]=0;



    //Credit history
    x=0;
    for(i=0;i<n;i++){
        if(users[i].credit_History=="1")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Re-payed debt applicant:"<< rate<<"%"<<endl;
    if(rate>50)
        missingData[10]=1;
    else
        missingData[10]=0;


    //convert into a 2D array
    float data[n][13];
    int countArea[3]={0};
    for(i=0;i<n;i++){
        data[i][0]=atof(users[i].loan_ID.c_str());
        if(users[i].gender=="Male")
            data[i][1]=1;
        else if(users[i].gender=="Female")
            data[i][1]=0;
        else
            data[i][1]=missingData[1];



        if(users[i].married=="Yes")
            data[i][2]=1;
        else if(users[i].married=="No")
            data[i][2]=0;
        else
            data[i][2]=missingData[2];



        if(users[i].dependent=="3+")
            data[i][3]=4;
        else if(users[i].dependent=="0" || users[i].dependent=="1" || users[i].dependent=="3")
            data[i][3]=atof(users[i].dependent.c_str());




        if(users[i].education=="Graduate")
            data[i][4]=1;
        else if(users[i].education=="Not Graduate")
            data[i][4]=0;
        else
            data[i][4]=missingData[4];


        if(users[i].employment=="Yes")
            data[i][5]=1;
        else if(users[i].employment=="No")
            data[i][5]=0;
        else
            data[i][5]=missingData[5];


        data[i][6]=atof(users[i].applicantIncome.c_str());
        data[i][7]=atof(users[i].coApplicantIncome.c_str());
        data[i][8]=atof(users[i].amount.c_str());
        data[i][9]=atof(users[i].loanTerm.c_str());
        if(users[i].credit_History=="0" || users[i].credit_History=="1")
            data[i][10]=atof(users[i].credit_History.c_str());
        else
            data[i][10]=missingData[10];


        if(users[i].area=="Urban"){
            data[i][11]=2;
            countArea[2]++;
        }
        else if(users[i].area=="Semiurban"){
            data[i][11]=1;
            countArea[1]++;
        }
        else if(users[i].area=="Rural"){
            data[i][11]=0;
            countArea[0]++;
        }

        if(users[i].status=="Y")
            data[i][12]=1;
        else
            data[i][12]=0;

    }
            int counts[4]={0,0,0,0};
            for(i=0;i<n;i++){
                counts[(int)data[i][3]-1]++;
            }
            int maxCount=counts[0],maxCountCatagory=1;
            for(i=1;i<4;i++){
                if(counts[i]>maxCount){
                    maxCount=counts[i];
                    maxCountCatagory=i+1;
                }
            }
            cout<<"Average dependent number: "<<maxCountCatagory<<endl;
        for(i=0;i<n;i++){
            if(users[i].dependent!="0" && users[i].dependent!="1" && users[i].dependent!="3" && users[i].dependent!="3+")
                data[i][3]=maxCountCatagory;
        }


        int maxCountArea=0;
        maxCountCatagory=0;
        for(i=0;i<3;i++){
            if(countArea[i]>maxCountArea){
                maxCountArea=countArea[i];
                maxCountCatagory=i;
            }
        }
       // cout<<"Max resident from: "<<maxCountCatagory<<endl;
        for(i=0;i<n;i++){
            if(users[i].area!="Urban" && users[i].area!="Semiurban" && users[i].area!="Rural")
                data[i][11]=maxCountArea;
        }



    float avgIncome=mean(data,n,6);
    cout<<"Average applicant income: $"<<avgIncome<<endl;
    for(i=0;i<n;i++){
        if(data[i][6]==0)
            data[i][6]=avgIncome;
    }

    float avgCAIncome=mean(data,n,7);
    cout<<"Average Co applicant income: $"<<avgCAIncome<<endl;
    for(i=0;i<n;i++){
        if(data[i][7]==0){
            data[i][7]=avgCAIncome;
        }
    }

    float avgLoan=mean(data,n,8);
    cout<<"Average Loan Amount: $"<<avgLoan<<endl;
    for(i=0;i<n;i++){
        if(data[i][8]==0){
            data[i][8]=avgLoan;
        }
    }


    float avgLoanTerm=mean(data,n,9);
    cout<<"Average Loan Term: "<<avgLoanTerm<<endl;
    for(i=0;i<n;i++){
        if(data[i][9]==0){
            data[i][9]=avgLoanTerm;
        }
    }

    //write on a file
    ofstream file("output.txt");
    file<<n<<"\t"<<"12"<<endl;

    for(i=0;i<n;i++){
        for(j=0;j<13;j++)
            file<<setw(10)<<data[i][j]<<" ";
        file<<endl;
    }

    file.close();
}
