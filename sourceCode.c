#include <stdio.h>

int keepermenu();
void customerinterface();
void oldcustomer();
int customermenu();


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
    while(cond)
    {
        //get customer id from the database to interact with it.
        switch (customermenu())
        {
            case 1:
                newentry();
                break;
            case 2:
                viewhistory();
                break;
            case 3:
                balance();
                break;
            case 4:
                editcredential();
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