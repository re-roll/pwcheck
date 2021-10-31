#include <stdio.h>
#include <stdlib.h>

#define max_len 100             //I decided to define it in order to not to define it each time when I work with the length of strings

int strLen (char str[max_len])  //Function gets the string and process it
{
    int i = 0;                  //Counter

    //While the program won't find the last symbol of string, I count its length
    while (str[i] != '\0') 
        i++; 

    return i;                   // From now I will be getting length of string from this function
}

int convertStr(int* arg, char* str) //I need this function because there is check if level and param are integer and what are they
{
    int len = strLen(str);
    for (int i = 0; i < len; i++)
        if ((str[i] < 48) || (str[i] > 57))
        {
            fprintf(stderr, "You entered the wrong argument\n");
            return -1;
        }
    
    *arg = atoi(str);
    return 0;
}

int cmprStr(char* str1, char* str2) //Function gets two strings and compare it
{
    //We can break the function and return 0 here if our lengths of strings are not equal
    if (strLen(str1) != strLen(str2))
        return 0;

    int len = strLen(str1);         //In the cycle we will work only with strings which length is already approaches
    for (int i = 0; i < len; i++)   //So I count to the last symbol in the string, not to 100
        if (str1[i] != str2[i])     //Function does the compare for each symbol
            return 0;               //And I will get 0 if strings are not the same

    return 1;                       //I will get 1 if strings are the same
}

void difSym (char* asciit, char pswd[max_len])
{
    int len = strLen(pswd);
    for (int i = 0; i < len; i++)
        *(asciit + pswd[i]) = 1;  //There I 'fill' the ascii array with 1 on the place where symbol of password is placed at 'true' ascii

}

int lowerCase (char str[max_len])
{
    for (int i = 0; i < max_len; i++)
    {
        if ((str[i] >= 'a') && (str[i] <= 'z')) //I check if there is any small letter in the string
            return 1;                           //And if it is, I will get 1
        if (str[i] == '\0') 
            break;                              //Cycle will stop if we get the end of the string
    }
    return 0;                                   //If there are no small letters, checking will return 0 (false)
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
    int i = 0;              //Counter
    if (lowerCase(str))
        i++;                //Here will be 1 if string contains some small letter
    if (upperCase(str))
        i++;                //Here will be 2 if string contains small and big letters
    
    if (i == 2)             //For checking on this level we should have small AND big letters in our string
        return 1;
    
    return 0;               //For any other case it will return 0 (false)
}

int lvl_2 (int p, char str[max_len])
{
    if ((p == 1) && (lvl_1(str))) /*For paramerter "1" I could write there "lowerCase(str) || upperCase(str) || .... and so on", 
    but level 2 will be passed only if we passed level 1 so for 100% there should be big and small letters*/
        return 1;

    if ((p == 2) && (lvl_1(str))) //For parameter "2" we should have small and big letters, so I just wrote "lvl_1(str)" because it checks the same
        return 1;

    if ((p == 3) && ((lvl_1(str)) && ((numSym(str)) || (specSym(str))))) /*For parameter "2" we should have 3 groups of symbols, BUT 
    level 1 will be passed only if we passed level 1, so big and small letters for 100% will be there, and then we will have
    only two options for the third place: digits or special symbols*/
        return 1;

    if ((p >= 4) && ((lvl_1(str) && numSym(str) && specSym(str)))) // Here we should have all the 4 groups in our string
        return 1;

    return 0;
}

int lvl_3 (int p, char str[max_len])
{
    //Level 3 will run only if level 2 with this parameter has passed
    if (!(lvl_2(p, str)))
        return 0;

    int cnt = 1; //We start count from 1 because minimum length of repeating is 2

    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] == str[i-1]) //Comparing
            cnt++;
        else
            cnt = 1; //If symbols are not same count is still 1 

        if (cnt == p)
            return 0; //We stop when we see that count of repeating is equal to parameter
    }
     
    return 1;
}

int lvl_4 (int p, char* str)
{
    //Level 4 will run only if level 3 with this parameter has passed
    if (!(lvl_3(p, str)))
        return 0;

    int cnt = 0; //Now we have substring with 0 repeating symbols

    int iFori; //The element after first symbol in substring#1
    int jForj; //The element after first symbol in substring#2

    int len = strLen(str);

    for (int i = 0; i < len - 1; i++)
        for (int j = i + 1; j <= len - 1; j++)
        {
            if (str[i] == str[j])
            {
                cnt++; //We found our first symbol in each of the substrings
                iFori = i + 1; //From now we will check the neighbor of the element id substring#1 
                jForj = j + 1; //From now we will check the neighbor of the element id substring#2
                for (int k = 1; k < p; k++) //We will stop all the below when iteration number will be equal to parameter
                {
                    if (str[iFori] == str[jForj]) //If the neighbors are the same:
                    {
                        cnt++; //Now we found the second element
                        iFori++; //And so on...
                        jForj++;
                    }
                    if (cnt == p) //We stop when we see that count of symbols in substrings is equal to parameter
                        return 0;
                }
            }
            else 
                cnt = 0; //Setting to zero if we haven't found
        }
    
    if (cnt != p)
        return 1; //Program should write the passsword only if the number of symbols in substrings is not equal to parameter

    return 0;
}

