#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;

struct Adresat {
    int id;
    string imie, nazwisko, adres, telefon, mail;
};

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

void wyswietlMenuLogowania() {

    system("cls");
    cout<<"1. Rejestracja"<<endl;
    cout<<"2. Logowanie"<<endl;
    cout<<"9. Wyjdz z programu"<<endl;
}

void zarejestruj(vector<Uzytkownik> &uzytkownicy) {

    Uzytkownik nowyUzytkownik;
    string nazwa,haslo;
    int ostatnieId=0;
    int i=0;
    cout<<"Podaj nazwe uzytkownika:"<<endl;
    cin>>nazwa;

    while(i<uzytkownicy.size()) {
        if(uzytkownicy[i].nazwa==nazwa) {
            cout<<"Taki uzytkownik istnieje, podaj inna nazwa"<<endl;
            cin>>nazwa;
            i=0;
        } else {
            i++;
        }
    }

    if(uzytkownicy.size()>0) {
        ostatnieId=uzytkownicy[uzytkownicy.size()-1].id;
    } else {
        ostatnieId=0;
    }
    cout<<"Podaj haslo:"<<endl;
    cin>>haslo;

    nowyUzytkownik.nazwa=nazwa;
    nowyUzytkownik.haslo=haslo;
    nowyUzytkownik.id=ostatnieId+1;

    uzytkownicy.push_back(nowyUzytkownik);

    cout<<"Uzytkownik zapisany"<<endl;
    Sleep(1000);
}

int odczytajZPlikuUzytkownicy(vector<Uzytkownik> &uzytkownicy) {

    fstream uzytkownicyPlik;
    uzytkownicyPlik.open("uzytkownicy.txt", ios::in);

    string linia;
    string daneUzytkownika[3];
    int nrlinii=1;
    int i=0;
    int j=0;


    Uzytkownik uzytkownikZPliku;

    while(getline(uzytkownicyPlik,linia)) {
        daneUzytkownika[0]="";
        daneUzytkownika[1]="";
        daneUzytkownika[2]="";
        j=0;
        for(int i=0; i<linia.length(); i++) {
            if(linia[i]=='|') {
                daneUzytkownika[j].insert(0,linia,0,i);
                linia.erase(0,i+1);
                i=0;
                j++;
            }
        }
        uzytkownikZPliku.id=atoi(daneUzytkownika[0].c_str());
        uzytkownikZPliku.nazwa=daneUzytkownika[1];
        uzytkownikZPliku.haslo=daneUzytkownika[2];

        uzytkownicy.push_back(uzytkownikZPliku);
    }
    uzytkownicyPlik.close();
}

void dopisanieDoPlikuUzytkownicy(vector<Uzytkownik> &uzytkownicy) {

    int iloscUzytkownikow=uzytkownicy.size();

    fstream uzytkownicyPlik;
    uzytkownicyPlik.open("uzytkownicy.txt", ios::out | ios::app);
    stringstream ss;
    ss << uzytkownicy[iloscUzytkownikow-1].id;
    string id = ss.str();

    uzytkownicyPlik<<id+'|'<<uzytkownicy[iloscUzytkownikow-1].nazwa+'|'<<uzytkownicy[iloscUzytkownikow-1].haslo+'|'<<endl;
    uzytkownicyPlik.close();
}

int logowanie(vector<Uzytkownik> &uzytkownicy) {

    string nazwa,haslo;
    cout<<"Podaj nazwe uzytkownika:"<<endl;
    cin>>nazwa;
    cout<<"Podaj haslo:"<<endl;
    cin>>haslo;

    for(int i=0; i<uzytkownicy.size(); i++) {
        if(uzytkownicy[i].nazwa==nazwa && uzytkownicy[i].haslo==haslo) {
            cout<<"Zalogowano pomyslnie"<<endl;
            Sleep(1000);
            return uzytkownicy[i].id;
        }
    }
    cout<<"Nieprawidlowe dane, nastapi przejscie do menu glownego"<<endl;
    Sleep(1000);
    return 0;
}
//-------------------------------------------------------------------------

