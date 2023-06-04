#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Laba2 { //Створення класу із назвою Лаба2
private:
    vector<char> _chars;//Поле множини чару в яка буде зберігати дані про об'єкт 
    int size = 1;//Поле розміру, яке ми потім будемо використовувати для перевірки чи об'єкт не є пустим
public:
    Laba2() {};//Пустий констуктор для ініціалізації пустого об'єкта

    Laba2(initializer_list<char> chars)//Конструктор який приймає параметр множини чару і записує в неї елементи які вказані користувачем
    {
        copy(chars.begin(), chars.end(), back_inserter(_chars));//Копіювання елементів в множину
        sort(_chars.begin(), _chars.end());//Сортування елементів в множині
        auto last = unique(_chars.begin(), _chars.end());
    }

    bool contains(char c) const //Метод перевірки наявності певного елемента в множині
    {
        return binary_search(_chars.begin(), _chars.end(), c);//Перевірення чи наявний той елемент в множині
    }

    void insert(char c) //Метод додавання елемента в множину(окремий метод від конструктора)
    {
        if (!contains(c)) //Перевірка чи немає цього цього елемента в множині
        {
            _chars.push_back(c);//Якщо немає того елементу в множині то береться елемент з параметра який передається в метод(тобто char c)
            sort(_chars.begin(), _chars.end());//і записується в множину і одразу сортується в алфавітному порядку
        }
    }

    void remove(char c) //Метод видалення елемента з множини
    {
        auto it = lower_bound(_chars.begin(), _chars.end(), c);//Пошук елемента в множині
        if (it != _chars.end() && *it == c) //Перевірка множини чи цей елемент є в множині, і якщо так то перехід до наступної строки
        {
            _chars.erase(it);//Видалення елемента
        }
    }

    friend void elementsInList(Laba2& Size);//Ініціалізація дружньої функції в класі

    Laba2 operator-(char c) const //Перевантаження оператора “–“ − видалити елемент з множини
    {
        Laba2 result(*this);//Береться певна множина
        result.remove(c);//Далі береться елемент з параметра(char c)
        return result;//І повертається множина вже без того елемента
    }

    bool operator>(const Laba2& other) const //Перевантаження оператора “>” − перевірка на підмножину
    {
        return includes(_chars.begin(), _chars.end(),//Повернення значення рівності двох множин, тобто береться кожен елемент першої множини
            other._chars.begin(), other._chars.end());//Потім другої і функцією includes перевіряє на рівніть
    }

    bool operator!=(const Laba2& other) const //Перевантаження оператора “!=” − перевірка множин на нерівність
    {
        return _chars != other._chars;//Повернення значеня нерівності двох множин
    }

    void print() const //Виведення кожного елемента множини
    {
        cout << "{";
        for (auto c : _chars) //Береться кожен елемент масиву і виводиться
        {
            cout << c << ",";
        }
        cout << "}" << std::endl;
    }

};

void elementsInList(Laba2& Size)//Дружня функція з класом Лаба2, яка перевіряє чи об'єкт пустий
{
    if (Size._chars.size() <= Size.size) //Перевірка чи кількість елементів в множині більше ніж поле int size = 1 
    {
        cout << "Fill a list" << endl;
    }
    else
        cout << "List is already filled" << endl;
}

int main()
{
    Laba2 nullList;//Створення пустого об'єкта
    Laba2 firstList = { 'a', 'b', 'c', 'd', 'a', 'e' };//Перший об'єкт із певними значеннями 
    firstList.print();//Виведення його і так далі для всіх
    Laba2 secondList = { 'a', 'b', 'c' };//І тут
    secondList.print();//І тут
    Laba2 thirdList = { 'x', 'y', 'z' };//І тут
    thirdList.print();//І тут так само

    elementsInList(nullList);//Та сама дружня функція перевірки 
    elementsInList(firstList);//Та сама дружня функція перевірки

    (firstList - 'a b').print();//Метод перевантаження оператора видалення з множини елемента
    (secondList - 'c').print();//Метод перевантаження оператора видалення з множини елемента
    (thirdList - 'y').print();//Метод перевантаження оператора видалення з множини елемента

    cout << (firstList > secondList) << endl;//Метод перевантаження оператора перевірки на підмножину
    cout << (firstList > thirdList) << endl;//Метод перевантаження оператора перевірки на підмножину

    cout << (firstList != secondList) << endl;//Метод перевантаження оператора перевірки нерівності множин
    cout << (firstList != firstList) << endl;//Метод перевантаження оператора перевірки нерівності множин
  
    return 0;
}
