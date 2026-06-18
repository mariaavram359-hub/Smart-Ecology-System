#ifndef OOP_DESEUHARTIE_H
#define OOP_DESEUHARTIE_H

#pragma once
#include "Deseu.h"
#include <string>

enum class CalitateHartie {
    CARTON,
    PRINT_ALB,
    MACULATURA
};

class DeseuHartie : public Deseu {
private:
    CalitateHartie calitate;

public:
    DeseuHartie(const float cantitate_hartie, const CalitateHartie calit);

    int timp_descompunere_ani() const override;
    float calculeaza_amprenta_carbon() const override;
    std::string get_tip() const override;
    std::string genereaza_raport_ecologic() const override;

    std::string calitate_hartie_to_string() const;

protected:
    void afiseaza_impl(std::ostream& os) const override;
};

#endif //OOP_DESEUHARTIE_H