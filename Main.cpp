#include "No.h"

int main()
{
	ArvoreB arvore;
	arvore.Insere(20);
	arvore.Insere(60);
	arvore.Insere(40);
	arvore.Insere(80);
	arvore.Insere(70);
	arvore.Insere(10);
	arvore.Insere(30);
	arvore.Insere(15);
	arvore.Insere(75);
	arvore.Insere(85);
	arvore.Insere(90);
	bool existe = arvore.Existe(20);
	existe = arvore.Existe(60);
	existe = arvore.Existe(40);
	existe = arvore.Existe(80);
	existe = arvore.Existe(70);
	existe = arvore.Existe(10);
	existe = arvore.Existe(30);
	existe = arvore.Existe(15);
	existe = arvore.Existe(75);
	existe = arvore.Existe(85);
	existe = arvore.Existe(90);
	
	existe = arvore.Existe(66);
	existe = arvore.Existe(88);
	existe = arvore.Existe(152);
	existe = arvore.Existe(895);
	existe = arvore.Existe(658);

	int f = 0;
}
