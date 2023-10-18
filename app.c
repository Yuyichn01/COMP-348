#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

// randomly generate phone number
void randomPhoneNumber(char myString[10000])
{
    int phoneIndex[10] = {398, 270, 925, 867, 209, 429, 908, 997};
    int randomNum1 = rand() % 9000 + 1000;
    int randomNum2 = rand() % 8;
    sprintf(myString, "%d", phoneIndex[randomNum2]);
    strcat(myString, "-");
    sprintf(myString + strlen(myString), "%d", randomNum1);
}

// randonly choose data in file
void randomChoose(char FileName[50], char returnString[10000], int numberOfChoice)
{

    bool keep_reading = true;
    int current_line = 1;

    FILE *file;
    file = fopen(FileName, "r");
    int read_line;

    read_line = (rand() % numberOfChoice) + 1;

    char filename[FILENAME_SIZE];
    char buffer[MAX_LINE];
    do
    {
        fgets(buffer, MAX_LINE, file);

        if (feof(file))
        {
            keep_reading = false;
            printf("Couldn't find the file, please put the file in the destination folder");
        }

        else if (current_line == read_line)
        {
            keep_reading = false;
            // delete '/n' in buffer
            for (int i = 0; i < sizeof(buffer); i++)
            {
                if (buffer[i] == '\n')
                    buffer[i] = '\0';
            }
            strcat(returnString, buffer);
        }

        current_line++;
    }

    while (keep_reading);

    read_line = 0;

    fclose(file);
}

// randomly generate SIN number
void SINNumber(char string[10000])
{

    // Generate a random 9-digit number
    int min = 100000000; // 10^8
    int max = 999999999; // (10^9 - 1)
    int randNum = rand() % (max - min + 1) + min;

    char buffer3[10];
    sprintf(buffer3, "%d", randNum);
    strcat(string, buffer3);
}

//  randomly generate password
char randomCharacter()
{
    const char charSet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=-{}[]|:;<>,.?/~";
    int charSetSize = sizeof(charSet) - 1;
    int randomIndex = rand() % charSetSize;
    return charSet[randomIndex];
}

