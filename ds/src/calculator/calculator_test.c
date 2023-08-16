/*********************************
 * Reviewer: Avigail
 * Author: Sigal Tal		
 * File: calculator.h
 * ******************************/
#include <stdio.h>
#include "calculator.h"

int main()
{
    char *str="((10.3 + 12.5) * 3 + 4 / (7.2 - 4.6))";

    printf("res: %f\n",Calculate(str));
    
    return 0;
}


