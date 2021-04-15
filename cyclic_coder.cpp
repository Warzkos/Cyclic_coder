#include <iostream>
#include <cmath>
#include <string>
#include <conio.h>

using namespace std;

string dodawanie_modulo(string a, string b)
{
    if (a == b)
        return "0";
    return "1";
}

char dodawanie_modulo(char a, string b)
{
    const char *x = b.c_str();
    char *wsk = &a;
    if (*wsk == *x)
        return '0';
    return '1';
}

void wstep()
{
    for(int i=0; i<50; i++)
        cout << "#";
    cout << endl;
    cout << "#";
    for(int i=0; i<9; i++)
        cout << " ";
    cout << "APLIKACJA KODUJACO-DEKODUJACA";
    for(int i=0; i<10; i++)
        cout << " ";
    cout << "#" << endl;
    for(int i=0; i<50; i++)
        cout << "#";
    cout << endl;
}

int main()
{
    wstep();
    char tablica_slow_informacyjnych[32768][15];
    char tablica_slow_kodowych[32768][40];
    string macierz_generujaca[70][70];
    string macierz_zabezpieczajaca[100][50];
    string odebrany_ciag[50];
    string syndrom[50];
    int n, k;
    string wielomian_generujacy;

    cout << "Podaj n (n<41): ";
    do{
        cin >> n;
    }while(n>40 || n<1);
    cout << "Podaj k (k<16): ";
    do{
        cin >> k;
    }while(k>15 || k<1);
    cout << "Podaj wielomian generujacy w postaci binarnej (CG2) (np. 101 dla x^2+1): ";


int sumajedynek=0;
do{
    cin >> wielomian_generujacy;
    char wielomian[wielomian_generujacy.size()];

    for(int i=0; i<wielomian_generujacy.size(); i++)
        wielomian[i]=wielomian_generujacy[i];

    char dzielna[n+1];
    for(int i=0; i<n+1; i++)
    {
        if(i==0 || i==n)
            dzielna[i]='1';
        else
            dzielna[i]='0';
    }
        int poczatek = n;
    for(int q=n-wielomian_generujacy.size()+1; q>-1; q--)
    {
        if(dzielna[poczatek]=='1')
        {
            int iteracje=0;
            for(int i=0; i<wielomian_generujacy.size(); i++)
            {
                if(dzielna[poczatek-iteracje]==wielomian[i])
                    dzielna[poczatek-iteracje]='0';
                else
                    dzielna[poczatek-iteracje]='1';
                iteracje++;
            }
        }
        poczatek--;
    }

    sumajedynek=0;
    for(int a=n; a>-1; a--)
        if(dzielna[a]=='1')
            sumajedynek++;
    if(sumajedynek!=0)
        {
            cout << "Reszta z dzielenia wielomianu wynosi: ";
            for(int a=n; a>-1; a--)
                cout << dzielna[a];
            cout << endl;
            cout << "Podano bledny wielomian generacyjny, prosze wprowadzic jeszcze raz: ";
        }
}while(sumajedynek!=0);

    int ileLiczb_01 = pow(2, k - 1);
    for (int kolumna = 0; kolumna < k; kolumna++)
    {
        for (int rzad = 0; rzad < pow(2, k);)
        {
            for (int w = 0; w < ileLiczb_01; w++)
            {
                tablica_slow_informacyjnych[rzad][kolumna] = '0';
                rzad++;
            }
            for (int w = 0; w < ileLiczb_01; w++)
            {
                tablica_slow_informacyjnych[rzad][kolumna] = '1';
                rzad++;
            }
        }
        ileLiczb_01 = ileLiczb_01 / 2;
    }

    cout << "Slowa informacyjne: ";
    for (int rzad = 0; rzad < pow(2, k); rzad++)
    {
        for (int kolumna = 0; kolumna < k; kolumna++)
            cout << tablica_slow_informacyjnych[rzad][kolumna];
        if (rzad != pow(2, k) - 1)
            cout << ", ";
    }
    cout << endl;

    for (int rzad = 0; rzad < k; rzad++)
    {
        int NminusK = n - k;
        for (int kolumna = rzad; kolumna < 1 + n - k + rzad; kolumna++)
        {
            macierz_generujaca[rzad][n - kolumna - 1] = wielomian_generujacy[NminusK];
            NminusK--;
        }
        for (int kolumna = 0; kolumna < n; kolumna++)
        {
            if (macierz_generujaca[rzad][kolumna].length() == 0)
                macierz_generujaca[rzad][kolumna] = "0";
        }
    }

    while (true)
    {
        int ileZle = 0;
        for (int rzad = 0; rzad < k; rzad++)
        {
            for (int kolumna = 0; kolumna < k; kolumna++)
            {
                if (macierz_generujaca[rzad][kolumna] != "0")
                    if (kolumna != rzad)
                        ileZle++;
            }
        }
        if (ileZle == 0)
            break;

        for(int rzadP=0; rzadP<k; rzadP++)
        {
            for(int kolumnaP=0; kolumnaP<k; kolumnaP++)
            {
                if(rzadP==kolumnaP)
                    if(macierz_generujaca[rzadP][kolumnaP]!="1")
                        {
                            for(int rzadX=0; rzadX<k; rzadX++){
                                if(macierz_generujaca[rzadX][kolumnaP]=="1"&&rzadX!=kolumnaP)
                                    for(int i=0; i<n; i++)
                                        macierz_generujaca[rzadP][i]=dodawanie_modulo(macierz_generujaca[rzadX][i],macierz_generujaca[rzadP][i]);
                            }
                        }
            }
        }

        for(int rzadP=0; rzadP<k; rzadP++)
        {
            for(int kolumnaP=0; kolumnaP<k; kolumnaP++)
            {
                if(rzadP!=kolumnaP)
                    if(macierz_generujaca[rzadP][kolumnaP]=="1")
                {
                    for(int rzadX=0; rzadX<k; rzadX++)
                        if(macierz_generujaca[rzadX][kolumnaP]=="1"&& rzadX!=rzadP)
                            for(int i=0; i<n; i++)
                                macierz_generujaca[rzadP][i]=dodawanie_modulo(macierz_generujaca[rzadX][i],macierz_generujaca[rzadP][i]);
                }
            }
        }
    }
    cout << endl;

    cout << "Macierz generujaca systematyczna" << endl;
    for (int rzad = 0; rzad < k; rzad++)
    {
        for (int kolumna = 0; kolumna < n; kolumna++)
            cout << macierz_generujaca[rzad][kolumna];
        cout << endl;
    }
    cout << endl;

    for (int rzadMG = 0; rzadMG < k; rzadMG++)
    {
        int kolumnaMZ = 0;
        for (int kolumnaMG = k; kolumnaMG < n; kolumnaMG++)
        {
            macierz_zabezpieczajaca[rzadMG][kolumnaMZ] = macierz_generujaca[rzadMG][kolumnaMG];
            kolumnaMZ++;
        }
    }
    for (int rzad = k; rzad < n; rzad++)
    {
        for (int kolumna = 0; kolumna < n - k; kolumna++)
        {
            if (kolumna + k == rzad)
                macierz_zabezpieczajaca[rzad][kolumna] = "1";
            else
                macierz_zabezpieczajaca[rzad][kolumna] = "0";
        }
    }

    cout << "Macierz zabezpieczajaca" << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n-k; j++)
            cout << macierz_zabezpieczajaca[i][j];
        cout << endl;} cout << endl;

    for (int rzad = 0; rzad < pow(2, k); rzad++)
        for (int kolumna = 0; kolumna < n; kolumna++)
            tablica_slow_kodowych[rzad][kolumna] = '0';

    for (int rzadTSK = 0; rzadTSK < pow(2, k); rzadTSK++)
    {
        for (int kolumnaTSK = 0; kolumnaTSK < n; kolumnaTSK++)
        {
            for (int kolumnaTSI = 0; kolumnaTSI < k; kolumnaTSI++)
            {
                if (tablica_slow_informacyjnych[rzadTSK][kolumnaTSI] == '1')
                    tablica_slow_kodowych[rzadTSK][kolumnaTSK] = dodawanie_modulo(tablica_slow_kodowych[rzadTSK][kolumnaTSK], macierz_generujaca[kolumnaTSI][kolumnaTSK]);
            }
        }
    }

    cout << "Tablica slow kodowych: ";
    for(int i=0; i<pow(2,k); i++)
    {
        for(int j=0; j<n; j++)
            cout << tablica_slow_kodowych[i][j];
        if(i!=pow(2,k)-1)
            cout << ", ";
    }

    int iloscJedynek=0;
        for(int i=1; i<pow(2,k); i++)
        {
            int ileJedynekTemp=0;
            for(int j=0; j<n; j++)
            {
                if(tablica_slow_kodowych[i][j]=='1')
                    ileJedynekTemp++;
            }
            if(i==1)
                iloscJedynek=ileJedynekTemp;
            if(ileJedynekTemp<iloscJedynek)
                iloscJedynek=ileJedynekTemp;
        }

        int dmin = iloscJedynek;
        int korekcja = (dmin-1)/2;

        cout << endl; cout << endl;
        cout << "Odleglosc minimalna kodu: " << dmin << endl; cout << "Zdolnosc detekcyjna kodu: " << dmin-1 << endl;
        cout << "Zdolnosc korekcyjna kodu: " << korekcja << endl;

    cout << endl;
    while(true){
    string odebrany_ciag_x;
    cout << "Podaj odebrany ciag (lub wpisz 'w' zeby zakonczyc): ";
    do{

    cin >> odebrany_ciag_x;
    if(odebrany_ciag_x=="w")
        return 0;
    if(odebrany_ciag_x.length()!=n)
    {
        cout << "Podano bledny ciag" << endl;
        cout << "Podaj odebrany ciag: ";
    }
    }while(odebrany_ciag_x.length()!=n);

    for(int i=0; i<n; i++)
        odebrany_ciag[i]=odebrany_ciag_x[i];


    for(int i=0; i<n-k; i++)
        syndrom[i]="0";

    for(int i=0; i<n-k; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(odebrany_ciag[j]=="1")
                syndrom[i]=dodawanie_modulo(syndrom[i], macierz_zabezpieczajaca[j][i]);
        }
    }
    cout << "syndrom: ";
    for(int i=0; i<n-k; i++)
        cout << syndrom[i];
    cout << endl;
    int wagaH=0;
    for(int i=0; i<n-k; i++)
        if(syndrom[i]=="1")
            wagaH++;

    if(wagaH==0){
        cout << "Odebrano poprawny ciag" << endl;
        cout << "Uzyte slowo kodowe: ";
        for(int i=0; i<k; i++)
            cout << odebrany_ciag[i];
            cout << endl;

    }
    else
    {

        if(wagaH>0 && wagaH<=korekcja)
        {
            cout << "Podany ciag posiada blad w czesci zabezpieczajacej" << endl;
            cout << "Ciag po poprawieniu: ";
            int kolumnaA=0;
            for(int kolumnaX=k; kolumnaX<n; kolumnaX++)
            {
                odebrany_ciag[kolumnaX]=dodawanie_modulo(odebrany_ciag[kolumnaX], syndrom[kolumnaA]);
                kolumnaA++;
            }
            for(int i=0; i<n; i++)
                cout << odebrany_ciag[i];
            cout << endl;
            cout << "Zdekodowane slowo informacyjne: ";
            for(int i=0; i<k; i++)
                cout << odebrany_ciag[i];
            cout << endl;
        }
        else{
        if(korekcja!=0){
        int przestawienia=0;
        for(int powt=0; powt<n; powt++)
        {
            przestawienia++;
            string slowo0[1]=odebrany_ciag[0];
            for(int i=0; i<n; i++)
            {
                if(i!=n-1)
                    odebrany_ciag[i]=odebrany_ciag[i+1];
                else
                    odebrany_ciag[i]=slowo0[0];
            }
            for(int i=0; i<n-k; i++)
                syndrom[i]="0";
            for(int i=0; i<n-k; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(odebrany_ciag[j]=="1")
                        syndrom[i]=dodawanie_modulo(syndrom[i], macierz_zabezpieczajaca[j][i]);
                }
            }
            cout << "Syndrom po " << przestawienia << " przesunieciach: ";
            for(int i=0; i<n-k; i++)
                cout << syndrom[i];
            cout << endl;

            wagaH=0;
            for(int i=0; i<n-k; i++)
                if(syndrom[i]=="1")
                    wagaH++;
            if(wagaH<=korekcja)
                break;
        }
        if(wagaH<=korekcja)
        {
            cout << "Podany ciag posada blad w czesci kodowej" << endl;
            cout << "Odebrany ciag przesuniety " << przestawienia << " razy w lewo: ";

            for(int i=0; i<n; i++)
                cout << odebrany_ciag[i];
            cout << endl;

            cout << "Syndrom wynosi: ";
            for(int i=0; i<n-k; i++)
                cout << syndrom[i];
            cout << endl;

            cout << "Odebrany przesuniety ciag po poprawieniu: ";
            int kolumnaA=0;
            for(int kolumnaX=k; kolumnaX<n; kolumnaX++)
            {
                odebrany_ciag[kolumnaX]=dodawanie_modulo(odebrany_ciag[kolumnaX], syndrom[kolumnaA]);
                kolumnaA++;
            }
            for(int i=0; i<n; i++)
                cout << odebrany_ciag[i];
            cout << endl;

            for(int i=przestawienia; i>0; i--)
            {
                string pamiec[1]=odebrany_ciag[n-1];
                for(int i=n-1; i>-1; i--)
                    {
                        if(i!=0)
                        {
                            odebrany_ciag[i]=odebrany_ciag[i-1];
                        }
                        else
                        {
                            odebrany_ciag[0]=pamiec[0];
                        }
                    }
            }
            cout << "Poprawiony odebrany ciag: ";
            for(int i=0; i<n; i++)
                cout << odebrany_ciag[i];
            cout << endl;

            cout << "Zdekodowane slowo informacyjne: ";
            for(int i=0; i<k; i++)
                cout << odebrany_ciag[i];
            cout << endl;
        }
        }

        }
        if(wagaH>korekcja)
            cout << "Odebrany ciag jest bledny i niekorygowalny" << endl; cout << endl;
    }
}

    return 0;
}
