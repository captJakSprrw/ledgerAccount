#include <stdio.h>

int keepermenu();
void customerinterface();
void oldcustomer();
int customermenu();
void logoprinter();
void welcome();
int login();


int main()
{
    logoprinter();
    welcome();
    if(login())
    {
        int cond = 1;
        while(cond)
        {
            switch(keepermenu())
            {
                case 1:
                    customerinterface();
                    break;
                case 2:
                    printhistory();
                    break;
                case 3:
                    printdatabase();
                    break;
                case 4:
                    cond = 0;
                    break;
            }
        }
    }
}

void customerinterface()
{
    int cond = 1;
    while(cond)
    {
        printf("Press: \n1. For old customer.\n2. To add new customer.\n3. To return back to main menu.\n ");
        int response;
        scanf("%d", &response);
        switch(response)
        {
            case 1:
                oldcustomer();
                break;
            case 2:
                addcustomer();
                break;
            case 3:
                cond = 0;
                break;
        }
    }
}

void oldcustomer()
{
    int cond = 1;
    int id = getid();
    int response;
    if (id == 0)
    {
        printf("-----New User-------\n");
        printf("Press:\n1. To add new user\n 2. Return to customer menu.\n");
        scanf("%d", &response);
        if(response == 1)
        {
            addcustomer();
        }
        cond = 0;
    }
    while(cond)
    {
        switch(customermenu())
        {
            case 1:
                newentry(id);
                break;
            case 2:
                viewhistory(id);
                break;
            case 3:
                balance(id);
                break;
            case 4:
                editcredential(id);
                break;
            case 5:
                cond = 0;
                break;
        }
    }
}

int keepermenu()
{
    int response;
    printf("Press: \n\n1. For customer menu.\n2. To print transcation history.\n3. To print all the customer's details.\n4. Quit.\n");
    scanf("%d", &response);
    return response;
}

int customermenu()
{
    int response;
    printf("Press: \n1. Enter new transaction entry.\n2. View older transactions\n3. View net balance\n4. Edit credentials\n5. Return to customer menu\n.");
    scanf("%d", &response);
    return response;
}

void logoprinter()
{
    printf(" ___________\n");
    printf("|***********|\n");
    printf("|***********|\n");
    printf("|---RecBo---|\n");
    printf("|***********|\n");
    printf("|***********|\n");
    printf("|___________|\n");
}

void welcome()
{
    printf("Welcome to RecBo, a digital ledger.\n");
}

int login()
{
    
}