/**
 * 主要思路:
 * 1.此处做了简化,即在getline()结束时强行给数组加'\n',这样当出现极端情况(已经到数组末尾但是某个类型未结束)不受制于以下情况:
 *  1).若再进行一次getline(),则getop函数的参数要变成为全局变量
 *  2).即使不进行getline(),在每一次while()时都需要考虑是否会越界,且到达数组末尾时需要结束getop()
 *
 * 2.因为getline()是将所有输入都读取到了数组中,因此所有类型都存在了数组中,因此使用lp来记录数组下一个读取到的位置,下次调用getop()时可以继续从lp位置读取,当lp为0时则需要读取下一行
 * 3.相对于之前使用getch(),ungetch()
 *  1)只需在getline()返回的数量为0时返回EOF即可,其他时刻无需考虑(当^Z跟在字符串后,不会被检测,检测到EOF时getline()返回的数量为0)
 *  2)lp进行-1操作回退相当于调用ungetch()
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
                op2 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                push(op1 + op2);
                break;
            case '*':
                op2 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                push(op1 * op2);
                break;
            case '-':
                op2 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                push(op1 - op2);
                break;
            case '/':
                op2 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                op1 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                if (op2 != 0.0)
                    push(op1 / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
                if (op2 == 0)
                    printf("error: zero divisor\n");
                else {
                    op1 = popStatus() == -1 ? storage[toupper(popVariables()) - 'A'] : pop();
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
        storage[toupper(popVariables()) - 'A'] = pop();
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

#define BUFFER 101

int getline(char s[], int length);
char line[BUFFER];
int lp = 0;  //记录line下一个被读取到的位置

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, len;

    if (lp == 0)
        len = getline(line, BUFFER);
    if (len == 0) return EOF;

    while ((s[0] = c = line[lp++]) == ' ' || c == '\t');

    s[1] = '\0';
    i = 0;

    lp = (c == '\n') ? 0 : lp;  //若到末尾(即已遇到'\n'),则需要读取下一行
    if (!isalpha(c) && !isdigit(c) && c != '-' && c != '.') return c;
    if (isalpha(c)) {
        while (isalpha(s[++i] = c = line[lp++]));
        s[i] = '\0';
        --lp; //相当于ungetch()
        if (i == 1) return VARIABLE;
        return METHOD;
    }
    if (c == '-') s[++i] = c = line[lp++];
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[lp++]));
    if (c == '.')
        while (isdigit(s[++i] = c = line[lp++]));
    s[i] = '\0';
    --lp;
    if (i == 1 && ispunct(s[0])) return s[0];
    return NUMBER;
}

int getline(char s[], int length)
{
    int i, c;

    i = 0;
    while (i < length - 1 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }

    if (c == '\n') {
        s[i++] = c;
    } else if (i > 0) {  //有输入时getline()一定以'\n'结尾,保证getop()中判断操作对象的类型时不会越界(lp<=len-1)
        s[i++] = '\n';
    }

    s[i] = '\0';
    return i;
}