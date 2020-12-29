#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID -1
#define HOW_MANY_POSSIBLE_SYMBOLS 256 /* количество допустимых символов */

int sum_len = 0;

enum { ENCODE, DECODE }; 

/* структура узла дерева */
struct node {
    int isZero;
    int isRoot;
    int isLeaf;
    
    struct node *parent;
    struct node *leftChild;
    struct node *rightChild;
    
    unsigned char symbol;
    int value;
    int order;
};
typedef struct node Node;

/* символ и укзатель на его вершину в дереве */
struct symbol {
    char symbol;
    Node *tree;
};
typedef struct symbol Symbol;

/* создание дерева
 * returns: указатель на корень дерева
 */
Node* createTree() {
    Node *tree = malloc(sizeof(Node));
    tree->isZero = 1;
    tree->isRoot = 1;
    tree->isLeaf = 1;
    
    tree->parent = NULL;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    
    tree->symbol = INVALID;
    tree->value = 0;
    tree->order = HOW_MANY_POSSIBLE_SYMBOLS * 2;
    
    return tree;
}

/* возвращаем вершину соответств. данному символу(если такой вершины нет то возвращаем nullptr)
 */
Node* getTreeFromSymbol(unsigned char symbol, Symbol **symbols) {
    Symbol *symbolPtr = symbols[(unsigned int)symbol];

    if (!symbolPtr) {
        return NULL;
    }
    
    return symbolPtr->tree;
}

/* разворот массива чисел
 * code: массив
 * codeSize: длина массива
 */
