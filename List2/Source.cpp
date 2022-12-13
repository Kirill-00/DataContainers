#include"List.h"
#include"List1.cpp"

//#define BASE_CHECK
//#define COUNT_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	//list.reverse_print();
	cout << "Введите индекс удоляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	list.reverse_print();
	cout << delimiter << endl;

	//List list2 = list;		//CopyConstructor
	List list2;
	list2 = list;			//CopyAssignment
	list2.print();
	list2.reverse_print();
#endif // COUNT_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::ConstReverseIterator rit = list.rbegin(); rit != list.rend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;

	List list2 = { 34, 55, 89 };
	List list3 = list + list2;
	for (int i : list)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // ITERATORS_CHECK

	List<int> i_list = { 2,5,8,13,21 };
	i_list.print();
	i_list.reverse_print();
	List<int> i_list_2 = { 34,55,89 };
	List<int> i_list_3 = i_list + i_list_2;
	for (int i : i_list_3)cout << i << tab; cout << endl;

	List<double>d_list_1 = { 2.7,3.14,5.3,8.9 };
	d_list_1.print();
	d_list_1.reverse_print();
	List<double>d_list_2 = { 25.4,88.97,98.2 };

	List<double>d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_3)cout << i << tab; cout << endl;

	List<std::string>s_list_1 = { "Хорошо","живет","на","свете","Винни-Пух" };
	List<std::string>s_list_2 = { "Вот","и","сказочке","конец" };
	List<std::string>s_list_3 = s_list_1 + s_list_2;
	for (std::string i : s_list_3)cout << i << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list_3.rbegin(); it != s_list_3.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

}