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
				string defaultValue;

				string* inregistrari = nullptr;
				int nrInregistrari = 0;

				void insertValues(string valoare)
				{
					inregistrari[nrInregistrari++] = valoare;
				}

				void updateValues(string valoare, string nouaValoare)
				{
					int k = 0;
					for (int i = 0; i < nrInregistrari; i++)
						if (inregistrari[i] == valoare)
						{
							inregistrari[i] = nouaValoare;
							k = 1;
						}
					if (k == 0)
						cout << "No results found!" << endl;
				}
		};
		coloana* c; //vector de coloane in tabela

		void createTable(string nume, coloana* c, int nrColoane) //adauga o tabela in baza de date 
		{
			this->nume = nume;
			this->nrColoane = nrColoane;
			this->c = new coloana[nrColoane];
			for (int i = 0; i < nrColoane; i++)
			{
				this->c[i].nume = c[i].nume;
				this->c[i].tip = c[i].tip;
				this->c[i].dimensiune = c[i].dimensiune;
				this->c[i].defaultValue = c[i].defaultValue;
			}
		}

		void dropTable()
		{
			nume = ""; //empty string
			nrColoane = 0; //noul nr de coloane al tabelei va fi 0
			delete[] c; //dezalocam vectorul de coloane
		}

		void displayTable()
		{
			cout << "Numele tabelei: " << nume << endl;
			for (int i = 0; i < nrColoane; i++)
			{
				cout << "Numele coloanei[" << i << "]: " << c[i].nume << endl;
				cout << "Tipul coloanei[" << i << "]: " << c[i].tip << endl;
				cout << "Dimensiunea coloanei[" << i << "]: " << c[i].dimensiune << endl;
				cout << "Valoarea prestabilita a coloanei[" << i << "]: " << c[i].defaultValue << endl;
			}
		}

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
				c[nrColoane].nume = token;
				c[nrColoane].nume.erase(c[nrColoane].nume.end() - 1);
				token = strtok(NULL, ", ");
				c[nrColoane].tip = token;
				token = strtok(NULL, ", ");
				c[nrColoane].dimensiune = (short)stoi(token);
				token = strtok(NULL, ", ");
				c[nrColoane].defaultValue = token;
				c[nrColoane].defaultValue.erase(c[nrColoane].defaultValue.end() - 1);
				token = strtok(NULL, "), ");
				nrColoane++;
			}

			tabela.createTable(numeTabela, c, nrColoane);
			tabele[nrTabele] = &tabela;
			nrTabele++;

			cout << tabele[0]->c[0].defaultValue << endl; // --> merge :) create table angajati ( (id, int, 10, 1) )

			break;
		}

		case display: {

			token = strtok(NULL, " ");
			string numeTabela = token;

			int k = 0;
			for (int i = 0; i < nrTabele && k == 0; i++)
				if (strcmp(tabele[i]->nume.c_str(), token) == 0)
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
			for(int i = 0; i < nrTabele && k == 0; i++)
				if (strcmp(tabele[i]->nume.c_str(), token) == 0)
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