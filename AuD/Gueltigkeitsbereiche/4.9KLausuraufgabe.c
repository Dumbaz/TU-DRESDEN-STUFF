#include <stdio.h>

void f ( int *a, int *b);

void g (int *x , int *y) {
    int z;
    z = *y; /* label 1 */
    if (z > 0)
        f(&z, y); /* $ 1 */
    else
        *x = z;
    /* label 2 */
}

void f(int *a, int *b) {
    *b = *a - 1; /* label 3 */
    while (*a > 1) {
        g(a, b); /* $2 */ /* label 4*/
    }
}

int main()
{
    int e, a;
    scanf("%i", &e); /* label 5 */
    f(&e, &a); /* $3 */ /* label 6 */
    printf("%d", a);
    return 0;
}

/* GUeltigkeitsbereiche

    f:  3-29
    g:  5-29
main:   22-29

in f:
int *a: 15-20
int *b: 15-20

in g:
int *x: 5-13
int *y: 5-13
int z:  6-13

int e:  24-29
int a:  24-29

*/

/* Pulsierender Speicher
   Haltepunkt   RM          Umgebung
                            1   2   3   4   5   6   7   8   9

   label 5      -           e   a
                            2   ?

   label 3      3                   a   b  
                            2   1   #1  #2

   label 1      2:3                         x   y   z
                            2   1   #1  #2  #1  #2  1

   label 3      1:2:3                                   a   b
                            2   0   #1  #2  #1  #2  1   #1  #2     a=7 Laut Loesung, aber das erscheint mir falsch

   label 2      2:3                         x   y   z
                            2   0   #1  #2  #1  #2  1

   label 4      3                   a   b
                            2   0   #1  #2

   label 1      2:3                          x   y   z
                            2   0   #1  #2   #1  #2  0

   label 2      2:3                         x   y   z
                            0   0   #1  #2  #1  #2  0

   label 4      3                   a   b
                            0   0   #1  #2

   label 6      -           e   a
                            0   0

   */
   
