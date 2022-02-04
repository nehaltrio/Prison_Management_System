#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

void login();
void addrecord();
void viewrecord();
void searchrecord();
void deleterecord();

struct record
{
    char id[10];
    char name[30];
    char age[10];
    char gender[10];
    char crime[40];
    char punishment[50];
} a;

void login()
{
    char user[10];
    char pass[10];
    int i,a=0 ;

    do
    {
        printf("\n  **************************  LOGIN FORM  **************************  ");
        printf(" \n                       ENTER USERNAME:-");
        scanf("%s", user);
        printf(" \n                       ENTER PASSWORD:-");

        for(i=0; i<4; i++)
        {
            pass[i] = getch();
            printf("*");
        }

        pass[i] = '\0';

        if((strcmpi(pass, "pass") == 0) && (strcmp(user, "user") == 0))
        {
            printf("  \n\n\nWELCOME TO PRISON MANAGEMENT SYSTEM !!");
            printf("\n\n\n\t\t\t\tPress any key to continue...");
            getch();
            break;
        }
        else
            printf("\n SORRY !!!!  LOGIN IS UNSUCESSFUL");
        printf("\n PRESS ANY KEY TO TRY AGAIN!!");
        a++;
        getch();
    }
    while(a);
}

void addrecord()
{
    system("cls");
    FILE *fp ;
    char another='Y',id[10];
    int choice;

    printf("\n\n\t\t***************************\n");
    printf("\t\t* WELCOME TO THE ADD MENU *");
    printf("\n\t\t***************************\n\n");

    fp = fopen ("file", "ab+" ) ;

    if ( fp == NULL )
    {
        fp=fopen("file","wb+");
        if(fp==NULL)
        {
            printf("\nSYSTEM ERROR...");
            printf("\nPRESS ANY KEY TO EXIT");
            getch();
            return ;
        }
    }

    while ( another == 'Y'|| another=='y' )

    {
        choice=0;
        fflush(stdin);

        printf ( "\n\tENTER PRISONER ID:\t");
        scanf("%s",id);

        rewind(fp);

        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(strcmp(a.id,id)==0)
            {
                printf("\n\tTHE RECORD ALREADY EXISTS.\n");
                choice=1;
            }
        }

        if(choice==0)
        {
            strcpy(a.id,id);

            printf("\tENTER PRISONER NAME: ");
            fflush(stdin);
            gets(a.name);

            printf("\tENTER GENDER: ");
            gets(a.gender);
            fflush(stdin);

            printf("\tENTER AGE: ");
            gets(a.age);
            fflush(stdin);

            printf("\tENTER CRIME: ");
            gets(a.crime);
            fflush(stdin);

            printf("\tENTER PUNISHMENT: ");
            gets(a.punishment);
            fflush(stdin);

            fwrite ( &a, sizeof ( a ), 1, fp ) ;
            printf("\nYOUR RECORD IS ADDED...\n");
        }

        printf ( "\n\tADD ANOTHER RECORD...(Y/N) \t" ) ;
        fflush ( stdin ) ;
        another = getch( ) ;
    }

    fclose ( fp ) ;
    printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();
}

void searchrecord()
{
    system("cls");
    FILE *fp ;
    char id[10],choice;
    int ch;

    printf("\n\n\t\t*******************************\n");
    printf("\t\t\t* SEARCH MENU *");
    printf("\n\t\t*******************************\n\n");

    do
    {
        fflush(stdin);
        fp = fopen ( "file", "rb" ) ;
        printf("\nENTER PRISONER ID:");
        gets(id);
        system("cls");

        while ( fread ( &a, sizeof ( a ), 1, fp ) == 1 )


            if(strcmpi(a.id,id)==0)
            {
                printf("\nTHE WHOLE RECORD OF ID - %s IS:",id);
                printf("\n");
                printf("\nPRISONER'S NAME IS: %s",a.name);
                printf("\nPRISONER'S GENDER IS: %s",a.gender);
                printf("\nPRISONER'S AGE IS: %s",a.age);
                printf("\nPRISONER'S CRIME IS: %s",a.crime);
                printf("\nPRISONER'S PUNISHMENT IS: %s",a.punishment);
                printf("\n");
                break;

            }

        if(strcmpi(a.id,id)!=0)
        {
            printf("\n\nSORRY!! ID - %s DOSEN'T EXIST!!!",id);
        }
        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N):");
        fflush(stdin);
        scanf("%c",&choice);
    }
    while(choice=='Y'||choice=='y');
    fclose (fp) ;
    getch();
}

