#include <stdio.h>
#include <string.h>

int keepermenu();
void customerinterface();
void oldcustomer();
int customermenu();
void logoprinter();
void welcome();
int login();
int authenticate();
void forgotpass();
int getid();
void addcustomer();
void newentry(int);
void viewhistory(int);
int balance(int);
void editcredential(int);
void printhistory();
void printdatabase();

struct chunk
{
    int len;
    char original[15];
};

struct idstruct
{
    int id;
    char credential[15];
};

struct custinfo
{
        int id;
        char name[30];
        char address[50];
        char email[30];
        char number[15];
};

struct transaction
{
        char date[10];
        int amount;
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

int getid()
{
        int cond = 1;
        int id;
        struct idstruct temp;
        char inputcred[15];
        printf("Enter mobile number : ");
        scanf(" %s", inputcred);
        inputcred[strcspn(inputcred, "\n")] = 0;
        FILE * f1 = fopen("id", "r");
        while((fread(&temp, sizeof(struct idstruct), 1, f1) == 1) && (cond == 1))
        {
                int i;
                for(int i = 0; (inputcred[i] != '\0' && temp.credential[i] != '\0'); i++)
                {
                        if(inputcred[i] != temp.credential[i])
                        {
                                id = 0;
                                cond = 1;
                                break;
                        }
                        cond = 0;
                        id = temp.id;
                }
        }
        fclose(f1);
        return id;
}

void addcustomer()
{
        struct chunk idinfo, temp;
        struct idstruct newid;
        FILE * f1 = fopen("info", "r");
        fseek(f1, sizeof(struct chunk), SEEK_SET);
        fread(&idinfo, sizeof(struct chunk), 1, f1);
        fclose(f1);
        FILE * f2 = fopen("id", "a");
        newid.id = (idinfo.len + 1);
        printf("Enter mobile number to add : ");
        scanf(" %s", newid.credential);
        newid.credential[strcspn(newid.credential, "\n")] = 0;
        fwrite(&newid, sizeof(struct idstruct), 1, f2);
        fclose(f2);
        FILE * f3 = fopen("copy", "a");
        f1 = fopen("info", "r");
        fread(&temp, sizeof(struct chunk), 1, f1);
        fwrite(&temp, sizeof(struct chunk), 1, f3);
        fseek(f3, sizeof(struct chunk), SEEK_CUR);
        struct chunk temp2 = {newid.id, "linuxisbetter"};
        fwrite(&temp2, sizeof(struct chunk), 1, f3);
        fclose(f1);
        fclose(f3);
        remove("info");
        rename("copy", "info");
        struct custinfo newinfo;
        int j;
        for(j = 0; newid.credential[j] != '\0'; j++)
        {
                newinfo.number[j] = newid.credential[j];
        }
        newinfo.id = newid.id;
        printf("Enter Name : ");
        scanf(" %[^\n]s", newinfo.name);
        printf("Enter email address : ");
        scanf(" %s", newinfo.email);
        printf("Enter address : ");
        scanf(" %[^\n]s", newinfo.address);
        char filename[10];
        sprintf(filename, "%d", newinfo.id);
        FILE * f4 = fopen(filename, "w");
        fwrite(&newinfo, sizeof(struct custinfo), 1, f4);
        fclose(f4); 
}

void newentry(int id)
{
        struct transaction newtransact;
        struct custinfo customer;
        printf("Enter date : ");
        scanf(" %[^\n]s", newtransact.date);
        printf("Enter amount : ");
        scanf("%d", &newtransact.amount);
        char filename[10]; 
        sprintf(filename, "%d", id);
        FILE * f1 = fopen(filename, "a");   
        fwrite(&newtransact, sizeof(struct transaction), 1, f1);
        fclose(f1);
}

void viewhistory(int id)
{
        struct custinfo info;
        struct transaction hist;
        char filename[10];
        sprintf(filename, "%d", id);
        FILE * f1 = fopen(filename, "r");
        fread(&info, sizeof(struct custinfo), 1, f1);
        printf("%d\n", info.id);
        printf("%s\n", info.name);
        printf("%s\n", info.number);
        printf("%s\n", info.email);
        printf("%s\n", info.address);
        printf("---------------------------\n");
        printf("Date : Amount\n");
        printf("----------------------------\n");
        while(fread(&hist, sizeof(struct transaction), 1, f1))
        {
                printf("%s\n", hist.date);
                printf("%d\n\n", hist.amount);
        }
}

int balance(int id)
{
        int sum = 0;
        struct transaction hist;
        char filename[10];
        sprintf(filename, "%d", id);
        FILE * f1 = fopen(filename, "r");
        fseek(f1, sizeof(struct custinfo), SEEK_SET);
        while(fread(&hist, sizeof(struct transaction), 1, f1))
        {
                sum += (hist.amount);
        }
        printf("The net balance is : %d\n", sum);
}

void editcredential(int id)
{
	int response, i;
	char filename[10];
        sprintf(filename, "%d", id);
        FILE * f1 = fopen(filename, "r");
	FILE * f2 = fopen("infocp", "w");
	struct custinfo curr;
	struct transaction temp;
	fread(&curr, sizeof(struct custinfo), 1, f1);
	printf("Name : %s\nemail : %s\naddress : %s\nMobile No. : %s\n", curr.name, curr.email, curr.address, curr.number);
	printf("Press :\n1. To change name\n2. To change email address\n3. To change address\n4. To return to customer menu.\n");
	scanf("%d", &response);
	switch(response)
	{
		case 1:
			printf("New name : ");
			scanf(" %[^\n]s", curr.name);
			break;
		case 2:
			printf("New email : ");
                        scanf(" %[^\n]s", curr.email);
			break;
		case 3:
			printf("New address : ");
                        scanf(" %[^\n]s", curr.address);
			break;
	}
	fwrite(&curr, sizeof(struct custinfo), 1, f2);
	while(fread(&temp, sizeof(struct transaction), 1, f1))
	{
		fwrite(&temp, sizeof(struct transaction), 1, f2);
		fseek(f2, sizeof(struct transaction), SEEK_CUR);
	}
	fclose(f1);
	fclose(f2);
	remove(filename);
	rename("infocp", filename);
}

void printhistory()
{
	printf("will be available soon\n");
}

void printdatabase()
{
	printf("will be available soon\n");
}
