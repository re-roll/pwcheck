#include <stdio.h>
#include <stdlib.h>

#define max_len 100 //I decided to define it in order to not to define it each time when I work with the length of strings

int strLen (char str[max_len]) //Function gets the string and process it
{
    int i; //Counter

    //While the program won't find the last symbol of string, I count its length
    while (str[i] != '\0') 
        i++; 

    return i; // From now I will be getting length of string from this function
}

int cmprStr(char* str1, char* str2) //Function gets two strings and compare it
{
    //We can break the function and return 0 here if our lengths of strings are not equal
    if (strLen(str1) != strLen(str2))
        return 0;


    int len = strLen(str1); //In the cycle we will work only with strings which length is already approaches
    for (int i = 0; i < len; i++) //So I count to the last symbol in the string, not to 100
        if (str1[i] != str2[i]) //Function does the compare for each symbol
            return 0; //I will get 0 if strings are not the same

    return 1; //I will get 1 if strings are the same
}

void difSym (char* asciit, char pswd[max_len])
{
    int len = strLen(pswd);
    for (int i = 0; i < len; i++)
    {
        *(asciit + pswd[i]) = 1;
        printf("%s\n", pswd);
    }

}

int lowerCase (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((str[i] >= 'a') && (str[i] <= 'z')) //I check if there is any small letter in the string
            return 1; //And if it is, I will get 1
        if (str[i] == '\0') 
            break; //Cycle will stop if we get the end of string
    }
    return 0; //If there are no small letters, checking will return 0 (false)
}

int upperCase (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((str[i] >= 'A') && (str[i] <= 'Z')) //I check if there is any big letter in the string
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
        if ((str[i] >= '0') && (str[i] <= '9')) //I check if there is any digit symbol in the string
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
        //I check if there is any special symbol in the string
        if (((str[i] > 31) && (str[i] < 48)) || ((str[i] > 57) && (str[i] < 65)) || ((str[i] > 90) && (str[i] < 97)) || ((str[i] > 122) && (str[i] < 127)))
            return 1;
        if (str[i] == '\0')
            break;
    }
    return 0;
}

int lvl_1 (char str[max_len])
{
    int i = 0; //Counter
    if (lowerCase(str))
        i++; //Here will be 1 if string contains some small letter
    if (upperCase(str))
        i++; //Here will be 1 if it doesn't contain big letter and 2 if does
    
    if (i == 2) //For checking on this level we should have small AND big letters in our string
        return 1;
    
    return 0; //For any other case it will return 0 (false)
}

int lvl_2 (int p, char str[max_len])
{
    if ((p == 1) && (lvl_1(str))) /*For paramerter "1" I could write there "lowerCase(str) || upperCase(str) || .... and so on", 
    but level 2 will be passed only if we passed level 1 so there for 100% should be big and small letters*/
        return 1;

    if ((p == 2) && (lvl_1(str))) //For parameter "2" we should have small and big letters, so I just wrote "lvl_1(str)" because it checks the same
        return 1;

    if ((p == 3) && ((lvl_1(str)) && ((numSym(str)) || (specSym(str))))) /*For parameter "2" we should have 3 groups of symbols, BUT 
    level 1 will be passed only if we passed level 1, so big and small letters for 100% will be there, and then we will have
    obly two options fot rhe third place: digits or special symbols*/
        return 1;

    if ((p >= 4) && ((lvl_1(str) && numSym(str) && specSym(str)))) // Here we should have all the 4 groups in our string
        return 1;

    return 0;
}

int lvl_3 (int p, char str[max_len])
{
    if (!(lvl_2(p, str)))
        return 0;

    int cnt = 1;

    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] == str[i-1])
            cnt++;
        else
            cnt = 1;

        if (cnt == p)
            return 0;
    }
     
    return 1;
}

int lvl_4 (int p, char* str)
{
    if (!(lvl_3(p, str)))
        return 0;

    int cnt = 0;

    int iFori;
    int jForj;

    int len = strLen(str);

    for (int i = 0; i < len - 1; i++)
        for (int j = i + 1; j <= len - 1; j++)
        {
            if (str[i] == str[j])
            {
                cnt++;
                iFori = i + 1;
                jForj = j + 1;
                for (int k = 1; k < p; k++)
                {
                    if (str[iFori] == str[jForj])
                    {
                        cnt++;
                        iFori++;
                        jForj++;
                    }
                    if (cnt == p)
                        return 0;
                }
            }
            else 
                cnt = 0;
        }
    
    if (cnt != p)
        return 1;

    return 0;
}

