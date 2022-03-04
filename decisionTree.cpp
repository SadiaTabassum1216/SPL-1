#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include<cstring>
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

struct node{
float *dataset;
string category;
struct node *left;
struct node *right;
};

struct tree{
int size;
struct node **subTree;
};

void storeArray(float a[][13], float b[][13],int n) {
int i,j;
for(i=0;i<n;++i){
    for(j=0;j<13;j++)
        a[i][j] = b[i][j];
    }
}
// Create nodes
struct node *newNode(float dataset[][13], string category,int n)
{
  struct node *temp = (struct node *)malloc(sizeof(struct node));

  temp->left= temp->right=NULL;
//  storeArray(temp->dataset,dataset,n);
  temp->category=category;

  return temp;
}


int minimum(float a[],int n){
    int i;
    int index=1;
    float m=a[1];
    for(i=1;i<n;i++){
        if(a[i]<m){
            m=a[i];
            index=i;
        }
    }
    cout<<"\nMinimum entropy: "<<m<<endl;
return i;//the category number
}

int minEntropy(float a[],int n){
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
for(j=1;j<13;j++){
        sum=0;
    for(i=0;i<n;i++)
        sum=sum+data[i][j];

    mean[j]=sum/(float)n;
}
return mean;
}

float* entropyCalculation(int n,float data[][13]){
int i,j;
float mean[13],percentage[13];
float *entropy=new float[13];

//Mean
int sum;
for(j=0;j<13;j++){
        sum=0;
   // mean[i]=Mean(m,n,a,i);
    for(i=0;i<n;i++)
        sum=sum+data[i][j];

    mean[j]=sum/(float)n;
}
cout<<"\nMean:\n";
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
cout<<"Percentage:\n";
for(i=1;i<13;i++)
    cout<<percentage[i]<<" ";

//Entropy
for(i=1;i<13;i++){
        entropy[i]=-(percentage[i]*log2(percentage[i])+(1-percentage[i])*log2(1-percentage[i]));
    }

cout<<"\nEntropy(In function):\n";
for(i=1;i<13;i++)
    cout<<entropy[i]<<" ";

    int m=minimum(entropy,13);

    return entropy;
}

void print(int n,float a[][13]){
int i,j;
cout<<"ID Gender Married Dependents Education Employed A.Income CA.Income LoanAmount Term Credit_History Area Status\n";
for(i=0;i<n;i++){
    cout<<users[i].loan_ID<<"\t";
    for(j=1;j<13;j++){
        cout<<a[i][j]<<"\t";
    }
    cout<<"\n";
    }
}

// Function to swap
void swapNode(struct node **a, struct node **b)
{
  struct node *t = *a;
  *a = *b;
  *b = t;
}

void swapArray(float a[], float b[]) {
int i;
for(i=0;i<13;++i){
    float temp;
    temp = a[i];
    a[i] = b[i];
    b[i] = temp;
    }
}

void decisionTree(int n, float a[][13]){
    float *entropy=entropyCalculation(n,a);
    float *mean=meanCalculation(n,a);
    int minEntropyCategory=minimum(entropy,n);    //the category number to split
    float minEntropyValue=minEntropy(entropy,n);  //minimum entropy
    int i,j,k=0,l=0;

    if(abs(minEntropyValue)<=EPS){
            return;
    }

    vector<int> temp;
    float value;

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

    decisionTree(leftSize,leftDataset);
    decisionTree(rightSize,rightDataset);

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

    //print(n,data);

    float* entropy=entropyCalculation(n,data);
    cout<<"\nEntropy(in main):\n";
    for(i=1;i<13;i++)
    cout<<entropy[i]<<" ";

}

