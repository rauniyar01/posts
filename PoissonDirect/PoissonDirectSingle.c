#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* time */
#include <math.h>

//declare functions
double funUniformSingle();             //generate uniform random variables on (0,1)
int funPoissonSingle(double lambda); //generate Poisson variables with parameter (ie mean) lambda

//START Main
int main()
{
    time_t s; //use CPU time for seed
    //intializes random number generator
    srand((unsigned)time(&s));

    double lambda = 8.7; //lambda is the Poisson parameter (that is, it's mean)

    int numbSim = 100;

    //START Collect statistists on Poisson variables
    //initialize statistics
    int numbPoissonTemp;
    double sumPoisson = 0;
    double sumPoissonSquared = 0;

    //loop through for each random variable
    for (int i = 0; i < numbSim; i++)
    {
        //generate a single poisson variable
        numbPoissonTemp = funPoissonSingle(lambda);

        //total sum of variables
        sumPoisson += numbPoissonTemp;
        //total sum of squared variables
        sumPoissonSquared += pow(numbPoissonTemp, 2);

        if (i < 5)
        {
            //print the first 5 numbers
            printf("One of the Poisson variables has the value %d\n", numbPoissonTemp);
        }
    }

    //calculate statistics
    double meanPoisson = sumPoisson / ((double)numbSim);                             //need to cast before doing divisions
    double varPoisson = sumPoissonSquared / ((double)numbSim) - pow(meanPoisson, 2); //need to cast before doing divisions
    printf("The average of the Poisson variables is %f\n", meanPoisson);
    printf("The variance of the Poisson variables is %f\n", varPoisson);
    print("For Poisson random variables, the mean and variance will more agree as the number of simuations increases.");

    //END Collect statistists on Poisson variables

    return (0);
}
//END Main

//START Function definitions
//Poisson function -- returns a single Poisson random variable
int funPoissonSingle(double lambda)
{
    double randExpTemp; //exponential variable
    double randUni;
    double sum_exp; //sum of exponential variable

    //initialize variables
    int randPoisson = -1; //Poisson variable
    sum_exp = 0;          //sum of exponential variable s
    do
    {
        randUni = funUniformSingle();                        //generate uniform variable
        randExpTemp = (-1 / lambda) * log(randUni); //generate exponential variable
        sum_exp = sum_exp + randExpTemp;            //add exponential variable to sum
        randPoisson++;                              //increase Poisson variable

    } while (sum_exp < 1); //stop loop if sum exceeds one
    return randPoisson;
}

//Uniform function -- returns a single standard uniform random variables
double funUniformSingle()
{
    double randUni;
    randUni = (double)rand() / (double)((unsigned)RAND_MAX + 1); //generate random variables on (0,1)
    return randUni;
}

//END  Function definitions