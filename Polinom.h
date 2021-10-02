#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//template<typename Tip>
class Polinom{                    // koeficijenata ce biti za 1 vise od stepena
    vector<int> koeficijenti;  // koeficijenti od najvceceg do najmanjeg
    string polinom;
public:
    Polinom(){}
    Polinom(vector<int> &k): koeficijenti(k) {} // pravi polinom stepena s ciji su koeficijenti k
    inline friend ostream& operator<< (ostream &, const Polinom &); // prvi parametar koji se prosljedjuje funkciji je cout -> ispisuje Polinom
   // inline friend istream& operator>>(istream &tok, Polinom &p);       // -||- cin
    inline double operator()(double ); // vraca vrijednost polinoma u datoj tacki
    inline friend Polinom operator*(const Polinom &,const Polinom &);
    inline friend Polinom operator^(Polinom &, int);
    double VratiVrijednost(double);
    double NulaPolinoma(double, double, double); // funkcija clanica
    vector<int> dajVektorKoeficijenata() { return koeficijenti; }
};

#include "Polinom.cpp"
