/*************************************************************************/
/*                                                                       */
/* Copyright (c) 2015 Mario J. García Navarro, Luis Arturo Mendoza Reyes */
/*                                                                       */
/* File name: LastFactor.c                                               */
/*                                                                       */
/* Author(s):                                                            */
/*          Mario Jacob García Navarro, Luis Arturo Mendoza Reyes        */
/*                                                                       */
/* Purpose:                                                              */
/*          This program finds the last digit different from zero        */
/*          of an n! number without calculating it                       */
/*                                                                       */
/* References:                                                           */
/*          Jaime Salazár algorithm shown during a class of "Analysis    */
/*          and Design of Algorithms" course                             */
/*                                                                       */
/* Restrictions:                                                         */
/*          The only restrictions are attached only to computational     */
/*          calculation limits                                           */
/*                                                                       */
/* Revision history:                                                     */
/*                                                                       */
/*          Jan 23 12:37 2015 - File created                             */
/*                                                                       */
/*          Jan 24 11:56 2015 - Main method for calculating added        */
/*                                                                       */
/*          Jan 26 12:24 2015 - Code refactoring & optimized methods     */
/*                                                                       */
/* Error handling:                                                       */
/*          If the user gives a number less than 1, it is asked to       */
/*          enter a valid one                                            */
/* Notes:                                                                */
/*          This code presents a solution for the second assignment      */
/*                                                                       */
/*************************************************************************/

#include <stdio.h>                       /* Used for the printf function */


/*************************************************************************/
/*                                                                       */
/*  Function: InitializeList                                             */
/*                                                                       */
/*  Purpose: The function will be in charge to initialize an array with  */
/*           the values of the numbers from 1, to the number given by    */
/*           the user                                                    */
/*                                                                       */
/*  Parameters:                                                          */
/*            Input :   The address pointer to the list, and the size    */
/*                      of the array, which is the number given by the   */
/*                      user                                             */
/*                                                                       */
/*            Output:   An initial array with all the numbers needed to  */
/*                      calculate the factorial of the n number          */
/*                                                                       */
/*************************************************************************/
void InitializeList(int *list, int size){
    /* Just start by the last digit until we reach to zero */
    for (int i = size - 1; i >= 0; --i)
        list[i] = i + 1; /* Assign the number to the list */
}

/*************************************************************************/
/*                                                                       */
/*  Function: ReduceNumber                                               */
/*                                                                       */
/*  Purpose: This function returns the number of 2's or 5's (depending   */
/*           the case) which a single number inside the array gives      */
/*                                                                       */
/*  Parameters:                                                          */
/*            Input :   The address pointer to the list, the factor      */
/*                      we will be using to divide (2 or 5), an index    */
/*                      to indicate the single number on the list that   */
/*                      we are working with, and finally a counter which */
/*                      indicates the number of 2's or 5's (accordingly  */
/*                      to the factor) that we already have              */
/*                                                                       */
/*            Output:   The number of 2's or 5's (accordingly to the     */
/*                      factor) that we have already before plus the     */
/*                      ones given by the single number                  */
/*                                                                       */
/*************************************************************************/
int ReduceNumber(int factor, int *list, int i, int counter){
    /* This variable indicates if it is possible to divide the number by
    the factor and still being an integer */
    int stillDivide = 1;
    
    while (stillDivide) {
        /* If the number can still be divided by the factor, without leaving
         a decimal part then continue */
        if (list[i] % factor == 0) {
            /* Divide the single number in the array by the factor*/
            int residue = list[i] / factor;
            counter++; /* Indicate that a 2 or a 5 have been founded */
            list[i] = residue; /* Store the number divided by the factor 
                                onto the main array */
            
            /* If the residue is 1 means that the number can be divided
             no more, so just kill the process */
            if (residue == 1)
                stillDivide = 0;
        }else
            stillDivide = 0; /* If not, just finish the process */
    }
    
    /* When all the possible 2's or 5's for the single number are accumulated 
     return the new value */
    return counter;
}

/*************************************************************************/
/*                                                                       */
/*  Function: GetNumbers                                                 */
/*                                                                       */
/*  Purpose:  This function obtains the number of 2's and 5's that are   */
/*            needed to calculate the first factor for the final product */
/*                                                                       */
/*  Parameters:                                                          */
/*            Input :   The address pointer to the list, and the size    */
/*                      of the array, which is the number given by the   */
/*                      user                                             */
/*                                                                       */
/*            Output:   The power for the base 2 number                  */
/*                                                                       */
/*************************************************************************/
int GetNumbers(int *list, int size){
    /* The counters that stores the number of 2's and the number of 5's,
     respectively */
    int numberTwo = 0, numberFive = 0;
    
    /* For all the numbers stored in the array, do the following */
    for (int i = 1; i < size; i++) {
        
        /* If the number is divisible by 2, then get the number of 2's */
        if(list[i] % 2 == 0)
            numberTwo = ReduceNumber(2, list, i, numberTwo);
        
        /* If the number is divisible by 5, then get the number of 5's */
        if(list[i] % 5 == 0)
            numberFive = ReduceNumber(5, list, i, numberFive);
        
         /* If the number is still bigger than 9, do a MODULE 10 to have
         only small numbers stored on the array. In case that the number 
         is smaller than 10, just keep it that way on the array */
        if (list[i] > 9) {
            list[i] = list[i] % 10;
        }
    }
    
    /* DEBUG MODE: Print the number of 2's and the number of 5's */
    #ifdef DEBUG
        printf("Number Two's = %d\nNumber Five's = %d\n", numberTwo, numberFive);
    #endif
    
    return numberTwo - numberFive;
}

