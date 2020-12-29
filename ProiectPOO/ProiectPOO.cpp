#pragma warning(disable:4996)

#include "Tabel.h"
#include <map>

using namespace std;

class Tabel
{
private:
	string nume;
	int nrColoane; //nr de coloane ale tabelei

public:
	class coloana
	{
	private:
		string nume;
		string tip;
		short dimensiune;
		string defaultValue = "NULL";
		string* inregistrari = nullptr;
		int nrInregistrari = 0;
	public:
		string getNume()
		{
			return nume;
		}
		void setNume(string n)
		{
			nume = n;
		}
		string getTip()
		{
			return tip;
		}
		void setTip(string t)
		{
			tip = t;
		}
		short getDimensiune()
		{
			return dimensiune;
		}
		void setDimensiune(short d)
		{
			dimensiune = d;
		}
		string getDefaultValue()
		{
			return defaultValue;
		}
		void setDefaultValue(string df)
		{
			defaultValue = df;
		}
		int getNrInregistrari()
		{
			return nrInregistrari;
		}
		void setNrInregistrari(int nr)
		{
			nrInregistrari = nr;
		}
		string* getInregistrari()
		{
			if (inregistrari != nullptr)
			{
				string* copie = new string[nrInregistrari];
				for (int i = 0; i < nrInregistrari; i++)
				{
					copie[i] = inregistrari[i];

				}
				return copie;
			}
			else
			{
				return nullptr;
			}
		}
		void setInregistrari(string* inr, int nrI)
		{
			if (inr != nullptr && nrI != 0)
			{
				nrInregistrari = nrI;
				if (inregistrari != nullptr)
				{
					delete[] inregistrari;

				}
				inregistrari = new string[nrI];
				for (int i = 0; i < nrI; i++)
				{
					inregistrari[i] = inr[i];
				}
			}
		}
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
		coloana& operator=(const coloana& c)
		{
			if (inregistrari != nullptr)
				delete[] inregistrari;
			this->nume = c.nume;
			this->tip = c.tip;
			this->dimensiune = c.dimensiune;
			this->defaultValue = c.defaultValue;
			if (c.inregistrari != nullptr && c.nrInregistrari > 0)
			{
				this->nrInregistrari = c.nrInregistrari;
				for (int i = 0; i < nrInregistrari; i++)
				{
					this->inregistrari[i] = c.inregistrari[i];
				}
			}
			else
			{
				this->nrInregistrari = 0;
				this->inregistrari = nullptr;
			}
		}
		string& operator[](int index)
		{
			if (index >= 0 && index < nrInregistrari)
			{
				return inregistrari[index];
			}
			//aruncare exceptie
			throw exception("index invalid");
		}
		coloana operator+(short val)
		{
			if (val > 0)
			{
				coloana copie = *this;
				copie.dimensiune += val;
				return copie;
			}
			else
				throw "Invalid value";
		}
		coloana operator++()
		{
			this->dimensiune++;
			return *this;
		}
		coloana operator++(int i)
		{
			coloana copie = *this;
			this->dimensiune++;
			return copie;
		}
		~coloana()
		{
			if (inregistrari != nullptr)
			{
				delete[] inregistrari;
				inregistrari = nullptr;
			}
		}
		friend ostream& operator<<(ostream&, coloana);
		friend istream& operator>>(istream&, coloana&);

	};
	coloana* c; //vector de coloane in tabela
	void createTable(string nume, coloana c[], int nrColoane) //adauga o tabela in baza de date 
	{
		this->nume = nume;
		this->nrColoane = nrColoane;
		this->c = new coloana[nrColoane];
		for (int i = 0; i < nrColoane; i++)
		{
			this->c[i].setNume(c[i].getNume());
			this->c[i].setTip(c[i].getTip());
			this->c[i].setDimensiune(c[i].getDimensiune());
			this->c[i].setDefaultValue(c[i].getDefaultValue());
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
			cout << "Numele coloanei[" << i << "]: " << c[i].getNume() << endl;
			cout << "Tipul coloanei[" << i << "]: " << c[i].getTip() << endl;
			cout << "Dimensiunea coloanei[" << i << "]: " << c[i].getDimensiune() << endl;
			cout << "Valoarea prestabilita a coloanei[" << i << "]: " << c[i].getDefaultValue() << endl;
		}
	}



	void select(coloana* c, string numeColoana, string valoare)
	{
		int j, k = 0;
		for (int i = 0; i < nrColoane; i++)
			if (c[i].getNume() == numeColoana)
				j = i;
		cout << c[j].getNume() << " " << c[j].getTip() << " " << c[j].getDimensiune() << " " << c[j].getDefaultValue() << endl << endl;
		for (int i = 0; i < c[j].getNrInregistrari(); i++)
			if (c[j].getInregistrari()[i] == valoare)
			{
				for (int z = 0; z < nrColoane; z++)
					cout << c[z].getInregistrari()[i] << " ";
				k = 1;
			}
		if (k == 0)
			cout << "No results found!" << endl;
	}
	string getNume()
	{
		return nume;
	}
	int getNrColoane()
	{
		return nrColoane;
	}
	void setNume(string nume)
	{
		this->nume = nume;
	}
	void setNrColoane(int nr)
	{
		if (nr > 0)
			nrColoane = nr;
	}

