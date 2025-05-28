#ifndef TESTAT_CIRCULATORIU_H
#define TESTAT_CIRCULATORIU_H

#include "Donator.h"
#include<chrono>

class TestatCirculatoriu : public Donator {
    private:
        std::chrono::minutes debitCardiac;
        bool reflexPupilarFotomotor;
        bool reflexCornean;
        bool presiuneSupraorbitala;    

    public:

        //Constructor TestatCirculatoriu
        TestatCirculatoriu(const std::string& NUME, const std::string& PRENUME, const std::string& DATA_NASTERII,
               std::string apartinator, const std::string& CNP, std::string numarMatricol,
               int debitCardiacMin, bool reflexPupilar, bool reflexCornean, bool presiuneSupraorbitala);

        TestatCirculatoriu(const TestatCirculatoriu& other);

        TestatCirculatoriu& operator=(const TestatCirculatoriu& other);

        std::shared_ptr<Donator> clone() const override;

        void verificareConditiiDeces() override;

       ~TestatCirculatoriu() override = default;
};

#endif