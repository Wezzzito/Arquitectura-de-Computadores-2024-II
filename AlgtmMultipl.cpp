#include <iostream>
#include <bitset>
using namespace std;
int bincomp_2(int num, int bits) {
    return (num >= 0) ? (num & ((1 << bits) - 1)) : ((1 << bits) + num);
}
class Operacion {
public:
    virtual int ejecutar(int A, int B, int bits) = 0;
};
class Suma : public Operacion {
public:
    int ejecutar(int A, int B, int bits) override {
        return (A + B) & ((1 << bits) - 1);
    }
};
class Resta : public Operacion {
public:
    int ejecutar(int A, int B, int bits) override {
        Suma suma;
        return suma.ejecutar(A, bincomp_2(-B, bits), bits);
    }
};
void print(int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((num >> i) & 1);
    }
}
void desplazar(int *Acc, int *Q, int *Q_1, int bits) {
    *Q_1 = *Q & 1;
    *Q = (*Q >> 1) | (*Acc & 1) << (bits - 1);
    *Acc = (*Acc >> 1) | (*Acc & (1 << (bits - 1)));
}
void booth(int M, int Q, int bits) {
    int Acc = 0, Q_1 = 0, contador = bits;
    Q = bincomp_2(Q, bits); 
    M = bincomp_2(M, bits);
    Suma suma_op;
    Resta resta_op;
    cout << "Estado inicial:\nA: ";
    print(Acc, bits);
    cout << "\nQ: ";
    print(Q, bits);
    cout << "\nQ-1: " << Q_1 << endl;
    while (contador > 0) {
        if((Q & 1) == 0 && Q_1 == 1) {
            Acc = suma_op.ejecutar(Acc, M, bits);
        }else if ((Q & 1) == 1 && Q_1 == 0) {
            Acc = resta_op.ejecutar(Acc, M, bits);
        }
        desplazar(&Acc, &Q, &Q_1, bits);
        cout << "Desplazamos:\nA: ";
        print(Acc, bits);
        cout << "\nQ: ";
        print(Q, bits);
        cout << "\nQ-1: " << Q_1 << endl;
        contador--;
    }
    cout << "Resultado:\n";
    print(Acc, bits);
    cout << " ";
    print(Q, bits);
}

int main(){
    int M = 0, Q = 0, bits = 1;
    do{
        cout << "Ingresa el numero de bits: " << endl;
        cin >> bits;
    }while(bits < 0);
    cout << "Ingresa el multiplicando (M): " << endl;
    cin >> M;
    cout << "Ingresa el multiplicador (Q): "<< endl;
    cin >> Q;
    booth(M, Q, bits);
    return 0;
}