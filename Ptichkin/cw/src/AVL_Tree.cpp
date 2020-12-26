#include "stdafx.h"
#include "AVL_Tree.h"

AVL_Tree::AVL_Tree(int key) {//конструктор
	this->height = 1;
	this->key = key;
	left = nullptr;
	right = nullptr;
}

bool AVL_Tree::find_key(int k) { //метод нахождения элемента с ключём k
	if (this == nullptr) {
		return 0;
	}
	if (key == k) {
		return true;
	}
	if ((left->find_key(k)) || (right->find_key(k))) {//рекурсивный вызов для поддеревьев
		return true;
	}
	return false;
}

int AVL_Tree::get_height() {//возвращает значение высоты дерева
	if (this != nullptr) {
		return height;
	}
	return 0;
}

int AVL_Tree::bfactor(){ //разница между высотами поддеревьев
	return right->get_height() - left->get_height();
}

void AVL_Tree::fixheight(){  //обновляет высоту после вставки/удаления элемента
	int hl = left->get_height();
	int hr = right->get_height();
	if (hl > hr) {
		height = hl + 1;
	}
	else {
		height = hr + 1;
	}
}

AVL_Tree* AVL_Tree::rotateright(ostream* stream){//поворот вправо
	if (stream != nullptr)
	*stream << "Производится поворот вправо\n";
	cout << "Производится поворот вправо\n";
	AVL_Tree* q = left;
	left = q->right;
	q->right = this;
	fixheight();
	q->fixheight();
	return q;
}

AVL_Tree* AVL_Tree::rotateleft(ostream* stream){//поворот влево
	if(stream!=nullptr)
	*stream << "Производится поворот влево\n";
	cout << "Производится поворот влево\n";
	AVL_Tree* q = right;
	right = q->left;
	q->left = this;
	fixheight();
	q->fixheight();
	return q;
}

AVL_Tree* AVL_Tree::balance(ostream* stream){//ребалансировка дерева
	fixheight();
	if (bfactor() == 2)
	{
		if (right->bfactor() < 0)
			right = right->rotateright(stream);
		return rotateleft(stream);
	}
	if (bfactor() == -2)
	{
		if (left->bfactor() > 0)
			left = left->rotateleft(stream);
		return rotateright(stream);
	}
	return this;
}

AVL_Tree* AVL_Tree::insert(int k, ostream* stream){//вставка элемента с ключём k
	if (!this) {
		cout << "Вставка элемента "<<k<<'\n';
		if (stream != nullptr)
		*stream << "Вставка элемента " << k << '\n';
		return new AVL_Tree(k);
	}
	if (k < key) {
		left = left->insert(k, stream); //рекурсивный вызов для поддеревьев
	}
	if (k > key) {
		right = right->insert(k, stream);//рекурсивный вызов для поддеревьев
	}
	return balance(stream);
}

AVL_Tree* AVL_Tree::findmin() { //нахождение элемента с минимальным ключём
	if (left != nullptr) {
		return left->findmin();
	}
	return this;
}

AVL_Tree* AVL_Tree::removemin() {  //удаление элемента с минимальным ключём
	if (left == nullptr) {
		return right;
	}
	left = left->removemin();
	return balance();
}

AVL_Tree* AVL_Tree::remove(int k, ostream* stream){ //исключение элемента с ключём k
	if (!this) return nullptr;
	if (k < key)
		left = left->remove(k, stream);//рекурсивный вызов для поддеревьев
	else if (k > key)
		right = right->remove(k, stream);//рекурсивный вызов для поддеревьев
	else
	{
		AVL_Tree* q = left;
		AVL_Tree* r = right;
		cout << "Производится исключение элемента "<<k<<'\n';
		if(stream!=nullptr)
		*stream << "Производится исключение элемента " << k << '\n';
		delete this;
		if (!r) return q;
		AVL_Tree* min = r->findmin();
		min->right = r->removemin();
		min->left = q;
		return min->balance(stream);
	}
	return balance(stream);
}

void AVL_Tree::destroy() {//рекурсивная очистка дерева
	if (this != nullptr) {
		left->destroy();
		right->destroy();
		delete this;
	}
}

void AVL_Tree::print_tree(ostream* stream, int depth) { //печать дерева в поток
	if (this!=nullptr) {
		if (right != nullptr) {
			right->print_tree(stream, depth + 1);//рекурсивный вызов для поддеревьев
		}
		for (int i = 0; i < depth; i++) *stream << "   ";//число пробелов зависит от высоты
		*stream << key << endl;
		if (left != nullptr) {
			left->print_tree(stream, depth + 1);//рекурсивный вызов для поддеревьев
		}
	}
	else {
		*stream << "Пустое дерево\n";
	}
}