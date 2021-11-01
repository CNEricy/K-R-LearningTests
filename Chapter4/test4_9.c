/**
 * char相关内容
 * character types: char, unsigned char, signed char
 * char - type for character representation.
 *        Equivalent to either signed char or unsigned char (which one is implementation-defined and may be controlled by a compiler commandline switch),
 *        but char is a distinct type, different from both signed char and unsigned char
 *
 * 前提:
 *  char c;
 *  while ((c = getchar()) != EOF) ;
 *  getchar()的返回值为EOF
 * 要点:
 * EOF为int类型
 * getchar()返回int值
 * char占一个字节(8bit)
 * -1(int) → 0xFFFFFFFF
 * 过程:
 * 当c = getchar()时,即int类型赋值给char类型,0xFFFFFFFF被截断成0xFF
 *  当char的具体类型为unsigned char时,0xFF为255,
 *      进行c != EOF判断时,此时由于EOF为int类型,因此c提升为int类型,但值仍为255,因此结果为true,此时显然结果与预期不同
 *  当char的具体类型为signed char时,0xFF为-1
 *      1.进行c != EOF判断时,此时由于EOF为int类型,因此c提升为int类型,但值仍为-1,因此结果为false,此时结果与预期相同
 *      2.但若此时getchar()返回的是ascii码为255(ascii范围为0-255)的值,被截断后的值为0xFF,值为-1,整型提升后仍为-1,此时结果为false,与预期不同
 *
 * 经过以上分析:显然用char类型去接收getchar()是不合理的,因为表示范围不够,因此需要用int类型去接收getchar(),此时也能处理好EOF
 *            这也是K&R(中文P15,英文P16上)所提到的
 *
 * 注:VC编译器、x86上的GCC都把char定义为signed char，而arm-linux-gcc却把char定义为 unsigned char
 */
#define BUFSIZE 100

int buf[BUFSIZE];  //char → int
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}