void zapiszKontakt(vector<Adresat> &adresaci, int id) {

    Adresat nowyAdresat;
    int iloscAdresow=adresaci.size();
    string imie, nazwisko, adres, telefon, mail;
    cout<<"Podaj imie"<<endl;
    cin>>imie;

    cout<<"Podaj nazwisko"<<endl;
    cin>>nazwisko;

    for(int i=0; i<iloscAdresow; i++) {
        if((adresaci[i].imie==imie) && (adresaci[i].nazwisko==nazwisko) ) {
            cout<<"Dany kontakt jest juz zapisany, nastapi przejscie do menu glownego"<<endl;
            Sleep(1000);
        }
    }
    nowyAdresat.imie=imie;
    nowyAdresat.nazwisko=nazwisko;

    cin.sync();
    cout<<"Podaj adres danej osoby"<<endl;
    getline(cin, adres);

    cout<<"Podaj telefon"<<endl;
    getline(cin, telefon);

    cout<<"Podaj email"<<endl;
    getline(cin, mail);

    nowyAdresat.adres=adres;
    nowyAdresat.telefon=telefon;
    nowyAdresat.mail=mail;
    nowyAdresat.id=id+1;

    adresaci.push_back(nowyAdresat);

    cout<<"Kontakt zapisany"<<endl;
    Sleep(1000);
}

void wyswieltDanegoAdresata(Adresat adresat) {

    cout<<adresat.imie+" "<<adresat.nazwisko+" "<<adresat.adres+" "<<adresat.telefon+" "<<adresat.mail<<endl;
}

void znajdzImie(vector<Adresat> adresaci) {

    int iloscAdresow=adresaci.size();
    string imie;
    cout<<"Podaj imie do wyszukania"<<endl;
    cin>>imie;
    for(int i=0; i<iloscAdresow; i++) {
        if(adresaci[i].imie==imie) {
            wyswieltDanegoAdresata(adresaci[i]);
        }
    }
    cout<<"Nacisnij dowolny przycisk aby przejsc do menu glownego"<<endl;
    getchar();
    getchar();
}

void znajdzNazwisko(vector<Adresat> adresaci) {

    int iloscAdresow=adresaci.size();
    string nazwisko;
    cout<<"Podaj nazwisko do wyszukania"<<endl;
    cin>>nazwisko;
    for(int i=0; i<iloscAdresow; i++) {
        if(adresaci[i].nazwisko==nazwisko) {
            wyswieltDanegoAdresata(adresaci[i]);
        }
    }
    cout<<"Nacisnij dowolny przycisk aby przejsc do menu glownego"<<endl;
    getchar();
    getchar();
}

void wyswietlWszystkie(vector<Adresat> adresaci) {

    int iloscAdresow=adresaci.size();
    if(iloscAdresow==0) {
        cout<<"Brak zapisanych adresow"<<endl;
    }
    for(int i = 0; i<iloscAdresow; i++) {
        wyswieltDanegoAdresata(adresaci[i]);
    }
    cout<<"Nacisnij dowolny przycisk aby przejsc do menu glownego"<<endl;
    getchar();
    getchar();
}

void usunKontakt(vector<Adresat> &adresaci) {

    int iloscAdresow=adresaci.size();
    vector <Adresat>::iterator it;
    int id;
    char wybor='n';
    cout<<"Podaj id kontaku do usuniecia"<<endl;
    cin>>id;

    for(int i=0; i<iloscAdresow; i++) {
        if(adresaci[i].id==id) {
            it=adresaci.begin()+i;
            cout<<"Aby usunac nacisnij: t "<<endl;
            cin>>wybor;

            if(wybor=='t') {
                adresaci.erase(it);
                cout<<"Kontakt zostal usuniety"<<endl;
                Sleep(1000);
            }
        }
    }
}

void wyswietlMenuEdycji() {

    cout<<"Co do edycji?"<<endl;
    cout<<"1. Imie"<<endl;
    cout<<"2. Nazwisko"<<endl;
    cout<<"3. Adres"<<endl;
    cout<<"4. Telefon"<<endl;
    cout<<"5. Mail"<<endl;
    cout<<"6. Powrot do menu"<<endl;
}

