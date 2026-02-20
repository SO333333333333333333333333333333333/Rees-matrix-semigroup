#include<stdio.h>

// 群 G = {e, a} を以下のように定義する。
typedef enum Group {e=1, a} Group;
int OrdG = 2;
Group CayleyTable[2 /*=OrdG*/][2 /*=OrdG*/] =
{
  // e, a
    {e, a}, // e
    {a, e}  // a
};
Group GX(Group x, Group y)
{
    return CayleyTable[x-1][y-1];
}

int Rows = 3;
int Columns = 2;
Group Matrix[3 /*=Rows*/][2 /*=Columns*/] =
{
    {e, 0},
    {0, e},
    {a, a}
};

typedef struct Semigroup
{
    int IsZero;
    int c;
    Group g;
    int r;
} Semigroup;
Semigroup SX(Semigroup x, Semigroup y)
{
    Semigroup z = {0, 0, 0, 0};
    if (x.IsZero == 1 || y.IsZero == 1)
    {
        z.IsZero = 1;
        return z;
    }
    else if (Matrix[x.r][y.c] == 0)
    {
        z.IsZero = 1;
        return z;
    }
    else
    {
        z.IsZero = 0;
        z.c = x.c;
        z.g = GX(GX(x.g, Matrix[x.r][y.c]), y.g);
        z.r = y.r;
        return z;
    }
}

void PrintSemigroup(Semigroup x)
{
    if (x.IsZero == 1)
    {
        printf("   0    ");
    }
    else
    {
        char g;
        if (x.g == e) g = 'e';
        else if (x.g == a) g = 'a';
        // else if (x.g == b) g = 'b';
        else g = '?';
        printf("(%d,%c,%d) ", x.c, g, x.r);
    }
}

int main(void)
{
    int i, j, k, l, m, n;
    Semigroup Zero = {1, 0, 0, 0};
    printf("        ");
    printf("|");
    PrintSemigroup(Zero);
    for (i = e; i <= OrdG; i++)
    {
        for (j = 0; j < Columns; j++)
        {
            for (k = 0; k < Rows; k++)
            {
                Semigroup x = {0, j, i, k};
                PrintSemigroup(x);
            }
        }
    }
    printf("\n");

    printf("--------");
    printf(" ");
    printf("--------");
    for (i = e; i <= OrdG; i++)
    {
        for (j = 0; j < Columns; j++)
        {
            for (k = 0; k < Rows; k++)
            {
                printf("--------");
            }
        }
    }
    printf("\n");

    PrintSemigroup(Zero);
    printf("|");
    PrintSemigroup(Zero);
    for (i = e; i <= OrdG; i++)
    {
        for (j = 0; j < Columns; j++)
        {
            for (k = 0; k < Rows; k++)
            {
                PrintSemigroup(Zero);
            }
        }
    }
    printf("\n");

    for (i = e; i <= OrdG; i++)
    {
        for (j = 0; j < Columns; j++)
        {
            for (k = 0; k < Rows; k++)
            {
                Semigroup x = {0, j, i, k};
                PrintSemigroup(x);
                printf("|");
                PrintSemigroup(Zero);
                for (l = e; l <= OrdG; l++)
                {
                    for (m = 0; m < Columns; m++)
                    {
                        for (n = 0; n < Rows; n++)
                        {
                            Semigroup y = {0, m, l, n};
                            Semigroup z = SX(x, y);
                            PrintSemigroup(z);
                        }
                    }
                }
                printf("\n");
            }
        }
    }

    return 0;
}