int passInput(char* pswd)
{
    char c;
    int i = 0;

    while ( (c = getchar()) != '\n')
    {
        if (i > max_len - 1)
            return -1;
        if (c == EOF)
            return -2;

        *(pswd + i) = c;
        i++; //Counter AND length of string
    }
    return 0;
}

int errorsZone (int lvl, int p)
{
    if (((lvl > 4) || (lvl < 1)) && (p < 1))//I wrote explanation of this in the "printf" for user
    {
        printf("ERROR! Security level should exist and be integer in the interval [1, 4]\n");
        printf("ERROR! Security parameter should exist and be positive integer\n");
        return -1; 
    }
    if ((lvl > 4) || (lvl < 1))//I wrote explanation of this in the "printf" for user
    {
        printf("ERROR! Security level should exist and be integer in the interval [1, 4]\n");
        return -2; 
    }
    if (p < 1) //I also wrote explanation of this in the "printf" for user
    {
        printf("ERROR! Security parameter should exist and be positive integer\n");
        return -3; //Program will stop
    }
    return 0;
}

int checking(int lvl, int p, int stats)
{
    char pswd[max_len];
    int codeOfError;

    int cnt = 0;
    int LENGTH = 0;
    int MIN = max_len;
    int NCHARS = 0;
    //End of declarations

    char asciit[127];
    for (int i = 0; i < 127; i++)
    {
        asciit[i] = '0';
    }
    while (1) //Cycle will stop only if there are any errors (and they will be, for example End Of File)
    {
        codeOfError = passInput(pswd); //We get Error Code from function
        if (codeOfError == -1) //This error code is already explained
        {
            return -1; //Program will stop with "printf" for explanation of the error
        }
        if ( codeOfError == -2)
            break; //Cycle will break due to the End Of File

        //Here is starting the checking for each password in file
        if (lvl == 1)
        {
            if (lvl_1(pswd))
                printf("%s\n", pswd); //If password is enough good for Level#1 the program will write it down
        }
        else if (lvl == 2)
        {
            if (lvl_2(p, pswd))
                printf("%s\n", pswd); //If password is enough good for Level#2 the program will write it down
        }
        else if (lvl == 3)
        {
            if (p == 1)
            {
                printf("Enter the correct parameter on this level (0 passwords were shown)\n"); //This error is explained in "printf"
                break;
            }
            else if (lvl_3(p, pswd))
                printf("%s\n", pswd); //If password is enough good for Level#3 the program will write it down
        }
        else if (lvl == 4)
        {
            if (p == 1)
            {
                printf("Enter the correct parameter on this level (0 passwords were shown)\n"); //This error is explained in "printf"
                break;
            }
            if (lvl_4(p, pswd))
                printf("%s\n", pswd); //If password is enough good for Level#4 the program will write it down
        }

        if (MIN > strLen(pswd))
            MIN = strLen(pswd);

        LENGTH +=strLen(pswd); // Length of ALL strings (for 0 iteration - 1 pass, for 1 - 1+2 passes etc.)
        
        //In this cycle I refresh my "buffer" because of strings length (for some purpose my program "fills" string (after it ends) with symbols of previous password)
        for (int i = 0; i < max_len; i++)
            pswd[i] = 0;

        cnt++; // Number of ALL strings
        difSym(asciit, pswd);
    }
    int cntsym = 0;
    for (int i = 0; i < 127; i++)
        if (asciit[i] != 0)
            cntsym++;
    printf("%d\n", cntsym);

    double AVG = (double)LENGTH / cnt;
    if (stats == 1)
    {
        printf("Statistika: \n");
        printf("Ruznych znaku: %d\n", NCHARS);
        printf("Minimalni delka: %d\n", MIN);
        printf("Prumerna delka: %.1f\n", AVG);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    //Declaration of variables for our arguments
    int lvl = 0;
    int p = 0;
    int stats = 0;
    //Variables assignment for our arguments
    for (int i = 1; i < argc; i++) //Cycle will stop if there are no more characters (arguments) in our string
    {
        if (i == 1) 
            lvl = atoi(argv[i]); //On the first place should be security level
        if (i == 2)
            p = atoi(argv[i]); //On the second place should be security parameter
        if ((i == 3) && (cmprStr(argv[i], "--stats"))) //On the third place should be statistics (or shouldn't, we check it with the help of "cmprStr" function)
            stats = 1; //THERE WILL BE STATISTICS
    }
    
    errorsZone (lvl, p);
    checking(lvl, p, stats);

    return 0; //Program is done
}
