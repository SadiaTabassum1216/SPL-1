#include "input.h"
#include "regression.h"
#include "kFoldValidation.h"
#include "form.h"

int main()
{
    int i;
    cout<<"\t\t**LOAN APPROVAL ESTIMATOR**"<<endl;
    cout<<"\n\t***One variate analysis of the dataset***\n"<<endl;
    datasetCreator("Train-Dataset.txt","output.txt");

    cout<<"\n\n\t\t***Validation***\n\n";
    cout<<"Multi variate regression:"<<endl;
    kFoldValidation("output.txt");

    float *regressionOutput=regressionFunc("output.txt");
    formFillup(regressionOutput,"output.txt");

}
