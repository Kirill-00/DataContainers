#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

class Tree
{
	class Element
	{
		int Data;                //Значение элемента
		Element* pLeft, * pRight;//Адреса потомков
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout<< "EDestructor:\t" << this << endl;
		}
		friend class Tree;
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
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}

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

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	int minValue(Element* Root) const
	{
		if (Root->pLeft == nullptr)return Root->Data;
		minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const
	{
		if (Root->pRight == nullptr)return Root->Data;
		maxValue(Root->pRight);
	}
	int count(Element* Root)
	{
		if (Root == nullptr)return 0;
		return count(Root->pRight) + count(Root->pLeft) + 1;
	}
	int sum(Element* Root)
	{
		if (Root == nullptr)return 0;
		return (Root->Data + sum(Root->pRight) + sum(Root->pLeft));
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "Введите колличество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Минимальное значение: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Количество элементов дерева: " << tree.count(tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << tree.sum(tree.getRoot()) << endl;

}