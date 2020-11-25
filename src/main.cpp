#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



char* readsent() {					//функция посимвольного считывания строки из файла
	int size = 10;
	int n = 0;
  char a;
	FILE* f = fopen("data.txt", "r");
	char* sent = (char*)malloc(size * sizeof(char));
	while ((sent[n] = fgetc(f)) != EOF ){
    if (sent[n] == ' ')
      continue;             
		if (n++ >= size-2) {
			size += 10;
			sent = (char*)realloc(sent, size * sizeof(char));        
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


typedef struct node{
  struct node* next;   //следующий
  struct node* prev;   //предыдущий
  struct node* child;  //сын
  char data;           //данные
  int isNull;          //пустой ли элемент
}node;

void free_list(node* elem){  // функция освобождения памяти, отведенной под списки
  if (elem->child)
    free_list(elem->child);
  if (elem->next)
    free_list(elem->next);
  printf("(del)[%c]\n",elem->data);
  free(elem);
}

void create_H_list(char* s, node* lst){   //функция создания ИС из строки
  char a = '1',b = '1';
  node* current = NULL;
  sscanf(s ,"%c%c", &a, &b);
  if ((a == '(')&&(b == ')')){
    lst->child = NULL;
    printf("(list is empty)");
    return;
  }
  shift(s,1);

  node* elem = (node*)malloc(sizeof(node));
  elem->prev = NULL;
  elem->next = NULL;
  elem->child = NULL;
  elem->data = ' ';
  elem->isNull = 0;
  printf("(creation of element)(first element of list)");
  lst->child = elem;
  while (1){
    sscanf(s ,"%c%c", &a, &b);
    if ((a == '(')&&(b == ')')){
      elem->isNull = 1;
      shift(s,2);
    }

    if (a != '(')
      shift(s,1);

    if ((a == '(')&&(b != ')')){
      printf("(moving to the lower level)\n");
      create_H_list(s, elem);
    }

    if ((a != '(')&&(a != ')')){
      elem->data = a;
    }

    if (a == ')'){
      if (elem->prev)
        elem->prev->next = NULL;
      free(elem);
      printf("(deleting an extra element)(sublist finished)\n");
      
      break;
    }


    current = elem;
    if (!current->child)
      printf("[%c]\n", current->data);
    elem = (node*)malloc(sizeof(node));
    elem->prev = current;
    elem->next = NULL;
    elem->child = NULL;
    elem->data = ' ';
    elem->isNull = 0;
    printf("(creation of element)");
    current->next = elem;
  }
} 

node* H_list_to_linar(node* H_lst, node* L_lst){  // функция преобразования ИС в ЛС 
  node* cur_H = H_lst->child;
  node* elem = NULL;
  node* cur_L = NULL;
  if (!cur_H){
    printf("(list is empty)");
    return NULL;
  }
  if (!L_lst->prev){
    cur_L = (node*)malloc(sizeof(node));
    printf("(creation of element)");
    cur_L->prev = L_lst;
    cur_L->next = NULL;
    cur_L->child = NULL;
    cur_L->data = ' ';
    cur_L->isNull = 0;
    L_lst->next = cur_L;
  }
  else
    cur_L = L_lst;

  while(cur_H){
   
    if (cur_H->child){
      cur_L = H_list_to_linar(cur_H, cur_L);

      if (cur_H->next){
        cur_H = cur_H->next;
        continue;
      }
     else
       break;
    }

    cur_L->data = cur_H->data;
    if (cur_H->isNull)
      cur_L->isNull = 1;
    printf("(creation of element)[%c]\n", cur_L->data);

    if (cur_H){
      elem = cur_L; 
      cur_L = (node*)malloc(sizeof(node));
      cur_L->prev = elem;
      cur_L->next = NULL;
      cur_L->child = NULL;
      cur_L->data = ' ';
      cur_L->isNull = 0;
      printf("(creation of element)");
      elem->next = cur_L;
    }
    else
      break;
    cur_H = cur_H->next;

  }
  if (!L_lst->prev){
    cur_L->prev->next = NULL;
    free(cur_L);
    printf("(deleting an extra element)(sublist finished)");
  }
  return cur_L;
}

void print_H_list(node* lst){     // функция вывода ИС на экран

  if (lst->child == NULL){
    printf("()");
    return;
  }

  node* current = lst->child;

  printf("(");
  while (current){
    if (current->child){
      print_H_list(current);
      if (current->next)   
        printf(" ");
    }
    else{
      if (!current->isNull)
        printf("%c",current->data);
      else
        printf("()");
      if (current->next)  
        printf(" ");
    }
    current = current->next;
  }
   printf(")");
}

void print_L_list(node* lst){           // функция вывода ЛС на экран и в файл
  FILE* f = fopen("answer.txt", "w");
  if (lst->next == NULL){
    printf("()");
    fprintf(f, "()");
    return;
  }
  node* current = lst->next;
  printf("(");
  fprintf(f, "(");
  while (current){
    if (!current->isNull){
      printf("%c",current->data);
      fprintf(f, "%c",current->data);
    }
    else{
      printf("()");
      fprintf(f, "()");
    }
    if (current->next){  
      printf(" ");
      fprintf(f, " ");
    }
    current = current->next;
  }
  printf(")");
  fprintf(f, ")");

  fclose(f);
}

int main(){
  char* s = readsent();         //считывание строки
  printf("\n(input)\n%s\n", s);

  node H_lst;
  H_lst.prev = NULL;
  H_lst.next = NULL;
  H_lst.child = NULL;

  node L_lst;
  L_lst.prev = NULL;
  L_lst.next = NULL;
  L_lst.child = NULL;

  create_H_list(s, &H_lst);      //считывания ИЛ

  printf("\n\n");

  printf("(hierarchical list)\n");
  print_H_list(&H_lst);          // вывести на экран ИС

  printf("\n\n");

  H_list_to_linar(&H_lst, &L_lst);    //преобразовать ИС в ЛС
 
  printf("\n\n"); 

  printf("(linear list)\n");
  print_L_list(&L_lst);               // вывести на экран и в файл ЛС

  free(s);
  printf("\n\n"); 
  if (H_lst.child){
    printf("(deleting of hierarchical list)\n");
    free_list(H_lst.child);
  }
  printf("\n");
  if (L_lst.next){
    printf("(deleting of linear list)\n");
    free_list(L_lst.next);
  }
  system("pause");
  return 0;
}