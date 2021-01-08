#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
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
		coloana();
		coloana(string nume, string tip, short dimensiune, string defaultValult);
		coloana(string nume, int nrInregistrari, string* inregistrari);
		string getNume();
		void setNume(string n);
		string getTip();
		void setTip(string t);
		short getDimensiune();
		void setDimensiune(short d);
		string getDefaultValue();
		void setDefaultValue(string df);
		int getNrInregistrari();
		void setNrInregistrari(int nr);
		string* getInregistrari();
		void setInregistrari(string* inr, int nrI);
		void insertValues(string valoare, string filename, string filenamereal);
		void updateValues(string valoare, string nouaValoare, string filename, string filenamereal);
		coloana(const coloana& c);
		coloana& operator=(const coloana& c);
		string& operator[](int index);
		coloana operator+(short val);
		coloana operator++();
		coloana operator++(int i);
		bool operator==(coloana c);
		coloana operator<=(coloana c);
		coloana operator>=(coloana c);
		bool operator!();
		explicit operator int();
		~coloana();
		friend ostream& operator<<(ostream&, coloana);
		friend istream& operator>>(istream&, coloana&);
	};
	coloana* c; //vector de coloane in tabela
	void createTable(string nume, coloana c[], int nrColoane); //adauga o tabela in baza de date
	void dropTable();
	void displayTable();
	void select(coloana* c, string* numeColoane, string coloanaa, int nrColoane, string valoare, string filename);
	Tabel();
	Tabel(string nume);
	Tabel(string nume, int nrColoane, coloana* c);
	string getNume();
	int getNrColoane();
	void setNume(string nume);
	void setNrColoane(int nr);
	Tabel(const Tabel& t);
	Tabel& operator=(const Tabel& t);
	coloana& operator[](int index);
	Tabel operator+(short val);
	Tabel operator++();
	bool operator==(Tabel t);
	Tabel operator<=(Tabel t);
	Tabel operator>=(Tabel t);
	bool operator!();
	explicit operator int();
	~Tabel();
	friend ostream& operator<<(ostream&, Tabel);
	friend istream& operator>>(istream&, Tabel&);
	friend void deleteValues(Tabel t, coloana* c, string numeColoana, string valoare, string filename, string filenamereal);
};