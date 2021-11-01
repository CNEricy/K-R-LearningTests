#define BUFSIZE 100

char buf = '\0';

int getch(void) /* get a (possibly pushed back) character */
{
    if (buf == '\0')
        return getchar();
    else {
        char t = buf;
        buf = '\0';
        return t;
    }
}

void ungetch(int c) /* push character back on input */
{
    if (buf != '\0')
        printf("ungetch: too many characters\n");
    else
        buf = c;
}