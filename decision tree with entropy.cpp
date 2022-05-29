#include<bits/stdc++.h>

#define EPS 1.0e-3
#define ERROR 404
#define catNum 13

int column,n;

using namespace std;

//dataset
struct user{
    float information[catNum];
}users[4095];


struct tree{
    int start;
    int end;
    bool isLeaf;
    bool decision;
    int splittingColumn;
}tree[10000];


int itr=0,leaf=0;
float mean[catNum-1];

//stack
int top=-1, stackArray[11];

//for push in string
void push(int a)
{
    top++;
    stackArray[top]=a;
    cout<<"Pushed "<<a<<endl;
}

//for pop in string
int pop()
{
    int a;
    a=stackArray[top];
    top--;
    cout<<"popped "<<a<<endl;
    return a;
}

int minIndex(float a[],int n){
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

float entropyValue(int num,int total)
{
    if(num==0 || num==total)
        return 0;
    float percentage=(float)num/(float)total;

    float entropy=-(percentage*log2(percentage)+(1-percentage)*log2(1-percentage));
   // cout<<"\nentropy: "<<entropy<<endl;
    return entropy;
}




float* informationGain(int start,int end)
{
    float *entropy=new float[catNum-1];

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

//        cout<<"\nCount low: "<<countLow<<"\nCount high: "<<countHigh<<"\nlow yes: "<<lowYes
//            <<"\nlow no: "<<lowNo<<"\nhigh yes: "<<highYes<<"\nHIgh no: "<<highNo<<endl;

    entropy[j]=((float)countLow/(float)(end-start+1))*entropyValue(lowYes,countLow)+
                ((float)countHigh/(float)(end-start+1))*entropyValue(highYes,countHigh);
    }

//    cout<<"\nEntropy:\n";
//    for(i=1;i<catNum-1;i++)
//        cout<<entropy[i]<<" ";
//
//    cout<<"\nMean: ";
//    for(i=1;i<catNum-1;i++)
//        cout<<mean[i]<<" ";

    return entropy;
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
            //cout<<users[i].information[k]<<"  ";
        }
       // cout<<endl;
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
\
}

void TreeConstruct(int start,int finish,int index)
{
    itr++;
    cout<<endl<<"Iteration: "<<itr<<"   Index: "<<index<<endl;
    int i,counting;

//    if(tree[index].isLeaf==true){
//        pop();
//        return;
//    }

    cout<<"\nstart: "<<start<<endl;
    cout<<"end: "<<finish<<endl;


    if(start>=finish || finish==-1){
            tree[index].isLeaf=true;
            leaf++;
            cout<<"Leaf number: "<<leaf<<endl;
        if(users[start].information[catNum-1]==1){
            tree[index].decision= true; //yes
            cout<<boolalpha<<"Leaf "<<index<<": "<<tree[index].decision<<endl;
        }
        else{
            tree[index].decision= false; //no
            cout<<boolalpha<<"Leaf "<<index<<": "<<tree[index].decision<<endl;
        }
      //  pop();
        return;
    }

    float *gain=informationGain(start,finish);  //entropy basically

    //so that checked categories are ignored
    for(i=0;i<=top;i++){
        gain[stackArray[i]]=ERROR;
    }
    cout<<"\nentropy:\n";
    for(i=1;i<catNum-1;i++)
        cout<<gain[i]<<" ";


    float minGainValue=minEntropy(gain,catNum-1);  //max info gain
    int splitColumn=minIndex(gain,catNum-1);   //index

    cout<<"\nMin Entropy index: "<<splitColumn<<endl;
    cout<<"Min entropy value: "<<minGainValue<<endl;

    push(splitColumn);

    if(minGainValue<=EPS || top>=10){    //leaf
        tree[index].isLeaf= true;
        leaf++;
        cout<<"Leaf number: "<<leaf<<endl;
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

    cout<<"mid Index: "<<midpoint<<endl;

    if(start<=midpoint){
        TreeConstruct(start,midpoint,2*index+1);
    }


    if(finish>midpoint){
        TreeConstruct(midpoint+1,finish,2*index+2);
    }

        pop();
        return;

}


//main
int main()
{
    int i,j,column,row;

    freopen("output.txt", "r", stdin);
    cin>>n>>column;
    row=n;
    //n=40;

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

    TreeConstruct(0,n-1,0);

    cout<<"\nTotal leaf: "<<leaf<<endl;

//    for(i=0;i<n;i++){
//            cout<<i<<": ";
//        for(j=0;j<13;j++)
//            cout<<users[i].information[j]<<" ";
//        cout<<endl;
//    }

    return 0;
}
