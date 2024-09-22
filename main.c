#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <limits.h>

struct Tech
{
    int number;
    char type[255];
    char breakdown[255];
    char master[255];
    char date[255];
    int price;
    struct Tech * next;
}buf;

typedef struct Tech Tech;
void StartApp();
void AddElement(Tech *head);
void RemoveElement(Tech *head);
void ChangeElement(Tech *head);
void GetAll(Tech *head);
void BreakdownByType(Tech *head);
void PriceByDate(Tech *head);
void SortByPrice(Tech *head);
void GetByMaster(Tech *head);
void SaveAndExit(Tech *head);
struct Tech *head;

int main()
{
     SetConsoleCP(1251);
     SetConsoleOutputCP(1251);

     head=(struct Tech*)malloc(sizeof(struct Tech));
     head->next=NULL;
     StartApp();

     printf("====================================================\n");
     printf("|        ������� ������                            |\n");
     printf("|        �����: ѳ����� ����� ��������             |\n");
     printf("|        �����: ��-224                             |\n");
     printf("====================================================\n");
     printf("\n");

     int commander;
     while(1)
     {
         puts("������ ��� ������ 䳿:");
         puts("1 - ��������� ��������");
         puts("2 - ��������� ��������");
         puts("3 - ����������� �����");
         puts("4 - ��������� ��� �����");
         puts("5 - ��������� ������������� �� ������� ����� ������");
         puts("6 - ���������� ������� ��������� ������� �� ������ ����");
         puts("7 - ���������� �� ���� �������� �������");
         puts("8 - ����� ��� ��������� �� �������� �������");
         puts("0 - �������� �� �����");
         scanf("%i", &commander);

         switch(commander)
         {
             case 1: AddElement(head); break;
             case 2: RemoveElement(head); break;
             case 3: ChangeElement(head); break;
             case 4: GetAll(head); break;
             case 5: BreakdownByType(head); break;
             case 6: PriceByDate(head); break;
             case 7: SortByPrice(head); break;
             case 8: GetByMaster(head); break;
             case 0: SaveAndExit(head);break;
         }
     }
}

void StartApp()
{
    struct Tech *element, *temp;

    FILE *file;
    file = fopen("mainfile.txt", "r");
    if(!file)
    {
        printf("���� �� ��������!\n");
        exit(1);
    }

    while(fread(&buf, sizeof(buf), 1, file))
    {
        element=(struct Tech*)malloc(sizeof(struct Tech));

        element->number=buf.number;
        strcpy(element->type, buf.type);
        strcpy(element->breakdown, buf.breakdown);
        strcpy(element->master, buf.master);
        strcpy(element->date, buf.date);
        element->price=buf.price;

        temp=head->next;
        head->next=element;
        element->next=temp;
    }

    fclose(file);
    return 0;
}

void AddElement(Tech *head)
{
    struct Tech *element, *temp;
    element=(struct Tech*)malloc(sizeof(struct Tech));
    printf("�������� ��������:\n");
    printf("����� ���������� | ��� ������ | ����������� | ������� ������� | ���� ������� | ֳ��\n");
    scanf("%i%s%s%s%s%i", &element->number, element->type, element->breakdown, element->master, element->date, &element->price);

    temp=head->next;
    head->next=element;
    element->next=temp;

    printf("������� ������ ������!\n");
    return 0;
}

void RemoveElement(Tech *head)
{
    struct Tech *element, *temp;
    element=head;

    int number;
    printf("������ ����� ����������� ��������: ");
    scanf("%i", &number);

    while(element!=NULL)
    {
        if(element->next->number==number)
        {
            temp=element->next;
            free(element->next);
            element->next=temp->next;

            printf("������� ������ ��������!\n");
            break;
        }
        else
        {
            element=element->next;
        }
    }

    return 0;
}

void ChangeElement(Tech *head)
{
    struct Tech *element;
    element=head->next;

    int number;
    printf("������ ����� ��������, ���� ������ ������: ");
    scanf("%i", &number);

    while(element!=NULL)
    {
        if(element->number==number)
        {
            printf("����������� �����:\n");
            printf("��� ������ | ����������� | ������� ������� | ���� ������� | ֳ��\n");
            scanf("%s%s%s%s%i", element->type, element->breakdown, element->master, element->date, &element->price);

            printf("������� ������ ������!\n");
            break;
        }
        else
        {
            element=element->next;
        }
    }

    return 0;
}

void GetAll(Tech *head)
{
    struct Tech *element;
    element=head->next;

    while(element!=NULL)
    {
        printf("%i | ��� ������: %s | �����������: %s | ������� �������: %s | ���� �������: %s | ֳ��: %i\n", element->number, element->type, element->breakdown, element->master, element->date, element->price);
        element=element->next;
    }

    return 0;
}

void BreakdownByType(Tech *head)
{
    struct Tech *element;
    element=head->next;

    char type[255];
    printf("������ ��� ������: ");
    scanf("%s", &type);

    printf("����������� �� ������� ����� ������:\n");
    while(element!=NULL)
    {
        if(!strcmp(element->type, type))
        {
            printf("%s\n", element->breakdown);
        }
        element=element->next;
    }

    return 0;
}

void PriceByDate(Tech *head)
{
    struct Tech *element;
    element=head->next;

    char date[255];
    printf("������ ���� �������: ");
    scanf("%s", &date);

    int result=0;
    while(element!=NULL)
    {
        if(!strcmp(element->date, date))
        {
            result+=element->price;
        }
        element=element->next;
    }

    printf("������� ��������� ������� �� ������ ����: %i\n", result);
    return 0;
}

void SortByPrice(Tech *head)
{
    struct Tech *element, *secondary, *temp;
    element=head->next;

    int previous=INT_MAX;
    while(element!=NULL)
    {
        int max=INT_MIN;

        secondary=head->next;
        while(secondary!=NULL)
        {
            if(secondary->price>max && secondary->price<previous)
            {
                temp=secondary;
                max=temp->price;
            }

            secondary=secondary->next;
        }

        printf("%i | ��� ������: %s | �����������: %s | ������� �������: %s | ���� �������: %s | ֳ��: %i\n", temp->number, temp->type, temp->breakdown, temp->master, temp->date, temp->price);
        previous=temp->price;
        element=element->next;
    }

    return 0;
}

void GetByMaster(Tech *head)
{
    struct Tech *element;
    element=head->next;

    char master[255];
    printf("������ ������� �������: ");
    scanf("%s", &master);

    printf("���������� ����� �������:\n");
    while(element!=NULL)
    {
        if(!strcmp(element->master, master))
        {
            printf("%i | ��� ������: %s | �����������: %s | ������� �������: %s | ���� �������: %s | ֳ��: %i\n", element->number, element->type, element->breakdown, element->master, element->date, element->price);
        }
        element=element->next;
    }

    return 0;
}

void SaveAndExit(Tech *head)
{
    struct Tech *element;
    element=head->next;

    FILE *file;
    file = fopen("mainfile.txt", "w");
    if(!file)
    {
        printf("���� �� ��������!\n");
        exit(1);
    }

    while(element!=NULL)
    {
        buf.number=element->number;
        strcpy(buf.type, element->type);
        strcpy(buf.breakdown, element->breakdown);
        strcpy(buf.master, element->master);
        strcpy(buf.date, element->date);
        buf.price=element->price;

        fwrite(&buf, sizeof(buf), 1, file);
        element=element->next;
    }

    fclose(file);
    free(head);
    exit(1);
}