void edytujKontakt(vector<Adresat> &adresaci) {

    int iloscAdresow=adresaci.size();
    string doZmiany;
    int id;
    char wybor;
    cout<<"Podaj id kontaku do edycji"<<endl;
    cin>>id;

    for(int i=0; i<iloscAdresow; i++) {
        if(adresaci[i].id==id) {
            wyswietlMenuEdycji();
            cin>>wybor;

            if(wybor=='1') {
                cin>>doZmiany;
                adresaci[i].imie=doZmiany;
                cout<<"Imie zostalo zaktualizowane"<<endl;
                Sleep(1000);
            } else if(wybor=='2') {
                cin>>doZmiany;
                adresaci[i].nazwisko=doZmiany;
                cout<<"Nazwisko zostalo zaktualizowane"<<endl;
                Sleep(1000);
            } else if(wybor=='3') {
                cin>>doZmiany;
                adresaci[i].adres=doZmiany;
                cout<<"Adres zostal zaktualizowany"<<endl;
                Sleep(1000);
            } else if(wybor=='4') {
                cin>>doZmiany;
                adresaci[i].telefon=doZmiany;
                cout<<"Adres zostal zaktualizowany"<<endl;
                Sleep(1000);
            } else if(wybor=='5') {
                cin>>doZmiany;
                adresaci[i].mail=doZmiany;
                cout<<"Mail zostal zaktualizowany"<<endl;
                Sleep(1000);
            }
        }
    }
}

string zmianaIntnaString(int liczba) {

    stringstream ss;
    ss << liczba;
    string wyraz = ss.str();

    return wyraz;
}

void usuniecieIEskportDoNowegoPliku(vector<Adresat> &adresaci, string numerUzytkownika) {

    string id;
    string nazwaPliku=numerUzytkownika+".txt";
    int iloscAdresow=adresaci.size();
    remove(nazwaPliku.c_str());
    fstream adresy;
    adresy.open(nazwaPliku.c_str(), ios::out | ios::app);
    for(int i=0; i<iloscAdresow; i++) {

        id=zmianaIntnaString(adresaci[i].id);

        adresy<<id+'|'<<adresaci[i].imie+'|'<<adresaci[i].nazwisko+'|'<<adresaci[i].adres+'|'<<adresaci[i].telefon+'|'<<adresaci[i].mail+'|'<<endl;
    }
    adresy.close();
}

void dopisanieDoPliku(vector<Adresat> &adresaci, string numerUzytkownika) {

    string id;
    string nazwaPliku=numerUzytkownika+".txt";
    int iloscAdresow=adresaci.size();
    fstream adresy;
    adresy.open(nazwaPliku.c_str(), ios::out | ios::app);

    id=zmianaIntnaString(adresaci[iloscAdresow-1].id);

    adresy<<id+'|'<<adresaci[iloscAdresow-1].imie+'|'<<adresaci[iloscAdresow-1].nazwisko+'|'<<adresaci[iloscAdresow-1].adres+'|'<<adresaci[iloscAdresow-1].telefon+'|'<<adresaci[iloscAdresow-1].mail+'|'<<endl;
    adresy.close();
}

bool sprawdzCzyPlikIstnieje( const char * plik ) {

    ifstream ifs( plik );
    if( !ifs.good() ) return false;

    ifs.close();
    return true;
}

