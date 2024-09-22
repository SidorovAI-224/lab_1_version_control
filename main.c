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
     printf("|        Курсова робота                            |\n");
     printf("|        Учень: Сідоров Денис Олегович             |\n");
     printf("|        Група: АІ-224                             |\n");
     printf("====================================================\n");
     printf("\n");

     int commander;
     while(1)
     {
         puts("Введіть код бажаної дії:");
         puts("1 - Додавання елемента");
         puts("2 - Видалення елемента");
         puts("3 - Коригування даних");
         puts("4 - Виведення всіх даних");
         puts("5 - Виведення несправностей за заданим типом техніки");
         puts("6 - Розрахунок вартості виконаних ремонтів на задану дату");
         puts("7 - Сортування по полю «вартість ремонту»");
         puts("8 - Пошук всіх замовлень за прізвищем майстра");
         puts("0 - Зберегти та вийти");
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
        printf("Файл не знайдено!\n");
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
    printf("Введення елементу:\n");
    printf("Номер замовлення | Тип техніки | Несправність | Прізвище майстра | Дата ремонту | Ціна\n");
    scanf("%i%s%s%s%s%i", &element->number, element->type, element->breakdown, element->master, element->date, &element->price);

    temp=head->next;
    head->next=element;
    element->next=temp;

    printf("Елемент успішно додано!\n");
    return 0;
}

void RemoveElement(Tech *head)
{
    struct Tech *element, *temp;
    element=head;

    int number;
    printf("Введіть номер видаляємого елементу: ");
    scanf("%i", &number);

    while(element!=NULL)
    {
        if(element->next->number==number)
        {
            temp=element->next;
            free(element->next);
            element->next=temp->next;

            printf("Елемент успішно видалено!\n");
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
    printf("Введіть номер елементу, який хочете змінити: ");
    scanf("%i", &number);

    while(element!=NULL)
    {
        if(element->number==number)
        {
            printf("Коригування даних:\n");
            printf("Тип техніки | Несправність | Прізвище майстра | Дата ремонту | Ціна\n");
            scanf("%s%s%s%s%i", element->type, element->breakdown, element->master, element->date, &element->price);

            printf("Елемент успішно змінено!\n");
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
        printf("%i | Тип техніки: %s | Несправність: %s | Прізвище майстра: %s | Дата ремонту: %s | Ціна: %i\n", element->number, element->type, element->breakdown, element->master, element->date, element->price);
        element=element->next;
    }

    return 0;
}

void BreakdownByType(Tech *head)
{
    struct Tech *element;
    element=head->next;

    char type[255];
    printf("Введіть тип техніки: ");
    scanf("%s", &type);

    printf("Несправності за заданим типом техніки:\n");
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
    printf("Введіть дату ремонту: ");
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

    printf("Вартість виконаних ремонтів на задану дату: %i\n", result);
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

        printf("%i | Тип техніки: %s | Несправність: %s | Прізвище майстра: %s | Дата ремонту: %s | Ціна: %i\n", temp->number, temp->type, temp->breakdown, temp->master, temp->date, temp->price);
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
    printf("Введіть прізвище майстра: ");
    scanf("%s", &master);

    printf("Замовлення цього майстра:\n");
    while(element!=NULL)
    {
        if(!strcmp(element->master, master))
        {
            printf("%i | Тип техніки: %s | Несправність: %s | Прізвище майстра: %s | Дата ремонту: %s | Ціна: %i\n", element->number, element->type, element->breakdown, element->master, element->date, element->price);
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
        printf("Файл не знайдено!\n");
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

