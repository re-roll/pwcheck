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

int cmprStr(char* str1, char* str2)
{
    if (strLen(str1) != strLen(str2))
        return 0;

    int len = strLen(str1);
    for (int i = 0; i < len; i++)
    {
        if (str1[i] != str2[i])
            return 0;
    }

    return 1;
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
    int cnt = 0;
    if (lowerCase(str))
        cnt++;
    if (upperCase(str))
        cnt++;
    
    if (cnt == 2)
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
    //Checking if 3 level returned "1"
    if (!(lvl_3(p, str)))
        return 0;
        
    //There will be returned "error" because we cannot find substring with the length of 1, minimal length is 2
    if (p == 1)
        return -1;

    int len = strLen(str);  //Finding the length of our password
    int cnt = 0;            //Starting number of symbols in substrings is 0
    
    int i;                  //Counter for symbols  in string [A, B, C, D, ...] Start in A
    int j;                  //Counter for symbols  in string [A, B, C, D, ...] Start in B
    
    int alt_i = 0;          //2 Counter for symbols  in string [A, B, C, D, ...] Start in C
    int alt_j = 1;          //2 Counter for symbols  in string [A, B, C, D, ...] Start in D

    for (int i = 0; i < len; i++) // Everything below will be checked for i symbol
    {
        for (int j = i+1; j < len; j++) // Everything below will be checked for j symbol
        {
            if (str[i] == str[j]) //Checking if value of i symbol is equal to value of j symbol
            {
                cnt++; //If str[0] == str[1] => We have 1 same symbol in all the substrings
                alt_i = i; //Just to remember it, wi will need this counter later
                alt_j = j; //Just to remember it, wi will need this counter later
                break; //If we found 1 symbol in subtrings we no longer need this CHECKING in the pair i-j
            }

            //I will delete it :)
            if (str[i] == '\0')
                break; //If we found 1 symbol in subtrings we no longer need this CHECKING in the pair i-j
        }
        break; //If we found 1 symbol in subtrings we no longer need this CHECKING in the pair i-j
    }

    alt_i++; //Now our 2 counter will be modified and our next start position will be in symbol i+1 = 1
    alt_j++; //Now our 2 counter will be modified and our next start position will be in symbol j+1 = 2

    for (int k = 1; k <= p; k++) 
    {
        for (int i = alt_i; i < len - k; i++) // Everything below will be checked for i+1 symbol
        {
            for (int j = alt_j; j <= len - k; j++) // Everything below will be checked for j+1 symbol
            {
                if (str[i] == str[j]) //Checking if value of i+1 symbol is equal to value of j+1 symbol
                {
                    while (cnt != p) //If we have param = 3 and we found symbols on the previous BIG ciklus, for now we have 1 symbol so this ciklus will be executed 2 times
                    {
                        cnt++; //If str[1] == str[2] => We already have 2 same symbols in all the substrings
                        alt_i = i; //...
                        alt_j = j;
                        break;
                    }
                    break;
                }

                if (str[i] == '\0')
                    break;
                
            }
            alt_j++;
        }
        alt_i++;
    }

    if (cnt == p)
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

    if (par < 1)
        printf("ERROR: Security parameter should be positive\n");

    char pswd[max_len];

    while (getchar() != EOF)
    {
        scanf("%s", pswd);
            if (lvl == 1)
        {
            if (lvl_1(pswd))
                printf("%s\n", pswd);
        }
        else if (lvl == 2)
        {
            if (lvl_2(par, pswd))
                printf("%s\n", pswd);
        }
        else if (lvl == 3)
        {
            if (lvl_3(par, pswd) == -1)
                printf("Enter the correct parameter on this level (0 passwords were shown)\n");
            else if (lvl_3(par, pswd))
                printf("%s\n", pswd);
        }
        else if (lvl == 4)
        {
            if (lvl_4(par, pswd) == -1)
                printf("Enter the correct parameter on this level (0 passwords were shown)\n");
            else if (lvl_4(par, pswd))
                printf("%s\n", pswd);
        }
        else
            printf("ERROR: Security level should be in the interval [1, 4]\n");
    }

    if (stats == 1)
    printf("Tady byde statistika\n");

    return 0;
}