	Tabel& operator=(const Tabel& t)
	{
		if (c != nullptr)
			delete[] c;
		this->nume = t.nume;
		if (c != nullptr && nrColoane > 0)
		{
			this->nrColoane = t.nrColoane;
			this->c = new coloana[t.nrColoane];
			for (int i = 0; i < nrColoane; i++)
				this->c[i] = t.c[i];
		}
		else
		{
			this->nrColoane = 0;
			this->c = nullptr;
		}

	}
	coloana& operator[](int index)
	{
		if (index >= 0 && index < nrColoane)
		{
			return c[index];
		}
		//aruncare exceptie
		throw exception("index invalid");
	}
	Tabel operator+(short val)
	{
		if (val > 0)
		{
			Tabel copie1 = *this, copie2 = *this;
			copie1.nrColoane += val;
			delete[] copie1.c;
			copie1.c = new coloana[copie1.nrColoane];
			for (int i = 0; i < copie2.nrColoane; i++)
			{
				copie1.c[i] = copie2.c[i];
			}
			return copie1;
		}
		else
			throw "Invalid value";
	}
	~Tabel()
	{
		if (c != nullptr)
		{
			delete[] c;
			c = nullptr;
		}
	}
	friend ostream& operator<<(ostream&, Tabel);
	friend istream& operator>>(istream&, Tabel&);
	friend void deleteValues(Tabel t, coloana* c, string numeColoana, string valoare);
};

void deleteValues(Tabel t, Tabel::coloana* c, string numeColoana, string valoare)
{
	int j, k = 0;
	for (int i = 0; i < t.getNrColoane(); i++)
		if (c[i].getNume() == numeColoana)
			j = i;
	for (int i = 0; i < c[j].getNrInregistrari(); i++)
		if (c[j].getInregistrari()[i] == valoare)
		{
			k = 1;
			string* zz;
			zz = new string[t.getNrColoane()];
			for (int i = 0; i < t.getNrColoane(); i++)
			{
				zz[i] = c[i].getDefaultValue();
			}
			c[i].setInregistrari(zz, t.getNrColoane());
		}
	if (k == 0)
		cout << "No results found!" << endl;
}

ostream& operator<<(ostream& out, Tabel t)
{
	out << "nume: " << t.nume << endl;
	out << "Numar Coloane: " << t.nrColoane << endl;
	out << "Coloane: ";
	if (t.c != nullptr)
	{
		for (int i = 0; i < t.nrColoane; i++)
		{
			out << t.c[i] << " ";
		}
	}
	return out;
}
ostream& operator<<(ostream& out, Tabel::coloana c)
{
	out << "Nume: " << c.getNume() << endl;
	out << "Tip: " << c.getTip() << endl;
	out << "Dimensiune: " << c.getDimensiune() << endl;
	out << "Default Value: " << c.getDefaultValue() << endl;
	out << "Numar inregistrari: " << c.getNrInregistrari() << endl;
	if (c.getInregistrari() != nullptr)
	{
		for (int i = 0; i < c.getNrInregistrari(); i++)
		{
			out << c.getInregistrari()[i] << " ";
		}
	}
	return out;
}
istream& operator>>(istream& in, Tabel& t)
{
	cout << "Nume = "; in >> t.nume;
	cout << "Numar Coloane = "; in >> t.nrColoane;
	if (t.c != nullptr)
	{
		delete[] t.c;
	}
	if (t.nrColoane > 0)
	{
		t.c = new Tabel::coloana[t.getNrColoane()];
		for (int i = 0; i < t.getNrColoane(); i++)
		{
			cout << "coloane[" << i << "] = ";
			in >> t.c[i];
		}
	}
	else
	{
		t.nrColoane = 0;
		t.c = nullptr;
	}
	return in;
}
istream& operator>>(istream& in, Tabel::coloana& c)
{
	cout << "Nume = "; string x; in >> x; c.setNume(x);
	cout << "Tip= "; string y; in >> y; c.setTip(y);
	cout << "Dimensiune= "; short z; in >> z; c.setDimensiune(z);
	cout << "Default Value= "; string xx; in >> xx; c.setDefaultValue(xx);
	cout << "Numar inregistrari= "; int yy; in >> yy; c.setNrInregistrari(yy);
	if (c.getInregistrari() != nullptr)
	{
		delete[] c.getInregistrari();
	}
	string* zz;
	zz = new string[yy];
	if (c.getNrInregistrari() > 0)
	{

		for (int i = 0; i < yy; i++)
		{
			cout << "Inregistrari[" << i << "] = ";
			in >> zz[i];
		}
		c.setInregistrari(zz, yy);
	}
	else
	{
		c.setInregistrari(nullptr, 0);
	}
	return in;
}
enum posibilitatiComenzi {
	eroare = 0,
	create = 1,
	drop = 2,
	display = 3,
	insert = 4,
	select = 5
};

posibilitatiComenzi optiune(char* token)
{
	string s = token;
	map<string, posibilitatiComenzi> m{
		{"create table", create},
		{"drop table", drop},
		{"display table", display},
		{"insert into", insert},
		{"select", select}
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

	case insert:
	{
		//token = strtok(NULL, " ");
		//string numeTabela = token;
		//int k = 0;
		//for (int i = 0; i < nrTabele && k == 0; i++)
		//	if (strcmp(tabele[i]->getNume().c_str(), token) == 0)
		//	{
		//		k = i;
		//	}

		//if (k == 0)
		//{
		//	cout << "Nu exista tabela " << numeTabela << "!" << endl;
		//	break;
		//}
		//else
		//{
		//	int j = 0;
		//	token = strtok(NULL, " ,()");
		//	string* p = new string[tabele[k]->getNrColoane()];
		//	while (token != NULL)
		//	{
		//		p[j] = token;
		//		token = strtok(NULL, " ,()");
		//		j++;
		//	}
		//	
		//	int nr_inregistrari;
		//}
	}

	case select:
	{

	}

	default: {
		cout << "Eroare de sintaxa!";
		break;
	}
	}

	return 0;
}