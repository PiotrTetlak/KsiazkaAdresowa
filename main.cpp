#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>


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

void odczytajZPlikuUzytkownicy(vector<Uzytkownik> &uzytkownicy, const string plikZUzytkownikami) {

    fstream uzytkownicyPlik;
    uzytkownicyPlik.open(plikZUzytkownikami.c_str(), ios::in);

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

void dopisanieDoPlikuUzytkownicy(vector<Uzytkownik> &uzytkownicy, const string plikZUzytkownikami) {

    int iloscUzytkownikow=uzytkownicy.size();

    fstream uzytkownicyPlik;
    uzytkownicyPlik.open(plikZUzytkownikami.c_str(), ios::out | ios::app);
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

void wyswietlMenuEdycji() {

    cout<<"Co do edycji?"<<endl;
    cout<<"1. Imie"<<endl;
    cout<<"2. Nazwisko"<<endl;
    cout<<"3. Adres"<<endl;
    cout<<"4. Telefon"<<endl;
    cout<<"5. Mail"<<endl;
    cout<<"6. Powrot do menu"<<endl;
}

string zmianaIntnaString(int liczba) {

    stringstream ss;
    ss << liczba;
    string wyraz = ss.str();

    return wyraz;
}

string znajdzNumerUzytkownika(string linia) {

    string numerUzytkownika;
    for(int i=0; i<linia.length(); i++) {
        if(linia[i]=='|') {
            linia.erase(0,i+1);

            for(int k=0; k<linia.length(); k++) {
                if(linia[k]=='|') {
                    numerUzytkownika.insert(0,linia,0,k);
                    linia.erase();
                }
            }
        }
    }

    return numerUzytkownika;
}

string znajdzIdAdresata(string linia) {

    string numerAdresata;
    for(int i=0; i<linia.length(); i++) {
        if(linia[i]=='|') {
            numerAdresata.insert(0,linia,0,i);
            linia.erase();
        }
    }

    return numerAdresata;
}

void usuniecieIEskportDoNowegoPliku(vector<Adresat> &adresaci, int idUzytkownika, const string plikZAdresami, const string plikTymczasowy) {

    int iloscAdresow=adresaci.size();
    remove(plikTymczasowy.c_str());

    string idUzyt=zmianaIntnaString(idUzytkownika);

    fstream odczyt;
    fstream zapis;
    odczyt.open(plikZAdresami.c_str(), ios::in);
    zapis.open(plikTymczasowy.c_str(), ios::out | ios::app);
    string linia;
    string numerUzytkownika, idAdresata;
    int m=0;

    while(getline(odczyt,linia)) {
        numerUzytkownika=znajdzNumerUzytkownika(linia);
        idAdresata=znajdzIdAdresata(linia);

        if(idUzyt==numerUzytkownika && m<iloscAdresow) {
            string id=zmianaIntnaString(adresaci[m].id);

            if(idAdresata==id) {
                zapis<<id+'|'<<numerUzytkownika+'|'<<adresaci[m].imie+'|'<<adresaci[m].nazwisko+'|'<<adresaci[m].adres+'|'<<adresaci[m].telefon+'|'<<adresaci[m].mail+'|'<<endl;
            }
            m++;
        } else if(idUzyt!=numerUzytkownika) {
            zapis<<linia<<endl;
        }
    }
    odczyt.close();
    zapis.close();
    remove(plikZAdresami.c_str());

    rename(plikTymczasowy.c_str(), plikZAdresami.c_str());

}

void dopisanieDoPliku(vector<Adresat> &adresaci, int idUzytkownika, const string plikZAdresami) {

    string id, numerUzytkownika;
    int iloscAdresow=adresaci.size();
    fstream adresy;
    adresy.open(plikZAdresami.c_str(), ios::out | ios::app);

    id=zmianaIntnaString(adresaci[iloscAdresow-1].id);
    numerUzytkownika=zmianaIntnaString(idUzytkownika);

    adresy<<id+'|'<<numerUzytkownika+'|'<<adresaci[iloscAdresow-1].imie+'|'<<adresaci[iloscAdresow-1].nazwisko+'|'<<adresaci[iloscAdresow-1].adres+'|'<<adresaci[iloscAdresow-1].telefon+'|'<<adresaci[iloscAdresow-1].mail+'|'<<endl;
    adresy.close();
}

bool sprawdzCzyPlikIstnieje( const char * plik ) {

    ifstream ifs( plik );
    if( !ifs.good() ) return false;

    ifs.close();
    return true;
}

void odczytajDanePojedynczegoKontaktu(string daneKontaktu[], string linia) {

    int j=0;

    for(int i=0; i<linia.length(); i++) {
        if(linia[i]=='|' && j==0) {
            daneKontaktu[j].insert(0,linia,0,i);
            linia.erase(0,i+1);
            i=0;
            j++;
            for(int k=0; k<linia.length(); k++) {
                if(linia[k]=='|') {
                    linia.erase(0,k+1);
                    break;
                }
            }
        } else if(linia[i]=='|') {
            daneKontaktu[j].insert(0,linia,0,i);
            linia.erase(0,i+1);
            i=0;
            j++;
        }
    }
}

void odczytajZPliku(vector<Adresat> &adresaci, int idUzytkownika, const string plikZAdresami) {

    string id=zmianaIntnaString(idUzytkownika);

    fstream adresy;
    adresy.open(plikZAdresami.c_str(), ios::in);
    int ostatnieId;

    string linia;
    string numerUzytkownika="";
    string daneKontaktu[6];

    Adresat adresatZPliku;

    while(getline(adresy,linia)) {

        daneKontaktu[0]="";
        daneKontaktu[1]="";
        daneKontaktu[2]="";
        daneKontaktu[3]="";
        daneKontaktu[4]="";
        daneKontaktu[5]="";

        numerUzytkownika=znajdzNumerUzytkownika(linia);
        odczytajDanePojedynczegoKontaktu(daneKontaktu, linia);

        if(numerUzytkownika==id) {
            adresatZPliku.id=atoi(daneKontaktu[0].c_str());
            adresatZPliku.imie=daneKontaktu[1];
            adresatZPliku.nazwisko=daneKontaktu[2];
            adresatZPliku.adres=daneKontaktu[3];
            adresatZPliku.telefon=daneKontaktu[4];
            adresatZPliku.mail=daneKontaktu[5];

            adresaci.push_back(adresatZPliku);
        }
    }
    adresy.close();
}

int znajdzPrzedostatnioLinie(const string plikZAdresami) {

    fstream mojplik;
    mojplik.open( plikZAdresami.c_str(), ios::in );
    string linia;
    int numerLinii=0;
    while( !mojplik.eof() ) {
        getline(mojplik,linia);
        numerLinii++;
    }
    mojplik.close();
    return numerLinii-1;
}

int znajdzOstatnieId(const string plikZAdresami) {

    fstream adresy;
    adresy.open( plikZAdresami.c_str(), ios::in );
    string linia, ostatniaLinia;
    string ostatnieId="";
    int numerLinii=1;
    int numerOstatniejLinii=znajdzPrzedostatnioLinie(plikZAdresami);

    while(getline(adresy,linia)) {
        if(numerLinii==numerOstatniejLinii) {
            ostatniaLinia=linia;
        }
        numerLinii++;
    }
    adresy.close();

    for(int i=0; i<ostatniaLinia.length(); i++) {
        if(ostatniaLinia[i]=='|') {
            ostatnieId.insert(0,ostatniaLinia,0,i);
        }
    }
    int id=atoi(ostatnieId.c_str());
    return id;
}

void edytujKontakt(vector<Adresat> &adresaci, int idUzytkownika, const string plikZAdresami, const string plikTymczasowy) {

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
                usuniecieIEskportDoNowegoPliku(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);
                cout<<"Imie zostalo zaktualizowane"<<endl;
                Sleep(1000);
            } else if(wybor=='2') {
                cin>>doZmiany;
                adresaci[i].nazwisko=doZmiany;
                usuniecieIEskportDoNowegoPliku(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);
                cout<<"Nazwisko zostalo zaktualizowane"<<endl;
                Sleep(1000);
            } else if(wybor=='3') {
                cin>>doZmiany;
                adresaci[i].adres=doZmiany;
                usuniecieIEskportDoNowegoPliku(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);
                cout<<"Adres zostal zaktualizowany"<<endl;
                Sleep(1000);
            } else if(wybor=='4') {
                cin>>doZmiany;
                adresaci[i].telefon=doZmiany;
                usuniecieIEskportDoNowegoPliku(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);
                cout<<"Adres zostal zaktualizowany"<<endl;
                Sleep(1000);
            } else if(wybor=='5') {
                cin>>doZmiany;
                adresaci[i].mail=doZmiany;
                usuniecieIEskportDoNowegoPliku(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);
                cout<<"Mail zostal zaktualizowany"<<endl;
                Sleep(1000);
            }
        }
    }
}

