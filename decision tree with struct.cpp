#include<bits/stdc++.h>

#define EPS 1.0e-3
#define ERROR -404
#define catNum 13

int column,n;

using namespace std;

//dataset
struct user{
    float information[catNum];
}users[5000];


struct tree{
    int start;
    int end;
    bool isLeaf;
    bool decision;
    int splittingColumn;
}tree[9000];


int itr=0,leaf=0;
float mean[catNum-1];

//stack
int top=-1, stackArray[11];

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
    float m=-1;
    for(i=1;i<n;i++){
        if(a[i]>m){
            m=a[i];
            index=i;
        }
    }
return index;//the category number
}


float maxGain(float a[],int n){
    int i;
    float m=-1;
    for(i=1;i<n;i++){
        if(a[i]>m){
            m=a[i];
        }
    }
return m;//max info gain
}

void meanCalculation(){
    int sum,i,j;
    for(j=1;j<catNum-1;j++){
        sum=0;
        for(i=0;i<n;i++)
            sum=sum+users[i].information[j];

        mean[j]=sum/(float)n;
    }
    return;
}
//
//float entropyValue(int start,int end)
//{
//
//    int i,j,countLow,countHigh,lowYes,lowNo,highYes,highNo;
//    for(j=1;j<catNum-1;j++){
//        countLow=0,countHigh=0,lowYes=0,lowNo=0,highYes=0,highNo=0;
//        for(i=start;i<end;i++){
//            if(users[i].information[j]<mean[j]){
//                countLow++;
//                if(users[i].information[12]==1)
//                    lowYes++;
//                else
//                    lowNo++;
//            }
//            else{
//                countHigh++;
//                if(users[i].information[12]==1)
//                    highYes++;
//                else
//                    highNo++;
//            }
//        }
//
//    int countYes=lowYes+highYes;
//    int countNo=lowNo+highNo;
//
//    float percentage=(float)num/(float)total;
//    if(num==0 || num==total)
//        return 0;
//    float entropy=-((countLow/(end-start+1))*(-lowYes/countLow)*log2(lowYes/countLow))
//   // float entropy=-(percentage*log2(percentage)+(1-percentage)*log2(1-percentage));
//    return entropy;
//    }
//}

float entropyValue(int num,int total)
{
    float percentage=(float)num/(float)total;
    if(num==0 || num==total)
        return 0;
    float entropy=-(percentage*log2(percentage)+(1-percentage)*log2(1-percentage));
    return entropy;
}

float* informationGain(int start,int end)
{
    float *gain=new float[catNum-1];

    int i,j,countLow,countHigh,lowYes,lowNo,highYes,highNo;

    for(j=1;j<catNum-1;j++){
        countLow=0,countHigh=0,lowYes=0,lowNo=0,highYes=0,highNo=0;
        for(i=start;i<=end;i++){
            if(users[i].information[j]<mean[j]){
                countLow++;
                if(users[i].information[12]==1)
                    lowYes++;
                else
                    lowNo++;
            }
            else{
                countHigh++;
                if(users[i].information[12]==1)
                    highYes++;
                else
                    highNo++;
            }
        }

        gain[j]=entropyValue(countLow,(end-start+1))-(((float)countLow/(float)(end-start+1))*entropyValue(lowYes,countLow))-
        (((float)countHigh/(float)(end-start+1))*entropyValue(highYes,countHigh));
    }

    cout<<"\nGain:\n";
    for(i=1;i<catNum-1;i++)
        cout<<gain[i]<<" ";

    return gain;
}

