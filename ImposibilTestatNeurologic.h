#ifndef IMPOSIBIL_TESTAT_NEUROLOGIC_H
#define IMPOSIBIL_TESTAT_NEUROLOGIC_H

#include "Donator.h"
#include "ClaseMici.h"

        enum testAuxiliar {
            Angiografie, 
            RMN,
            Fara_testare
        };

        enum testareReflex {
            Prezent,
            Absent,
            Verificare_imposibila
        };

class ImposibilTestatNeurologic : public Donator {

    private:
      
        Medic medicATI;
        Medic medic2; 
        testAuxiliar test;
        std::vector<std::pair<std::string, testareReflex> > reflexe;
      

    public:
    
        ImposibilTestatNeurologic(
        const std::string& NUME, const std::string& PRENUME, const std::string& DATA_NASTERII,
        const std::string& apartinator, const std::string& CNP, const std::string& numarMatricol,
        const std::string& numeMedicATI, const std::string& prenumeMedicATI, const std::string& functieMedicATI,
        const std::string& numeMedic2, const std::string& prenumeMedic2, const std::string& functieMedic2, 
        testAuxiliar test);

        ImposibilTestatNeurologic(const ImposibilTestatNeurologic& other);

        ImposibilTestatNeurologic& operator=(const ImposibilTestatNeurologic& other);
        
        std::shared_ptr<Donator> clone() const override;

        std::vector<std::pair<std::string, testareReflex> >& getReflexe();

        void setReflexe(std::vector <testareReflex>);

        void verificareConditiiDeces() override;

        void verificareAtestareDeces() override;

       ~ImposibilTestatNeurologic() override = default;

};

#endif