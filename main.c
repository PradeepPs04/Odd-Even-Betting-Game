#include <stdio.h>
#include <string.h> // for comparing strings
#include <stdlib.h> // for atoi function and random function
#include <time.h>   // to change the algorithm of random function to get new number each time

float add_new_member(char name[])
{
    FILE *fp = fopen("Data.txt", "a+");
    char check_name[25];
    int unique_name;

    while (1)
    {
        printf("Enter user name(no spaces): ");
        scanf("%s", name);
        unique_name = 1;
        while ((fscanf(fp, "%s", check_name)) != EOF) // this will check name till end of the file
        {
            if (strcmp(name, check_name) == 0) // if user name matches with file name or not
            {
                unique_name = 0;
                break;
            }
        }
        if (unique_name == 0)
        {
            printf("Name already taken\n\n");
            rewind(fp);
        }
        else
        {
            printf("Account has been created!");
            fprintf(fp, "%s ", name); // writing name to the file
            break;
        }
    }

    float money;
    printf("\nEnter how much money do you want to deposit (max Rs.10k): ");
    scanf("%f", &money);
    fprintf(fp, "%0.2f\n", money); // writing money to the file

    fclose(fp);
    return money; // returning money to use that in other functions
}

float old_member(char name[])
{
    FILE *fp = fopen("Data.txt", "r");
    char check_name[25], balance[10];
    printf("Enter user name(no spaces): ");
    scanf("%s", name);
    int name_found = 0;

    while ((fscanf(fp, "%s", check_name)) != EOF)
    {
        if (strcmp(name, check_name) == 0) // checking if entered user name is correct or not
        {
            name_found = 1;
            break;
        }
    }
    if (name_found == 0)
    {
        printf("User name not found!\n");
        printf("\nDo you want to create one\n");
        int choice;
        printf("Enter 1 to create new account\n");
        printf("Enter 2 to exit\n");
        printf("Enter: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            float money = add_new_member(name);
            return money;
        }
    }
    else
    {
        // Displaying details of the user if name is found in the file
        printf("\nUser name: %s\t", name);
        fscanf(fp, "%s", balance);
        float money = atoi(balance); // converting money to integer
        printf("Balance: Rs.%s\n", balance);

        return money; // returning money so we can use that in other function
    }
    fclose(fp);
    return 0;
}

int Random_Number()
{ // This function will return a random number
    int maximum_number = 6, minimum_number = 1;
    srand(time(NULL)); // to get a different number every time
    int number;
    number = rand();
    number = number % (maximum_number - minimum_number + 1) + minimum_number; // For a desired range
    return number;
}

void Odd_Even(float *balance)
{
    float bet;
    int choice;
    int number;

    while (1)
    {
        number = Random_Number();

        printf("\nEnter 1 for odd");
        printf("\nEnter 2 for even");
        printf("\nEnter 3 to quit");

        printf("\nEnter: ");
        scanf("%d", &choice);

        if (choice == 3)
        {
            break;
        }

        if (choice != 1 && choice != 2 && choice != 3)
        {
            printf("Wrong choice\n");
        }
        else
        {
            if (*balance == 0)
            {
                break;
            }

            printf("\nEnter your bet: ");
            scanf("%f", &bet);

            if (!(bet > *balance))     // if bet amount is not greater than the account balance
            {
                printf("\nNumber is: %d ", number);
                if (number % 2 == 0)
                {
                    printf("(Even)");
                }
                else
                {
                    printf("(Odd)");
                }

                if ((number == 1 || number == 3 || number == 5) && choice == 1)
                {
                    printf("\nYou won\n");
                    *balance = *balance - bet + bet * 2;
                    printf("New balance: %0.2f\n", *balance);
                }
                else if ((number == 2 || number == 4 || number == 6) && choice == 2)
                {
                    printf("\nYou won\n");
                    *balance = *balance - bet + bet * 2;
                    printf("New balance: %0.2f\n", *balance);
                }
                else
                {
                    printf("\nYou loose\n");
                    *balance = *balance - bet;
                    printf("New balance: %0.2f\n", *balance);
                }
            }
            else
            {
                printf("Insufficient balance\n");
            }
        }
    }
}

void Update_Balance(float *new_balance, char name[])
{ // Copying all data to temp.txt except the user name who played game
    char copy_data[25];
    FILE *fp = fopen("Data.txt", "r");
    FILE *fs = fopen("Temp.txt", "w");
    while ((fscanf(fp, "%s", copy_data)) != EOF)
    {

        if (strcmp(copy_data, name) == 0) // if user name is found in data.txt
        {                                 // copying his name and updated balance to temp.txt
            fprintf(fs, "%s ", copy_data);
            fscanf(fp, "%s", copy_data);
            fprintf(fs, "%0.2f\n", *new_balance);
        }
        else
        {
            fprintf(fs, "%s ", copy_data);
            fscanf(fp, "%s", copy_data);
            fprintf(fs, "%s\n", copy_data);
        }
    }
    fclose(fp);
    fclose(fs);

    // Copying everything from temp.txt to data.txt
    fp = fopen("Data.txt", "w"); // write mode will clear everying in data.txt and overwrite with updated data
    fs = fopen("Temp.txt", "r");
    char ch;
    while ((ch = fgetc(fs)) != EOF)
    {
        fputc(ch, fp);
    }
    fclose(fp);
    fclose(fs);
}

int main()
{

    char new_old_choice;
    float account_balance;
    char name[25];
    char rules_choice;
label:
    printf("Enter 1 to know the rules\n");
    printf("Enter 2 to continue\n");
    printf("Enter: ");

    scanf("%c", &rules_choice);
    fflush(stdin);

    if (rules_choice != '1' && rules_choice != '2')
    {
        printf("Wrong choice\n\n");
        goto label;
    }

    if (rules_choice == '1')
    {
        printf("This is a number guessing betting game\n");
        printf("If you select odd and number is 1, 3 or 5. You'll get 2X of your bet\n");
        printf("If you select lower and number is 2, 4 or 6. You'll get 2X of your bet\n");
        printf("Otherwise you will loose\n");
    }

    while (1)
    {
        printf("\nEnter 1 if you have already a acount");
        printf("\nEnter 2 if you are new\n");
        printf("\nEnter: ");

        scanf("%c", &new_old_choice);
        fflush(stdin);

        if (new_old_choice == '2')
        {
            account_balance = add_new_member(name); // Adding new memnber to file
            break;
        }
        else if (new_old_choice == '1')
        {
            account_balance = old_member(name);
            break;
        }
        else
            printf("Wrong choice\n");
    }

    if (account_balance != 0)
    {
        char game_choice;
    label2:
        printf("\nEnter 1 to play Odd-Even");
        printf("\nEnter 2 to exit");
        printf("\nEnter: ");
        scanf("%c", &game_choice);
        fflush(stdin);

        if (game_choice != '1' && game_choice != '2')
        {
            printf("Wrong choice\n");
            goto label2;
        }
        if (game_choice == '1')
        {
            Odd_Even(&account_balance);             // Sending address of balance so it will changes in main also
            Update_Balance(&account_balance, name); // This function will update balance in file of user
        }
    }
    return 0;
}