int usunKontakt(vector<Adresat> &adresaci, int idUzytkownika, const string plikZAdresami, const string plikTymczasowy) {

    int iloscAdresow=adresaci.size();
    vector <Adresat>::iterator it;
    int id, ostatnieId;
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
                usuniecieIEskportDoNowegoPliku(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);
                ostatnieId=znajdzOstatnieId(plikZAdresami);
                cout<<"Kontakt zostal usuniety"<<endl;
                Sleep(1000);
                return ostatnieId;
            }
        }
    }
}

int zapiszKontakt(vector<Adresat> &adresaci, int id, int idUzytkownika, const string plikZAdresami) {

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
            return 0;
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

    dopisanieDoPliku(adresaci, idUzytkownika, plikZAdresami);
    int ostatnieId=nowyAdresat.id;

    cout<<"Kontakt zapisany"<<endl;
    Sleep(1000);

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
void wejdzDoMenuGlownego(vector<Adresat> &adresaci, int idUzytkownika, const string plikZAdresami, const string plikTymczasowy) {
    char wybor;
    int ostatnieId=0;

    if(sprawdzCzyPlikIstnieje(plikZAdresami.c_str())==true) {
        odczytajZPliku(adresaci, idUzytkownika, plikZAdresami);
        ostatnieId=znajdzOstatnieId(plikZAdresami);
    }

    while(1) {
        wyswietlMenuGlowne();

        cin>>wybor;

        if(wybor=='1') {
            zapiszKontakt(adresaci, ostatnieId, idUzytkownika, plikZAdresami);
        } else if(wybor=='2') {
            znajdzImie(adresaci);
        } else if(wybor=='3') {
            znajdzNazwisko(adresaci);
        } else if(wybor=='4') {
            wyswietlWszystkie(adresaci);
        } else if(wybor=='5') {
            if(adresaci.size()>0) {
                ostatnieId=usunKontakt(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);
            } else {
                cout<<"Brak adresatow do usuniecia"<<endl;
                Sleep(1000);
            }
        } else if(wybor=='6') {
            edytujKontakt(adresaci, idUzytkownika, plikZAdresami, plikTymczasowy);

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

    const string plikZAdresami="adresy.txt";
    const string plikZUzytkownikami="uzytkownicy.txt";
    const string plikTymczsowy="adresy_tymczasowe.txt";

    int idZalogowanegoUzytkownika;
    char wyborLogowanie;

    if(sprawdzCzyPlikIstnieje(plikZUzytkownikami.c_str())==true) {
        odczytajZPlikuUzytkownicy(uzytkownicy, plikZUzytkownikami);
    }

    while(1) {
        adresaci.clear();
        wyswietlMenuLogowania();

        cin>>wyborLogowanie;

        if(wyborLogowanie=='1') {
            zarejestruj(uzytkownicy);
            dopisanieDoPlikuUzytkownicy(uzytkownicy, plikZUzytkownikami);
        } else if(wyborLogowanie=='2') {
            idZalogowanegoUzytkownika=logowanie(uzytkownicy);
            if(idZalogowanegoUzytkownika!=0) {
                wejdzDoMenuGlownego(adresaci, idZalogowanegoUzytkownika, plikZAdresami, plikTymczsowy);
            }
        } else if(wyborLogowanie=='9') {
            exit(0);
        }
    }
    return 0;
}
