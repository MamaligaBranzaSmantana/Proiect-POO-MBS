#pragma warning(disable:4996)

#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <fstream>
#include "Tabel.h"
using namespace std;

enum posibilitatiComenzi {
    eroare = 0,
    create = 1,
    drop = 2,
    display = 3,
    insert = 4,
    deletee = 5, //folosim deletee fiindca delete deja exista
    select = 6,
    update = 7
};

posibilitatiComenzi optiune(char* token)
{
    string s = token;
    map<string, posibilitatiComenzi> m{
        {"create table", create},
        {"drop table", drop},
        {"display table", display},
        {"insert into", insert},
        {"delete from", deletee},
        {"select", select},
        {"update", update}
    };

    auto iterator = m.find(s);
    if (iterator != m.end())
        return iterator->second;
    return eroare; //in cazul in care optiunea nu este valabila intoarce eroare
}

int main()
{
    Tabel tabele[5]; //pointer la vector de tabele --> aici stocam entitatile
    int nrTabele = 0; //numarul initial de tabele este 0
    Tabel inregistrari[5][5]; //matricea care stocheaza inregistrarile

    //Consideram ca se introduce in consola comanda: "create table angajati( (), () )";
    //case pt identificarea comenzii
    
    cout << "Introduceti comanda dorita: "; //proiectPOO.exe comenzi.txt
    string s;
    getline(cin >> ws, s);

    char* comandaIntrodusa = new char[strlen(s.c_str() + 1)];
    strcpy(comandaIntrodusa, s.c_str());

    char* token = strtok(comandaIntrodusa, " "); //extrage proiectPOO.exe

    if (strcmp(token, "proiectPOO.exe") != 0)
        cout << "Comanda introdusa gresit! Pentru a porni aplicatia rulati: proiectPOO.exe";
    else {

        token = strtok(NULL, " "); //numele fisierului de unde se citesc comenzile

        ifstream fisierComenzi;
        string numeFisierComenzi = token;
        fisierComenzi.open(numeFisierComenzi, ios::in);

        bool acces = true;
        while (acces == true)
        {
            string ss;
            getline(fisierComenzi, ss); //citeste pana la EOF

            if (fisierComenzi.eof())
            {
                cout << "Toate comenzile din fisier au fost rulate";
                break;
            }

            char* comandaIntrodusaFisier = new char[strlen(ss.c_str() + 1)];
            strcpy(comandaIntrodusaFisier, ss.c_str());

            token = strtok(comandaIntrodusaFisier, " ");

            char verif[50] = "";
            strcat(verif, token);
            if ((strcmp(token, "select") != 0) && (strcmp(token, "update") != 0))
            {
                strcat(verif, " ");
                token = strtok(NULL, " ");
                strcat(verif, token);

                switch (optiune(verif))
                {
                case create: {

                    Tabel tabela;

                    token = strtok(NULL, " ");
                    string numeTabela = token;

                    string numeFisier = numeTabela + "_structura.txt"; //numele fisierului asociat tabelei
                    ofstream f(numeFisier);

                    int nrColoane = 0;
                    Tabel::coloana c[10];
                    token = strtok(NULL, "(");
                    while (token != NULL)
                    {
                        //Citim atributele coloanei: nume, tip, dimensiune, defaultValue
                        token = strtok(NULL, " ()");
                        if (token == NULL)
                            break;
                        string ss = token;
                        ss.erase(ss.end() - 1);
                        c[nrColoane].setNume(ss);
                        token = strtok(NULL, ", ");
                        c[nrColoane].setTip(token);
                        token = strtok(NULL, ", ");
                        c[nrColoane].setDimensiune((short)stoi(token));
                        token = strtok(NULL, ", ");
                        c[nrColoane].setDefaultValue(token);
                        ss = token;
                        ss.erase(ss.end() - 1);
                        c[nrColoane].setDefaultValue(ss);
                        nrColoane++;
                    }

                    tabela.createTable(numeTabela, c, nrColoane);
                    tabele[nrTabele] = tabela;
                    nrTabele++;

                    cout << tabele[0].c[2].getNume() << endl; // --> merge :) create table angajati ( (id, number, 10, 1), (nume, varchar2, 10, Anonim), (salariu, number, 4, -) )

                    break;
                }

                case display: {

                    token = strtok(NULL, " ");
                    string numeTabela = token;

                    int k = 0;
                    for (int i = 0; i < nrTabele && k == 0; i++)
                        if (strcmp(tabele[i].getNume().c_str(), token) == 0)
                        {
                            tabele[i].displayTable();
                            k = 1;
                        }

                    //Exemplu comanda: display table angajati

                    if (k == 0)
                        cout << "Nu exista tabela " << numeTabela << "!" << endl;

                    break;
                }

                case drop: {
                    token = strtok(NULL, " ");
                    string numeTabela = token;

                    int k = 0;
                    for (int i = 0; i < nrTabele && k == 0; i++)
                        if (strcmp(tabele[i].getNume().c_str(), token) == 0)
                        {
                            tabele[i].dropTable();
                            k = 1;
                        }


                    if (k == 0)
                        cout << "Nu exista tabela " << numeTabela << "!" << endl;

                    break;
                }

                case insert: {
                    token = strtok(NULL, " ");
                    string numeTabela = token;
                    string numefisierreal = numeTabela + ".txt";
                    ofstream f(numefisierreal);
                    string numefisier = numeTabela + ".bin";
                    ofstream g(numefisier);
                    int k = 0;
                    for (int i = 0; i < nrTabele && k == 0; i++)
                        if (strcmp(tabele[i].getNume().c_str(), token) == 0)
                        {
                            token = strtok(NULL, " (,)");
                            int j = 0;
                            while (token != NULL)
                            {
                                tabele[i].c[j++].insertValues(token, numefisier, numefisierreal);
                                token = strtok(NULL, " (,)");
                            }
                            k = 1;
                        }
                    // insert into angajati ( (1, Ion, 4000) )
                    if (k == 0)
                        cout << "Nu exista tabela " << numeTabela << "!" << endl;
                    break;
                }

                case deletee: {
                    token = strtok(NULL, " ");
                    string numeTabela = token;
                    string numefisierreal = numeTabela + ".txt";
                    ofstream f(numefisierreal);
                    string numefisier = numeTabela + ".bin";
                    ofstream g(numefisier);
                    int k = 0;
                    token = strtok(NULL, " "); //where
                    for (int i = 0; i < nrTabele && k == 0; i++)
                        if (tabele[i].getNume() == numeTabela)
                        {
                            token = strtok(NULL, " (,)"); //nume_coloana
                            string nume_coloana = token;
                            token = strtok(NULL, " ="); //valoare
                            string valoare = token;
                            deleteValues(tabele[i], tabele[i].c, nume_coloana, valoare, numefisier, numefisierreal);
                            k = 1;
                        }
                    // delete from angajati where salariu = 4000 
                    if (k == 0)
                        cout << "Nu exista tabela " << numeTabela << "!" << endl;
                    break;
                }

                default: {
                    cout << "Eroare de sintaxa!";
                    acces = false;
                    break;
                }
                }
            }
            else {
                switch (optiune(verif))
                {
                case select: {


                }

                case update: {

                }

                default: {
                    cout << "Eroare de sintaxa!";
                    acces = false;
                    break;
                }

                }
            }
        }
    }
    return 0;
}


