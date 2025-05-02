/* 
Donatii de Organe
*/

#include<iostream>
#include<chrono>
#include<vector>
#include<utility>
#include<string>
#include<memory>
#include<fstream>
#include<sstream>

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

class Donator {
    protected:
        const std::string NUME;
        const std::string PRENUME;
        const std::string DATA_NASTERII;
        std::string apartinator;
        const std::string CNP;
        std::string numarMatricol;
        std::vector <std::string> organeDisponibile;

    public:

     Donator(const std::string& NUME, const std::string& PRENUME, const std::string& DATA_NASTERII,
        std::string apartinator, const std::string& CNP, std::string numarMatricol)
        : NUME(NUME), PRENUME(PRENUME), DATA_NASTERII(DATA_NASTERII), apartinator(apartinator), CNP(CNP), numarMatricol(numarMatricol) {}

         virtual Donator* clone() const = 0;

        //Avizam faptul ca testele de reflexe au iesit negative, iar in caz de imposibilitate, ca s-a efectuat testul aditional.
        virtual void verificareConditiiDeces() = 0;
        
        // virtual void efectuareTransplant();

        //Verificam functia medicilor care au realizat atestarea pentru a ne asigura ca respecta legislatia din Romania.
        virtual void verificareAtestareDeces() {}

        std::vector<std::string>& getOrganeDisponibile()
        {
            return organeDisponibile;
        }

        std::string getNumarMatricol()
        {
            return numarMatricol;
        }

        virtual ~Donator() = default;
        
};



class Pacient {
    private:
        const std::string NUME;
        const std::string PRENUME;
        const std::string CNP;
        std::string organNecesar;

    public:
        Pacient(const std::string NUME, const std::string PRENUME, const std::string CNP, std::string organNecesar)
        : NUME(NUME), PRENUME(PRENUME), CNP(CNP), organNecesar(organNecesar) {}

        ~Pacient() {}

        void verificarePosibilitateTransplant(std::vector <Donator> posibiliDonatori) {
            for(Donator& i : posibiliDonatori)
            {
                for(std::string& j : i.getOrganeDisponibile())
                {
                    if (j == organNecesar)
                        std::cout << "Transplantul se poate efectua! A fost gasita o potrivire cu donatorul cu numarul matricol " 
                        << i.getNumarMatricol() << '\n';
                }
            }
        }

};


class Pacienti {
    private: 
        std::vector <Pacient> pacienti;
    public:
};

class Medic {
    private: 
        const std::string NUME;
        const std::string PRENUME;
        std::string functie;

    public:
            Medic(const std::string& nume, const std::string& prenume, const std::string& functie)
            : NUME(nume), PRENUME(prenume), functie(functie) {}

            std::string getNUME() { return NUME; }

            std::string getPRENUME() { return PRENUME; }

