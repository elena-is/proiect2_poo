#ifndef CLASEMICI_H
#define CLASEMICI_H

#include<vector>
#include<type_traits>
#include<iostream>
#include<stack>
#include "Donator.h"
#include "Medic.h"

class Donn {
    private:
        std::shared_ptr<Donator> pointer;
    
    public:
        Donn(std::shared_ptr<Donator> ptr = nullptr) : pointer(ptr) {}

        void verificareConditiiDeces();

        void verificareAtestareDeces();

        std::vector<std::string>& getOrganeDisponibile();

        Donn clone() const;

        int verificareTipReal();

        std::string getNumarMatricol() const;

        friend std::ostream& operator<<(std::ostream& os, const Donn& d);

};

class Pacient {
    private:
        const std::string NUME;
        const std::string PRENUME;
        const std::string CNP;
        std::string organNecesar;

    public:
        Pacient(const std::string NUME, const std::string PRENUME, const std::string CNP, std::string organNecesar);

        ~Pacient();

        void verificarePosibilitateTransplant(std::vector <Donn> posibiliDonatori);

        std::string getNume();

        Donn verificarePosibilitateTransplantReturnare(std::vector <Donn> posibiliDonatori);

};

class Pacienti {
    private: 
        std::vector <Pacient> pacienti;
    public:

    std::vector<Pacient>& getPacienti();

    void citestePacienti(const std::string& numeFisier);

    void sortarePacienti();

    std::vector <Pacient> getPacientii();

};

/* class Medic {
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
*/


//template pentru afisare element care nu este pointer
template <class T>
typename std::enable_if<!std::is_pointer<T>::value, void>::type
afiseaza_element(const T& element) {
    std::cout << element << '\n';
}

//template pentru afisare element care este pointer
template<class T>
typename std::enable_if<std::is_pointer<T>::value, void>::type
afiseaza_element(const T& element) {
    if (element != nullptr) {
        std::cout << *element << '\n';
    } else {
        std::cout << "Pointer null\n";
    }
}

//functie care afiseaza vectorul
template <class T>
void afiseaza_vector(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        afiseaza_element(elem);
    }
}



#endif // CLASE_MICI_H