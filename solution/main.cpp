/**
 * @file
 * @mainpage
 * <h1>Maticove operace, zadani c. 4</h1>
 *
 * pocita hodnoty matice pomoci gaussovy eliminacni metody
 *
 * @author Michal Kalita
 */

#include "functions.h"

/**
 * Hlavni program
 * je povolen jeden argument, a to nazev souboru s matici
 * @param argc pocet argumentu
 * @param args argumenty
 * @return 0 pokud program probehl bez chyby
 */
int main(int argc, char **args) {
    double **array = NULL;
    unsigned int rows = 0, cols = 0;
    int iterator;
    char character;

    if (argc == 1) { // zadna data v parametrech
        cout << "Nacist matici ze souboru? [a/n]: ";
        cin >> character;

        if (character == 'a' || character == 'A') {
            array = load_matrix_file(rows, cols);
        } else {
            array = load_matrix_user(rows, cols);
        }
    }

    if (argc == 2) {
        cout << "load_matrix_file" << endl;
        array = load_matrix_file(args[1], rows, cols);
    }
    else if (argc > 2) {
        cout << "Nerozpoznane parametry programu" << endl;
        cout << "program [input_file]" << endl;
        cout << "program - nazev programu" << endl;
        cout << "input_file - soubor s matici\n"
                "\ttextovy soubor, na kazdem radku je stejny pocet cisel,"
                "cisla jsou oddelena bilym znakem" << endl;
        return 1;
    }

    print(array, cols, rows);

    if (cols > 3) {
        cout << "Nelze vypocitat determinant" << endl;
    } else {
        double det = determinant(array, cols, rows);
        if (det != INFINITY) {
            cout << "Determinant matice je: " << det << endl;
        } else {
            cout << "Nelze vypocitat determinant" << endl;
        }
    }

    double **triangle = gauss_elimination((const double **) array, cols, rows);
    if (triangle != 0) {
        print(triangle, cols, rows);

        for (iterator = 0; iterator < rows; ++iterator) {
            cout << "x" << iterator + 1 << " = " << triangle[iterator][cols - 1] << endl;
        }

        cout << "Chcete ulozit do souboru? [a/n]: ";
        cin >> character;
        if (character == 'a' || character == 'A' || character == '\n') {
            saveToFile(triangle, cols, rows);
        }
    } else {
        cout << "Nelze vypocitat pomoci gaussovy eliminacni metody" << endl;
    }

    // mazani dat
    if (triangle != 0) {
        delete[] triangle[0];
        for (iterator = 1; iterator < rows; ++iterator) {
            delete[] triangle[iterator];
        }
        delete[] triangle;
    }

    delete[] array[0];
    for (iterator = 1; iterator < rows; ++iterator) {
        delete[] array[iterator];
    }
    delete[] array;

    return 0;
}
