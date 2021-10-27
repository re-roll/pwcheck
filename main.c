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
        if (((str[i] > 31) && (str[i] < 48)) || ((str[i] > 57) && (str[i] < 65)) || ((str[i] > 90) && (str[i] < 97)) || ((str[i] > 122) && (str[i] < 127)))
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
    if (!(lvl_2(p, str)))
        return 0;
        
    if (p == 1)
        return -1;

    int cnt = 1;

    for (int i = 1; i < max_len; i++)
    {
        if (str[i] == str[i-1])
            cnt++;
        else
            cnt = 1;

        if (cnt == p)
            return 0;

        if (str[i] == '\0')
            break;
    }
     
     return 1;
}

int lvl_4(int p, char str[max_len])
{
    if (!(lvl_3(p, str)))
        return 0;
        
    if (p == 1)
        return -1;

    int len = strLen(str);
    int cnt = 0;
    int alt_i = 0;
    int alt_j = 0;

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            printf("%d %d\n", i, j);
            if (str[i] == str[j])
            {
                cnt++;
                alt_i = i;
                alt_j = j;
                printf("Count: %d char: %c\n", cnt, str[i]);
                break;
            }

            if (str[i] == '\0')
                break;
            
            if (alt_j != 0)
                break;
        }
        if (alt_i != 0)
            break;
    }

    alt_i++;
    alt_j++;

    printf("Zacatek\n");

    for (int k = 1; k <= p; k++)
    {
        for (int i = alt_i; i < len - k; i++)
        {
            for (int j = alt_j; j <= len - k; j++)
            {
                printf("%d %d\n", i, j);
                if (str[i] == str[j])
                {
                    cnt++;
                    alt_i = i;
                    alt_j = j;
                    printf("Count: %d char: %c\n", cnt, str[i]);
                    break;
                }
                

                if (str[i] == '\0')
                    break;
                
                if (alt_j != 0)
                    break;
            }
            if (alt_i != 0)
                break;
        }
        alt_i++;
        alt_j++;
        if (cnt == k)
            break;
    }

    printf("Count is: %d\n", cnt);
     
    return 1;
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
        if (cmprStr(argv[i], "--stats"))
            stats = 1;
    }

    printf("Level: %d\n", lvl);
    printf("Parameter: %d\n", par);
    printf("-- stats: %d\n", stats);

    char pswd[100];

    printf("\n");

    scanf("%s", pswd);

    if (lvl == 1)
        if (lvl_1(pswd))
            printf("New: %s\n", pswd);
    
    if (lvl == 2)
        if (lvl_2(par, pswd))
            printf("New: %s\n", pswd);

    if (lvl == 3)
    {
        if (lvl_3(par, pswd) == -1)
            printf("Enter the correct parameter on this level\n");
        else if (lvl_3(par, pswd))
            printf("New: %s\n", pswd);
    }

    if (lvl == 4)
        if (lvl_4(par, pswd))
            printf("New: %s\n", pswd);

    printf("\n");

    return 0;
}
