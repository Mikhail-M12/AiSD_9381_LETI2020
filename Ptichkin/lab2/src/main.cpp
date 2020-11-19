#include "list.h"

int input_num(string message){
    int num = 0;
    cout<<message<<'\n';
    char* input = new char[10];
    fgets(input, 10, stdin);
    while(sscanf(input, "%d", &num)!=1){
        cout<<"Ввод некорректный!\n"<<message<<'\n';
	fgets(input, 10, stdin);
    }
    delete [] input;
    return num;
}

void data_save(DATA_LIST* input_mass, int count_of_list){//сохранение данных в файл
    char* file_name = new char[256];
    cout<<"Введите имя файла сохранения\n";
    cin>>file_name;
    getchar(); //вытаскиваем символ переноса строки из потока
    fstream output_file;
    output_file.open(file_name, fstream::out | fstream::app);//открытие или создание файла на запись
    for(int i=0;i<count_of_list;i++){
    	write_list(input_mass[i].list, &output_file);
	output_file<<" Глубина: "<<input_mass[i].rez<<'\n';
    }
    delete [] file_name;
    output_file.close();
}

void clear_memory(DATA_LIST* input_mass, int count_of_string){//функция очистки памяти
    for(int i = 0; i<count_of_string; i++){
        destroy(input_mass[i].list);
    }
    delete [] input_mass;
}

int rec_func_depth(LIST* list, int mid_depth){
    //промежуточные данные
    if(is_Atom(list)){
	cout<<list->node.atom<<" на глубине "<<mid_depth<<'\n';
    	return 0;
    }
    if(is_Null(list)){
    	return 0;
    }
    int hd_depth = 1+ rec_func_depth(head(list), mid_depth+1);
    int tl_depth = rec_func_depth(tail(list), mid_depth);
    if(hd_depth>tl_depth){
	return hd_depth;
    } 
    else{
    	return tl_depth;
    }
}

int data_analis(DATA_LIST* input_mass, int count_of_list){
    cout<<"------------------------------------------------------------------------------------------\nИсходные данные:\n";
    string dialog_text="\nВыберите дальнейшее действие:\n1 - сохранить данные в файл и продолжить\n2 - сохранить данные в файл и выйти\n3 - продолжить без сохранения\n4 - выйти без сохранения";
    for(int i = 0; i<count_of_list;i++){
        write_list(input_mass[i].list, &cout);
        cout<<'\n';
    }
    cout<<"\nПромежуточные данные алгоритма:\n\n";
    for(int i = 0; i<count_of_list;i++){
	cout<<"Рассчёт глубины для списка : ";
	write_list(input_mass[i].list, &cout);
	cout<<'\n';
    	input_mass[i].rez = rec_func_depth(input_mass[i].list, 0);
	cout<<"Итоговая глубина: "<<input_mass[i].rez<<"\n\n";
    }
    while(1){
        switch (input_num(dialog_text)){ //выбор дальнейших действий пользователем
	    case 1: data_save(input_mass, count_of_list);clear_memory(input_mass, count_of_list);return 1; break;//сохранение и очистка данных
	    case 2: data_save(input_mass, count_of_list);clear_memory(input_mass, count_of_list);return 0; break;
	    case 3: clear_memory(input_mass, count_of_list);return 1; break;
	    case 4: clear_memory(input_mass, count_of_list);return 0; break;
	    default: cout<<"Команда не распознана!\n";break;
        }
    }
}

int console_input(){
    string message = "Введите количество списков";
    int count_of_list = input_num(message);
    if (count_of_list<=0){
        return 1;
    }
    DATA_LIST* input_mass = new DATA_LIST[count_of_list];
    for(int i = 0; i<count_of_list; i++){
	cout<<"Список "<<i+1<<": ";
    	read_list(input_mass[i].list, nullptr, &cin);//считывание строки из консоли
    }
    if(data_analis(input_mass, count_of_list)){//вызов функции анализа данных
        return 1;
    }
    return 0;
}

int file_input(){
    int count_of_list = 0;
    int correct_file_name_flag = 0;  //флаг корректного имени файла ввода
    fstream file_input;
    char* file_name = new char[256];
    while(!correct_file_name_flag){//цикл до ввода корректного имени файла
        cout<<"Введите имя файла\n\n";
        cin>>file_name;
        file_input.open(file_name, fstream::in);//открывается файл ввода
	if(file_input.is_open()){
	    correct_file_name_flag = 1;
	}
	else{
	    cout<<"\nФайла с таким именем не найдено!\n";
	    memset(file_name, '\0', 256);
	}
    }
    getchar();//убираем символ переноса строки из потока ввода
    delete [] file_name;
    int buff = 10;//буффер количества строк
    int file_end_flag = 1;//флаг конца файла
    DATA_LIST* input_mass = new DATA_LIST[buff];
    DATA_LIST* rezerv_mass;
    while(file_end_flag){
	if(count_of_list==buff){//проверка на заполнение буффера
	    buff+=10;
	    rezerv_mass = new DATA_LIST[buff];
	    for(int i = 0;i<buff-10;i++){
	    	rezerv_mass[i].list = input_mass[i].list;
	    }
	    delete [] input_mass;
            input_mass = rezerv_mass;
            rezerv_mass = nullptr;
	}
	//считывание строки из файла
	read_list(input_mass[count_of_list].list, &file_end_flag, &file_input);
	count_of_list++;
    }
    file_input.close();
    delete input_mass[count_of_list-1].list;
    if(data_analis(input_mass, count_of_list-1)){//вызов функции анализа данных
        return 1;
    }
    return 0;
}

int main(){
    string start_dialog = "\nВыберите способ ввода данных:\n1 - Ввод с консоли\n2 - Ввод из файла";
    while(1){
	switch(input_num(start_dialog)){
	case 1:
    	    cout<<"Выбран ввод с консоли\n\n";
	    if(!console_input()){
	        return 0;
	    }
	    break;
    	case 2:
    	    cout<<"Выбран ввод из файла\n\n";
	    if(!file_input()){
	        return 0;
	    }
	    break;
    	default:
    	    cout<<"Ответ некорректный!\n\n";
    	}
    }
}
