#pragma warning(disable:4996)

#include <iostream>
#include <string>
#include <string.h>
#include <map>

using namespace std;

class Tabel {
	public:
		string nume;
		int nrColoane; //nr de coloane ale tabelei
		class coloana {
			public:
				string nume;
				string tip;
				short dimensiune;
				int defaultValue;
		};
		coloana* c; //vector de coloane in tabela
};

Tabel tabele[20]; //vector de tabele --> aici stocam entitatile 
int nrTabele = 0; //numarul initial de tabele este 0

void addTable(Tabel newTable) //adauga o tabela in baza de date //Functia asta este de fapt exact ce fac in create tabel deci nu vad rostul clasei createTable 
{
	tabele[nrTabele].nume = newTable.nume;
	for (int i = 0; i < newTable.nrColoane; i++)
	{
		tabele[nrTabele].c = new Tabel::coloana[newTable.nrColoane];
		tabele[nrTabele].c[i].nume = newTable.c[i].nume;
		tabele[nrTabele].c[i].tip = newTable.c[i].tip;
		tabele[nrTabele].c[i].dimensiune = newTable.c[i].dimensiune;
		tabele[nrTabele].c[i].defaultValue = newTable.c[i].defaultValue;
	}
	nrTabele++;
}

class comanda {  //interfata comanda mama -- identifica tipul comenzii
	public: 
		virtual void idComanda(string comandaIntrodusa) = 0; //functie virtuala care identifica tipul comenzii --> Daca este select, insert, create etc. (cu un switch)
};

class createTable : public comanda {
	public:
		Tabel t; //declarare tabela
		
		void idComanda(string comandaIntrodusa) override //citim numele, tipul, etc. al fiecarei coloane
		{

		}
		
		createTable(string nume, Tabel::coloana* c, int nrColoane) //connstructor cu parametrii
		{
			t.nume = nume;
			t.nrColoane = nrColoane;
			t.c = new Tabel::coloana[nrColoane];
			for (int i = 0; i < nrColoane; i++)
			{
				t.c[i].nume = c[i].nume;
				t.c[i].tip = c[i].tip;
				t.c[i].dimensiune = c[i].dimensiune;
				t.c[i].defaultValue = c[i].defaultValue;
			}
		}
};

class dropTable { //ar trebui sa stearga de tot Tabelul t
	public:
		dropTable(Tabel* t, int i)
		{
			t[i].nume = ""; //empty string
			t[i].nrColoane = 0; //noul nr de coloane al tabelei va fi 0
			delete[] t[i].c; //dezalocam vectorul de coloane
		}
};

class displayTable {
	public:

};

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
	//consideram ca se introduce in consola comanda: "create table angajati( (), () )";
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
			token = strtok(NULL, " ");
			string numeTabela = token;

			int nrColoane = 0;
			Tabel::coloana c[10];
			token = strtok(NULL, "(");
			while (token != NULL)
			{
				token = strtok(NULL, " (");
				//Citim atributele coloanei: nume, tip, dimensiune, defaultValue
				c[nrColoane].nume = token;
				token = strtok(NULL, ",");
				c[nrColoane].tip = token;
				token = strtok(NULL, ",");
				c[nrColoane].dimensiune = (short)token;
				token = strtok(NULL, ",");
				c[nrColoane].defaultValue = (int)token;
				token = strtok(NULL, "), ");
				nrColoane++;
			}

			createTable tabela(numeTabela, c, nrColoane);
			addTable(tabela.t);

			break;
		}

		case display: {

			break;
		}

		case drop: {
			token = strtok(NULL, " ");
			string numeTabela = token;

			int k = 0;
			for(int i = 0; i <nrTabele && k == 0; i++)
				if (strcmp(tabele[i].nume.c_str(), token) == 0)
				{
					dropTable tabela(tabele, i);
					k = 1;
				}
			
			break;
		}

		default: {
			cout << "Eroare de sintaxa!";
			break;
		}
	}

	return 0;
}