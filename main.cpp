#include <iostream>
#include <vector>
#include <string>
#include "Polinom.h"

using namespace std;

// vraca tacku u kojoj se sijeku polinomi P i Q u intervalu [a,b]
// baca izuzetak ako je (P(a) - P(b))*(Q(a) - Q(b)) > 0
// koristeci metod bisekcije(polovljenja intervala)
double PresjekPolinoma(Polinom &P, Polinom &Q, double a, double b, double e){
    if ((P.VratiVrijednost(a) - P.VratiVrijednost(b))*(Q.VratiVrijednost(a) - Q.VratiVrijednost(b)) > 0)
        throw "";

    if ((P.VratiVrijednost(a) - Q.VratiVrijednost(a))*(P.VratiVrijednost(b) - Q.VratiVrijednost(b)) > 0)
        throw "Vrijednost presjeka polinoma u datim tackama je istog znaka.";

    double c;
    while (abs(b - a) > e){
        c = (a + b)/2;
        if ((P.VratiVrijednost(a) - Q.VratiVrijednost(a))*(P.VratiVrijednost(c) - Q.VratiVrijednost(c)) < 0)
            b = c;
        else
            a = c;
    }

    return c;
}

// funkcija prima niz polinoma te ih sortira po velicini
void Sortiraj(Polinom *niz, int broj_elemenata){
    int mini;
    for (int i = 0; i < broj_elemenata - 1; i++){
        mini = i;
        for (int j = i + 1; j < broj_elemenata; j++){
            if (niz[mini].dajVektorKoeficijenata().size() > niz[j].dajVektorKoeficijenata().size())
                mini = j;
            else if(niz[mini].dajVektorKoeficijenata().size() == niz[j].dajVektorKoeficijenata().size())
                if (niz[mini].dajVektorKoeficijenata()[0] >= niz[j].dajVektorKoeficijenata()[0])
                    mini = j;
        }
        swap(niz[mini], niz[i]);
    }
}

int main()
{
    vector<int> v{1, 2, 0, -3};
    Polinom p(v);
    cout << "P=" << p << endl << endl; // ispisuje polinom ispravno
    cout << p(2) << endl << endl; // nalazi vrijednost polinoma u tacki ispravno

    vector<int> v1{2, -1, 0, 6}, v2{3, 1, -3};
    Polinom p1(v1), p2(v2);
    cout << p1*p2 << endl << endl;    // ispravno mnozi dva polinoma

    Polinom p3 = p^2;
    cout << p3 << endl << endl; // ispravno stepenovano

    try{
        double nula = p.NulaPolinoma(0., 5., 0.000001);  // ispravno radi
        cout << "Nula polinoma je " << nula << endl;

        cout << "Tacka u kojoj se sijeku polinomi je " << PresjekPolinoma(p, p1, 0., 5., 0.00001) << endl << endl;
    }
    catch(const char poruka[]){
        cout << poruka << endl;
    }

    Polinom niz_polinoma[]{p, p1, p2};
    Sortiraj(niz_polinoma, 3);  // ispravno radi
    for(auto i : niz_polinoma)
        cout << i << endl;
}
