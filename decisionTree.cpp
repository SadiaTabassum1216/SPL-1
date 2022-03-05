#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include<vector>
using namespace std;

#define EPS 1.0e-9

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


//tree tracker array
int treeTrack[4095];
int treeIndex=0;

//stack
int top=-1, stackArray[12];
//for push in string
void push(int a)
{
    top++;
    stackArray[top]=a;
}

//for pop in string
int pop()
{
    int a;
    a=stackArray[top];
    top--;
    return a;
}

int minEntropyIndex(float a[],int n){
    int i;
    int index=1;
    float m=a[1];
    for(i=1;i<n;i++){
        if(a[i]<m){
            m=a[i];
            index=i;
        }
    }
  //  cout<<"\nMinimum entropy: "<<m<<endl;
return index;//the category number
}

float minEntropy(float a[],int n){
    int i;
    float m=a[1];
    for(i=1;i<n;i++){
        if(a[i]<m){
            m=a[i];
        }
    }
return m;//min entropy
}

float* meanCalculation(int n,float data[][13]){
float *mean=new float[13];
int sum,i,j;
for(j=1;j<12;j++){
        sum=0;
    for(i=0;i<n;i++)
        sum=sum+data[i][j];

    mean[j]=sum/(float)n;
}
return mean;
}

float* entropyCalculation(int n,float data[][13]){
int i,j;
float mean[12],percentage[12];
float *entropy=new float[12];

//Mean
int sum;
for(j=1;j<12;j++){
        sum=0;
    for(i=0;i<n;i++)
        sum=sum+data[i][j];

    mean[j]=sum/(float)n;
}
//cout<<"\nMean:\n";
//for(i=1;i<12;i++)
//    cout<<mean[i]<<" ";
//    cout<<endl;

//Percentage
int c;

for(j=1;j<12;j++){
        c=0;
    for(i=0;i<n;i++){
        if(data[i][j]<mean[j])
            c++;
    }
    percentage[j]=(float)c/(float)n;
}
//cout<<"Percentage:\n";
//for(i=1;i<12;i++)
//    cout<<percentage[i]<<" ";

//Entropy
for(i=1;i<12;i++){
        entropy[i]=-(percentage[i]*log2(percentage[i])+(1-percentage[i])*log2(1-percentage[i]));
    }

cout<<"\n\nEntropy:\n";
for(i=1;i<12;i++)
    cout<<entropy[i]<<" ";

    int m=minEntropyIndex(entropy,12);

    return entropy;
}

void print(int n,float a[][13]){
int i,j;
cout<<"ID Gender Married Dependents Education Employed A.Income CA.Income LoanAmount Term Credit_History Area Status\n";
for(i=0;i<n;i++){
    for(j=0;j<13;j++){
        cout<<a[i][j]<<"\t";
    }
    cout<<"\n";
    }
}

void decisionTree(int n, float a[][13]){
    int i,j,k=0,l=0,popped;
    float *entropy=entropyCalculation(n,a);
    for(i=top;i>=0;i--){
        entropy[stackArray[i]]=404;
    }

    float *mean=meanCalculation(n,a);
    int minEntropyCategory=minEntropyIndex(entropy,12);    //the category number to split
    float minEntropyValue=minEntropy(entropy,12);  //minimum entropy
    treeTrack[treeIndex]=minEntropyCategory;



    if(n<=1){
        treeTrack[2*treeIndex+1]=-1;    //yes
        treeTrack[2*treeIndex+2]=-2;    //no
        treeIndex=(treeIndex-1)/2;
        popped=pop();
        return;
    }

    if(minEntropyValue<=EPS || minEntropyValue!=minEntropyValue){
            treeTrack[2*treeIndex+1]=-1;    //yes
            treeTrack[2*treeIndex+2]=-2;    //no
            treeIndex=(treeIndex-1)/2;
            popped=pop();
            return;
    }

    if(minEntropyValue==404)
        return;

    push(minEntropyCategory);

    cout<<"\nMin entropy value: "<<minEntropyValue;
    cout<<"\nMin entropy category: "<<minEntropyCategory;
    cout<<"\nTree Index: "<<treeIndex;

    cout<<"\nTree Track:\n";
        for(i=0;i<30;i++){
        cout<<treeTrack[i]<<" ";
    }

    cout<<"\nStack: ";
    for(i=0;i<=top;i++){
        cout<<stackArray[i]<<" ";
    }




    if(treeTrack[treeIndex]!=-10){
      //  popped=pop();
    }

    int leftSize=0,rightSize=0;

    for(i=0;i<n;i++){
        if(a[i][minEntropyCategory]<mean[minEntropyCategory])
            leftSize++;

        else
            rightSize++;

    }
       float leftDataset[leftSize][13],rightDataset[rightSize][13];

    for(i=0;i<n;i++){
        if(a[i][minEntropyCategory]<mean[minEntropyCategory]){
             for(int j=0;j<13; j++){
                leftDataset[k][j]=a[i][j];
                }
                k++;
        }
        else{
           for(int j=0;j<13; j++){
                rightDataset[l][j]=a[i][j];
                }
            l++;
        }
    }
    cout<<"\nLeftSize: "<<leftSize<<"\nRight size: "<<rightSize<<endl;
    treeIndex=2*treeIndex+1;
    decisionTree(leftSize,leftDataset);

    treeIndex=2*treeIndex+2;
    decisionTree(rightSize,rightDataset);

}


//main
int main()
{

    //read train file
    ifstream fp("random.txt");
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
//            cout <<i+1<<"\t"<<users[i].loan_ID<<"\t"<<users[i].gender<<"\t"<<users[i].married<<"\t"
//            <<users[i].dependent<<"\t"<<users[i].education<<"\t"<<users[i].employment<<"\t"
//            <<users[i].applicantIncome<<"\t"<<users[i].coApplicantIncome<<"\t"
//            <<users[i].amount<<"\t"<<users[i].loanTerm<<"\t"
//            <<users[i].credit_History<< setw (20)<<users[i].area<< setw (10)<<users[i].status <<endl;
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

    for(i=0;i<4095;i++){
        treeTrack[i]=-10;
    }

   // print(n,data);
    decisionTree(n,data);

        cout<<"\nFinal Tree Track:\n";
        for(i=0;i<30;i++){
        cout<<"("<<i<<")"<<treeTrack[i]<<" ";
    }


return 0;
}
