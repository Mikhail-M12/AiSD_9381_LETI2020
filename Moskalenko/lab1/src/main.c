#include <stdio.h>
    #include <ctype.h>
    #include <stdlib.h>
    #include <string.h>

    int checkingSign(char sign); //функция на проверку знака операции (+, - или *). sign - проверка знака
    int numbersRow(char* numbers, int* start, int tab);  //функция проверки ряда цифра (выражение, индекс элемента, значение табуляции)
    void constMessage(char* message, int* start, int pad);    //функция проверки константного выражения (выражение, индекс элемента)
    char* readMessage();   //функция динамического считывания строки

    int checkingSign(char sign){
        if (sign == '+' || sign == '-' || sign == '*')
            return 1;
        else return 0;
    }

    int numbersRow(char* numbers, int* start, int tab){   /* функция на проверку ряда цифр. иначе рекурсивный вызов */
        for(int i = 0; i < tab; i++)
            printf("\t");
        printf("START numbersRow\n");

        if (!isdigit(numbers[*start])) {                  //если знак - не цифра, то возвращается 0.
            printf("Не цифра %c\n", numbers[*start]);
            for(int i = 0; i < tab; i++)
                printf("\t");
            printf("FINISH numbersRow\n");
            return 0;
        }
        if (isdigit(numbers[*start]) && (numbers[(*start)+1] == '\0' ||   /* если цифра крайняя(перед знаком операции или /0),
                                                                          то возвращается 1. */
            checkingSign(numbers[(*start)+1]))) {
            for(int i = 0; i < tab; i++)
                printf("\t");
            printf("DIGIT \033[32m%c\033[0m\n",numbers[*start]);
            (*start)++;
            for(int i = 0; i < tab; i++)
                printf("\t");
            printf("FINISH numbersRow\n");
            return 1;
        }

        if (isdigit(numbers[*start]) && (numbers[(*start)+1] != '\0') &&    //если цифра не крайняя, то далее рекурсивный вызов
            (!checkingSign(numbers[(*start)+1]))) {
            for(int i = 0; i < tab; i++)
                printf("\t");
            printf("ROW OF DIGITS \033[32m%c\033[0m ...\n", numbers[*start]);
            (*start)++;
            return numbersRow(numbers, start,tab+1);
        }
        return 0;
    }

    void printT(int pad){
        for(int i = 0; i < pad; i++)
            printf("\t\t");
    }

    void constMessage(char* message, int* start, int pad){
        printT(pad);
        printf("NEW ROW.START constMessage\n");
        if (!numbersRow(message, start, pad)){
            printT(pad);                        //выводим пробелы
            printf("FINISH constMessage\n");
            printf("\033[1;31m" "He константное выражение\n");     //вызов NumbersRow. если встретилась НЕ цифра, то выводим сообщение и выходим
            return;
        }
        else{
            if (message[*start] == '\0') {//если дальше знаков нет, то это const. выходим
                printT(pad);
                printf("End of sentence. FINISH constMessage\n");
                printf("\033[1;31m" "Константное выражение\n");
                return;
            }
            if (checkingSign(message[*start])){                    //если встретился знак операции, то выводим сообщение и сдвигаемся на знак далее
                printf("\033[1;34m" "Знак операции %c\033[0m\n", message[*start]);
                (*start)++;
                printT(pad);
                printf("FINISH constMessage\n");
                return constMessage(message,start,pad+1);
            }
        }
        }



    char* readMessage(){            //считывание строки
        char* n = malloc(10);
        int size = 0;
        char c = fgetc(stdin);
        while (1){
            c = fgetc(stdin);
            if (c == '\n')
                break;
            n = (char*)realloc(n,size+1);  //увеличиваем память
            n[size++] = c;
        }
        n[size] = '\0';
        return n;
    }

    int main(){
        int choiceRead;
        printf("Нажмите 1 при вводе данных с клавиатуры,\n 2 - при считывания с файла\n");
        scanf("%d",&choiceRead);
        char* n;
        switch(choiceRead) {
            case 1:
                printf("Введите строку для тестирования\n");
                n = readMessage();
                break;

            case 2:
                printf("Введите полный путь файла с данными\n");
                char *name = readMessage();                                     //при данном выборе считываются данные с файла и далее происходит работа с ними
                FILE *fileTask = fopen(name, "r");
                if (!fileTask){
                    printf("Ошибка при чтении файла. Вероятно, файла с таким названием нет.\n");
                    return 0;
                }
                n = malloc(100);
                char c;
                int i;
                for(i = 0; (c = getc(fileTask)) != '\n' && (c != EOF); ++i) {
                    n[i] = c; // заполнение строки
                }
                n[i] = '\0';
                if (fclose(fileTask) == EOF) printf ("Ошибка\n");
                else printf ("Считывание выполнено\n");
                n = realloc(n,strlen(n)+1);
                printf("%s\n",n);
                free(name);
                break;

            default:
                printf("Такого варианта нет. Вы должны ввести A или B.\n");
                return 0;
        }
        int s = 0;
        int* z = &s;
        constMessage(n,z,0);  //вызов функции
        free(n);
        return 0;
}
