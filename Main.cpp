#include "No.h"

int main()
{
	BTree arvore;
	arvore.Insert(20);
	arvore.Insert(60);
	arvore.Insert(40);
	arvore.Insert(80);
	arvore.Insert(70);
	arvore.Insert(10);
	arvore.Insert(30);
	arvore.Insert(15);
	arvore.Insert(75);
	arvore.Insert(85);
	arvore.Insert(90);
	bool exists = arvore.Exists(20);
	exists = arvore.Exists(60);
	exists = arvore.Exists(40);
	exists = arvore.Exists(80);
	exists = arvore.Exists(70);
	exists = arvore.Exists(10);
	exists = arvore.Exists(30);
	exists = arvore.Exists(15);
	exists = arvore.Exists(75);
	exists = arvore.Exists(85);
	exists = arvore.Exists(90);
	
	exists = arvore.Exists(66);
	exists = arvore.Exists(88);
	exists = arvore.Exists(152);
	exists = arvore.Exists(895);
	exists = arvore.Exists(658);

	int f = 0;
}
