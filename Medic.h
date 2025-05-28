#ifndef MEDIC_H
#define MEDIC_H
//Design Pattern de tip Memento pentru a salva si restaura functia medicului

#include<string>
#include<iostream>
//#include "ClaseMici.h"
#include <stack>

class MedicMemento {
    private:
        std::string functieSalvata;

    public:
        MedicMemento(const std::string& functie) : functieSalvata(functie) {};

        friend class Medic;
};

class Medic {
    private: 
        const std::string NUME;
        const std::string PRENUME;
        std::string functie;

    public:
    Medic(const std::string& nume, const std::string& prenume, const std::string& functie);

            Medic(const Medic& other);

            Medic& operator=(const Medic& other);

            std::string getNUME();

            std::string getPRENUME();

            std::string getFunctie();

            void setFunctie(std::string functieNoua);

            void afiseazaMedic() const;

        friend class MedicMemento;

        MedicMemento creazaMemento() const;

        void restaureazaMemento(const MedicMemento& m);
};



class MedicCaretaker {
    private:
        std::stack <MedicMemento> istoricFunctii;
    
    public:
        void salveazaFunctie(const Medic& m) {
            istoricFunctii.push(m.creazaMemento());
        }

        void restaureazaFunctie(Medic& m) {
            if (!istoricFunctii.empty()) {
                m.restaureazaMemento(istoricFunctii.top());
                istoricFunctii.pop();
            } else {
                std::cout << "Nu exista functii salvate pentru restaurare.\n";
            }
        }
};


#endif // MEDIC_H