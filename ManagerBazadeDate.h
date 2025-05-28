#ifndef MANAGER_H
#define MANAGER_H

#include<iostream>
#include<mutex>

class ManagerBazaDate {
    private:
        static std::unique_ptr<ManagerBazaDate> Manager;
        static std::mutex mutexManager;
        std::string conexiune;

        ManagerBazaDate() : conexiune("Conexiune la baza de date") {}

        ManagerBazaDate(const ManagerBazaDate&) = delete;
        ManagerBazaDate& operator=(const ManagerBazaDate&) = delete;

    public:
        static ManagerBazaDate& getInstanta();

        void conectare();

        void deconectare();
};

#endif