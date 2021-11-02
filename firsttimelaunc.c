#include <stdio.h>

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

int main()
{
	struct chunk pass = {8, "password"}, total = {1, "linuxisbetter"};
	struct idstruct mob = {1, "9953281985"};
	FILE *f1 = fopen("info", "w");
	fwrite(&pass, sizeof(struct chunk), 1, f1);
	fwrite(&total, sizeof(struct chunk), 1, f1);
	fclose(f1);
	FILE *f2 = fopen("id", "w");
	fwrite(&mob, sizeof(struct idstruct), 1, f2);
	fclose(f2);
}
