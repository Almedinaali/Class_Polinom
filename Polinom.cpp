#pragma once
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include "Polinom.h"
using namespace std;


ostream& operator<<(ostream &out, const Polinom &p){ // treba ispisati pd èlana s najveæim do èlana s najmanjim koef
    int stepen(p.koeficijenti.size() - 1);
    vector<int> k(p.koeficijenti);

    if (stepen == 0)  // ako je stepena 0 ispisuje samo slobodni clan
        out << k[0];
    else{
        out << k[0] << "x^" << stepen;
        stepen--;
        for (int i = 1; i < k.size(); i++, --stepen){ // posto su koeficijenti u k poredani od najveceg do najmanjeg
            if (k[i] != 0){  // ako je koeficijent != 0
                if (k[i] > 0) // koef pozitivan
                    out << "+";
                else if (k[i] < 0) // ako je koef negativan
                    out << "-";

                if (stepen == 0 && k[i] > 0)  // ako je slobodni clan veci od nule
                    out << k[i];
                else if (stepen == 0 && k[i] < 0)  // ako je slobodan clan manji od 0
                    out << -k[i];
                else if (k[i] == 1 || k[i] == -1) // ako je koeficijent = 1 ispisi x
                    out << "x";
                else if (k[i] < 0) // da u ispisu ne bismo imali --
                    out << -k[i] << "x";
                else    // tj ako je k[i] > 0 ispisi npr 2x, 7x,...
                    out << k[i] << "x";

                if (stepen > 1)    // ako je stepen veci od 1 ispisi i stepen
                    out << "^" << stepen;
            }
        }
    }

    return out;
}
/*
  // polinom se unosi kao zbir monoma koji nisu sortirani po stepenu pa ih treba sortirati prije umetanja koeficijenata u vektor k
istream& Polinom::operator>>(istream &tok, Polinom &p){
    tok >> p.polinom;

    vector<vector<int>> koeficijenti_i_stepeni;  // sadrzat ce par (koef, stepen)

}
*/

double Polinom::operator()(double x){ // vraca vrijednost polinoma u proslijedjenoj tacki
    double vrijednost(0);
    int stepen(koeficijenti.size() - 1);
    for (int i = 0; i < stepen; i++, stepen--){
        vrijednost += (koeficijenti[i] * pow(x, stepen));
    }
    vrijednost += koeficijenti[koeficijenti.size() - 1];
    return vrijednost;
}

Polinom operator*(const Polinom &p1, const Polinom &p2){

    vector<vector<int>> koeficijenti_i_stepeni;

// koeficijenti je vektor sortiran prema stepenu od najveceg do najmanjeg
    for (int i = 0; i < p1.koeficijenti.size(); i++){
        for (int j = 0; j < p2.koeficijenti.size(); j++){
            vector<int> pom(2);      // (koeficijent, stepen)
            pom[0] = p1.koeficijenti[i] * p2.koeficijenti[j];   // prva koord vektora
            pom[1] = (p1.koeficijenti.size() - 1 - i) + (p2.koeficijenti.size() - 1 - j);  // druga koord vektora
            koeficijenti_i_stepeni.push_back(pom);
        }
    }
// sad u koeficijenti_i_stepeni saberemo sto se sabrati moze
    for (int i = 0; i < koeficijenti_i_stepeni.size(); i++){  //
        for (int j = i + 1; j < koeficijenti_i_stepeni.size() - 1; j++){
            if (koeficijenti_i_stepeni[i][1] == koeficijenti_i_stepeni[j][1]){   // ako su stepeni dva elementa jednaki
                koeficijenti_i_stepeni[i][0] += koeficijenti_i_stepeni[j][0];    // saberi njihove koeficijente
                koeficijenti_i_stepeni.erase(koeficijenti_i_stepeni.begin() + j);  // obrisi podvektor koji si dodao kao sabirak
            }
        }
    }

    vector<int> koef;
    for (int i = 0; i < koeficijenti_i_stepeni.size(); i++){
        koef.push_back(koeficijenti_i_stepeni[i][0]);
    }
    Polinom p3(koef);
    return p3;
}

Polinom operator^(Polinom &p, int stepen){
    Polinom stepenovani(p.koeficijenti);

    if (stepen == 1)
        return stepenovani;

    for (int i = 0; i < stepen - 1; i++)
        stepenovani = stepenovani * p;

 //   this->koeficijenti = p.koeficijenti;

 //   return *this;
    return stepenovani;
}


double Polinom::VratiVrijednost(double x){ // pomocna funkcija jednaka operator()
    double vrijednost(0);
    int stepen(koeficijenti.size() - 1);
    for (int i = 0; i < stepen; i++, stepen--){  // ide do predzadnjeg koeficijenta
        vrijednost += (koeficijenti[i] * pow(x, stepen));
    }
    vrijednost += koeficijenti[koeficijenti.size() - 1];  // dodaje jos slobodni clan
    return vrijednost;
}
// ako su vrijednosti polinoma u tackama a i b suprotnog znaka
// vraca nulu polinoma izmedju tacaka a i b s preciznoscu barem e
// u suprotnom baca izuzetak
// posto je clanica poziva se kao p.NulaPolinoma(...)
// pa se moze koristiti pokazivac *this koji se odnosi na polinom nad kojim es zove funkcija
double Polinom::NulaPolinoma(double a, double b, double e){
    Polinom p = (*this);  // ispravno uradi

    if (p.VratiVrijednost(a) * p.VratiVrijednost(b) > 0)   // ako su vrijednosti polinoma istog znaka ili = 0
        throw "Vrijednosti polinoma u datim tackama su istog znaka.";

    double c;
    while (abs(b - a) > e){
        c = (a + b)/2;
        if (p.VratiVrijednost(a) * p.VratiVrijednost(c) < 0)
            b = c;
        else
            a = c;
    }

    return c;
}
