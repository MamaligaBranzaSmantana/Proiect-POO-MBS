#include "Tabel.h"

Tabel::coloana::coloana()
{
	nume = "Necunoscut";
	tip = "Necunoscut";
	dimensiune = 0;
	defaultValue = "NULL";
	nrInregistrari = 0;
	inregistrari = nullptr;
}

Tabel::coloana::coloana(string nume, string tip, short dimensiune, string defaultValue) :coloana()
{
	this->nume = nume;
	this->tip = tip;
	this->dimensiune = dimensiune;
	this->defaultValue = defaultValue;
}

Tabel::coloana::coloana(string nume, int nrInregistrari, string* inregistrari) :coloana()
{
	this->nume = nume;
	if (nrInregistrari > 0 && inregistrari != nullptr)
	{
		this->nrInregistrari = nrInregistrari;
		this->inregistrari = new string[nrInregistrari];
		for (int i = 0; i < nrInregistrari; i++)
			this->inregistrari[i] = inregistrari[i];
	}
}

string Tabel::coloana::getNume()
{
	return nume;
}
void Tabel::coloana::setNume(string n)
{
	nume = n;
}
string Tabel::coloana::getTip()
{
	return tip;
}
void Tabel::coloana::setTip(string t)
{
	tip = t;
}
short Tabel::coloana::getDimensiune()
{
	return dimensiune;
}
void Tabel::coloana::setDimensiune(short d)
{
	dimensiune = d;
}
string Tabel::coloana::getDefaultValue()
{
	return defaultValue;
}
void Tabel::coloana::setDefaultValue(string df)
{
	defaultValue = df;
}
int Tabel::coloana::getNrInregistrari()
{
	return nrInregistrari;
}
void Tabel::coloana::setNrInregistrari(int nr)
{
	nrInregistrari = nr;
}
string* Tabel::coloana::getInregistrari()
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
void Tabel::coloana::setInregistrari(string* inr, int nrI)
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
void Tabel::coloana::insertValues(string valoare)
{
	inregistrari[nrInregistrari++] = valoare;
}

void Tabel::coloana::updateValues(string valoare, string nouaValoare)
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
Tabel::coloana::coloana(const coloana& c)
{
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
Tabel::coloana& Tabel::coloana::operator=(const Tabel::coloana& c)
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
	return *this;
}
string& Tabel::coloana::operator[](int index)
{
	if (index >= 0 && index < nrInregistrari)
	{
		return inregistrari[index];
	}
	//aruncare exceptie
	throw exception("index invalid");
}
Tabel::coloana Tabel::coloana::operator+(short val)
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
Tabel::coloana Tabel::coloana::operator++()
{
	this->dimensiune++;
	return *this;
}
Tabel::coloana Tabel::coloana::operator++(int i)
{
	coloana copie = *this;
	this->dimensiune++;
	return copie;
}
bool Tabel::coloana::operator==(coloana c)
{
	if (this->nume != c.nume)
		return false;
	else
	{
		if (this->tip != c.tip)
			return false;
		else
		{
			if (this->dimensiune != c.dimensiune)
				return false;
			else
			{
				if (this->defaultValue != c.defaultValue)
					return false;
				else
				{
					if (this->nrInregistrari != c.nrInregistrari)
						return false;
					else
					{
						if (this->inregistrari != c.inregistrari)
							return false;
						else
							return true;
					}
				}
			}
		}

	}
}
Tabel::coloana Tabel::coloana::operator<=(coloana c)
{
	if (this->dimensiune <= c.dimensiune)
		return *this;
	else
		return c;
}
Tabel::coloana Tabel::coloana::operator>=(coloana c)
{
	if (this->dimensiune >= c.dimensiune)
		return *this;
	else
		return c;
}
bool Tabel::coloana::operator!()
{
	return nrInregistrari > 0;
}
inline Tabel::coloana::operator int()
{
	return nrInregistrari;
}
Tabel::coloana::~coloana()
{
	if (inregistrari != nullptr)
	{
		delete[] inregistrari;
		inregistrari = nullptr;
	}
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
