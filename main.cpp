#include "include/StatieSortare.h"
#include "include/ContainerPlastic.h"
#include "include/ContainerBiodegradabile.h"
#include "include/ContainerElectronice.h"
#include "include/Exceptii.h"
#include "include/DeseuPlastic.h"
#include "include/DeseuBiologic.h"
#include "include/DeseuElectronic.h"
#include "include/DeseuFactory.h"
#include <iostream>
#include "include/ContainerSticla.h"
#include "include/DeseuSticla.h"
#include "Logger.h"
#include <memory>
#include <sstream>

bool autentifica_admin() {
    const std::string parola_corecta = "admin123";
    std::string parola_introdusa;
    int incercari = 3;

    while (incercari > 0) {
        std::cout << "Introduceti parola de administrator: ";
        std::cin >> parola_introdusa;

        if (parola_introdusa == parola_corecta) {
            Logger::get_instance().success("Autentificare reusita!");
            return true;
        }

        incercari--;
        if (incercari > 0)
            Logger::get_instance().warning("Parola gresita! Mai aveti " + std::to_string(incercari) + " incercari.");
    }

    Logger::get_instance().error("Prea multe incercari gresite. Acces blocat!");
    return false;
}

void curata_cin() {
    if (std::cin.eof()) {
        std::cout << "\n[Sistem] Iesire de urgenta (EOF detectat).\n";
        exit(0);
    }
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int main() {
    std::cout << "=== PORNIRE SISTEM SMART DE GESTIONARE A DESEURILOR ===\n\n";

    StatieSortare statia_centrala;
    auto* c_plastic = new ContainerPlastic(101, "Strada Primaverii", 200.0f, 85.5f);
    auto* c_bio = new ContainerBiodegradabile(102, "Piata Centrala", 150.0f, 18.5f, true);
    auto* c_electric = new ContainerElectronice(103, "Liceul Teoretic", 50.0f, true);
    auto* c_sticla = new ContainerSticla(104, "Parcul Central", 50.0f, true);

    statia_centrala.adaugaContainer(c_plastic);
    statia_centrala.adaugaContainer(c_bio);
    statia_centrala.adaugaContainer(c_electric);
    statia_centrala.adaugaContainer(c_sticla);

    c_plastic->set_prag_colectare(80.0f);
    c_bio->set_prag_colectare(70.0f);
    c_electric->set_prag_colectare(60.0f);
    c_sticla->set_prag_colectare(65.0f);

    try {
        *c_plastic += DeseuPlastic(50.0f, TipPlastic::PET);
        *c_bio += DeseuBiologic(100.0f, true);
        *c_electric += DeseuElectronic(10.0f, false);
        *c_plastic += DeseuElectronic(5.0f, true);
        *c_sticla += DeseuSticla(15.0f, CuloareSticla::VERDE, false);

    } catch (const EroareTipDeseu& eroare) {
        Logger::get_instance().error(eroare.what());
    } catch (const EroareSuprasolicitare<int>& eroare) {
        std::stringstream ss;
        ss << eroare;
        Logger::get_instance().error(ss.str());
    } catch (const std::exception& eroare) {
        Logger::get_instance().error(eroare.what());
    }

    statia_centrala.colecteaza_tot_gunoiul();
///
    StatieSortare statia_sector_2;
    statia_sector_2.adaugaContainer(new ContainerPlastic(201, "Aleea Trandafirilor", 300.0f, 90.0f));
    statia_sector_2.adaugaContainer(new ContainerBiodegradabile(202, "Parcul Tineretului", 200.0f, 15.0f, false));
    statia_sector_2.adaugaContainer(new ContainerElectronice(203, "Bulevardul Unirii", 50.0f, true));
    statia_sector_2.adaugaContainer(new ContainerSticla(204, "Centrul Vechi", 100.0f, true));

    // bool sistem_pornit = true;
    int rol = 0;
    while (rol != 3) {
        std::cout << "\n=========================================\n";
        std::cout << "        SELECTARE ROL UTILIZATOR         \n";
        std::cout << "=========================================\n";
        std::cout << "1. Cetatean (Arunca deseuri)\n";
        std::cout << "2. Administrator (Gestioneaza sistemul)\n";
        std::cout << "3. Oprire Sistem\n";
        std::cout << "Alegeti rolul: ";

        // int rol;
        if (!(std::cin >> rol)) {
            curata_cin();
            continue;
        }

        if (rol == 3) {
            break;
        }

        if (rol == 1) {
            bool in_meniu_cetatean = true;
            while (in_meniu_cetatean) {
                std::cout << "\n--- INTERFATA CETATEAN ---\n";
                std::cout << "1. Vezi containerele disponibile\n";
                std::cout << "2. Arunca gunoi\n";
                std::cout << "3. Inapoi la selectia rolului\n";
                std::cout << "Alegere: ";

                int optiune_c;
                if (!(std::cin >> optiune_c)) {
                    curata_cin();
                    continue;
                }

                switch (optiune_c) {
                    case 1:
                        statia_sector_2.afiseaza_rezumat();
                        break;
                    case 2: {
                        try {
                            std::cout << "\nIntroduceti ID-ul (Indexul) containerului (0=Plastic, 1=Bio, 2=Electronice, 3=Sticla): ";
                            int index;
                            if (!(std::cin >> index)) {
                                curata_cin();
                                throw std::invalid_argument("Index invalid!");
                            }

                            // statia_sector_2[index];

                            std::cout << "Introduceti cantitatea (kg): ";
                            float cantitate;
                            if (!(std::cin >> cantitate)) {
                                curata_cin();
                                throw std::invalid_argument("Cantitate invalida!");
                            }

                            if (cantitate <= 0) {
                                throw EroareCantitateInvalida("Cantitatea introdusa trebuie sa fie strict pozitiva!");
                            }

                            std::cout << "Introduceti tipul deseului (Plastic / Biologic / Electronice / Sticla): ";
                            std::string tip;
                            std::cin >> tip;

                            std::unique_ptr<Deseu> deseu(DeseuFactory::creeaza(tip, cantitate));
                            *(statia_sector_2[index]) += *deseu;

                            std::cout << deseu->genereaza_raport_ecologic();

                            statia_sector_2.colectare_automata();

                        } catch (const std::exception& e) {
                            Logger::get_instance().error("ACTIUNE RESPINSA: " + std::string(e.what()));
                        }
                        break;
                    }
                    case 3:
                        in_meniu_cetatean = false;
                        break;
                    default:
                        std::cout << "Optiune invalida!\n";
                }

            }
        }
        else if (rol == 2) {
            if (!autentifica_admin()) {
                std::cout << "[Sistem] Acces refuzat la interfata de administrator.\n";
                continue;
            }

            bool in_meniu_admin = true;
            while (in_meniu_admin) {
                std::cout << "1. Mentenanta (Detalii tehnice)\n";
                std::cout << "2. Sorteaza flota dupa umplere\n";
                std::cout << "3. Raport complet statie\n";
                std::cout << "4. Cauta container dupa ID\n";
                std::cout << "5. Inapoi la selectia rolului\n";
                std::cout << "Alegere: ";

                int optiune_a;
                if (!(std::cin >> optiune_a)) {
                    curata_cin();
                    continue;
                }

                switch (optiune_a) {
                    case 1:
                        statia_sector_2.mentenanta_rutina();
                        break;
                    case 2: {
                        std::cout << "\nAlegeti criteriul de sortare:\n";
                        std::cout << "1. Dupa gradul de umplere (Descrescator)\n";
                        std::cout << "2. Dupa ID (Crescator)\n";
                        std::cout << "Alegere: ";
                        int crit;
                        if (!(std::cin >> crit)) {
                            curata_cin();
                            break;
                        }

                        if (crit == 1) {
                            SortareDupaUmplere strategie_umplere;
                            statia_sector_2.executa_sortare(strategie_umplere);
                            Logger::get_instance().success("Flota a fost sortata dupa gradul de umplere!");
                        } else if (crit == 2) {
                            SortareDupaID strategie_id;
                            statia_sector_2.executa_sortare(strategie_id);
                            Logger::get_instance().success("Flota a fost sortata dupa ID!");
                        } else {
                            std::cout << "Criteriu invalid.\n";
                        }

                        // Afișăm rezultatul sortării
                        statia_sector_2.afiseaza_rezumat();
                        break;
                    }
                    case 3:
                        statia_sector_2.afiseaza_raport_complet();
                        break;
                    case 4: {
                        std::cout << "Introduceti ID-ul containerului: ";
                        int id_cautat;
                        if (!(std::cin >> id_cautat)) {
                            curata_cin();
                            break;
                        }
                        try {
                            const ContainerDeseuri* gasit = statia_sector_2.cauta_dupa_id(id_cautat);
                            std::cout << *gasit << "\n";
                        } catch (const std::out_of_range& e) {
                            std::cerr << "[Eroare] " << e.what() << "\n";
                        }
                        break;
                    }
                    case 5:
                        in_meniu_admin = false;
                        break;
                    default: std::cout << "Optiune invalida!\n";
                }
            }
        } else {
            std::cout << "Rol invalid!\n";
        }
    }


    std::cout << "\n[SISTEM OPRIT] Va multumim ca pastrati orasul curat!\n";
    return 0;
}