#include "Tabel.h"
#include <stdexcept>
#include <fstream>

void Tabel::createTable(string nume, coloana* c, int nrColoane) //adauga o tabela in baza de date
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

void Tabel::dropTable()
{
    nume = ""; //empty string
    nrColoane = 0; //noul nr de coloane al tabelei va fi 0
    delete[] c; //dezalocam vectorul de coloane
}
void Tabel::displayTable()
{
	string numeFisier = nume + "_structura.txt";
	ofstream f(numeFisier, ios::out);
	f << "Numele tabelei: " << this->getNume() << endl;
	for (int i = 0; i < this->getNrColoane(); i++)
	{
		f << "Numele coloanei[" << i << "]: " << this->c[i].getNume() << endl;
		f << "Tipul coloanei[" << i << "]: " << this->c[i].getTip() << endl;
		f << "Dimensiunea coloanei[" << i << "]: " << this->c[i].getDimensiune() << endl;
		f << "Valoarea prestabilita a coloanei[" << i << "]: " << this->c[i].getDefaultValue() << endl;
	}
}

void Tabel::select(Tabel::coloana* c, string* numeColoane, string coloanaa, int nrColoanesel, string valoare, string filename)
{
	int j, k = 0;
	ofstream f;
	f.open(filename, ios::out | ios::trunc);
	for (int i = 0; i < nrColoane; i++)
		if (c[i].getNume() == coloanaa)
			j = i;
	f << c[j].getNume() << endl << endl;
	for (int i = 0; i < c[j].getNrInregistrari(); i++)
		if (c[j].getInregistrari()[i] == valoare)
		{
			for (int z = 0; z < nrColoane; z++)
			{
				if (numeColoane[0] == "all")
					f << c[z].getInregistrari()[i] << " ";
				else
				{
					for (int ii = 0; ii < nrColoanesel; ii++)
						if (c[z].getNume() == numeColoane[ii])
						{
							f << c[z].getInregistrari()[i] << " ";
						}
				}
			}
			k = 1;
			f << endl;
		}

	f.close();
	if (k == 0)
		cout << "No results found!" << endl;
}
Tabel::Tabel()
{
    nume = "Necunoscut";
    nrColoane = 0;
    c = nullptr;
}
Tabel::Tabel(string nume) :Tabel()
{
    this->nume = nume;
}
Tabel::Tabel(string nume, int nrColoane, coloana* c)
{
    this->nume = nume;
    this->nrColoane = nrColoane;
    this->c = new coloana[nrColoane];
    for (int i = 0; i < nrColoane; i++)
        this->c[i] = c[i];
}
string Tabel::getNume()
{
    return nume;
}

int Tabel::getNrColoane()
{
    return nrColoane;
}

void Tabel::setNume(string nume)
{
    this->nume = nume;
}

void Tabel::setNrColoane(int nr)
{
    if (nr > 0)
        nrColoane = nr;
}
Tabel::Tabel(const Tabel& t)
{
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
Tabel& Tabel::operator=(const Tabel& t)
{
    if (c != nullptr)
        delete[] c;
    this->nume = t.nume;
    if (t.c != nullptr && t.nrColoane > 0)
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
    return *this;
}
Tabel::coloana& Tabel::operator[](int index)
{
    if (index >= 0 && index < nrColoane)
    {
        return c[index];
    }
    //aruncare exceptie
    throw invalid_argument("index invalid");
}
Tabel Tabel::operator+(short val)
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
Tabel Tabel::operator++()
{

    Tabel copie1 = *this, copie2 = *this;
    copie1.nrColoane++;
    delete[] copie1.c;
    copie1.c = new coloana[copie1.nrColoane];
    for (int i = 0; i < copie2.nrColoane; i++)
    {
        copie1.c[i] = copie2.c[i];
    }
    return copie1;
}
bool Tabel::operator==(Tabel t)
{
    if (this->nume != t.nume)
        return false;
    else
    {
        if (this->nrColoane != t.nrColoane)
        {
            return false;
        }
        else
        {
            int k = 0;
            for (int i = 0; i < nrColoane; i++)
            {
                if (this->c[i] == t.c[i])
                    k++;
            }
            if (k == nrColoane)
                return true;
            else
                return false;
        }
    }
}
Tabel Tabel::operator<=(Tabel t)
{
    if (this->nrColoane <= t.nrColoane)
        return *this;
    else
        return t;
}
Tabel Tabel::operator>=(Tabel t)
{
    if (this->nrColoane >= t.nrColoane)
        return *this;
    else
        return t;
}
bool Tabel::operator!()
{
    return nrColoane > 0;
}
Tabel::operator int()
{
    return nrColoane;
}
Tabel::~Tabel()
{
    if (c != nullptr)
    {
        delete[] c;
        c = nullptr;
    }
}
Tabel t;
ostream& operator<<(ostream& out, Tabel t)
{
    out << "nume: " << t.getNume() << endl;
    out << "Numar Coloane: " << t.getNrColoane() << endl;
    out << "Coloane: ";
    if (t.c != nullptr)
    {
        for (int i = 0; i < t.getNrColoane(); i++)
        {
            out << t.c[i] << " ";
        }
    }
    return out;
}
istream& operator>>(istream& in, Tabel& t)
{
    cout << "Nume = "; string x; in >> x; t.setNume(x);
    cout << "Numar Coloane = "; int y; in >> y; t.setNrColoane(y);
    if (t.c != nullptr)
    {
        delete[] t.c;
    }
    if (t.getNrColoane() > 0)
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
void deleteValues(Tabel t, Tabel::coloana* c, string numeColoana, string valoare, string filename, string filenamereal)
{
	int j, k = 0;
	for (int i = 0; i < t.getNrColoane(); i++)
		if (c[i].getNume() == numeColoana)
			j = i;
	int ctr = 0;
	for (int i = 0; i < c[j].getNrInregistrari(); i++)
		if (c[j].getInregistrari()[i] == valoare)
		{
			ctr++;
			k = 1;
		}
	string* cc; int ctr2 = 0;
	cc = new string[c[j].getNrInregistrari() - ctr];
	for (int i = 0; i < c[j].getNrInregistrari(); i++)
		if (c[j].getInregistrari()[i] != valoare)
		{
			cc[ctr2++] = c[j].getInregistrari()[i];
		}
	c->setInregistrari(cc, ctr2 - 1);
	if (k == 0)
		cout << "No results found!" << endl;
	else
	{
		ofstream f(filename, ios::binary | ios::trunc);
		for (int j = 0; j < t.nrColoane; j++)
		{
			f.write((char*)c[j].getNrInregistrari(), sizeof(c[j].getNrInregistrari()));
			for (int i = 0; i < c[j].getNrInregistrari(); i++)
			{
				f.write((char*)&c[j].getInregistrari()[i], sizeof(c[j].getInregistrari()[i]));
			}
		}
		f.close();
		ofstream s;
		s.open(filenamereal, ios::out | ios::trunc);
		for (int j = 0; j < t.nrColoane; j++)
		{
			s << c[j].getNrInregistrari() << endl;
			for (int i = 0; i < c[j].getNrInregistrari(); i++)
			{
				s << c[j].getInregistrari()[i] << " ";
			}
		}
		s.close();
	}
}