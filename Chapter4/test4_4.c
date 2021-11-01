

#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);

void push(double);

double pop(void);

void showTop();

void copyTop();

void swapTops();

void clearStack();

/* reverse Polish calculator */

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
    int commandStatus;

    commandStatus = 1;
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 == 0)
                    printf("error: zero divisor\n");
                else {
                    double op1 = pop();
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
                if (commandStatus == 1)
                    printf("\t%.8g\n", pop());
                commandStatus = 1;
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

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

void showTop()
{
    if (sp > 0)
        printf("top value of stack is %.8g\n", val[sp-1]);
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
    val[0]='\0';
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
    if (!isdigit(c) && c != '.') {
        if (c != '-')
            return c;
        else if (!isdigit(c = getch())) {
            ungetch(c);
            return '-';
        } else
            s[++i] = c;
    }

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
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