int split(int start,int end, int splitColumn)
{
    int beforeIndex=start;
    int afterIndex=end;
    int i,j,k;

    float threshhold=mean[splitColumn];
    cout<<"\nThreshhold: "<<threshhold<<endl;

    struct user copyDataset[end-start+1]; //temporary

    for(i=start,j=0;i<=end;i++,j++){        //.......................
        copyDataset[j]=users[i];
        for(k=0;k<=12;k++){
            cout<<users[i].information[k]<<"  ";
        }
        cout<<endl;
    }

    //partitioning
	for (i=start,j=0;i<end;i++,j++){
       // cout<<copyDataset[j].information[splitColumn]<<endl;
		if(copyDataset[j].information[splitColumn]<threshhold){
			users[beforeIndex]=copyDataset[j];
			beforeIndex++;
		}
		else{
			users[afterIndex]=copyDataset[j];
			afterIndex--;
		}
	}

	if(copyDataset[j].information[splitColumn]<threshhold){
        users[beforeIndex]=copyDataset[j];
        return beforeIndex;
	}
	else
    {
        users[afterIndex]=copyDataset[j];
        return beforeIndex-1;
    }

	//cout<<"\nBefore: "<<beforeIndex<<"   After: "<<afterIndex<<endl;
	//delete[] copyDataset;

}

void TreeConstruct(int start,int finish,int index)
{
    itr++;
    cout<<endl<<"Iteration: "<<itr<<endl;
    int i,counting;

//    if(tree[index].isLeaf==true){
//        pop();
//        return;
//    }

    if(start>=finish || finish==-1){
            tree[index].isLeaf=true;
            leaf++;
        if(users[start].information[catNum-1]==1){
            tree[index].decision= true; //yes
            cout<<boolalpha<<"Leaf "<<index<<": "<<tree[index].decision<<endl;
        }
        else{
            tree[index].decision= false; //no
            cout<<boolalpha<<"Leaf "<<index<<": "<<tree[index].decision<<endl;
        }
        pop();
        return;
    }

    float *gain=informationGain(start,finish);

    //so that checked categories are ignored
    for(i=0;i<=top;i++){
        gain[stackArray[i]]=ERROR;
    }
    cout<<"\nGain:\n";
    for(i=1;i<catNum-1;i++)
        cout<<gain[i]<<" ";


    float maxGainValue=maxGain(gain,catNum-1);  //max info gain
    int splitColumn=maxGainIndex(gain,catNum-1);   //index

    cout<<"\nMax gain index: "<<splitColumn<<endl;
    cout<<"Max gain value: "<<maxGainValue<<endl;

    push(splitColumn);

    if(maxGainValue>=(1-EPS) || top>=11){    //leaf
        tree[index].isLeaf= true;
        leaf++;
        counting=0;

        for(i=start;i<finish;i++){
            if(users[i].information[12]==1)
                counting++;
        }

        if(counting>=(finish-start-counting+1)){
            tree[index].decision= true; //yes
            cout<<boolalpha<<"Leaf "<<index<<": "<<tree[index].decision<<endl;
        }
        else{
            tree[index].decision= false; //no
            cout<<boolalpha<<"Leaf "<<index<<": "<<tree[index].decision<<endl;
        }

        pop();
        return;
    }

    //decision tree construct
    tree[index].start=start;
    tree[index].end=finish;
    tree[index].splittingColumn=splitColumn;
    tree[index].isLeaf=false;


    //print stack
    cout<<"\nStack: ";
    for(i=0;i<=top;i++){
        cout<<stackArray[i]<<" ";
    }

    int midpoint=split(start,finish,splitColumn);
    cout<<"\nstart: "<<start<<endl;
    cout<<"end: "<<finish<<endl;
    cout<<"mid Index: "<<midpoint<<endl;



    TreeConstruct(start,midpoint,2*index+1);
    TreeConstruct(midpoint+1,finish,2*index+2);
}


//main
int main()
{
    int i,j,column,row;

    freopen("bleh.txt", "r", stdin);
    cin>>n>>column;
    row=n;
    n=10;

    float dataSet[row][catNum];

    for(i=0;i<row;i++){
        for(j=0;j<=column;j++){
            cin>>users[i].information[j];
            dataSet[i][j]=users[i].information[j];
        }
    }

    cout<<"Total customer is: "<<n<<endl;

    meanCalculation();

    cout<<"Mean: ";
    for(i=1;i<12;i++){
        cout<<mean[i]<<"  ";
    }
    cout<<endl;

    TreeConstruct(0,9,0);

    cout<<"\nTotal leaf: "<<leaf<<endl;

    return 0;
}
