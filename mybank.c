#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int i, j;
int main_exit;
void main();
void close();
struct date
{
    int month, day, year;
};
struct
{
    char name[60];
    int acc_no, age;
    char acc_type[10];
    float amt;
    struct date deposit;
    struct date withdraw;
} add, check, rem, transaction;

float interest(float t, float amount, int rate)
{
    float SI;
    SI = (rate * t * amount) / 100.0;
    return (SI);
}
void new_acc()
{
    int choice;
    FILE *ptr;
    ptr = fopen("record.txt", "a+");
    printf(" ADD RECORD  ");
    printf("\n\n\nEnter today's date(dd/mm/yyyy):");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
account_no:
    printf("\nEnter the account number:");
    scanf("%d", &check.acc_no);
    while (fscanf(ptr, "%d %s %d %s %f %d/%d/%d\n", &add.acc_no, add.name, &add.age, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (check.acc_no == add.acc_no)
        {
            printf("Account no. already in use");
            goto account_no;
        }
    }
    add.acc_no = check.acc_no;
    printf("\nEnter the name:");
    scanf("%s", add.name);
    printf("\nEnter the age:");
    scanf("%d", &add.age);
    printf("\nEnter the amount to deposit/* :$");
    scanf("%f", &add.amt);
    printf("\nType of account:\n1.Saving\n2.Current\n\n\tEnter your choice:");
    scanf("%s", add.acc_type);
    fprintf(ptr, "%d %s %d %s %f %d/%d/%d\n", add.acc_no, add.name, add.age, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
    fclose(ptr);
    printf("\nAccount created successfully!");
add_invalid:
    printf("\n\n\nEnter 1 to go to the main main and 0 to exit:");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        main();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
void view_list()
{
    FILE *view;
    view = fopen("record.txt", "r");
    int temp = 0;
    printf("\nACC. NO.\tNAME\t\t\tADDRESS\t\t\tPHONE\n");
    while (fscanf(view, "%d %s %d %s %f %d/%d/%d", &add.acc_no, add.name, &add.age, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        printf("\n%6d\t %10s", add.acc_no, add.name);
        temp++;
    }
    fclose(view);
    if (temp == 0)
    {
        printf("\nNO RECORDS!!\n");
    }
view_list_invalid:
    printf("\n\nEnter 1 to go to the main main and 0 to exit:");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        main();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto view_list_invalid;
    }
}
void transact()
{
    int choice, temp = 0;
    FILE *old, *new;
    old = fopen("record.txt", "r");
    new = fopen("new.txt", "w");
    printf("Enter the account no. of the customer:");
    scanf("%d", &transaction.acc_no);
    while (fscanf(old, "%d %s %d %s %f %d/%d/%d", &add.acc_no, add.name, &add.age, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {

        if (add.acc_no == transaction.acc_no)
        {
            temp = 1;
            printf("\n\nDo you want to\n1.Deposit\n2.Withdraw\n\nEnter your choice 1 for deposit and 2 for withdraw):");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter the amount you want to deposit: ");
                scanf("%f", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(new, "%d %s %d %s %f %d/%d/%d\n", add.acc_no, add.name, add.age, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nDeposited successfully!");
            }
            else
            {
                printf("Enter the amount you want to withdraw:$ ");
                scanf("%f", &transaction.amt);
                add.amt -= transaction.amt;
                fprintf(new, "%d %s %d %s %f %d/%d/%d\n", add.acc_no, add.name, add.age, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(new, "%d %s %d  %s %f %d/%d/%d\n", add.acc_no, add.name, add.age, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(new);
    remove("record.txt");
    rename("new.txt", "record.txt");
    if (temp != 1)
    {
        printf("\n\nRecord not found!!");
    transact_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to main main and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            transact();
        else if (main_exit == 1)
            main();
        else if (main_exit == 2)
            close();
        else
        {
            printf("\nInvalid!");
            goto transact_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main main and 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            main();
        else
            close();
    }
}
void erase()
{
    FILE *old, *new;
    int temp = 0;
    old = fopen("record.txt", "r");
    new = fopen("new.txt", "w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf("%d", &rem.acc_no);
    while (fscanf(old, "%d %s %d %s %f %d/%d/%d", &add.acc_no, add.name, &add.age, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (add.acc_no != rem.acc_no)
            fprintf(new, "%d %s %d  %s %f %d/%d/%d\n", add.acc_no, add.name, add.age, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        else
        {
            temp++;
            printf("\nRecord deleted successfully!\n");
        }
    }
    fclose(old);
    fclose(new);
    remove("record.txt");
    rename("new.txt", "record.txt");
    if (temp == 0)
    {
        printf("\nRecord not found!!\a\a\a");
    erase_invalid:
        printf("\nEnter 0 to try again,1 to return to main main and 2 to exit:");
        scanf("%d", &main_exit);

        if (main_exit == 1)
            main();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            erase();
        else
        {
            printf("\nInvalid!\a");
            goto erase_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main main and 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            main();
        else
            close();
    }
}

void see()
{
    FILE *ptr;
    int temp = 0, rate;
    float time;
    float intrst;
    ptr = fopen("record.txt", "r");
    printf("Enter the account number:");
    scanf("%d", &check.acc_no);
    while (fscanf(ptr, "%d %s %d %s %f %d/%d/%d", &add.acc_no, add.name, &add.age, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (add.acc_no == check.acc_no)
        {
            temp = 1;
            printf("\nAccount NO.:%d\nName:%s \nAge:%d \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\n\n", add.acc_no, add.name, add.age, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            if (strcmpi(add.acc_type, "saving") == 0)
            {
                time = (1.0 / 12.0);
                rate = 8;
                intrst = interest(time, add.amt, rate);
                printf("\n\nYou will get $.%.2f as interest on %d of every month", intrst, add.deposit.day);
            }
            else if (strcmpi(add.acc_type, "current") == 0)
            {

                printf("\n\nYou will get no interest\a\a");
            }
        }
    }
    fclose(ptr);
    if (temp != 1)
    {
        printf("\nRecord not found!!\n");
    see_invalid:
        printf("\nEnter 0 to try again,1 to return to main main and 2 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            main();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            see();
        else
        {
            printf("\nInvalid!\a");
            goto see_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main main and 0 to exit:");
        scanf("%d", &main_exit);
    }
    if (main_exit == 1)
    {
        main();
    }

    else
    {
        close();
    }
}
void close(void)
{
    printf("\n\n\n\nThanks for visiting....");
}

void main()
{
    int choice;
    printf("Welcome to my Bank...:)\n");
    printf("\n\n1.Create new account\n2.For transactions\n3.Check the details of existing account\n4.Removing existing account\n5.View customer's list\n6.Exit\n\n\n\nEnter your choice:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        new_acc();
        break;
    case 2:
        transact();
        break;
    case 3:
        see();
        break;
    case 4:
        erase();
        break;
    case 5:
        view_list();
        break;
    case 6:
        close();
        break;
    }
}