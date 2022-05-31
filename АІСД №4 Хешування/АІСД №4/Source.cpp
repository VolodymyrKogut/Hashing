#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Node
{
	Node()
	{
		next = nullptr;
	}
	Node* next;
	char element[256] = {};
};

class Dictionary
{
public:
	Dictionary(int NUM)
	{
		this->NUM = NUM;
		node = new Node * [NUM];

		for (int i = 0; i < NUM; i++)
			node[i] = new Node[NUM];
	}

	~Dictionary()
	{
		delete[]node;
	}

	void makenull()
	{
		for (int i = 0; i < NUM; i++)
			node[i] = NULL;
	}

	bool member(char str[])
	{
		Node* temporary = node[hash(str)];
		while (temporary != nullptr)
		{
			if (temporary->element == str)
				return true;
			temporary = temporary->next;
		}
		return false;
	}

	int insert(char str[])
	{
		if (!member(str))
		{
			Node* temporary = node[hash(str)];
			if (temporary->element == "")
				strcpy(temporary->element, str);
			else
			{
				while (temporary->next != nullptr)
					temporary = temporary->next;
				temporary->next = new Node();
				strcpy(temporary->next->element, str);
			}
			return 1;
		}
		return 0;
	}

	int Delete(char str[])
	{
		Node* temporary = node[hash(str)];
		if (!member(str))
			return 0;

		if (temporary->element == str)
			node[hash(str)] = node[hash(str)]->next;
		else
		{
			while (temporary->next != nullptr)
			{
				if (temporary->next->element == str)
				{
					Node* t = temporary->next;
					temporary->next = temporary->next->next;
					delete t;
					return 1;
				}
				temporary = temporary->next;
			}
		}
		return 0;
	}

	void print()
	{
		for (int i = 0; i < NUM; i++)
		{
			std::cout << "-> " << i + 1 << " = ";
			Node* temporary = node[i];
			while (temporary != nullptr)
			{
				std::cout << temporary->element << " ";
				temporary = temporary->next;
			}
			std::cout << std::endl;
		}
	}

private:
	int hash(char str[])
	{
		int sum = 0;
		int i = 0;

		while (str[i] != '\0')
		{
			sum += int(str[i]);
			i++;
		}
		return sum % NUM;
	}

	int NUM;
	Node** node;
};

int main()
{
	Dictionary test(15);
	char str[256];

	std::cout << "Filling:\n" << std::endl;
	for (int i = 0; i < 15; i++)
	{
		std::cin.getline(str, 256);
		test.insert(str);
	}

	std::cout << "\Output:" << std::endl;
	test.print();

	return 0;
}