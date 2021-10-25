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

int lowerCase (char str[max_len])
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

int upperCase (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((str[i] >= 'A') && (str[i] <= 'Z'))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int numSym (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((str[i] >= '0') && (str[i] <= '9'))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int specSym (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if (((str[i] > 31) && (str[i] < 48)) || ((str[i] > 57) && (str[i] < 65)) || ((str[i] > 122) && (str[i] < 127)))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int lvl_1 (char str[max_len])
{
    int k = 0;
    if (lowerCase(str))
        k++;
    if (upperCase(str))
        k++;
    
    if (k == 2)
        return 1;
    
    return 0;
}

int lvl_2 (int p, char str[max_len])
{
    if ((p == 1) && (lvl_1(str)))
        return 1;
        
    if ((p == 2) && (lvl_1(str)))
        return 1;

    if ((p == 3) && ((lvl_1(str) && numSym(str)) || (lvl_1(str) && specSym(str))))
        return 1;

    if ((p >= 4) && ((lvl_1(str) && numSym(str) && specSym(str))))
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

    for (int i = 0; i < argc; i++)
    {
        printf("%s", argv[i]);
    }

    printf("Level: %d\n", lvl);
    printf("Parameter: %d\n", par);
    printf("-- stats: %d\n", stats);

    return 0;
}