int main()
{
    // seed random number
    srand(time(NULL));

    // display menu
    int input1;
    char str1[50], str2[50], str3[50];
    // the final output string
    char str5[10000][100];
    char returnString[50];
    char options[][20] = {"User ID", "First Name", "Last Name", "Country", "Phone Number", "Email Address", "SIN", "Password"};
    printf("TableGen Menu\n---------------\n1. Generate new table \n2. Exit\n\nSelection: ");
    scanf("%d", &input1);

    // filter user input1
    while (input1 > 2 || input1 < 1)
    {
        printf("The choice doesn't exist, please try again\n");
        scanf("%d", &input1);
    }

    if (input1 == 2)
    {
        printf("Goodbye and thanks for using TableGen\n");
        exit(0);
    }
    else
    {
        system("clear");
        printf("Column Options\n-----------\n1. User ID          5. Phone Number \n2.First name        6. Email address      \n3.Last name         7. SIN\n4.Country           8. Password\nEnter column list (comma-seperated, no spaces): \n");
    }

    scanf("%49s", str1);
    printf("Enter row count (1 < n < 1M): ");
    scanf("%49s", str2);
    printf("Enter output file name (no suffix): ");
    scanf("%49s", str3);
    printf("Summary of properties: \n");
    printf("Columns: ");
    printf("%s\n", str1);
    printf("Row count: ");
    printf("%s\n", str2);
    printf("File name: ");
    printf("%s\n", str3);

    // convert str 1 strings into numbers to str4

    int str4[10];

    const char *delimiter = ",";
    char *token = strtok(str1, delimiter);
    int index = 0;

    while (token != NULL && index < sizeof(str1))
    {
        sscanf(token, "%d", &str4[index]);
        token = strtok(NULL, delimiter);
        index++;
    }

    // Printing the converted integers
    for (int i = 0; i < index; i++)
    {
        printf("Integer %d: %d\n", i, str4[i]);
    }

    int columnNumber = index;
    int rowNumber = atoi(str2);

    // generate first row
    for (int i = 0; i < columnNumber; i++)
    {
        if (i == columnNumber - 1)
        {
            strcat(str5[i], options[str4[i] - 1]);
            strcat(str5[i], "\n");
            break;
        }
        strcat(str5[i], options[str4[i] - 1]);
        strcat(str5[i], ", ");
    }

    // data arrays for all user information
    char userID[10000][10];
    char lastNames[10000][50];
    char firstNames[10000][50];
    char countries[10000][50];
    char SinNumber[10000][50];
    char phoneNumber[10000][50];
    char password[10000][50];
    char email[10000][50];

    // orderly generate userIDs array

    for (int i = 1; i <= rowNumber; i++)
    {
        char buffer[10];                           // Buffer to store each number
        snprintf(buffer, sizeof(buffer), "%d", i); // Convert the number to a string
        strcat(userID[i], buffer);                 // Append the string to the result
    }

    // randomly generate lastNames
    for (int i = 0; i <= rowNumber; i++)
    {
        if (i == rowNumber)
        {
            strcat(lastNames[i], "\0");
            break;
        }
        randomChoose("last_names.txt", lastNames[i], 1000);
    }

    // randomly generate firstNames
    for (int i = 0; i <= rowNumber; i++)
    {
        if (i == rowNumber)
        {
            strcat(firstNames[i], "\0");
            break;
        }
        randomChoose("first_names.txt", firstNames[i], 1000);
    }

    // randomly generate countries
    for (int i = 0; i <= rowNumber; i++)
    {
        if (i == rowNumber)
        {
            strcat(countries[i], "\0");
            break;
        }
        randomChoose("Countries.txt", countries[i], 195);
    }

    // randomly generate SINs
    for (int i = 0; i <= rowNumber; i++)
    {
        if (i == rowNumber)
        {
            strcat(SinNumber[i], "\0");
            break;
        }
        SINNumber(SinNumber[i]);
    }

    // randomly genrate phone number
    for (int i = 0; i <= rowNumber; i++)
    {
        if (i == rowNumber)
        {
            strcat(phoneNumber[i], "\0");
            break;
        }
        randomPhoneNumber(phoneNumber[i]);
    }

    // randomly genrate password
    for (int i = 0; i <= rowNumber; i++)
    {
        int passwordLength = (rand() % 11) + 6;
        if (i == rowNumber)
        {
            strcat(phoneNumber[i], "\0");
            break;
        }
        for (int j = 0; j < passwordLength; j++)
        {
            char randomChar = randomCharacter();
            strncat(password[i], &randomChar, 1);
        }
    }

    // sort last names array
    int length = rowNumber;
    char temp[50];

    for (int i = 0; i < length - 1; i++)
    {
        int j_min = i;
        for (int j = i + 1; j < length; j++)
        {
            if (strcmp(lastNames[j], lastNames[j_min]) < 0)
                j_min = j;
        }
        if (j_min != i)
        {
            strcpy(temp, lastNames[i]);
            strcpy(lastNames[i], lastNames[j_min]);
            strcpy(lastNames[j_min], temp);
        }
    }

    // generate email array
    for (int i = 0; i <= rowNumber; i++)
    {
        if (i == rowNumber)
        {
            strcat(email[i], "\0");
            break;
        }

        email[i][0] = firstNames[i][0];
        strcat(email[i], lastNames[i]);
        strcat(email[i], "@");
        randomChoose("email_suffixes.txt", email[i], 100);
    }

    // concate to string and output to text file
    int k = columnNumber;
    for (int i = 1; i < rowNumber; i++)
    {
        if (k == rowNumber * columnNumber)
        {
            strcat(str5[k], "\0");
            break;
        }

        for (int j = 0; j < columnNumber; j++)
        {
            switch (str4[j])
            {
            case 1:
                strcat(str5[k], userID[i]);
                break;
            case 2:
                strcat(str5[k], firstNames[i]);
                break;
            case 3:
                strcat(str5[k], lastNames[i]);
                break;
            case 4:
                strcat(str5[k], countries[i]);

                break;
            case 5:
                strcat(str5[k], phoneNumber[i]);
                break;
            case 6:
                strcat(str5[k], email[i]);
                break;
            case 7:
                strcat(str5[k], SinNumber[i]);

                break;
            case 8:
                strcat(str5[k], password[i]);
                break;
            }
            if (j != columnNumber - 1)
                strcat(str5[k], ", ");

            if (j == columnNumber - 1)
            {
                strcat(str5[k], "\n");
            }
        }
        k++;
    }

    printf("%s", "The output text is: \n");

    for (int i = 0; i < rowNumber + columnNumber; i++)
    {
        printf("%s", str5[i]);
    }

    printf("%s", "Converting to csv file\n");
    FILE *csvFile;

    // Open the CSV file for writing (create if it doesn't exist)
    csvFile = fopen("myoutput.csv", "w");

    if (csvFile == NULL)
    {
        perror("Error opening the file");
        printf("%s", "please create a new csv file named 'myoutput.csv for write in data\n");
        return 1;
    }

    // Write the data to the CSV file
    for (int i = 0; i < rowNumber + columnNumber; i++)
    {
        fputs(str5[i], csvFile);
    }

    // Close the CSV file
    fclose(csvFile);

    printf("%s", "Successfully converted to csv file\n");

    return 0;
}
