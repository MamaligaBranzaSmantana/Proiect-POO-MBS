#pragma warning(disable:4996)

#include "Tabel.h"
#include <map>

using namespace std;

enum posibilitatiComenzi {
	eroare = 0,
	create = 1,
	drop = 2,
	display = 3
};

posibilitatiComenzi optiune(char* token)
{
	string s = token;
	map<string, posibilitatiComenzi> m{
		{"create table", create},
		{"drop table", drop},
		{"display table", display},
	};

	auto iterator = m.find(s);
	if (iterator != m.end())
		return iterator->second;
	return eroare; //in cazul in care optiunea nu este valabila intoarce eroare
}

int main()
{
	Tabel* tabele[20]; //pointer la vector de tabele --> aici stocam entitatile 
	int nrTabele = 0; //numarul initial de tabele este 0
	Tabel inregistrari[20][20]; //matricea care stocheaza inregistrarile

	//Consideram ca se introduce in consola comanda: "create table angajati( (), () )";
	//case pt identificarea comenzii
	cout << "Introduceti comanda dorita: ";
	string s;
	getline(cin >> ws, s);

	char* comandaIntrodusa = new char[strlen(s.c_str() + 1)];
	strcpy_s(comandaIntrodusa, strlen(s.c_str()) + 1, s.c_str());

	char* token = strtok(comandaIntrodusa, " ");
	char verif[50] = "";
	strcat(verif, token);
	strcat(verif, " ");
	token = strtok(NULL, " ");
	strcat(verif, token);

	switch (optiune(verif))
	{
	case create: {

		Tabel tabela;

		token = strtok(NULL, " ");
		string numeTabela = token;

		int nrColoane = 0;
		Tabel::coloana c[10];
		token = strtok(NULL, "(");
		while (token != NULL)
		{
			token = strtok(NULL, " (");
			//Citim atributele coloanei: nume, tip, dimensiune, defaultValue
			c[nrColoane].setNume(token);
			c[nrColoane].getNume().erase(c[nrColoane].getNume().end() - 1);
			token = strtok(NULL, ", ");
			c[nrColoane].setTip(token);
			token = strtok(NULL, ", ");
			c[nrColoane].setDimensiune((short)stoi(token));
			token = strtok(NULL, ", ");
			c[nrColoane].setDefaultValue(token);
			c[nrColoane].getDefaultValue().erase(c[nrColoane].getDefaultValue().end() - 1);
			token = strtok(NULL, "), ");
			nrColoane++;
		}

		tabela.createTable(numeTabela, c, nrColoane);
		tabele[nrTabele] = &tabela;
		nrTabele++;

		cout << tabele[0]->c[0].getDefaultValue() << endl; // --> merge :) create table angajati ( (id, int, 10, 1) )

		break;
	}

	case display: {

		token = strtok(NULL, " ");
		string numeTabela = token;

		int k = 0;
		for (int i = 0; i < nrTabele && k == 0; i++)
			if (strcmp(tabele[i]->getNume().c_str(), token) == 0)
			{
				tabele[i]->displayTable();
				k = 1;
			}

		if (k == 0)
			cout << "Nu exista tabela " << numeTabela << "!" << endl;

		break;
	}

	case drop: {
		token = strtok(NULL, " ");
		string numeTabela = token;

		int k = 0;
		for (int i = 0; i < nrTabele && k == 0; i++)
			if (strcmp(tabele[i]->getNume().c_str(), token) == 0)
			{
				tabele[i]->dropTable();
				k = 1;
			}


		if (k == 0)
			cout << "Nu exista tabela " << numeTabela << "!" << endl;

		break;
	}

	default: {
		cout << "Eroare de sintaxa!";
		break;
	}
	}

	return 0;
}