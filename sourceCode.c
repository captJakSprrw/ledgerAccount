#include <stdio.h>

int keepermenu();
void customerinterface();


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
                
                break;
            case 2:
                break;
            case 3:
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