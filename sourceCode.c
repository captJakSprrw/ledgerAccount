#include <stdio.h>

int keepermenu();
void customerinterface();
void oldcustomer();
int customermenu();
void logoprinter();
void welcome();
int login();
int authenticate();
void forgotpass();

struct chunk
{
    int len;
    char original[15];
};

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

int authenticate()
{
    int returnval, i, trial = 1;
    int cond = 1;
    char buffer[15];
    char dev[15] = "captJakSprrw";
    while(cond)
    {
        printf("who is the developer of ReBo?\n");
        scanf(" %s", buffer);
        for(i = 0; ((buffer[i] != '\0') || (dev[i] != '\0')); i++)
        {
            if(buffer[i] != dev[i])
            {
                if(trial == 3)
                {
                    returnval = 0;
                    cond = 0;
                    break;
                }
                trial++;
                break;
            }
            returnval = 1;
            cond = 0;
        }
    }
    return returnval;
}

void forgotpass()
{
    if(authenticate())
    {
        struct chunk originalc;
        char buffer[15], confirmbuffer[15], temp;
        int i,cond = 1;
        while(cond)
        {
            int k;
            printf("Enter New Password:\n");
            scanf(" %c", &temp);
            for(i = 0; (i < 16 && temp != '\n'); i++)
            {
                buffer[i] = temp;
                scanf("%c", &temp);
            }
            printf("Confirm Password:\n");
            scanf(" %c", &temp);
            for(k = 0; (k < 16 && temp != '\n'); k++)
            {
                confirmbuffer[k] = temp;
                scanf("%c", &temp);
            }
            if(k == i)
            {
                int j;
                for(j = 0; j < i; j++)
                {
                    if(confirmbuffer[j] != buffer[j])
                    {
                        cond = 1;
                        printf("Did not match\n");
                        break;
                    }
                    originalc.original[j] = buffer[j];
                    cond = 0;
                }
            }
            else
            {
                printf("Did not match\n");
            }
        }
        originalc.len = i;
        FILE * fi = fopen("info", "w");
        fwrite(&originalc, sizeof(struct chunk), 1, fi);
        fclose(fi);
        printf("Password changed\nPlease log in again.\n");
    }
}

int login()
{
    int returnval;
    char buffer[15], temp;
    int cond = 1, valid;
    struct chunk info;
    while(cond)
    {
        FILE * f1 = fopen("info", "r");
        fread(&info, sizeof(struct chunk), 1, f1);
        fclose(f1);
        int i, response;
        printf("Enter Password:\n");
        scanf(" %c", &temp);
        for(i = 0; (i < 16 && temp != '\n'); i++)
        {
            buffer[i] = temp;
            scanf("%c", &temp);
        }
        if(info.len == i)
        {
            int j;
            for(j = 0; j < i; j++)
            {
                if(info.original[j] != buffer[j])
                {
                    cond = 1;
                    printf("incorrect password\n");
                    printf("Press \n1. If forgot password\n2. To retry\n3.Quit\n");
                    scanf("%d", &response);
                    if(response == 1)
                    {
                        forgotpass();
                        response = 0;
                    }
                    else if(response == 3)
                    {
                        returnval = 0;
                        cond = 0;
                    }
                    break;
                }
                cond = 0;
                returnval = 1;
            }
        }
        else
        {
            printf("incorrect password\n");
            printf("Press \n1. If forgot password\n2. To retry\n3.Quit\n");
            scanf("%d", &response);
            if(response == 1)
            {
                forgotpass();
                response = 0;
            }
            else if(response == 3)
            {
                returnval = 0;
                cond = 0;
            }
        }
    }
    return returnval;
}

