#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;				//Значение элемента
		Element *pLeft, *pRight;//Адреса потомков
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool isLeaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree():Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return(double)Sum(Root) / Count(Root);
	}
	int Depth()const
	{
		return Depth(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		minValue(Root->pLeft);*/
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		maxValue(Root->pRight);*/
		if (Root == nullptr)return 0;
		return Root->pRight ? minValue(Root->pRight) : Root->Data;
	}
	int Count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		return count(Root->pRight) + count(Root->pLeft) + 1;*/
		return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	int Sum(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		return (Root->Data + sum(Root->pRight) + sum(Root->pLeft));*/
		return !Root ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Depth(Root->pLeft) < Depth(Root->pRight))return Depth(Root->pRight) + 1;
		else return Depth(Root->pLeft) + 1;*/
		int left_depth = Depth(Root->pLeft) + 1;
		int right_depth = Depth(Root->pRight) + 1;
		return left_depth > right_depth ? left_depth : right_depth;
		/*return !Root ? 0 : 
			Depth(Root->pLeft) > Depth(Root->pRight) ?
			Depth(Root->pLeft) + 1 :
			Depth(Root->pRight) + 1;*/
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
	int n;
	cout << "Введите колличество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.clear();
	tree.print();
	cout << endl;
	cout << "Минимальное значение: " << tree.minValue() << endl;
	cout << "Максимальное значение: " << tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree.Count() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Среднее-арефметическое элементов дерева: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

	UniqueTree unique_tree;
	for (int i = 0; i < n; i++)
	{
		unique_tree.insert(rand() % 100);
	}
	unique_tree.print();
	cout << "Минимальное значение в дереве: " << unique_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << unique_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << unique_tree.Count() << endl;
	cout << "Сумма элементов в дереве: " << unique_tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов в дереве: " << unique_tree.Avg() << endl;
	cout << "Глубина дерева: " << unique_tree.Depth() << endl;
#endif // BASE_CHECK

	Tree my_tree = { 50, 25, 75, 16, 32, 58, 85, 48, 49, 64, 91 };
	my_tree.print();
	cout << "Минимальное значение в дереве: " << my_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << my_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << my_tree.Count() << endl;
	cout << "Сумма элементов в дереве: " << my_tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов в дереве: " << my_tree.Avg() << endl;
	cout << "Глубина дерева: " << my_tree.Depth() << endl;

	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	my_tree.erase(value);
	my_tree.print();
}