//Reading password
int passInput(char* pswd)
{
    char c;
    int i = 0;

    while ( (c = getchar()) != '\n')
    {
        if (i > max_len - 1)
            return -1; //Password shouldn't be longer than 100
        
        if (c == EOF)
            return -2; //Break when it reaches the end of file

        *(pswd + i) = c; //For each symbol in password we write character 'c'
        i++; 
    }
    
    return 0;
}

int checking(int lvl, int p, int stats)
{
    char pswd[max_len]; //Buffer for future passwords
    int codeOfExit;

    //Variables for statistics
    int cnt = 0;
    int LENGTH = 0; 
    int MIN = max_len;
    int NCHARS = 0;
    //End of declarations

    //In this cycle I create the array for ascii with all 0
    char asciit[127];
    for (int i = 0; i < 127; i++)
        asciit[i] = 0;

    while (1) //Cycle will stop only if there are any exit codes (and they will be, for example End Of File)
    {
        //In this cycle I refresh my "buffer" because of strings length 
        for (int i = 0; i < max_len; i++)
            pswd[i] = 0;

        codeOfExit = passInput(pswd);   //We get Exit Code from function

        if (codeOfExit == -1)           //This exit code is already explained in passInput
        {
            fprintf(stderr, "Password is too long\n");
            return -1;                  //Program will stop with "stderr" for explanation of the error
        }
        if (codeOfExit == -2)
            break;                      //Cycle will break due to the End Of File

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
            if (lvl_3(p, pswd))
                printf("%s\n", pswd); //If password is enough good for Level#3 the program will write it down
        }
        else if (lvl == 4)
        {
            if (lvl_4(p, pswd))
                printf("%s\n", pswd); //If password is enough good for Level#4 the program will write it down
        }

        //Finding minimum
        if (MIN > strLen(pswd))
            MIN = strLen(pswd);

        LENGTH +=strLen(pswd); // Length of ALL strings (for 0 iteration - 1 pass, for 1 - 1+2 passes etc.)

        //Calling function for statistics for NCHARS
        if (stats == 1)
            difSym(asciit, pswd);

        cnt++; // Number of ALL strings
    }
    
    //Statistics
    if (stats == 1)
    {
        double AVG = (double)LENGTH / cnt;
        for (int i = 0; i < 127; i++)
        if (asciit[i] != 0)
            NCHARS++;
        printf("Statistika: \n");
        printf("Ruznych znaku: %d\n", NCHARS);
        printf("Minimalni delka: %d\n", MIN);
        printf("Prumerna delka: %.1f", AVG);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    //Declaration of variables for our arguments
    int lvl = 0;
    int p = 0;
    int stats = 0;

    //If user won't insert the level and parametr he will get the stderr and program will stop
    if (argc < 3)
    {
        fprintf(stderr, "You entered too few arguments\n");
        return -1;
    }

    //Variables assignment for our arguments
    for (int i = 1; i < argc; i++) //Cycle will stop if there are no more characters (arguements) in our string
    {
        if (i == 1) 
        {
            convertStr(&lvl, argv[i]); //On the first place should be security level
            if ((lvl > 4) || (lvl < 1)) //Shouldn't be greater than 4 and less than 1
            {
                fprintf(stderr, "Check out your level\n");
                return -1;
            }
        }
        if (i == 2)
        {
            convertStr(&p, argv[i]); //On the second place should be security parameter
            if (p < 1) //Shouldn't be less than 1
            {
                fprintf(stderr, "Check out your parameter\n");
                return -1;
            }
        }
        if ((i == 3) && (cmprStr(argv[i], "--stats"))) //On the third place should be statistics (or shouldn't, we check it with the help of "cmprStr" function)
            stats = 1; //If it's 1, checking() will write the statistics
        else if ((i == 3) && (!(cmprStr(argv[i], "--stats")))) //If there is the third arguement and it's not --stats program will write an error
        {
            fprintf(stderr, "Check out your stats\n");
            return -1;
        }
        else if (i > 3) //We shouldn't have more than 3 arguements
        {
            fprintf(stderr, "Check out your arguements\n");
            return -1;
        }
    }
    
    //Working with passwords
    if (checking(lvl, p, stats) != 0)
        return -1;

    return 0; //Program is done
}
