#include <iostream>
#include <iomanip>
using namespace std;

struct Print; //предварительное объявление базовой стратегии

//контекст
class FormattedArray {
    int Size; //размерность массива
    int* Array;//сам массив
    int N;//сколько элементов в строке
    int C; //разделитель

    Print* s; //указатель на базовую стратегию
public:
    FormattedArray(int arr[], int size, int n, char c) {
        Size = size;
        Array = new int[Size];
        N = n;
        C = c;
        for (int i = 0; i < Size; i++)
        {
            Array[i] = arr[i];
        }
    }
    void setStrategy(Print* strat) {
        s = strat;
    }
    void useStrategy();
};

//стратегии
//базовая абстрактная стратегия, ее задача - определить интерфейс для алгоритма
struct Print {
    virtual void print(int arr[], int size, int n, char c) = 0; //чвф
};

//конкретные стратегии-наследники от базовой стратегии
struct PrintOfN : public Print {
    virtual void print(int arr[], int size, int n, char c) {
        cout << "PrintOfN strategy: " << endl;
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << "\t";
            if ((i+1) % n == 0)
            {
                cout << endl;
            }
        }
    }
};

struct PrintOfOne : public Print {
    virtual void print(int arr[], int size, int n, char c) {
        cout << "PrintOfOne strategy: " << endl;
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << endl;
        }
    }
};

struct PrintOfChar : public Print {
    virtual void print(int arr[], int size, int n, char c) {
        cout << "PrintOfChar strategy: " << endl;
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << c;
        }
    }
};

//научимся применять стратегии
void FormattedArray::useStrategy() {
    s->print(this->Array, this->Size, this->N, this->C);
}

//Клиент
int main() {
    setlocale(LC_ALL, "Ru");
    int size;
    cout << "Введите размер массива: ";
    cin >> size;
    int *array = new int[size];
    cout << "Ввод массива..." << endl;;
    for (int i = 0; i < size; ++i)
    {
        array[i] = i + 1;
        //cout << "Введите " << i+1 << " элемент массива: ";
        //cin >> array[i];
    }

    int n;
    cout << "Печать по n элементов в строке через пробел. Введите n: ";
    cin >> n;
    char c;
    cout << "Введите разделитель: ";
    cin >> c;

    FormattedArray* N = new FormattedArray(array, size, n, c);
    Print* strategy = new PrintOfN();

    N->setStrategy(strategy); //назначаю стратегию
    N->useStrategy(); //печатаем число через использование стратегии
    delete strategy;

    cout << endl;

    strategy = new PrintOfOne();
    N->setStrategy(strategy);
    N->useStrategy();
    delete strategy;

    strategy = new PrintOfChar();
    N->setStrategy(strategy);
    N->useStrategy();
    delete strategy;
    

    return 0;
}