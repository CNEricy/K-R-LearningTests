/**
 * 变量使用功能: 变量不区分大小写
 * 1.使用STO命令给变量赋值,例如 1 2 + A STO //A=3
 * 2.使用RCL命令查询变量值(变量默认值为0),例如:A RCL  //output: 3
 * 3.使用'+','-','*','/'对变量进行算数运算, 例如: A B + //output: 3
 *
 * 主要思路:
 * 主要难点是将变量用于简单算术运算,因此考虑一下方式解决该问题:
 *  1.新增宏定义用于判断变量
 *  2.检测到数字或变量时向状态(变量/数字)栈记录,该步骤是为了记录变量与数字出现的先后顺序
 *  3.检测变量的同时向变量栈记录变量出现的先后顺序
 *  4.将检测到'+','-','*','/'算术运算符时:
 *      4.1:先从状态栈中取出顶上两个状态
 *      4.2:若判断为变量,则变量栈中弹出变量,否则弹出数字
 *      4.3:计算结果
 */

#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define METHOD '1' /* signal that a method maybe was used */
#define VARIABLE '2'
#define PUNCTUATION '3'
#define ISVAR -1
#define ISNUM 1


int getop(char []);

void push(double);

double pop(void);

void showTop();

void copyTop();

void swapTops();

void clearStack();

void judgeMethod(char []);

void pushVariables(char);
char popVariables();

void pushStatus(int);
int popStatus();


double storage[27]; //a(A)-z(Z),latest value
//int var = -1;
int commandStatus;

/* reverse Polish calculator */

int main(void)
{
    int type;
    double op1, op2;
    char s[MAXOP];

    commandStatus = 1;
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                pushStatus(ISNUM);
                break;
            case METHOD:
                judgeMethod(s);
                break;
            case VARIABLE:
                pushVariables(s[0]);
                pushStatus(ISVAR);
                break;
            case '+':
                op2 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                push(op1 + op2);
                break;
            case '*':
                op2 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                push(op1 * op2);
                break;
            case '-':
                op2 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                push(op1 - op2);
                break;
            case '/':
                op2 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                if (op2 != 0.0)
                    push(op1 / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                if (op2 == 0)
                    printf("error: zero divisor\n");
                else {
                    op1 = popStatus() == -1 ? storage[toupper(popVariables())-'A'] : pop();
                    double val = op1 - (int) (op1 / op2) * op2;
                    if (op2 * val < 0)  //用'/'可能会遇到val为0的情况
                        val = -val; //op2与val符号相反,更改val符号
                    push(val);
                }
                break;
            case '@':
                showTop();
                commandStatus = -1;
                break;
            case '#':
                copyTop();
                commandStatus = -1;
                break;
            case '$':
                swapTops();
                commandStatus = -1;
                break;
            case '^':
                clearStack();
                commandStatus = -1;
                break;
            case '\n':
                if (commandStatus == 1) {
                    storage[26] = pop();
                    printf("\t%.8g\n", storage[26]);
                }
                commandStatus = 1;
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

void judgeMethod(char s[])
{
    if (!strcmp(s, "sin"))
        push(sin(pop()));
    else if (!strcmp(s, "cos"))
        push(cos(pop()));
    else if (!strcmp(s, "exp"))
        push(exp(pop()));
    else if (!strcmp(s, "pow")) {
        double op2 = pop();
        double op1 = pop();
        if ((op1 == 0 && op2 <= 0) || (op1 < 0 && !isdigit(op2)))
            printf("error: domain error\n");
        else
            push(pow(op1, op2));
    } else if (!strcmp(s, "STO")) {
        storage[toupper(popVariables())-'A'] = pop();
        popStatus();
        commandStatus = -1;
    } else if (!strcmp(s, "RCL")) {
        printf("\t%.8g\n", storage[toupper(popVariables()) - 'A']);
        popStatus();
        commandStatus = -1;
    } else if (!strcmp(s, "MR")) {
        storage[26] = pop();
    } else
        printf("error: unknown command %s\n", s);
}

#define MAXVAL  100 /* maximum depth of val stack */
#define MAXLETTER 26

int sp = 0; /* next free stack position */
int va = 0;
int st = 0;
double val[MAXVAL]; /* value stack */
char variables[MAXVAL];
int status[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void pushVariables(char v)
{
    if (va < MAXVAL)
        variables[va++] = v;
    else
        printf("error: variable stack full, can't push %c\n", v);
}

char popVariables()
{
    if (va > 0)
        return variables[--va];
    else {
        printf("error: variable stack empty\n");
        return 'a';
    }
}

void pushStatus(int s)
{
    if (st < MAXVAL)
        status[st++] = s;
    else
        printf("error: status stack full, can't push %d\n", s);
}

int popStatus()
{
    if (st > 0)
        return status[--st];
    else {
        printf("error: status stack empty\n");
        return 0;
    }
}

void showTop()
{
    if (sp > 0)
        printf("top value of stack is %.8g\n", val[sp - 1]);
    else
        printf("error: stack empty\n");
}

void copyTop()
{
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("error: stack empty\n");
}

void swapTops()
{
    if (sp < 2)
        printf("error: stack has not enough element");
    if (sp > 2) {
        double op2 = pop();
        double op1 = pop();
        push(op2);
        push(op1);
    }
}

void clearStack()
{
    val[0] = '\0';
    sp = 0;
}

#include <ctype.h>

int getch(void);

void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t');

    s[1] = '\0';
    i = 0;

    if (!isalpha(c) && !isdigit(c) && c != '-' && c != '.') return c;
    if (isalpha(c)) {  //检测是字母变量还是方法
        while (isalpha(s[++i] = c = getch())); //空白符将跳出循环
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        if (i == 1) return VARIABLE;
        return METHOD;
    }
    if (c == '-') s[++i] = c = getch();
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    if (i == 1 && ispunct(s[0])) return s[0];
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}