void reverseCode(int *code, int codeSize) {
    if (code == NULL) {
        printf("reverseCode: tried to reverse a NULL code.\n");
        return;
    }
    
    int *start = code;
    int *end = code+(codeSize-1);
    
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

/* возвращает массив 0 и 1 соотв. данной вершине в дереве
 * node: вершина
 * n: макс количество символов в массиве 
 */
int* codeOfNode(Node *node, int *n) {
    Node *current = node;
    int *code = malloc(sizeof(int) * HOW_MANY_POSSIBLE_SYMBOLS * 2);
    
    int i = 0;
    while (!current->isRoot) {
        Node *parent = current->parent;
        code[i] = (parent->leftChild == current) ? 0 : 1;
        current = current->parent;
        i++;
    }
    reverseCode(code, i);
    
    *n = i;
    return code;
}

/* создает ребенка от данной вершины
 * parent:вершина
 * isRoot: 1 если это корень, иначе 0
 * symbol: символ ноой вершины(ребенка)
 * value: значение в венршине
 * returns: ребенка.
 */
Node* addChild(Node *parent, int isZero, int isRoot, unsigned char symbol, int value, int order) {
    Node *node = malloc(sizeof(Node));
    node->isZero = isZero;
    node->isRoot = isRoot;
    node->isLeaf = 1;
    node->parent = parent;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->symbol = symbol;
    node->value = value;
    node->order = order;
    return node;
}

/* добавляет новый сивол в дерево и в массив символов
 * symbol: символ
 * symbols: массив символов
 * returns: указатель на родителя вершины которую мы создали
 */
Node* addSymbol(unsigned char symbol, Node **zeroNode, Symbol **symbols) {
    Node *leftNode = addChild(*zeroNode, 1, 0, INVALID, 0, (*zeroNode)->order - 2);
    Node *rightNode = addChild(*zeroNode, 0, 0, symbol, 1, (*zeroNode)->order - 1);
    
    Node *previousZeroNode = *zeroNode;
    (*zeroNode)->isZero = 0;
    (*zeroNode)->isLeaf = 0;
    (*zeroNode)->leftChild = leftNode;
    (*zeroNode)->rightChild = rightNode;
    
    unsigned int symbolIndex = (unsigned int)symbol;
    symbols[symbolIndex] = malloc(sizeof(Symbol));
    symbols[symbolIndex]->symbol = symbol;
    symbols[symbolIndex]->tree = rightNode;
    
    *zeroNode = leftNode;
    
    return previousZeroNode;
}

/* поиск вершины с таким же значением
 * currMax: наша вершина.
 * root: корень.
 * returns: вершину с таким же значением как у данной, иначе nullptr.
 */
Node* findReplaceNode(Node *cur, Node *root) {
    Node *result = cur;
    
    if (root->value > result->value && !root->isLeaf) {
        Node *greatestLeft = findReplaceNode(result, root->leftChild);
        if (greatestLeft) result = greatestLeft;
        
        Node *greatestRight = findReplaceNode(result, root->rightChild);
        if (greatestRight) result = greatestRight;
    } else if (root->value == result->value && root->order > result->order) {
        result = root;
    }
    
    return (result != cur) ? result : NULL;
}

/* поменять местами вершины в дереве
 */
void swapNodes(Node *n1, Node *n2) {
    int tempOrder = n1->order;
    n1->order = n2->order;
    n2->order = tempOrder;
    
    if (n1->parent->leftChild == n1) {
        n1->parent->leftChild = n2;
    } else {
        n1->parent->rightChild = n2;
    }
    
    if (n2->parent->leftChild == n2) {
        n2->parent->leftChild = n1;
    } else {
        n2->parent->rightChild = n1;
    }
    
    Node *temp = n1->parent;
    n1->parent = n2->parent;
    n2->parent = temp;
}

/* обновление дерева
 * currNode: начальная вершина с которой происходит обновление
 * root: корень дерева.
 */
void updateTree(Node *currNode, Node *root) {
    while (!currNode->isRoot) {
        Node *replaceNode = findReplaceNode(currNode, root);
        
        if (replaceNode && currNode->parent != replaceNode) {
            swapNodes(currNode, replaceNode);
        }
        
        (currNode->value)++;
        currNode = currNode->parent;
    }
    
    (currNode->value)++;
}

unsigned char addCodeToBuffer(int *code, int codeSize, FILE *fp, unsigned char buffer, int *bufferSize) {
    unsigned char currBuffer = buffer;
    for(int i = 0; i < codeSize;i++){
        printf("%i", code[i]);
    }
    sum_len+= codeSize;
    int i;
    for (i = 0; i < codeSize; i++) {
        unsigned char bit = ((char) code[i]) << (*bufferSize - 1);
        currBuffer = currBuffer | bit;
        
        (*bufferSize)--;
        
        if (*bufferSize == 0) {
            fwrite(&currBuffer, sizeof(char), 1, fp);
            currBuffer = 0;
            *bufferSize = 8;
        }
    }
    
    return currBuffer;
}

unsigned char addByteToBuffer(char byte, FILE *fp, unsigned char buffer, int *bufferSize) {
    unsigned char currBuffer = buffer;
    
    int howManyBitsWillBeWritten = *bufferSize;
    int shiftSize = 8 - howManyBitsWillBeWritten;
    unsigned char tempByte = ((char) byte) >> shiftSize;
    currBuffer = currBuffer | tempByte;
    


    fwrite(&currBuffer, sizeof(char), 1, fp);
    
    currBuffer = byte << howManyBitsWillBeWritten;
    
    return (*bufferSize == 8) ? 0 : currBuffer;
}

/* запись буфера в конечный файл
 * в последний бит так же записывается количество бит, для декодера
 *
 * fp: файл вывода.
 * buffer: буфер.
 * bufferSize: размер буфера.
 */
void writeRemainingBits(FILE *fp, unsigned char buffer, int bufferSize) {
    if (bufferSize < 8) {
        fwrite(&buffer, sizeof(unsigned char), 1, fp);
    }
    
    /* записывает сколько битов нужно прочитать(для декодера) */
    buffer = (bufferSize == 8) ? 8 : 8 - bufferSize;
    fwrite(&buffer, sizeof(unsigned char), 1, fp);
}

/* кодировка
 * fp_in: вход файл
 * fp_out: выход файл
 */
void encode(FILE *fp_in, FILE *fp_out) {
    Node *root = createTree();
    Node *zeroNode = root;
    
    unsigned char buffer = 0;
    int bufferSize = 8;
    
    Symbol **symbols = calloc(HOW_MANY_POSSIBLE_SYMBOLS, sizeof(Symbol*)); /* initializing with 0s */
    
    unsigned char currByte;
    while (fread(&currByte, sizeof(unsigned char), 1, fp_in) > 0) {
        Node *symbolTree = getTreeFromSymbol(currByte, symbols);
        
        if (symbolTree) {
            int codeSize;
            int *symbolCode = codeOfNode(symbolTree, &codeSize);
            buffer = addCodeToBuffer(symbolCode, codeSize, fp_out, buffer, &bufferSize);
            
            updateTree(symbolTree, root);
            free(symbolCode);
        } else {
            int codeSize;
            
            int *zeroCode = codeOfNode(zeroNode, &codeSize);
            buffer = addCodeToBuffer(zeroCode, codeSize, fp_out, buffer, &bufferSize);
            buffer = addByteToBuffer(currByte, fp_out, buffer, &bufferSize);
            
            Node *newNode = addSymbol(currByte, &zeroNode, symbols);
            updateTree(newNode, root);
            free(zeroCode);
        }
    }
    
    writeRemainingBits(fp_out, buffer, bufferSize);
}

/* читает след бит из буфера и возвращает его
 * fp: вход файл
 * buffer: буфер
 * bufferSize: сколько осталось бит в буфере
 * fileSize: размер файла
 * returns: 0 или 1.
 */
int readBit(FILE *fp, unsigned char *buffer, int *bufferSize, long int fileSize, int readHowManyBitsAtTheEnd) {
    if (*bufferSize == 0) {
        *bufferSize = 8;
        fread(buffer, sizeof(unsigned char), 1, fp);
    }
    
    if (readHowManyBitsAtTheEnd != 8) {
        if (ftell(fp) == fileSize && readHowManyBitsAtTheEnd <= (8 - *bufferSize)) return -1;
    }
    
    if (ftell(fp) > fileSize || feof(fp)) return -1;
    
    (*bufferSize)--;
    
    return (*buffer >> *bufferSize) & 1;
}

char readByte(FILE *fp, unsigned char *buffer, int *bufferSize, long int fileSize, int readHowManyBitsAtTheEnd) {
    char result = 0;
    
    int i, bit;
    for (i = 0; i < 8; i++) {
        bit = readBit(fp, buffer, bufferSize, fileSize, readHowManyBitsAtTheEnd);
        bit = bit << (7-i);
        result |= bit;
    }
    
    return result;
}

/* декодирование
 * fp_in: вход файл
 * fp_out: выход файл
 */
void decode(FILE *fp_in, FILE *fp_out) {
    Node *root = createTree();
    Node *zeroNode = root;
    
    unsigned char buffer = 0;
    int bufferSize = 0;
    
    Symbol **symbols = calloc(HOW_MANY_POSSIBLE_SYMBOLS, sizeof(Symbol*));
   
    fseek(fp_in, -1, SEEK_END);
    long int fileSize = ftell(fp_in);
    
    unsigned char readHowManyBitsAtTheEnd;
    fread(&readHowManyBitsAtTheEnd, sizeof(unsigned char), 1, fp_in);
    rewind(fp_in);
    
    while (!feof(fp_in)) {
        Node *currNode = root;
        
        int endOfFile = 0;
        while (!currNode->isLeaf && !endOfFile) {
            int bit = readBit(fp_in, &buffer, &bufferSize, fileSize, readHowManyBitsAtTheEnd);
            if (bit == 0) {
                currNode = currNode->leftChild;
            } else if (bit == 1) {
                currNode = currNode->rightChild;
            } else {
                endOfFile = 1;
            }
        }
        
        if (endOfFile) break;
        
        unsigned char c;
        if (currNode->isZero) {
            c = readByte(fp_in, &buffer, &bufferSize, fileSize, readHowManyBitsAtTheEnd);
            currNode = addSymbol(c, &zeroNode, symbols);
        } else {
            c = currNode->symbol;
        }
        
        fwrite(&c, sizeof(unsigned char), 1, fp_out);
        updateTree(currNode, root);
    }
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
        printf("Usage:\n");
		printf("\t./fgk input_file output_file -c (to encode)\n");
		printf("\t./fgk input_file output_file -d (to decode)\n");
		exit(1);
	}
	
    FILE *fp_in;
    FILE *fp_out;
    int option;
    
    fp_in = fopen(argv[1], "rb");
    while (fp_in == NULL) {
        char in_file[100];
        printf("The file %s could not be opened. Try again: ", argv[1]);
        scanf("%s", in_file);
        fp_in = fopen(in_file, "rb");
    }

    fp_out = fopen(argv[2], "wb");

    if (strcmp(argv[3], "-e") == 0 || strcmp(argv[3], "-E") == 0) {
        option = ENCODE;
    } else if (strcmp(argv[3], "-d") == 0 || strcmp(argv[3], "-D") == 0) {
        option = DECODE;
    } else {
        char opt;
        do {
            printf("type 'e' to encode or 'd' to decode: ");
            scanf("%c", &opt);
            getchar();
        } while (opt != 'e' && opt != 'E' && opt != 'd' && opt != 'D');
        option = (opt == 'e' || opt == 'E') ? ENCODE : DECODE;
    }
    
    if (option == ENCODE) {
        encode(fp_in, fp_out);
        printf("\n%i\n", sum_len);
        printf("\nThe file was encoded.\n");
    } else {
        decode(fp_in, fp_out);
        printf("\nThe file was decoded.\n");
    }
    
    fclose(fp_in);
    fclose(fp_out);
    
    return 0;
}