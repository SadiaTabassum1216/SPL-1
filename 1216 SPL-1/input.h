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
}usersMainDataset[5000];

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

float meanCalc(float a[][13],int n,int category)
{
    int i,sum=0;

    for(i=0;i<n;i++)
    {
        sum=sum+a[i][category];
    }
return sum/n;
}

//main
void datasetCreator(string input,string output)
{

    //read train file
    ifstream fp(input);
    int i=0,n=0,j;

    string line,temp="";
    getline(fp,line);   //first line

    for(i=0;;++i){
        getline(fp,line,',');
        usersMainDataset[i].loan_ID=line;

        getline(fp,line,',');
        usersMainDataset[i].gender=line;

        getline(fp,line,',');
        usersMainDataset[i].married=line;

        getline(fp,line,',');
        usersMainDataset[i].dependent=line;

        getline(fp,line,',');
        usersMainDataset[i].education=line;

        getline(fp,line,',');
        usersMainDataset[i].employment=line;

        getline(fp,line,',');
        usersMainDataset[i].applicantIncome=line;

        getline(fp,line,',');
        usersMainDataset[i].coApplicantIncome=line;

        getline(fp,line,',');
        usersMainDataset[i].amount=line;

        getline(fp,line,',');
        usersMainDataset[i].loanTerm=line;

        getline(fp,line,',');
        usersMainDataset[i].credit_History=line;

        getline(fp,line,',');
        usersMainDataset[i].area=line;

        getline(fp,line,'\n');
        usersMainDataset[i].status=line;

        if(!fp)
            break;
            /*cout <<i+1<<"\t"<<usersMainDataset[i].loan_ID<<"\t"<<usersMainDataset[i].gender<<"\t"<<usersMainDataset[i].married<<"\t"
            <<usersMainDataset[i].dependent<<"\t"<<usersMainDataset[i].education<<"\t"<<usersMainDataset[i].employment<<"\t"
            <<usersMainDataset[i].applicantIncome<<"\t"<<usersMainDataset[i].coApplicantIncome<<"\t"
            <<usersMainDataset[i].amount<<"\t"<<usersMainDataset[i].loanTerm<<"\t"
            <<usersMainDataset[i].credit_History<< setw (20)<<usersMainDataset[i].area<< setw (10)<<usersMainDataset[i].status <<endl;*/
        ++n;
    }

    fp.close();
    cout<<"Total customer is: "<<n<<endl;
    int x=0;
    float rate;
    for(i=0;i<n;i++){
        if(usersMainDataset[i].status=="Y")
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
        if(usersMainDataset[i].gender=="Male")
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
        if(usersMainDataset[i].married=="Yes")
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
        if(usersMainDataset[i].education=="Graduate")
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
        if(usersMainDataset[i].employment=="Yes")
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
        if(usersMainDataset[i].credit_History=="1")
            x++;
    }
    rate=(float)x/(float)n*100.00;
    cout<<"Previous credit history:"<< rate<<"%"<<endl;
    if(rate>50)
        missingData[10]=1;
    else
        missingData[10]=0;



    //convert into a 2D array with missing data analysis
    float data[n][13];
    int countArea[3]={0};
    for(i=0;i<n;i++){
        data[i][0]=atof(usersMainDataset[i].loan_ID.c_str());
        if(usersMainDataset[i].gender=="Male")
            data[i][1]=1;
        else if(usersMainDataset[i].gender=="Female")
            data[i][1]=0;
        else
            data[i][1]=missingData[1];



        if(usersMainDataset[i].married=="Yes")
            data[i][2]=1;
        else if(usersMainDataset[i].married=="No")
            data[i][2]=0;
        else
            data[i][2]=missingData[2];



        if(usersMainDataset[i].dependent=="3+")
            data[i][3]=4;
        else if(usersMainDataset[i].dependent=="0" || usersMainDataset[i].dependent=="1"|| usersMainDataset[i].dependent=="2" || usersMainDataset[i].dependent=="3")
            data[i][3]=atof(usersMainDataset[i].dependent.c_str());




        if(usersMainDataset[i].education=="Graduate")
            data[i][4]=1;
        else if(usersMainDataset[i].education=="Not Graduate")
            data[i][4]=0;
        else
            data[i][4]=missingData[4];


        if(usersMainDataset[i].employment=="Yes")
            data[i][5]=1;
        else if(usersMainDataset[i].employment=="No")
            data[i][5]=0;
        else
            data[i][5]=missingData[5];


        data[i][6]=atof(usersMainDataset[i].applicantIncome.c_str());
        data[i][7]=atof(usersMainDataset[i].coApplicantIncome.c_str());
        data[i][8]=atof(usersMainDataset[i].amount.c_str());
        data[i][9]=atof(usersMainDataset[i].loanTerm.c_str());
        if(usersMainDataset[i].credit_History=="0" || usersMainDataset[i].credit_History=="1")
            data[i][10]=atof(usersMainDataset[i].credit_History.c_str());
        else
            data[i][10]=missingData[10];


        if(usersMainDataset[i].area=="Urban"){
            data[i][11]=2;
            countArea[2]++;
        }
        else if(usersMainDataset[i].area=="Semiurban"){
            data[i][11]=1;
            countArea[1]++;
        }
        else if(usersMainDataset[i].area=="Rural"){
            data[i][11]=0;
            countArea[0]++;
        }

        if(usersMainDataset[i].status=="Y")
            data[i][12]=1;
        else
            data[i][12]=0;

    }


            int counts[5];

            for(i=0;i<5;i++)
                counts[i]=0;


            for(i=0;i<n/2;i++){
                counts[(int)data[i][3]]++;
            }



            int maxCount=counts[0],maxCountCatagory=0;
            for(i=1;i<5;i++){
                if(counts[i]>maxCount){
                    maxCount=counts[i];
                    maxCountCatagory=i;
                }
            }



            cout<<"Average dependent number: "<<maxCountCatagory<<endl;
        for(i=0;i<n;i++){
            if(usersMainDataset[i].dependent!="0" && usersMainDataset[i].dependent!="1" && usersMainDataset[i].dependent!="3" && usersMainDataset[i].dependent!="3+")
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
        cout<<"Max resident from: ";
        if(maxCountCatagory==0)
            cout<<"Rural area"<<endl;
        else if(maxCountCatagory==1)
            cout<<"Semi urbun area"<<endl;
        else
            cout<<"Urban area"<<endl;


        for(i=0;i<n;i++){
            if(usersMainDataset[i].area!="Urban" && usersMainDataset[i].area!="Semiurban" && usersMainDataset[i].area!="Rural")
                data[i][11]=maxCountArea;
        }



    float avgIncome=meanCalc(data,n,6);
    cout<<"Average applicant income: $"<<avgIncome<<endl;
    for(i=0;i<n;i++){
        if(data[i][6]==0)
            data[i][6]=avgIncome;
    }

    float avgCAIncome=meanCalc(data,n,7);
    cout<<"Average Co applicant income: $"<<avgCAIncome<<endl;
    for(i=0;i<n;i++){
        if(data[i][7]==0){
            data[i][7]=avgCAIncome;
        }
    }

    float avgLoan=meanCalc(data,n,8);
    cout<<"Average Loan Amount: $"<<avgLoan<<endl;
    for(i=0;i<n;i++){
        if(data[i][8]==0){
            data[i][8]=avgLoan;
        }
    }


    float avgLoanTerm=meanCalc(data,n,9);
    cout<<"Average Loan Term: "<<avgLoanTerm<<endl;
    for(i=0;i<n;i++){
        if(data[i][9]==0){
            data[i][9]=avgLoanTerm;
        }
    }




    //write on a file
    ofstream file(output);
    file<<n<<"\t"<<"12"<<endl;

    for(i=0;i<n;i++){
        for(j=0;j<13;j++)
            file<<setw(10)<<data[i][j]<<" ";
        file<<endl;
    }

    file.close();
}
