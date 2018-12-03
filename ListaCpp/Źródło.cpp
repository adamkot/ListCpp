#include <iostream> 
#include <string>
using namespace std; 

class list
{
private:
	bool empty = true; //czy lista jest pusta
	//do przechowywania "obiektu" w liœcie. Przechowuje string i wskazania na lewy i prawy obiekt
	struct item 
	{
		string z;
		item* left = NULL;
		item* right = NULL;
	};
	item* lastItem; //ostatni zapisany do listy

public:
	void add(string text);
	void add(string text, int index);
	void del(string text);
	string listToString();
};

//dodawanie do listy (na koñcu)
void  list::add(string text)
{
	if (empty) 
	{
		item* i = new item;
		i->z = text;
		i->left = NULL;
		i->right = NULL;
		lastItem = i;
		empty = false;
	}
	else
	{
		for (item* x = lastItem; x != NULL; x = x->left)
		{
			if (x->z == text) {
				cout << "element jest juz na liscie" << endl;
				break;
			}
			else if (x->left == NULL)
			{
				item* i = new item;
				i->z = text;
				lastItem->right = i;
				i->left = lastItem;
				i->right = NULL;
				lastItem = i;
			}
		}
	}
}

void list::add(string text, int index)
{
	if (index > 0) 
	{
		if (!empty)
		{
			int i = 0;
			for (item* x = lastItem; x != NULL; x = x->left)
			{
				i++;
				if (x->z == text) {
					cout << "element jest juz na liscie" << endl;
					i = -1;
					break;
				}
			}
			if (i >= index)
			{
				item* x = lastItem;
				item* y = x;
				for (; x != NULL; )
				{
					y = x;
					x = x->left;
				}
				
				for (int i = 0; i < index; i++)
				{
					y = y->right;
				}
				item* i = new item;
				i->z = text;
				y->left->right = i;
				i->left = y->left;
				i->right = y;
				y->left = i;
			}
			else 
			{
				cout << "index poza zakresem listy" << endl;
			}
		}
	}
	else
	{
		cout << "podano niewlasciwy index" << endl;
	}
	
}

void list::del(string text)
{
	if (!empty)
	{
		
		for(item* x = lastItem; x != NULL; x = x->left)
		{
			if (x->z == text) {
				if (x->left == NULL && x->right == NULL)
				{
					//jedyny
					lastItem = NULL;
					empty = true;
				}
				else if (x->left == NULL)
				{
					//pierwszy
					x->right->left = NULL;
				}
				else if (x->right == NULL)
				{
					//ostatni
					x->left->right = NULL;
					lastItem = x->left;
				}
				else
				{
					//œrodek
					x->left->right = x->right;
					x->right->left = x->left;
				}
				free(x);
				break;
			} 
		}
	}
	else
	{
		cout << "lista jest pusta" << endl;
	}
}

string list::listToString()
{
	string listText = "";
	if(!empty) 
	{
		item* x = lastItem;
		while (x->left != NULL)
		{
			x = x->left;
		}
		while (x != NULL)
		{
			listText = listText + x->z + "; ";
			x = x->right;
		}
	}
	return listText;
}

int main()
{
	list *l = new list; // nowa lista
	l->add("test_0"); //dodaj do listy
	l->add("test_1"); //dodaj do listy kolejny
	l->add("test_2"); //dodaj do listy kolejny
	l->add("test_3"); //dodaj do listy kolejny
	cout << l->listToString() << endl; //wypisz listê
	l->add("test_1+", 1);
	cout << l->listToString() << endl; //wypisz listê
	l->del("test_1");
	cout << l->listToString() << endl; //wypisz listê
	getchar();
	return 0;
}
