#include "Donator.h"
//#include "ClaseMici.h"
#include "utilitare.h"
#include "Exceptii.h"
#include <iostream>

int main()
{
    std::vector <Donn> donatori;
    try {
    donatori = citireDonatori("donatori.txt");
        for (Donn d : donatori) {
            d.verificareConditiiDeces(); 
            std::cout << '\n';
            if( d.verificareTipReal() == 1 || d.verificareTipReal() == 2)
                d.verificareAtestareDeces();
            std::cout << '\n';
            std::cout << '\n';
        }
    } catch (const EroareCitire& e) {
    std::cerr << e.what() << std::endl;
    }

    std::vector <Donn> fostiDonatori;
    for (int i = 0; i < donatori.size(); i++)
    {
        if (donatori[i].getOrganeDisponibile().size() == 0)
        {
            fostiDonatori.push_back(donatori[i].clone());
            donatori.erase(donatori.begin() + i);
        }
    }

    int numarDonatoriTineri = Donator::getContorNascutiDupa2000();
    std::cout << "Numar decedati care au mai putin de 25 de ani: " << numarDonatoriTineri << '\n';


    Pacienti suferinzi;
    suferinzi.citestePacienti("pacienti.txt");
    std::cout << "Pacienti curenti: \n";
    for (auto i : suferinzi.getPacienti())
    {
        std::cout << i.getNume() << '\n';
    }
    
    std::cout << '\n';
    suferinzi.getPacienti()[1].verificarePosibilitateTransplant(donatori);

}