#include <stdexcept>
#include <string>

class EroareCitire : public std::runtime_error {
public:
    explicit EroareCitire(const std::string& mesaj);
};

class DonatorNegasit : public std::exception {
public:
    const char* what() const noexcept override {
        return "Nu s-a gasit niciun donator compatibil!";
    }
};

class DonatorMinor : public std::exception {
public:
    const char* what() const noexcept override {
        return "Nu este permis ca donatorul sa fie minor!!";
    }
};