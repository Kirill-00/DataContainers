#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;       //Значение элемента
	Element* pNext; //Адрес слудующего элемента
	static unsigned int count;	//Количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

unsigned int Element::count = 0;	//Статическую переменную можно проинициализировать только за классом

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head; //Указатель на начальный элемент списка
	//Голова является точкой входа в список
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	//					Constructors
	ForwardList() :Head(nullptr), size(0)
	{
		//Конструктор по умолчанию создает пустой список.
		//Eусли Голова указывает на 0, то список пуст
		cout << "LConstructor:\t" << this << endl;

	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		/*initializer_list - это контейнер.
		Контейнер - это объект, который организует хранение других объектов в памяти.
		У любого контейнера есть методы
		begin() - возвращает ИТЕРАТОР на начало контейнера.
		end()   - возвращает ИТЕРАТОР на конец контейнера.
		-----------------------------------------------
		int*		указатель
		const int*	константный указатель
		const* int  указатель на константу
		int const*  указатель на константу
		const int const* константный указатель на константу*/
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;	//Из конструктора копирования вызываем оператор присваивания
#ifdef DEBUG
		cout << "CopyConstructor:\t" << this << endl;
#endif // DEBUG


	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);	//Функция std::move() вызывает MoveAssignment
#ifdef DEBUG
		cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG


	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;

	}

	//            Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		int a = 2;
		int b = 3;
		a = b;
		if (this == &other)return *this;
		while (Head)pop_front();
		//Deep copy:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	//           Adding Elements:
	void push_front(int Data)
	{
		/*//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Пристыковываем новый элемент к началу списка:
		New->pNext = Head;
		//3) Переводим Голову на новый элемент:
		Head = New;*/

		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до последнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//Теперь Итератор указывает на последний элемент списка,
		//и к нему можно пристыковать новый элемент.
		//3) Пристегиваем к последнему элементу списка новый элемент:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
			/*if(Temp->pNext)*/Temp = Temp->pNext;
		//3) Включаем новый элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//          Removing elemets
	void pop_front()
	{
		//1) Сохраняем адрес удаляемого элемента:
		Element* erased = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти:
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) Удаляем последний элемент из памяти:
		delete Temp->pNext;
		//3) Зануляем указатель на следующий элемент:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Head == 0)return pop_front();
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
		size--;
	}

	//               Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		/*Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого
		//можно получить доступ к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}*/
		//for(start	;	stop	;	step) group-of-statements;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка:\t  " << size << endl;
		cout << "Общее количество элементов списка:" << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);

	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}
		this->Head = reverse.Head;
		this->size = reverse.size;
		reverse.Head = nullptr;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;	//CopyConstructor
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define RANGE_BASE_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
//#define PREFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	/*list.push_back(123);
	list.print();*/
	/*list.pop_front();
	list.print();*/
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

	list1 = list1;
	ForwardList list3 = list1 + list2;
	list3.print();

#endif // COUNT_CHECK

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;

	//range-based for (for для диапазона, т.е., для контейнера)
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASE_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

#ifdef PREFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	cout << "List created, loading data..." << endl;
	time_t start = time(NULL);
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	time_t end = time(NULL);
	cout << "Data load complete" << endl;
	cout << "Spent time: " << end - start << endl;
	//list.print();
	cout << "Start copying" << endl;
	start = time(NULL);
	ForwardList list2 = list;
	cout << "End copying" << endl;
	end = time(NULL);
	cout << "Spent time: " << end - start << endl;
	//list2.print();  
#endif // PREFORMANCE_CHECK
}
