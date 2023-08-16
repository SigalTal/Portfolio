/*********************************
 * Reviewer: Avigail
 * Author: Sigal Tal		
 * File: calculator.h
 * ******************************/

#include <string.h>/*strlen*/
#include <stdlib.h>/*strtod*/
#include <assert.h>
#include "calculator.h"
#include "stack.h"

#define NAN (0.0f / 0.0f)

enum state{OPERATORS=0,OPERANDS=1};

static char * HandleOperator(char* exp);
static char * HandleOperand(char* exp);
static char * HandleSpace(char* exp);
static char * HandleOpenParenth(char* exp);
static char * HandleCloseParenth(char* exp);
static void InitHandlers();
static double Subtraction(double *num1, double *num2);
static double Add(double *num1, double *num2);
static double Multiplication(double *num1, double *num2);
static double Division(double *num1, double *num2);
static void MathAction();


typedef char *(*func_ptr_t)(char* exp);
typedef double (*math_func_t)(double *num1, double *num2);

static int operator_level_g[128]={0};
static math_func_t meth_operators_g[128]={NULL};
static func_ptr_t handlers_g[128]={NULL};
stack_t *stack[2]={NULL};

double Calculate(const char *expression)
{ 
    size_t len = strlen(expression);
    double res=0;

    assert(expression);

    InitHandlers();

    stack[OPERATORS] = StackCreate(len,sizeof(char));
    if(!stack[OPERATORS])
    {
        return NAN;
    }
    
    stack[OPERANDS] = StackCreate(len,sizeof(double));
    if(!stack[OPERANDS])
    {
        StackDestroy(stack[OPERATORS]);
        return NAN;
    }

    while(*expression)
    {
        expression = handlers_g[(int)*expression]((char *)expression);
    }

    while(!StackIsEmpty(stack[OPERATORS]))
    {
        MathAction();
    }

    StackPeek(stack[OPERANDS],&res);
    StackDestroy(stack[OPERANDS]);
    StackDestroy(stack[OPERATORS]);

    return res; 
}

static void InitHandlers()
{
    handlers_g['0']=HandleOperand;
    handlers_g['1']=HandleOperand;
    handlers_g['2']=HandleOperand;
    handlers_g['3']=HandleOperand;
    handlers_g['4']=HandleOperand;
    handlers_g['5']=HandleOperand;
    handlers_g['6']=HandleOperand;
    handlers_g['7']=HandleOperand;
    handlers_g['8']=HandleOperand;
    handlers_g['9']=HandleOperand;
    handlers_g['+']=HandleOperator;
    handlers_g['-']=HandleOperator;
    handlers_g['*']=HandleOperator;
    handlers_g['/']=HandleOperator;
    handlers_g['(']=HandleOpenParenth;
    handlers_g[')']=HandleCloseParenth;
    handlers_g[' ']=HandleSpace;
    operator_level_g['(']=1;
    operator_level_g['+']=2;
    operator_level_g['-']=2;
    operator_level_g['*']=3;
    operator_level_g['/']=3;
    meth_operators_g['+']=Add;
    meth_operators_g['-']=Subtraction;
    meth_operators_g['*']=Multiplication;
    meth_operators_g['/']=Division;
}

static char *HandleOperand(char* exp)
{
    char *new_ptr=NULL;
    double num = strtod(exp,&new_ptr);
    StackPush(stack[OPERANDS],&num);

    return new_ptr;
}

static char *HandleOperator(char* exp)
{
    char peeked_operator=0;

    assert(exp);
    
    while(!StackIsEmpty(stack[OPERATORS]) && 
            (StackPeek(stack[OPERATORS],&peeked_operator),
            operator_level_g[(int)*exp]<=operator_level_g[(int)peeked_operator]))
    {
        MathAction();
    }

    StackPush(stack[OPERATORS],exp);

    return ++exp;
}

static char * HandleSpace(char* exp)
{
    return ++exp;
}

static char *HandleOpenParenth(char* exp)
{
    StackPush(stack[OPERATORS],exp);

    return ++exp;
}

static char *HandleCloseParenth(char* exp)
{
    char operator=0;
    StackPeek(stack[OPERATORS],&operator);
    while(operator!='(')
    {
        MathAction();
        StackPeek(stack[OPERATORS],&operator);
    }

    StackPop(stack[OPERATORS]);

    return ++exp;
}

static void MathAction()
{
    char peeked_operator=0;
    double peeked_number1=0;
    double peeked_number2=0;
    double result=0;

    StackPeek(stack[OPERATORS],&peeked_operator);
    
    StackPeek(stack[OPERANDS],&peeked_number1);
    StackPop(stack[OPERANDS]);
    
    StackPeek(stack[OPERANDS],&peeked_number2);
    StackPop(stack[OPERANDS]);
    
    result=meth_operators_g[(int)peeked_operator](&peeked_number1,&peeked_number2);
    
    StackPush(stack[OPERANDS],&result);
    StackPop(stack[OPERATORS]);
}

static double Subtraction(double *num1, double *num2)
{
    return *num2-*num1;
}
static double Add(double *num1, double *num2)
{
    return *num2+*num1;
}
static double Multiplication(double *num1, double *num2)
{
    return (*num2)*(*num1);
}
static double Division(double *num1, double *num2)
{
    return (*num2)/(*num1);
}

