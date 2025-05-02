#include <stdexcept>
#include <string>

class EroareCitire : public std::runtime_error {
public:
    explicit EroareCitire(const std::string& mesaj);
};