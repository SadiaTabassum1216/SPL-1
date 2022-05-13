#include<bits/stdc++.h>
#include <iostream>
#include <string>

#define EPS 1.0e-9
#define INITIAL -10
#define ERROR 404
#define catNum 13

int column,n;

using namespace std;

struct node {
  float data[5000][13];
  float userNum;
  bool isLeaf;
  bool decision;
  int column;
}tree[5000];

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

int maxGainIndex(float a[],int n){
    int i;
    int index=1;
    float m=a[1];
    for(i=1;i<n;i++){
        if(a[i]>m){
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


float maxGain(float a[],int n){
    int i;
    float m=a[1];
    for(i=1;i<n;i++){
        if(a[i]>m){
            m=a[i];
        }
    }
return m;//max info gain
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
    entropy[j]=entropyValue(countLow,n);
    }


    cout<<"\n\nEntropy:\n";
    for(i=1;i<catNum-1;i++)
        cout<<entropy[i]<<" ";

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
                if(data[i][catNum-1]==1)
                    lowYes++;
                else
                    lowNo++;
            }
            else{
                countHigh++;
                if(data[i][catNum-1]==1)
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

void decisionTree(int n,float mean[catNum-1]){

    int i,j,k=0,l=0,counting;

    if(tree[treeIndex].isLeaf== true){
        return;
    }

    float *entropy=entropyCalculation(n,tree[treeIndex].data,mean);
    float *gain=informationGain(n,tree[treeIndex].data,mean);

    float minEntropyValue=minEntropy(entropy,catNum-1);  //minimum entropy
    int maxIndex=maxGainIndex(gain,catNum-1);   //max info gain
    float maxGainValue=maxGain(gain,catNum-1);  //index
    cout<<endl;
    cout<<"Max gain index: "<<maxIndex<<endl;
    cout<<"Max gain value: "<<maxGainValue<<endl;

    tree[treeIndex].column=maxIndex;


    //so that checked categories are ignored
    for(i=0;i<=top;i++){
        entropy[stackArray[i]]=ERROR;
    }

    push(maxIndex);

    //checks leaf and generates decision
    if(minEntropyValue<=EPS || minEntropyValue==ERROR || minEntropyValue!=minEntropyValue || n==1 || top>=(catNum-1)){
        tree[treeIndex].isLeaf= true;
        counting=0;
        for(i=0;i<n;i++){
            if(tree[treeIndex].data[i][catNum-1]==1)
                counting++;
        }

        if(counting>=(n-counting)){
            tree[2*treeIndex+1].decision= true; //yes
            tree[2*treeIndex+2].decision= false; //no

        }

        else{
            tree[2*treeIndex+1].decision= false; //no
            tree[2*treeIndex+2].decision= true; //yes
        }

        treeIndex=(treeIndex-1)/2;
        pop();
        return;

    }


    //splits the dataset
    int leftSize=0,rightSize=0;

    for(i=0;i<n;i++){
        if(tree[treeIndex].data[i][maxIndex]<mean[maxIndex])
            leftSize++;

        else
            rightSize++;

    }

    float leftDataset[leftSize][catNum],rightDataset[rightSize][catNum];


    for(i=0;i<n;i++){
        if(tree[treeIndex].data[i][maxIndex]<mean[maxIndex]){
            for(int j=0;j<catNum; j++){
                leftDataset[k][j]=tree[treeIndex].data[i][j];
            }
            k++;
        }
        else{
            for(int j=0;j<catNum; j++){
                rightDataset[l][j]=tree[treeIndex].data[i][j];
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

    for(i=0;i<leftSize;i++){
        for(j=0;j<13;j++){
            tree[2*treeIndex+1].data[i][j]=leftDataset[i][j];
        }
    }

    for(i=0;i<rightSize;i++){
        for(j=0;j<13;j++){
            tree[2*treeIndex+2].data[i][j]=rightDataset[i][j];
        }
    }

    tree[2*treeIndex+1].userNum=leftSize;
    tree[2*treeIndex+2].userNum=rightSize;

    treeIndex=2*treeIndex+1;
    decisionTree(leftSize,mean);

    treeIndex=2*treeIndex+2;
    decisionTree(rightSize,mean);

}


//main
int main()
{
    int i,j,column,row;

    freopen("output.txt", "r", stdin);
    cin>>n>>column;
    row=n;

    float dataSet[row][catNum];

    for(i=0;i<row;i++){
        for(j=0;j<=column;j++){
            cin>>dataSet[i][j];
            tree[0].data[i][j]=dataSet[i][j];
        }
    }


    cout<<"Total customer is: "<<n<<endl;
    tree[0].userNum=n;

   // print(n,data);
   float *mean=meanCalculation(n,dataSet);

    decisionTree(n,mean);


    return 0;
}
