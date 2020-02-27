#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
 
 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
 
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2
 
 
typedef int Status;
typedef int Boolean;
typedef int SElemType;
 
 
 
typedef struct SqStack
{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
 
Status InitStack(SqStack *S)
{
    (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!(*S).base)
        return (OVERFLOW);
    (*S).top=(*S).base;
    (*S).stacksize=STACK_INIT_SIZE;
    return OK;
}
 
 
 
Status GetTop(SqStack S,SElemType *e)
{
    if(S.top>S.base)
    {
        *e=*(S.top-1);
        return OK;
    }
    else
        return ERROR;
}
 
Status Push(SqStack *S,SElemType e)
{
    if((*S).top-(*S).base>=(*S).stacksize)
    {
        (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!(*S).base)
            return(OVERFLOW);
        (*S).top=(*S).base+(*S).stacksize;
        (*S).stacksize+=STACKINCREMENT;
    }
    *((*S).top)++=e;
    return OK;
}
 
Status Pop(SqStack *S,SElemType *e)
{
    if((*S).top==(*S).base)
        return ERROR;
    *e=*--(*S).top;
    return OK;
}
 
 
SElemType Precede(SElemType t1,SElemType t2)
{
    SElemType f;
    switch(t2)
    {
    case '+':
    case '-':if(t1=='('||t1=='=')
                 f='<';
             else
                 f='>';
        break;
    case '*':
    case '/':if(t1=='*'||t1=='/'||t1==')')
                 f='>';
             else
                 f='<';
        break;
    case '(':if(t1==')')
             {
                 printf("ERROR1\n");
                 return(ERROR);
             }
             else
                 f='<';
        break;
    case ')':switch(t1)
             {
    case '(':f='=';
        break;
    case '=':printf("ERROR2\n");
        return(ERROR);
    default: f='>';
             }
             break;
    case '=':switch(t1)
             {
    case '=':f='=';
        break;
    case '(':printf("ERROR2\n");
        return(ERROR);
    default: f='>';
             }
    }
    return f;
}
 
Status In(SElemType c)
{
    switch(c)
    {
    case'+':
    case'-':
    case'*':
    case'/':
    case'(':
    case')':
    case'=':return TRUE;
    default:return FALSE;
    }
}
SElemType Operate(SElemType a,SElemType theta,SElemType b)
{
    SElemType c;
    switch(theta)
    {
    case'+':c=a+b;
        break;
    case'-':c=a-b;
        break;
    case'*':c=a*b;
        break;
    case'/':c=a/b;
    }
    return c;
}
SElemType Evaluateexpression_r()
{
    SqStack OPTR,OPND;
    SElemType a,b,d,x,theta;
    char c;
    char z[10];
    int i;
    InitStack(&OPTR);
    Push(&OPTR,'=');
    InitStack(&OPND);
    c=getchar();
    GetTop(OPTR,&x);
    while(c!='='||x!='=')
    {
        if(In(c))
            switch(Precede(x,c))
        {
            case'<':Push(&OPTR,c);
                c=getchar();
                break;
            case'=':Pop(&OPTR,&x);
                c=getchar();
                break;
            case'>':Pop(&OPTR,&theta);
                Pop(&OPND,&b);
                Pop(&OPND,&a);
                Push(&OPND,Operate(a,theta,b));
        }
        else if(c>='0'&&c<='9')
        {
            i=0;
            do
            {
                z[i]=c;
                i++;
                c=getchar();
            }while(c>='0'&&c<='9');
            z[i]=0;
            d=atoi(z);
            Push(&OPND,d);
        }
        else
        {
            printf("ERROR3\n");
            return(ERROR);
        }
        GetTop(OPTR,&x);
    }
    GetTop(OPND,&x);
    return x;
}
 
void main()
{
    printf("请输入算术表达式,负数要用(0-正数)表示,并以=结束\n");
    printf("%d\n",Evaluateexpression_r());
}
