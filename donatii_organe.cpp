#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include "Donator.h"
#include "ImposibilTestatNeurologic.h"
#include "TestatNeurologic.h"
#include "TestatCirculatoriu.h"
#include "utilitare.h"
#include "Exceptii.h"
//#include "ClaseMici.h"

    int Donator::contorNascutiDupa2000 = 0;

    Donator::Donator(const std::string& NUME, const std::string& PRENUME, const std::string& DATA_NASTERII,
        std::string apartinator, const std::string& CNP, std::string numarMatricol)
        : NUME(NUME), PRENUME(PRENUME), DATA_NASTERII(DATA_NASTERII), apartinator(apartinator), CNP(CNP), numarMatricol(numarMatricol) {
            if( CNP[0] == '5' || CNP[0] == '6')
                contorNascutiDupa2000++;

            if (DATA_NASTERII.length() >= 2) {
        char penultima = DATA_NASTERII[DATA_NASTERII.length() - 2];
        char ultima = DATA_NASTERII[DATA_NASTERII.length() - 1];

        if (penultima == '0' && ultima > '7') {
            throw DonatorMinor();
        }
        else if (penultima == '1')
            throw DonatorMinor();
        }
        }

            Donator::Donator(const Donator& other)
        : NUME(other.NUME), PRENUME(other.PRENUME), DATA_NASTERII(other.DATA_NASTERII),
          apartinator(other.apartinator), CNP(other.CNP), numarMatricol(other.numarMatricol),
          organeDisponibile(other.organeDisponibile) {
        }

        Donator& Donator::operator=(const Donator& other) {
            if (this != &other) {
            organeDisponibile = other.organeDisponibile;
            numarMatricol = other.numarMatricol;
            apartinator = other.apartinator;
            }
            return *this;
        }

        int Donator::getContorNascutiDupa2000() {
        return contorNascutiDupa2000;
         }


        //Verificam functia medicilor care au realizat atestarea pentru a ne asigura ca respecta legislatia din Romania.
        void Donator::verificareAtestareDeces() {}

        std::vector<std::string>& Donator::getOrganeDisponibile()
        {
            return organeDisponibile;
        }

        void Donator::setOrganeDisponibile(std::vector<std::string> organe){
            organeDisponibile = organe;
        }

        std::string Donator::getNumarMatricol()
        {
            return numarMatricol;
        }

        Medic::Medic(const std::string& nume, const std::string& prenume, const std::string& functie)
            : NUME(nume), PRENUME(prenume), functie(functie) {}

         Medic::Medic(const Medic& other)
        : NUME(other.NUME), PRENUME(other.PRENUME), functie(other.functie) {
        }

        Medic& Medic::operator=(const Medic& other) {
        if (this != &other) {
            functie = other.functie;
        }
        return *this;
        }

        std::string Medic::getNUME() { return NUME; }

        std::string Medic::getPRENUME() { return PRENUME; }

        std::string Medic::getFunctie() { return functie; }


         Pacient::Pacient(const std::string NUME, const std::string PRENUME, const std::string CNP, std::string organNecesar)
        : NUME(NUME), PRENUME(PRENUME), CNP(CNP), organNecesar(organNecesar) {}

        Pacient::~Pacient() {}

        void Pacient::verificarePosibilitateTransplant(std::vector <Donn> posibiliDonatori) {
            for(auto i : posibiliDonatori)
            {
                for(std::string& j : i.getOrganeDisponibile())
                {
                    if (j == organNecesar)
                        std::cout << "Transplantul se poate efectua! A fost gasita o potrivire cu donatorul cu numarul matricol " 
                        << i.getNumarMatricol() << '\n';
                }
            }
        }


   ImposibilTestatNeurologic::ImposibilTestatNeurologic(
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

        ImposibilTestatNeurologic::ImposibilTestatNeurologic(const ImposibilTestatNeurologic& other)
        : Donator(other), 
          medicATI(other.medicATI), medic2(other.medic2), test(other.test),
          reflexe(other.reflexe) {
        }

            ImposibilTestatNeurologic& ImposibilTestatNeurologic::operator=(const ImposibilTestatNeurologic& other) {
            if (this != &other) {
            Donator::operator=(other);

            medicATI = other.medicATI;
            medic2 = other.medic2;
            test = other.test;
            reflexe = other.reflexe;
        }
        return *this;
        }


        std::shared_ptr<Donator> ImposibilTestatNeurologic::clone() const {
        return std::make_shared<ImposibilTestatNeurologic>(*this);  
        }

        std::vector<std::pair<std::string, testareReflex> >& ImposibilTestatNeurologic::getReflexe() {
            return reflexe;
        }

        void ImposibilTestatNeurologic::setReflexe(std::vector <testareReflex> a){
            for(int i=0; i<reflexe.size();i++)
            {
                reflexe[i].second = a[i];
            }
        }

        void ImposibilTestatNeurologic::verificareConditiiDeces()
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

        void ImposibilTestatNeurologic::verificareAtestareDeces() {
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



         TestatNeurologic::TestatNeurologic(
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

         TestatNeurologic::TestatNeurologic(const TestatNeurologic& other)
        : Donator(other),
          medicATI(other.medicATI),
          medic2(other.medic2), 
          reflexe(other.reflexe) {}

        TestatNeurologic& TestatNeurologic::operator=(const TestatNeurologic& other) {
            if (this != &other) {
            Donator::operator=(other); 
            medicATI = other.medicATI; 
            medic2 = other.medic2; 
            reflexe = other.reflexe; 
            }
            return *this;
        }



       std::shared_ptr<Donator> TestatNeurologic::clone() const{
        return std::make_shared<TestatNeurologic>(*this);  
        }

        std::vector<std::pair<std::string, bool> >& TestatNeurologic::getReflexe() {
            return reflexe;
         }

        void TestatNeurologic::setReflexe(std::vector <bool> a){
            for(int i=0; i < reflexe.size(); i++)
            {
                reflexe[i].second = a[i];
            }
        }
         
        void TestatNeurologic::verificareConditiiDeces()
        {   
            int ok = 1;
            for(int i=0; i<reflexe.size(); i++)
            {
                if(reflexe[i].second == true)
                    {
                        std::cout << NUME << " " << PRENUME << " prezenta urmatorul reflex in momentul atestarii decesului : "
                    << reflexe[i].first << '\n';
                    ok = 0;
                    }
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


            void TestatNeurologic::verificareAtestareDeces() {
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


   TestatCirculatoriu::TestatCirculatoriu(const std::string& NUME, const std::string& PRENUME, const std::string& DATA_NASTERII,
               std::string apartinator, const std::string& CNP, std::string numarMatricol,
               int debitCardiacMin, bool reflexPupilar, bool reflexCornean, bool presiuneSupraorbitala)
         : Donator(NUME, PRENUME, DATA_NASTERII, apartinator, CNP, numarMatricol), 
          debitCardiac(debitCardiacMin), reflexPupilarFotomotor(reflexPupilar), reflexCornean(reflexCornean),
          presiuneSupraorbitala(presiuneSupraorbitala) {}
    
    TestatCirculatoriu::TestatCirculatoriu(const TestatCirculatoriu& other)
        : Donator(other),
          debitCardiac(other.debitCardiac),
          reflexPupilarFotomotor(other.reflexPupilarFotomotor),
          reflexCornean(other.reflexCornean),
          presiuneSupraorbitala(other.presiuneSupraorbitala) {}

    TestatCirculatoriu& TestatCirculatoriu::operator=(const TestatCirculatoriu& other) {
        if (this != &other) {
            Donator::operator=(other);
            debitCardiac = other.debitCardiac;
            reflexPupilarFotomotor = other.reflexPupilarFotomotor;
            reflexCornean = other.reflexCornean;
            presiuneSupraorbitala = other.presiuneSupraorbitala;
        }
        return *this;
    }
        

        std::shared_ptr<Donator> TestatCirculatoriu::clone() const {
            return std::make_shared<TestatCirculatoriu>(*this); 
        }

        void TestatCirculatoriu::verificareConditiiDeces()
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
                << " avea reflexe ale nervilor cranieni prezente in momentul atestarii decesului pe cale circulatorie. Recomandam luarea masurilor legale necesare. \n";
                ok = 0;
            }
            if (ok == 1)
                std::cout << "Conditiile premergatoare atestarii decesului pe cale cardiaca pentru " <<NUME << " " 
                << PRENUME <<" au fost indeplinite corespunzator. \n";
            
        }


std::vector<Donn> citireDonatori(const std::string& fisier) {
    std::fstream fin(fisier);
    std::vector <Donn> donatori;

    std::string linie;
    while(std::getline(fin, linie)) {
        if (linie.empty())
            continue;
        std::string Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol, COD;
        Nume = linie;
        if (!std::getline(fin, Prenume)) throw EroareCitire("Prenume lipsă");
        if (!std::getline(fin, Data_nasterii)) throw EroareCitire("Data nașterii lipsă");
        if (!std::getline(fin, Apartinator)) throw EroareCitire("Apartinator lipsă");
        if (!std::getline(fin, CNP)) throw EroareCitire("CNP lipsă");
        if (!std::getline(fin, NumarMatricol)) throw EroareCitire("Număr matricol lipsă");
        if (!std::getline(fin, COD)) throw EroareCitire("COD lipsă");

        if(COD == "1")
        {
            std::string MedNume, MedPrenume, MedFunctie, Med2Nume, Med2Prenume, Med2Functie;
            if (!std::getline(fin, MedNume)) throw EroareCitire("MedNume lipsă");
            if (!std::getline(fin, MedPrenume)) throw EroareCitire("MedPrenume lipsă");
            if (!std::getline(fin, MedFunctie)) throw EroareCitire("MedFunctie lipsă");
            if (!std::getline(fin, Med2Nume)) throw EroareCitire("Med2Nume lipsă");
            if (!std::getline(fin, Med2Prenume)) throw EroareCitire("Med2Prenume lipsă");
            if (!std::getline(fin, Med2Functie)) throw EroareCitire("Med2Functie lipsă");

        std::string test;
        if (!std::getline(fin, test)) throw EroareCitire("Test auxiliar lipsă");
        testAuxiliar Aux = static_cast<testAuxiliar> (std::stoi(test));
        std::vector<testareReflex> reflexxe;
        for (int i=0; i<8;i++)
        {
            if (!std::getline(fin, linie)) throw EroareCitire("Reflex lipsă la poziția " + std::to_string(i));
            reflexxe.push_back(static_cast <testareReflex> (std::stoi(linie)));
        }

        ImposibilTestatNeurologic obiect(Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol,
            MedNume, MedPrenume, MedFunctie,
            Med2Nume, Med2Prenume, Med2Functie,
            Aux
        );

        obiect.setReflexe(reflexxe);


        std::vector <std::string> a = { "inima", "rinichi", "plamani", "ficat", "pancreas" };
        obiect.setOrganeDisponibile(a);


       Donn d(std::make_shared<ImposibilTestatNeurologic>(obiect));
        donatori.push_back(d);
        }
        else if (COD == "2")
        {
            std::string MedNume, MedPrenume, MedFunctie, Med2Nume, Med2Prenume, Med2Functie;
            if (!std::getline(fin, MedNume)) throw EroareCitire("MedNume lipsă");
            if (!std::getline(fin, MedPrenume)) throw EroareCitire("MedPrenume lipsă");
            if (!std::getline(fin, MedFunctie)) throw EroareCitire("MedFunctie lipsă");
            if (!std::getline(fin, Med2Nume)) throw EroareCitire("Med2Nume lipsă");
            if (!std::getline(fin, Med2Prenume)) throw EroareCitire("Med2Prenume lipsă");
            if (!std::getline(fin, Med2Functie)) throw EroareCitire("Med2Functie lipsă");

            std::vector <bool> reflexxe;
            for (int i=0; i<8;i++)
            {  if (!std::getline(fin, linie)) throw EroareCitire("Reflex lipsă la poziția " + std::to_string(i));
                reflexxe.push_back(static_cast<bool>(std::stoi(linie)));
            }
            TestatNeurologic obiect(Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol,
            MedNume, MedPrenume, MedFunctie, 
            Med2Nume, Med2Prenume, Med2Functie
            );

            obiect.setReflexe(reflexxe);

            std::vector <std::string> a = { "inima", "rinichi", "plamani", "ficat", "pancreas" };
            obiect.setOrganeDisponibile(a);

            Donn d(std::make_shared<TestatNeurologic>(obiect));
            donatori.push_back(d);            
        }
        else if (COD == "3")
        {   
            bool a, b, c;
            std::string x;
            if (!std::getline(fin, x)) throw EroareCitire("Debit cardiac lipsă");
            int mi = std::stoi(x);
            int debitCardiac = mi;
            if (!std::getline(fin, x)) throw EroareCitire("Valoare A lipsă");
            mi = std::stoi(x);
            a = static_cast <bool> (mi);
            if (!std::getline(fin, x)) throw EroareCitire("Valoare B lipsă");
            mi = std::stoi(x);
            b = static_cast <bool> (mi);
            if (!std::getline(fin, x)) throw EroareCitire("Valoare C lipsă");
            mi = std::stoi(x);
            c = static_cast <bool> (mi);

            TestatCirculatoriu obiect(Nume, Prenume, Data_nasterii, Apartinator, CNP, NumarMatricol,
            debitCardiac, a, b, c);
            Donn d(std::make_shared<TestatCirculatoriu>(obiect));
            donatori.push_back(d);
        }
        else {
            throw EroareCitire("Cod necunoscut: " + COD);
        }

    }
    return donatori;
}

      void Donn::verificareConditiiDeces() {
        if (pointer)
            pointer->verificareConditiiDeces();
        }

        void Donn::verificareAtestareDeces() {
        if (pointer)
            pointer->verificareAtestareDeces();
    }

     std::vector<std::string>& Donn::getOrganeDisponibile() {
        return pointer->getOrganeDisponibile();
    }

      Donn Donn::clone() const {
        return Donn(pointer ? pointer->clone() : nullptr);
    }


    int Donn::verificareTipReal(){
        if (pointer == std::dynamic_pointer_cast<ImposibilTestatNeurologic>(pointer))
            return 1;
        else if (pointer == std::dynamic_pointer_cast<TestatNeurologic>(pointer))
            return 2;
        else if (pointer == std::dynamic_pointer_cast<TestatCirculatoriu>(pointer))
            return 3;
        else 
            return 100;
    }

    EroareCitire::EroareCitire(const std::string& mesaj)
        : std::runtime_error("Eroare la citire: " + mesaj) {}


    void Pacienti::citestePacienti(const std::string& numeFisier) {
        std::ifstream fin(numeFisier);
        if (!fin)
            throw EroareCitire("Nu s-a putut deschide fișierul " + numeFisier);

        std::string linie;
        while (std::getline(fin, linie)) {
            if (linie.empty()) continue;
            std::string nume = linie;

            std::string prenume, cnp, organ;
            if (!std::getline(fin, prenume)) throw EroareCitire("Prenume lipsă");
            if (!std::getline(fin, cnp)) throw EroareCitire("CNP lipsă");
            if (!std::getline(fin, organ)) throw EroareCitire("Organ necesar lipsă");

            pacienti.emplace_back(nume, prenume, cnp, organ);
        }
    }


    std::vector<Pacient>& Pacienti::getPacienti() {
        return pacienti;
    }

    std::string Pacient::getNume() {
        return NUME;
    }

    std::string Donn::getNumarMatricol() {
        return pointer->getNumarMatricol();
    }


    //sortare vector de indici ca nu putem sorta direct pentru ca avem membri const
    void Pacienti::sortarePacienti() {
        std::vector<size_t> indici(pacienti.size());
        for (size_t i = 0; i < indici.size(); ++i)
            indici[i] = i;

        std::sort(indici.begin(), indici.end(), [this](size_t a, size_t b) {
            return pacienti[a].getNume() < pacienti[b].getNume();
        });

        std::cout << "Lista pacienti sortati: \n";
        for (size_t i : indici)
        {
            Pacient& p = pacienti[i];
            std::cout << p.getNume() << '\n';
        }
    }

       Donn Pacient::verificarePosibilitateTransplantReturnare(std::vector <Donn> posibiliDonatori) {
            for(auto i : posibiliDonatori)
            {
                for(std::string& j : i.getOrganeDisponibile())
                {
                    if (j == organNecesar)
                        return i;
                }
            }

            throw DonatorNegasit();
        }

        std::vector <Pacient> Pacienti::getPacientii(){
            return pacienti;
        }


