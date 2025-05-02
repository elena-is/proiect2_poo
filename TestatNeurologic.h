#ifndef TESTAT_NEUROLOGIC_H
#define TESTAT_NEUROLOGIC_H

#include "Donator.h"
#include "ClaseMici.h"

class TestatNeurologic : public Donator {
    private: 
       
        Medic medicATI;
        Medic medic2;
        std::vector<std::pair<std::string, bool> > reflexe;

    public:

          TestatNeurologic(
        const std::string& NUME, const std::string& PRENUME, const std::string& DATA_NASTERII,
        const std::string& apartinator, const std::string& CNP, const std::string& numarMatricol,
        const std::string& numeMedicATI, const std::string& prenumeMedicATI, const std::string& functieMedicATI,
        const std::string& numeMedic2, const std::string& prenumeMedic2, const std::string& functieMedic2);

        TestatNeurologic(const TestatNeurologic& other);

        TestatNeurologic& operator=(const TestatNeurologic& other);
        
       std::shared_ptr<Donator> clone() const override;

        std::vector<std::pair<std::string, bool> >& getReflexe();
         
        void setReflexe(std::vector <bool> a);

        void verificareConditiiDeces() override;

        void verificareAtestareDeces() override;

       ~TestatNeurologic() override = default;

};

#endif