int odczytajZPliku(vector<Adresat> &adresaci, string numerUzytkownika) {

    string nazwaPliku=numerUzytkownika+".txt";
    fstream adresy;
    adresy.open(nazwaPliku.c_str(), ios::in);
    int ostatnieId;

    string linia;
    string daneKontaktu[6];
    int nrlinii=1;
    int i=0;
    int j=0;


    Adresat adresatZPliku;

    while(getline(adresy,linia)) {
        daneKontaktu[0]="";
        daneKontaktu[1]="";
        daneKontaktu[2]="";
        daneKontaktu[3]="";
        daneKontaktu[4]="";
        daneKontaktu[5]="";
        j=0;
        for(int i=0; i<linia.length(); i++) {
            if(linia[i]=='|') {
                daneKontaktu[j].insert(0,linia,0,i);
                linia.erase(0,i+1);
                i=0;
                j++;
            }
        }
        adresatZPliku.id=atoi(daneKontaktu[0].c_str());
        adresatZPliku.imie=daneKontaktu[1];
        adresatZPliku.nazwisko=daneKontaktu[2];
        adresatZPliku.adres=daneKontaktu[3];
        adresatZPliku.telefon=daneKontaktu[4];
        adresatZPliku.mail=daneKontaktu[5];

        adresaci.push_back(adresatZPliku);
    }
    adresy.close();

    if(adresaci.size()>0) {
        ostatnieId=adresaci[adresaci.size()-1].id;
    } else {
        ostatnieId=0;
    }
    return ostatnieId;
}

void wyswietlMenuGlowne() {

    system("cls");
    cout<<"1. Zapisz kontakt"<<endl;
    cout<<"2. Znajdz kontakt po imieniu"<<endl;
    cout<<"3. Znajdz kontakt po nazwisku"<<endl;
    cout<<"4. Pokaz wszystkie kontakty"<<endl;
    cout<<"5. Usun kontakt"<<endl;
    cout<<"6. Edytuj kontakt"<<endl;
    cout<<"9. Wyjdz do logowania"<<endl;
}
void wejdzDoMenuGlownego(vector<Adresat> &adresaci, int idUzytkownika) {
    char wybor;
    int ostatnieId=0;
    string numerUzytkownika;

    numerUzytkownika=zmianaIntnaString(idUzytkownika);
    string nazwaPliku=numerUzytkownika+".txt";

    if(sprawdzCzyPlikIstnieje(nazwaPliku.c_str())==true) {
        ostatnieId=odczytajZPliku(adresaci, numerUzytkownika);
    }

    while(1) {
        wyswietlMenuGlowne();

        cin>>wybor;

        if(wybor=='1') {
            zapiszKontakt(adresaci, ostatnieId);
            ostatnieId=adresaci[adresaci.size()-1].id;
            dopisanieDoPliku(adresaci, numerUzytkownika);
        } else if(wybor=='2') {
            znajdzImie(adresaci);
        } else if(wybor=='3') {
            znajdzNazwisko(adresaci);
        } else if(wybor=='4') {
            wyswietlWszystkie(adresaci);
        } else if(wybor=='5') {
            if(adresaci.size()>0) {
                usunKontakt(adresaci);
                ostatnieId=adresaci[adresaci.size()-1].id;
                usuniecieIEskportDoNowegoPliku(adresaci, numerUzytkownika);
            } else {
                cout<<"Brak adresatow do usuniecia"<<endl;
                Sleep(1000);
            }
        } else if(wybor=='6') {
            edytujKontakt(adresaci);
            usuniecieIEskportDoNowegoPliku(adresaci, numerUzytkownika);
        } else if(wybor=='9') {
            break;
        } else {
            cout<<"Wybierz poprawny przycisk (od 1 do 5)"<< endl;
            Sleep(2000);
        }
    }
}

int main() {

    vector<Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;

    int idZalogowanegoUzytkownika;
    char wyborLogowanie;

    if(sprawdzCzyPlikIstnieje("uzytkownicy.txt")==true) {
        odczytajZPlikuUzytkownicy(uzytkownicy);
    }

    while(1) {
        adresaci.clear();
        wyswietlMenuLogowania();

        cin>>wyborLogowanie;

        if(wyborLogowanie=='1') {
            zarejestruj(uzytkownicy);
            dopisanieDoPlikuUzytkownicy(uzytkownicy);
        } else if(wyborLogowanie=='2') {
            idZalogowanegoUzytkownika=logowanie(uzytkownicy);
            if(idZalogowanegoUzytkownika!=0) {
                wejdzDoMenuGlownego(adresaci, idZalogowanegoUzytkownika);
            }
        } else if(wyborLogowanie=='9') {
            exit(0);
        }
    }
    return 0;
}