void viewrecord()
{
    system("cls");
    FILE *fp;

    printf("\n\n\t\t***************************\n");
    printf("\t\t   * LIST OF PRISONERS *");
    printf("\n\t\t***************************\n\n");

    fp=fopen("file","rb");
    rewind(fp);
    while((fread(&a,sizeof(a),1,fp))==1)
    {
        printf("||NOTE:-PRESS ENTER KEY TO LOAD OTHER RECORDS||\n");
        printf("\nPRISONER'S ID: %s",a.id);
        printf("\nPRISONER'S NAME IS: %s",a.name);
        printf("\nPRISONER'S GENDER IS: %s",a.gender);
        printf("\nPRISONER'S AGE IS: %s",a.age);
        printf("\nPRISONER'S CRIME IS: %s",a.crime);
        printf("\nPRISONER'S PUNISHMENT IS: %s",a.punishment);

        getch();
        printf("\n\n");
    }
    fclose(fp);
    getch();
}

void deleterecord( )
{
    system("cls");
    FILE *fp,*ft ;
    char another = 'Y',id[16];;
    int choice,check;
    char pass[8];

    printf("\n\n\t\t*************************\n");
    printf("\t\t* WELCOME TO DELETE MENU*");
    printf("\n\t\t*************************\n\n");

    printf("\nENTER PASSWORD\n");
    int i;
    for(  i=0; i<4; i++)
    {
        pass[i]=getch();
        printf("*");
    }
    pass[i]='\0';
    if (strcmpi(pass,"pass")==0)
    {
        printf("\n\t\t*ACCESS GRANTED*\n\n");
        while ( another == 'Y' || another == 'y' )
        {
            fflush(stdin);
            fp = fopen ("file", "rb" ) ;
            if ( fp == NULL )
            {
                printf("\nTHE FILE DOES NOT EXIST");
                printf("\nPRESS ANY KEY TO GO BACK.");
                getch();
                return ;
            }
            ft = fopen ("temp","wb");

            if(ft==NULL)
            {
                printf("\nSYSTEM ERROR");
                printf("\nPRESS ANY KEY TO GO BACK");
                getch();
                return ;
            }
            printf("\n\tENTER THE ID OF RECORD TO BE DELETED:");
            fflush(stdin);
            gets(id);

            while(fread(&a,sizeof(a),1,fp)==1)

            {
                if(strcmp(a.id,id)!=0)
                    fwrite(&a,sizeof(a),1,ft);
            }
            fclose(ft);
            fclose(fp);
            remove("file");
            rename("temp","file");
            printf("\nDELETED SUCCESFULLY...");
            getch();

            printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");
            fflush(stdin);
            scanf("%c",&another);
        }
        printf("\n\n\tPRESS ANY KEY TO EXIT...");

        getch();
    }
    else
    {
        printf("\nSorry!Invalid password\n");
        exit(0);
    }
}

int main()
{
    login();
    int ch;


    while(1)
    {
        printf("\n\n\t\t***********************************\n");
        printf("\t\t\t*PRISONER RECORD*\n");
        printf("\t\t***********************************");
        printf("\n\n\t\t\t\tMAIN MENU:");
        printf("\n\n\t\t\tADD RECORD\t[1]");
        printf("\n\t\t\tSEARCH RECORD\t[2]");
        printf("\n\t\t\tVIEW RECORD\t[3]");
        printf("\n\t\t\tDELETE RECORD\t[4]");
        printf("\n\t\t\tEXIT\t\t[5]");
        printf("\n\n\t\t\tENTER YOUR CHOICE:");
        scanf("%d",&ch);

        switch(ch)
        {
        case 1:
            addrecord();
            break;

        case 2:
            searchrecord();
            break;

        case 3:
            viewrecord();
            break;

        case 4:
            deleterecord();
            break;

        case 5:
            system("cls");
            printf("\n\n\t\tHAVE A GOOD DAY!!");
            getch();
            exit(0);

        default:
            printf("\nYOU ENTERED WRONG CHOICE.");
            printf("\nPRESS ANY KEY TO TRY AGAIN");
            getch();
            break;
        }
        system("cls");
    }
}
