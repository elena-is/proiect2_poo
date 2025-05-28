#ifndef DONATOR_H
#define DONATOR_H

#include<string>
#include<vector>
#include<utility>

class Donator {
    protected:
        const std::string NUME;
        const std::string PRENUME;
        const std::string DATA_NASTERII;
        std::string apartinator;
        const std::string CNP;
        std::string numarMatricol;
        std::vector <std::string> organeDisponibile;
        static int contorNascutiDupa2000;

    public:

     Donator(const std::string& NUME, const std::string& PRENUME, const std::string& DATA_NASTERII,
        std::string apartinator, const std::string& CNP, std::string numarMatricol);

        Donator(const Donator& other);
        
        Donator& operator=(const Donator& other);

        virtual std::shared_ptr<Donator> clone() const = 0;

        static int getContorNascutiDupa2000();

        //Avizam faptul ca testele de reflexe au iesit negative, iar in caz de imposibilitate, ca s-a efectuat testul aditional.
        virtual void verificareConditiiDeces() = 0;
        
        // virtual void efectuareTransplant();

        //Verificam functia medicilor care au realizat atestarea pentru a ne asigura ca respecta legislatia din Romania.
        virtual void verificareAtestareDeces();

        std::vector<std::string>& getOrganeDisponibile();

        void setOrganeDisponibile(std::vector<std::string> organe);

        std::string getNumarMatricol();

        virtual ~Donator() = default;
        
};

#endif