/*************************************************************************/
/*                                                                       */
/*  Function: ModTwoBase                                                 */
/*                                                                       */
/*  Purpose:  This function powers a base 2 into an n power and then,    */
/*            calculate the MOD 10 of the result, which is needed to     */
/*            find the first digit for the final product                 */
/*                                                                       */
/*  Parameters:                                                          */
/*            Input :   The power n                                      */
/*                                                                       */
/*            Output:   The first digit for the final product            */
/*                                                                       */
/*            Notes:    This method has been deprecated due to it's      */
/*                      incredible CPU usage and unifficiently use       */
/*                      of resources. Therefore, it was limited highly   */
/*                      by computational power. A new method has been    */
/*                      added to rip out all those issues                */
/*                                                                       */
/*************************************************************************/
int ModTwoBase(int n){
    /* The powered base 2 by n power. Begins in 1 because 2 at 0 = 1 */
    long poweredTwo = 1;
    
    /* We start at one because the value for 0 power have been already 
     assigned */
    for (int i = 1; i <= n; i++)
        poweredTwo *= 2; /* The resulting number is just composed 
                          by multiplyng the 2 base n times */
    
    /* DEBUG Mode: Print the final resulting number */
    #ifdef DEBUG
        printf("Powered Number: %ld\n",poweredTwo);
    #endif
    
    /* Return only the final digit, not the resulting powered number */
    return poweredTwo % 10;
}

/*************************************************************************/
/*                                                                       */
/*  Function: FirstDigit                                                 */
/*                                                                       */
/*  Purpose:  It finds the first digit for the final product in an       */
/*            efficient way using mathematical previous analyzed         */
/*            patterns. Basically, assigns an early defined number to    */
/*            to a variable to know the final result for the second      */
/*            digit without the need to calculate the powered number     */
/*                                                                       */
/*  Parameters:                                                          */
/*            Input :   The power n                                      */
/*                                                                       */
/*            Output:   The second digit for the final product           */
/*                                                                       */
/*************************************************************************/
int FirstDigit(int power){
    /* The pattern previously observed followed the structure stored on
     the array */
    int pattern[] = {2, 4, 8, 6};
    
    /* The index will reset the assignation numbers */
    int index = 0, firstDigit = 0;
    
    /* A pathway through all the numbers will be done, this is the main 
     process */
    for (int i = 1; i <= power; i++) {
        /* The pattern number is assigned currently to the first digit */
        firstDigit = pattern[index];
        
        /* The index increases by one, discarding the overflow event 
         through a module 4 */
        index = (index + 1) % 4;
    }
    
    /* DEBUG Mode: Print the first digit */
    #ifdef DEBUG
        printf("First Digit: %d\n",firstDigit);
    #endif
    
    /* The last number stored through the pattern will have the actual
     second digit */
    return firstDigit;
}

/*************************************************************************/
/*                                                                       */
/*  Function: SecondDigit                                                */
/*                                                                       */
/*  Purpose:  It computates all the process which is required to find    */
/*            the second digit for the final product                     */
/*                                                                       */
/*  Parameters:                                                          */
/*            Input :   The address pointer to the list, and the size    */
/*                      of the array, which is the number given by the   */
/*                      user                                             */
/*                                                                       */
/*            Output:   The second digit for the final product           */
/*                                                                       */
/*************************************************************************/
int SecondDigit(int *list, int size){
    /* Start by the second number, due to the fact that the first one will
     always be equals to 1 and the result will be the same */
    for (int i = 1; i < size; i++)
        list[i] = (list[i - 1] * list[i]) % 10; /* Multiply the current number
                                                 with the previous one, then
                                                 get mod 10 and store it in 
                                                 the current position */
    
    /* DEBUG Mode: Print the second digit needed for the product */
    #ifdef DEBUG
        printf("Second Digit: %d\n",list[size - 1]);
    #endif
    
    /* The last position will have the second digit we need */
    return list[size - 1];
}

int main(int argc, const char * argv[])
{
    int n = 0; /* It will store the number given by the user */
    int firstDigit, secondDigit; /* The variables that will store the digits
                                  needed for the final product */
    int isNotCorrect = 1;    /* Error handling variable */
    
    /* If the number given by the user is not valid, keep asking
     for one that it is */
    while (isNotCorrect) {
        printf("Ingresa el número n: ");
        scanf("%d",&n);
        
        /* The number is not valid if it is negative */
        if (n < 0)
            printf("El número no es válido. Vuelve a intentarlo.\n\n");
        else
            isNotCorrect = 0;
    }
    
    /* If the number is bigger than zero, the follow the normal process */
    if (n > 0) {
        int list[n]; /* Set an array with size of 'n'*/
        InitializeList(list, n); /* Initialize the array with numbers
                              need by the factorial */
    
        /* Get the number of n power for the base 2 */
        firstDigit = GetNumbers(list, n);
    
        /* Get the first digit */
        firstDigit = FirstDigit(firstDigit);
    
        /* Get the second digit */
        secondDigit = SecondDigit(list, n);
    
        /* Print the final result which is given by the product, then MOD 10 */
        printf("\nEl último digito diferente de 0 del factorial de %d es: %d\n",n, (firstDigit * secondDigit) % 10);
        
    } else
        /* If not, just by mathematical definition (0! = 1), print 1 */
        printf("\nEl último digito diferente de 0 del factorial de 0 es: 1\n");
    
        /* Succesful return */
        return 0;
}

