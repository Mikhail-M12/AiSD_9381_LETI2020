#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct data {					//структура для хранения всех необходимых данных
	int sum;	//сумма всего выражения
	int mul;	//переменная хранит промежуточные значения произведений
	int max;	//порог переполнения
	int tabs;	//количество табуляций
	char* s;	//строка-вырожение
	FILE* f;	//файл-ответ
} data;

char* readsent() {					//функция посимвольного считывания строки из файла
	int size = 10;
	int n = 0;
	FILE* f = fopen("data.txt", "r");
	char* sent = malloc(size * sizeof(char));
	while ((sent[n] = fgetc(f)) != EOF  ){                
		if (++n >= size) {
			size += 10;
			sent = realloc (sent, size * sizeof(char));        
		}   
	} 
	sent[n]='\n';
	sent[n+1]='\0';
	fclose(f);
	return sent;
}

void shift(char* sent, int ind) {			//функция сдвига строки-выражения влево (удаление)
	int i = 0;
	for(i = ind; i<strlen(sent); i++)
		sent[i-ind] = sent[i];
	sent[strlen(sent)-ind]='\0';
}

int numlen(int num) {					//функция измерения длины числа
	int n = 0;
	while (num>0) {
		num = num / 10;
		n++;
	}
	return n;
}

void printtabs(FILE* f, int n) {			//функция отвечающая за отступы в файле-ответе
	int i;
	for(i=0; i<n; i++)
		fprintf(f, "\t");
	fprintf(f, "|______");
}

void mult(data *dt) {					//рекурсивная функция умножения
	int num=0;
	char sign;
	char sign2;
	sscanf(dt->s, "%c%d%c", &sign, &num, &sign2);
	dt->mul = dt->mul * num;	//подсчет произведения
	if (dt->mul > dt->max)		//переполнение
		return;
	fprintf(dt->f, "%d", dt->mul);
	shift(dt->s, numlen(num)+1);
	if(strchr("*", sign2)) {
		fprintf(dt->f, " --> ");
		mult(dt);		//следующий множитель
	}
}

void calc(data *dt) {					//рекурсивная функция счета
	int num = 0;
	char sign;
	char sign2;
	int mul = 0;
	sscanf(dt->s, "%c%d%c", &sign, &num, &sign2);
	if (num > dt->max) {				//переполнение числа
		printtabs(dt->f, dt->tabs++);
		fprintf(dt->f, "ПЕРЕПОЛНЕНИЕ (%d)\n", num);
		dt->sum = num;
		return;
	}
	if (strchr("\n", sign)) {
		return;
	}
	if (strchr("+", sign)) {			//сложение
		if(strchr("*", sign2)) {		//сумма с произведение
			shift(dt->s, numlen(num)+1);
			printtabs(dt->f, dt->tabs);
			fprintf(dt->f, "%d --> ", num);
			dt->mul = num;
			mult(dt);		//подсчет произведения
			if (dt->mul > dt->max) {	//перполнение произведения
				fprintf(dt->f, "ПЕРЕПОЛНЕНИЕ (%d)\n", dt->mul);
				dt->sum = dt->mul;
				return;
			}
			dt->sum = dt->sum + dt->mul;
			if (dt->sum > dt->max) {	//переполнение суммы
				fprintf(dt->f, "\n");
				printtabs(dt->f, dt->tabs++);
				fprintf(dt->f, "ПЕРЕПОЛНЕНИЕ (%d)\n", dt->sum);
				return;
			}
			fprintf(dt->f, "\n");
			printtabs(dt->f, dt->tabs++);
			fprintf(dt->f, "%d (+)\n", dt->sum);
		}
		else {					//сумма двух слагаемых
			dt->sum= dt->sum + num;
			if (dt->sum > dt->max) {	//переполнение суммы
				printtabs(dt->f, dt->tabs++);
				fprintf(dt->f, "ПЕРЕПОЛНЕНИЕ (%d)\n", dt->sum);
				return;
			}
			shift(dt->s, numlen(num)+1);
			printtabs(dt->f, dt->tabs++);
			fprintf(dt->f, "%d (+)\n", dt->sum);
		}
		calc(dt);	//переход к следующему действию
		return;
	}
	if (strchr("-", sign)) {			//вычитание
		if(strchr("*", sign2)) {		//разность с произведением
			shift(dt->s, numlen(num)+1);
			printtabs(dt->f, dt->tabs);
			fprintf(dt->f, "%d --> ", num);
			dt->mul = num;
			mult(dt);			//подсчет произведения
			if (dt->mul > dt->max) {	//переполнение произведения
				fprintf(dt->f, "ПЕРЕПОЛНЕНИЕ (%d)\n", dt->mul);
				dt->sum = dt->mul;

				return;
			}
			dt->sum = dt->sum - dt->mul;	//подсчтет разности с произведением
			fprintf(dt->f, "\n");
			printtabs(dt->f, dt->tabs++);
			fprintf(dt->f, "%d (-)\n", dt->sum);
		}
		else {					//разность с простым вычитаемым
			dt->sum= dt->sum - num;
			shift(dt->s,  numlen(num)+1);
			printtabs(dt->f, dt->tabs++);
			fprintf(dt->f, " %d (-)\n", dt->sum);
		}
		calc(dt);	//переход к следующему действию
		return;
	}
	if (strchr("*", sign)) {			//умножение
		shift(dt->s, numlen(num)+1);
		printtabs(dt->f, dt->tabs++);
		fprintf(dt->f, "%d --> ", dt->sum);
		dt->mul = dt->sum * num;		//произведение из двух множетилей
		if (dt->sum > dt->max) {		//переполнение произведения
			fprintf(dt->f, "ПЕРЕПОЛНЕНИЕ (%d)\n", dt->sum);
			return;
		}

		if (strchr("*", sign2)){
			fprintf(dt->f, "%d --> ", dt->mul);
			mult(dt);			//произведение из 3+ множетелей
		}
		else
			fprintf(dt->f, "%d", dt->mul);
		dt->sum = dt->mul;
		if (dt->sum > dt->max) {		//переполнение произведения
			fprintf(dt->f, "ПЕРЕПОЛНЕНИЕ (%d)\n", dt->sum);
			return;
		}
		fprintf(dt->f, "\n");
		calc(dt);	//переход к следующему действию
		return;
	}

}

int main() {
	data dt;
	dt.sum = 0;
	dt.tabs = 0;
	dt.s = readsent();
	dt.f = fopen("answer.txt", "w");
	char sign;

	sscanf(dt.s, "%d", &dt.max);
	shift(dt.s, numlen(dt.max)+1);

	sscanf(dt.s, "%d%c", &dt.sum, &sign);
	shift(dt.s,  numlen(dt.sum));
	if (strchr("\n", sign))  	//если было введено только одно число 
		if (dt.sum < dt.max)
			fprintf(ft.f, "Ответ: %d\n", dt.sum);
		else
			fprintf(ft.f, "ПЕРЕПОЛНЕНИЕ");
	else {
		if (dt.sum < dt.max) {
			fprintf(f1, "%d%s", dt.sum, dt.s);
			calc(&dt);	//вход в рекурсивную функцию подсчета
			if (dt.sum < dt.max)
				fprintf(dt.f, "\nОтвет: %d\n", dt.sum);
		}
		else
			fprintf(dt.f, "ПЕРЕПОЛНЕНИЕ");
	}

	fclose(dt.f);
	free(dt.s);
	return 0;
}
