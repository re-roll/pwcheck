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
    for (int i = 1; i < max_len - 1; i++)
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

int subStr(int i, int j, char* str)
{
    int len = strLen(str);
    for (i = 0; i < len; i++)
        for (j = 1; j < len - 1; i++)
            if (str[i] == str[j])
                return 1;
    
    return 0;
}

int lvl_4(int p, char str[max_len])
{
    for (int k = 2; k <= p; k++)
        for (int i = 0; i < max_len; i++)
            for (int j = 1; j < max_len - 1; i++)
            if (subStr(i, j, str))
                return 0;
    
    return 0;
}

int cmprStr(char* str1, char* str2)
{
    int len = strLen(str1);
    for (int i = 0; i < len; i++)
    {
        if (str1[i] != str2[i])
            return 0;
    }

    if (strLen(str1) != strLen(str2))
        return 0;

    return 1;
}

int main(int argc, char* argv[])
{
    int lvl = 0;
    int par = 0;
    int stats = 0;

    for (int i = 1; i < argc; i++)
    {
        if (i == 1)
            lvl = atoi(argv[i]);
        if (i == 2)
            par = atoi(argv[i]);
        if (i == 3)
            if (cmprStr(argv[i], "--stats"))
                stats = 1;
    }

    

    printf("Level: %d\n", lvl);
    printf("Parameter: %d\n", par);
    printf("-- stats: %d\n", stats);

    return 0;
}
