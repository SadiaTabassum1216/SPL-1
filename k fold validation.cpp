#include<bits/stdc++.h>
#include "test.h"
#include "regression.h"
#define catNum 13
#define k 5


using namespace std;

int n;

//dataset
struct user{
    float information[catNum];
}users[5000],train[5000],test[1000];

void shuffle(){
    int i,j;
    struct user temp;
    srand(time(0));
    for (i=0;i<n;i++) {
        j=rand()%n;
        temp=users[i];
        users[i]=users[j];
        users[j]=temp;
    }
}

void printFolderData(struct user *client, int size)
{
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<13;j++){
            cout<<client[i].information[j]<<"  ";
        }
        cout<<endl;
    }
}

using namespace std;

//main
int main()

//int kFoldValidation(string input)//total file
{
    int i,j,l,m,itr,itr2,row,column,n;
    string input="bleh.txt";

    {
     ifstream cin(input);
        cin>>row>>column;
        n=row;
    //n=15;

        for(i=0;i<row;i++){
            for(j=0;j<=column;j++){
                cin>>users[i].information[j];
            }
        }
    }


    cout<<"Total customer is: "<<n<<endl;
    cout<<"Number of groups(k value): "<<k<<endl;

//    cout<<"Before shuffle: "<<endl;
//    printFolderData(users,n);

    shuffle();

//    cout<<"After shuffle: "<<endl;
//    printFolderData(users,n);

    int userPerGroup=n/k;
    cout<<"User per group: "<<userPerGroup<<endl;
    int start=0,end=-1;

    for(i=0;i<k;i++){
        start=end+1;
        end=start+userPerGroup-1;
        cout<<"\nGroup: "<<i+1<<"\tStart: "<<start<<"\tEnd: "<<end<<endl;
       for(l=0;l<start;l++){
            for(j=0;j<=column;j++){
                train[l].information[j]=users[l].information[j];
            }
        }
        for(l=start,m=0;l<=end;l++,m++){
            for(j=0;j<=column;j++){
                test[m].information[j]=users[l].information[j];
            }
        }
        for(l=end+1,m=start;l<n;l++,m++){
            for(j=0;j<=column;j++){
                train[m].information[j]=users[l].information[j];
            }
        }

        //write a train file
        {ofstream file("train.txt");
        file<<n-userPerGroup<<"\t"<<"12"<<endl;

        for(itr=0;itr<(n-userPerGroup);itr++){
            for(itr2=0;itr2<13;itr2++)
                file<<setw(10)<<train[itr].information[itr2];
            file<<endl;
        }
        file.close();
        }

        float *regressionOutput=regression("train.txt");

        //write a test file
       {

        ofstream file2("test.txt");
        file2<<userPerGroup<<"\t"<<"12"<<endl;

        for(itr=0;itr<userPerGroup;itr++){
            for(itr2=0;itr2<13;itr2++)
                file2<<setw(10)<<test[itr].information[itr2];
            file2<<endl;
        }
        file2.close();
       }

        float rate=validation(regressionOutput,"test.txt");
        cout<<"\nRate of fold "<<i+1<<" is: "<<rate<<"%"<<endl;


//        cout<<"Train dataset: "<<endl;
//        printFolderData(train,n-userPerGroup);
//        cout<<"Test dataset: "<<endl;
//        printFolderData(test,userPerGroup);
//        cout<<endl;

    }

    return 0;
}
