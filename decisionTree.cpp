#include<bits/stdc++.h>
#include <iostream>
#include <string>

#define EPS 1.0e-9
#define INITIAL -10
#define ERROR 404
#define catNum 13

int column,n;

using namespace std;

//tree tracker array
int treeTrack[4095];
int treeIndex=0;

//stack
int top=-1, stackArray[catNum-1];

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

float* meanCalculation(int n,float data[][catNum]){
float *mean=new float[13];
int sum,i,j;
for(j=1;j<catNum-1;j++){
        sum=0;
    for(i=0;i<n;i++)
        sum=sum+data[i][j];

    mean[j]=sum/(float)n;
}
return mean;
}

float entropyValue(int num,int total)
{
    float percentage=(float)num/(float)total;
    float entropy=-(percentage*log2(percentage)+(1-percentage)*log2(1-percentage));
    return entropy;
}


float* entropyCalculation(int n,float data[][catNum], float mean[catNum-1]){
int i,j;
//float percentage[catNum-1];
float *entropy=new float[catNum-1];

//Percentage
int countLow,countHigh;

for(j=1;j<catNum-1;j++){
        countLow=0,countHigh=0;
    for(i=0;i<n;i++){
        if(data[i][j]<mean[j])
            countLow++;
        else
            countHigh++;


    }
//    percentage[j]=(float)countLow/(float)n;
//    entropy[j]=-(percentage[j]*log2(percentage[j])+(1-percentage[j])*log2(1-percentage[j]));
    entropy[j]=entropyValue(countLow,n);
}


cout<<"\n\nEntropy:\n";
for(i=1;i<catNum-1;i++)
    cout<<entropy[i]<<" ";

    int m=minEntropyIndex(entropy,catNum-1);

    return entropy;
}



float* informationGain(int n,float data[][catNum], float mean[catNum-1])
{
    float *gain=new float[catNum-1];

    int i,j,countLow,countHigh,lowYes,lowNo,highYes,highNo;

    for(j=1;j<catNum-1;j++){
        countLow=0,countHigh=0,lowYes=0,lowNo=0,highYes=0,highNo=0;
        for(i=0;i<n;i++){
            if(data[i][j]<mean[j]){
                countLow++;
                if(data[i][catNum]==1)
                    lowYes++;
                else
                    lowNo++;
                }
            else{
                countHigh++;
                if(data[i][catNum]==1)
                    highYes++;
                else
                    highNo++;
                }
            }
        gain[j]=entropyValue(countLow,n)-((countLow/n)*entropyValue(lowYes,countLow))-((countHigh/n)*entropyValue(highYes,countHigh));

        }

cout<<"\nGain:\n";
for(i=1;i<catNum-1;i++)
    cout<<gain[i]<<" ";

return gain;
}



void print(int n,float a[][catNum]){
    int i,j;
    cout<<"ID Gender Married Dependents Education Employed A.Income CA.Income LoanAmount Term Credit_History Area Status\n";
    for(i=0;i<n;i++){
        for(j=0;j<13;j++){
            cout<<a[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

void decisionTree(int n, float a[][catNum],float mean[catNum-1]){

    int i,j,k=0,l=0,counting;


    //checks if it is an already checked state
        if(treeTrack[treeIndex]!=INITIAL){
            if(treeIndex==0)
                treeIndex=2*treeIndex+2;
            else{
                treeIndex=(treeIndex-1)/2;
                pop();
                return;
            }
        }

    //calculates entropy here
    float *entropy=entropyCalculation(n,a,mean);
    float *gain=informationGain(n,a,mean);

    for(i=0;i<=top;i++){
        entropy[stackArray[i]]=ERROR;
    }

    int minEntropyCategory=minEntropyIndex(entropy,catNum-1);    //the category number to split
    float minEntropyValue=minEntropy(entropy,catNum-1);  //minimum entropy
    treeTrack[treeIndex]=minEntropyCategory;


    //prints everything
    cout<<"\nMin entropy value: "<<minEntropyValue;
    cout<<"\nMin entropy category: "<<minEntropyCategory;
    cout<<"\nTree Index: "<<treeIndex;

    cout<<"\nTree Track:\n\t";
    for(i=0;i<4095;i++){
        if(treeTrack[i]!=INITIAL)
            cout<<"("<<i<<")"<<treeTrack[i]<<"   ";
    }



    //checks leaf and generates decision
    if(minEntropyValue==0 || minEntropyValue==ERROR || minEntropyValue!=minEntropyValue || n==1 || top>(catNum-1)){
           counting=0;
           for(i=0;i<n;i++){
                if(a[i][catNum-1]==1)
                    counting++;
           }

           if(counting>=(n-counting)){
               treeTrack[2*treeIndex+1]=-1; //yes
               treeTrack[2*treeIndex+2]=-2; //no
           }

           else{
               treeTrack[2*treeIndex+1]=-2; //no
               treeTrack[2*treeIndex+2]=-1; //yes
           }

           treeIndex=(treeIndex-1)/2;
           pop();
           return;

    }


    //update stack and tree track array
    push(minEntropyCategory);
    treeTrack[treeIndex]=minEntropyCategory;


    //splits the dataset
    int leftSize=0,rightSize=0;

    for(i=0;i<n;i++){
        if(a[i][minEntropyCategory]<mean[minEntropyCategory])
            leftSize++;

        else
            rightSize++;

    }

    float leftDataset[leftSize][catNum],rightDataset[rightSize][catNum];

    for(i=0;i<n;i++){
        if(a[i][minEntropyCategory]<mean[minEntropyCategory]){
            for(int j=0;j<catNum; j++){
                leftDataset[k][j]=a[i][j];
            }
            k++;
        }
        else{
            for(int j=0;j<catNum; j++){
                rightDataset[l][j]=a[i][j];
            }
            l++;
        }
    }

    //print stack
    cout<<"\nStack: ";
    for(i=0;i<=top;i++){
        cout<<stackArray[i]<<" ";
    }
    cout<<"\nLeftSize: "<<leftSize<<"\nRight size: "<<rightSize<<endl;


    //recursion here
    treeIndex=2*treeIndex+1;
    decisionTree(leftSize,leftDataset,mean);

    //treeIndex=2*treeIndex+2;
    treeIndex++;
    decisionTree(rightSize,rightDataset,mean);


   // return;
}


//main
int main()
{
    int i,j,column,row;

    freopen("output.txt", "r", stdin);
    cin>>n>>column;
    row=n;

    float data[row][catNum];

    for(i=0;i<row;i++){
        for(j=0;j<=column;j++){
            cin>>data[i][j];
        }
    }


    cout<<"Total customer is: "<<n<<endl;


//    for(i=0;i<20;i++){
//        for(j=0;j<=column;j++){
//            cout<<setw(6)<<data[i][j];
//        }
//        cout<<endl;
//    }

    for(i=0;i<4095;i++){
        treeTrack[i]=INITIAL;
    }

   // print(n,data);
   float *mean=meanCalculation(n,data);

    decisionTree(n,data,mean);

        cout<<"\n\nFinal Tree Track:\n";
        for(i=0;i<4095;i++){
                if(treeTrack[i]!=INITIAL)
                    cout<<"("<<i<<")"<<treeTrack[i]<<"   ";
        }

return 0;
}
