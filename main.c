#include <stdio.h>
#include <stdlib.h>

#define max_len 100

int strLen (char str[max_len])
{
    int i;
    while (str[i] != '\0')
        i++;

    return i;
}

int par_1 (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((str[i] >= 'a') && (str[i] <= 'z'))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int par_2 (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((par_1(str)) && ((str[i] >= 'A') && (str[i] <= 'Z')))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int par_3 (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((par_2(str)) && ((str[i] >= '0') && (str[i] <= '9')))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int par_4 (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((par_3(str)) && (((str[i] > 31) && (str[i] < 48)) || ((str[i] > 57) && (str[i] < 65)) || ((str[i] > 122) && (str[i] < 127))))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int lvl_1 (char str[max_len])
{
    int k = 0;
    if (par_1(str))
        k++;
    if (par_2(str))
        k++;
    
    if (k == 2)
        return 1;
    
    return 0;
}

int lvl_2 (int p, char str[max_len])
{
    if ((p == 1) && (par_1(str)))
        return 1;
    
    if ((p == 2) && (par_2(str)))
        return 1;

    if ((p == 3) && (par_3(str)))
        return 1;

    if ((p >= 4) && (par_4(str)))
        return 1;

    return 0;
}

int lvl_3 (int p, char str[max_len])
{
    int k = 1;
    for (int i = 1; i < max_len; i++)
    {
        if (str[i] == str[i-1])
            k++;
        else
            k = 1;
        if (k == p)
            return 0;
    }

    return 1;
}

int main(int argc, char* argv[])
{
    int lvl = 0;
    int par = 0;
    int stats = 0;

    printf("Level: %d\n", lvl);
    printf("Parameter: %d\n", par);
    printf("-- stats: %d\n", stats);

    return 0;
}
