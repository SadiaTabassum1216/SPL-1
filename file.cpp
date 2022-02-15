#include<bits/stdc++.h>
using namespace std;

struct user
{
    string loan_ID;
    string gender;
    bool married;
    int dependent;
    string education;
    string employment;
    int applicantIncome;
    int coApplicantIncome;
    int amount;
    int loanTerm;
    int credit_History;
    string area;
    bool status;
}users[1000];

void split(string str, char del){
      string temp = "";

      for(int i=0; i<(int)str.size(); i++){
        // If cur char is not del, then append it to the cur "word", otherwise
          // you have completed the word, print it, and start a new word.
         if(str[i] != del){
            temp += str[i];
        }
          else{
            cout << temp << " ";
              temp = "";
        }
    }

      cout << temp;
}
//main
int main()
{
    ifstream fp("Train Dataset.txt");
    int i=1,c;
    string line;
    getline(fp,line);

        while(getline(fp,line))
              {
            cout <<i<<" "<< line<<endl;
            i++;
              }

    fp.close();
}
