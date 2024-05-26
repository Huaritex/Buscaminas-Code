#include <iostream>
#include <vector>
using namespace std;

struct Mina {
    int fila;
    int columna;
    char tipo; // 'S' para mina pequeña, 'L' para mina grande
};

// Prototipos de funciones
void inicializar_campo(vector<vector<char>>& campo, int m, int n);
void colocar_mina_pequena(vector<vector<char>>& campo, int fila, int columna);
void colocar_mina_grande(vector<vector<char>>& campo, int fila, int columna);
void colocar_minas(vector<vector<char>>& campo, const vector<Mina>& minas);
void calcular_numeros(vector<vector<char>>& campo);
void imprimir_campo(const vector<vector<char>>& campo);

int main() {
    // Variables de apoyo
    int m, n, k;
    cout << "Introduzca fila, columna y numero de minas en ese orden: ";
    cin >> m >> n >> k;

    vector<Mina> minas(k);
    for (int i = 0; i < k; ++i) {
        char tipo;
        cout << "Introduzca fila, columna y tipo de mina (S para pequena, L para grande) para la mina " << i + 1 << ": ";
        cin >> minas[i].fila >> minas[i].columna >> tipo;
        minas[i].tipo = tipo;
        // Convertir a índice basado en 0
        minas[i].fila--;
        minas[i].columna--;
    }

    vector<vector<char>> campo(m, vector<char>(n, '0'));
    
    inicializar_campo(campo, m, n);
    colocar_minas(campo, minas);
    calcular_numeros(campo);
    imprimir_campo(campo);
    cout << "tu matriz se creo afortunadamente" << endl;
    return 0;
}

// Función para inicializar el campo en 0
void inicializar_campo(vector<vector<char>>& campo, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            campo[i][j] = '0';
        }
    }
}

// Función para colocar una mina pequeña
void colocar_mina_pequena(vector<vector<char>>& campo, int fila, int columna) {
    campo[fila][columna] = 'S';
}

// Función para colocar una mina grande
void colocar_mina_grande(vector<vector<char>>& campo, int fila, int columna) {
    campo[fila][columna] = 'L';
    if (fila + 1 < campo.size()) campo[fila + 1][columna] = 'L';
    if (columna + 1 < campo[0].size()) campo[fila][columna + 1] = 'L';
    if (fila + 1 < campo.size() && columna + 1 < campo[0].size()) campo[fila + 1][columna + 1] = 'L';
}

// Función para colocar minas en el campo
void colocar_minas(vector<vector<char>>& campo, const vector<Mina>& minas) {
    for (const Mina& mina : minas) {
        if (mina.tipo == 'S') {
            colocar_mina_pequena(campo, mina.fila, mina.columna);
        } else if (mina.tipo == 'L') {
            colocar_mina_grande(campo, mina.fila, mina.columna);
        }
    }
}

// Función para calcular los números del campo
void calcular_numeros(vector<vector<char>>& campo) {
    int m = campo.size();
    int n = campo[0].size();
    int number_1[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int number_2[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (campo[i][j] == 'S' || campo[i][j] == 'L') 
                continue;

            int count = 0;
            for (int d = 0; d < 8; ++d) {
                int ni = i + number_1[d];
                int nj = j + number_2[d];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && (campo[ni][nj] == 'S' || campo[ni][nj] == 'L')) {
                    count++;
                }
            }
            campo[i][j] = '0' + count;
        }
    }
}

// Función para imprimir el campo
void imprimir_campo(const vector<vector<char>>& campo) {
    for (const auto& fila : campo) {
        for (size_t j = 0; j < fila.size(); ++j) {
            cout << fila[j];
            if (j < fila.size() - 1) cout << ' ';
        }
        cout << '\n';
    }
}