            std::string getFunctie() { return functie; }
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
        const std::string& numeMedic2, const std::string& prenumeMedic2, const std::string& functieMedic2, testAuxiliar test)
        : Donator(NUME, PRENUME, DATA_NASTERII, apartinator, CNP, numarMatricol),  
          medicATI(numeMedicATI, prenumeMedicATI, functieMedicATI),
          medic2(numeMedic2, prenumeMedic2, functieMedic2), test(test)
        { 
        reflexe.push_back(std::make_pair("Reflex Pupilar Fotomotor", Prezent));
        reflexe.push_back(std::make_pair("Reflex Cornean", Prezent));
        reflexe.push_back(std::make_pair("Reflex Voma", Prezent));
        reflexe.push_back(std::make_pair("Reflex Tuse", Prezent));
        reflexe.push_back(std::make_pair("Reflex Motor Nervi Cranieni", Prezent));
        reflexe.push_back(std::make_pair("Reflex Oculo Cefalic", Prezent));
        reflexe.push_back(std::make_pair("Reflex Oculo Vestibular", Prezent));
        reflexe.push_back(std::make_pair("Test Apnee", Prezent));
        }

        Donator* clone() const override {
        return new ImposibilTestatNeurologic(*this);  
        }

        std::vector<std::pair<std::string, testareReflex>>& getReflexe() {
            return reflexe;
        }

        void verificareConditiiDeces() override
        {
            int caz = 1;
           for(int i=0; i < reflexe.size(); i++)
           {
            if(reflexe[i].second == 2)
                {
                    std::cout << reflexe[i].first << " nu a putut fi testat corespunzator. Se verifica testarea auxiliara. \n";
                    if (test == Fara_testare)
                        std::cout << "Testarea auxiliara nu a fost realizata pentru "<< NUME << " "<<PRENUME <<'.'
                        << "Recomandam luarea masurilor legale necesare. \n";
                    else
                        std::cout << "Test auxiliar efectuat: " << test << '\n';
                }
           }
        }

        void verificareAtestareDeces() override {
            bool ok = 1;
            if (medicATI.getFunctie() != "Medic anestezie - terapie intensiva")
            {
                std::cout << medicATI.getNUME() << " " << medicATI.getPRENUME() << " nu avea competentele necesare pentru a atesta decesul pe cale cerebrala. "
                << "Recomandam luarea masurilor legale necesare.  \n";
                ok = 0;
            }
            if (medic2.getFunctie() != "Medic anestezie - terapie intensiva" && medic2.getFunctie() != "Medic neurolog" 
            && medic2.getFunctie() != "Medic neurochirurg")
            {
                std::cout << medic2.getNUME() << " " << medic2.getPRENUME() << " nu avea competentele necesare pentru a atesta decesul pe cale cerebrala. "
                << "Recomandam luarea masurilor legale necesare.  \n";
                ok = 0;
            }
            if (ok == 1)
                std::cout << "Decesul a fost atestat corespunzator de personal autorizat. \n";

        }

       ~ImposibilTestatNeurologic() override = default;

};

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
        const std::string& numeMedic2, const std::string& prenumeMedic2, const std::string& functieMedic2)
        : Donator(NUME, PRENUME, DATA_NASTERII, apartinator, CNP, numarMatricol),  // Apelează constructorul clasei Donator
          medicATI(numeMedicATI, prenumeMedicATI, functieMedicATI),
          medic2(numeMedic2, prenumeMedic2, functieMedic2) {
        
        // Inițializarea reflexelor
        reflexe.push_back(std::make_pair("Reflex Pupilar Fotomotor", true));
        reflexe.push_back(std::make_pair("Reflex Cornean", true));
        reflexe.push_back(std::make_pair("Reflex Voma", true));
        reflexe.push_back(std::make_pair("Reflex Tuse", true));
        reflexe.push_back(std::make_pair("Reflex Motor Nervi Cranieni", true));
        reflexe.push_back(std::make_pair("Reflex Oculo Cefalic", true));
        reflexe.push_back(std::make_pair("Reflex Oculo Vestibular", true));
        reflexe.push_back(std::make_pair("Test Apnee", true));
        }


       Donator* clone() const override {
        return new TestatNeurologic(*this);  
        }

         std::vector<std::pair<std::string, bool> >& getReflexe() {
            return reflexe;
         }

        void verificareConditiiDeces() override
        {   
            int ok = 1;
            for(int i=0; i<reflexe.size(); i++)
            {
                if(reflexe[i].second == true)
                    std::cout << NUME << " " << PRENUME << " prezenta urmatorul reflex in momentul atestarii decesului : "
                    << reflexe[i].first << '\n';
                    ok = 0;
            }
            if (ok == 0)
              {
                std::cout << "Medicii " << medicATI.getNUME() <<  " " << medicATI.getPRENUME() <<" si " <<medic2.getNUME() << " "
                << medic2.getPRENUME() << " sunt chemati in fata instantei judecatoresti. \n";
              }
            else
            {
                std::cout << "Verificarea conditiilor de deces pe cale cerebrala pentru " << NUME << " "
                << PRENUME << " a fost efectuata corespunzator. \n";
            }
        }


            void verificareAtestareDeces() override {
            bool ok = 1;
            if (medicATI.getFunctie() != "Medic anestezie - terapie intensiva")
            {
                std::cout << medicATI.getNUME() << " " << medicATI.getPRENUME() << " nu avea competentele necesare pentru a atesta decesul pe cale cerebrala. "
                << "Recomandam luarea masurilor legale necesare.  \n";
                ok = 0;
            }
            if (medic2.getFunctie() != "Medic anestezie - terapie intensiva" && medic2.getFunctie() != "Medic neurolog" 
            && medic2.getFunctie() != "Medic neurochirurg")
            {
                std::cout << medic2.getNUME() << " " << medic2.getPRENUME() << " nu avea competentele necesare pentru a atesta decesul pe cale cerebrala. "
                << "Recomandam luarea masurilor legale necesare.  \n";
                ok = 0;
            }
            if (ok == 1)
                std::cout << "Decesul a fost atestat corespunzator de personal autorizat. \n";

        }

       ~TestatNeurologic() override = default;

};






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
               int debitCardiacMin, bool reflexPupilar, bool reflexCornean, bool presiuneSupraorbitala)
         : Donator(NUME, PRENUME, DATA_NASTERII, apartinator, CNP, numarMatricol), 
          debitCardiac(debitCardiacMin), reflexPupilarFotomotor(reflexPupilar), reflexCornean(reflexCornean),
          presiuneSupraorbitala(presiuneSupraorbitala) {}

        Donator* clone() const override {
            return new TestatCirculatoriu(*this); 
        }

        void verificareConditiiDeces() override
        {   
            bool ok = 1;
            if (debitCardiac < std::chrono::minutes(5))
                { std::cout << "Lipsa activitatii cardiace nu a fost verificata corespunzator pentru " << NUME << " " << PRENUME << 
                ". Recomandam luarea masurilor legale necesare. " << '\n';
                ok = 0;
                }
            if (reflexPupilarFotomotor == 1 || reflexCornean == 1 || presiuneSupraorbitala == 1)
            {
                std::cout << "Donatorul " << NUME << " " << PRENUME 
                << "avea reflexe ale nervilor cranieni prezente in momentul atestarii decesului pe cale circulatorie. Recomandam luarea masurilor legale necesare. \n";
                ok = 0;
            }
            if (ok == 1)
                std::cout << "Conditiile premergatoare atestarii decesului pe cale cardiaca pentru " <<NUME << " " 
                << PRENUME <<" au fost indeplinite corespunzator. \n";
            
        }

       ~TestatCirculatoriu() override = default;
};


class Donn {
    private:
        std::shared_ptr<Donator> pointer;
    
    public:
        Donn(std::shared_ptr<Donator> ptr = nullptr) : pointer(ptr) {}

};
    




std::vector<Donn> citireDonatori(const std::string& fisier) {
    std::fstream fin(fisier);
    std::vector <Donn> donatori;

    std::string linie;
    while(std::getline(fin, linie)) {
        if (linie.empty())
            continue;
        std::string Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol, COD;
        Nume = linie;
        std::getline(fin, Prenume);
        std::getline(fin, Data_nasterii);
        std::getline(fin, Apartinator);
        std::getline(fin, CNP);
        std::getline(fin, NumarMatricol);
        std::getline(fin, COD);

        if(COD == "1")
        {
            std::string MedNume, MedPrenume, MedFunctie, Med2Nume, Med2Prenume, Med2Functie;
            std::getline(fin, MedNume);
            std::getline(fin, MedPrenume);
            std::getline(fin, MedFunctie);
            std::getline(fin, Med2Nume);
            std::getline(fin, Med2Prenume);
            std::getline(fin, Med2Functie);

        std::string test;
        std::getline(fin, test);
        testAuxiliar Aux = static_cast<testAuxiliar> (std::stoi(test));
        std::vector<testareReflex> reflexxe;
        for (int i=0; i<8;i++)
        {
            std::getline(fin, linie);
            if(linie.empty())
            {
                int refl = std::stoi(linie);
                reflexxe.push_back(static_cast <testareReflex> (refl));
            }
        }

        ImposibilTestatNeurologic obiect(Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol,
            MedNume, MedPrenume, MedFunctie,
            Med2Nume, Med2Prenume, Med2Functie,
            Aux
        );

        for (int i=0; i < obiect.getReflexe().size(); i++)
        {
            obiect.getReflexe()[i].second = reflexxe[i];
        }


        std::vector <std::string> h;
        h.push_back("inima");
        h.push_back("rinichi");
        h.push_back("plamani");
        h.push_back("ficat");
        h.push_back("pancreas");
        obiect.getOrganeDisponibile() = h;


       Donn d(std::make_shared<ImposibilTestatNeurologic>(obiect));
        donatori.push_back(d);
        }
        else if (COD == "2")
        {
            std::string MedNume, MedPrenume, MedFunctie, Med2Nume, Med2Prenume, Med2Functie;
            std::getline(fin, MedNume);
            std::getline(fin, MedPrenume);
            std::getline(fin, MedFunctie);
            std::getline(fin, Med2Nume);
            std::getline(fin, Med2Prenume);
            std::getline(fin, Med2Functie);
            std::vector <bool> reflexxe;
            for (int i=0; i<8;i++)
            {
            std::getline(fin, linie);
            if(linie.empty())
            {
                bool refl = static_cast <bool> (std::stoi(linie));
                reflexxe.push_back(refl);
            }}
            TestatNeurologic obiect(Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol,
            MedNume, MedPrenume, MedFunctie, 
            Med2Nume, Med2Prenume, Med2Functie
            );

            for (int i=0; i < obiect.getReflexe().size(); i++)
            {
            obiect.getReflexe()[i].second = reflexxe[i];
            }
            Donn d(std::make_shared<TestatNeurologic>(obiect));
            donatori.push_back(d);            
        }
        else if (COD == "3")
        {   
            bool a, b, c;
            std::string x;
            std::getline(fin, x);
            int mi = std::stoi(x);
            int debitCardiac = mi;
            std::getline(fin, x);
            mi = std::stoi(x);
            a = static_cast <bool> (mi);
            std::getline(fin, x);
            mi = std::stoi(x);
            b = static_cast <bool> (mi);
            std::getline(fin, x);
            mi = std::stoi(x);
            c = static_cast <bool> (mi);

            TestatCirculatoriu obiect(Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol,
            debitCardiac, a, b, c);
            Donn d(std::make_shared<TestatCirculatoriu>(obiect));
            donatori.push_back(d);
        }
    }
}


int main()
{
    Pacienti suferinzi;

}