#include "bluetooth.hpp"

bluetooth::bluetooth()
{
}

bluetooth::~bluetooth()
{
}

// Método para transformar el mensaje de string a ascii y luego a binario
void bluetooth::mensaje_bin(string mensaje)
{
    cout << endl
         << "El mensaje es: " << mensaje << endl;
    msg_binario = new bitset<8>[mensaje.length()];
    bitset<8> temp[mensaje.length()];

    for (int i = 0; i < mensaje.length(); i++)
    {
        int aux = 0;
        aux = (int)mensaje[i];
        v_mensaje_aux.push_back(aux);
        temp[i] = bitset<8>(mensaje[i]);
        msg_binario[i] = temp[i];
    }
    cout << endl
         << endl
         << " Mensaje en binario: " << endl;
    for (int i = 0; i < mensaje.length(); i++)
    {
        cout << msg_binario[i] << endl;
    }
}

// Método para transformar los string a enteros y meterlos en el vector
void bluetooth::transforma(string r1_string, string r2_string, string r3_string, string r4_string, string r5_string, string r1_aux_string)
{
    cout << endl;
    for (int i = 0; i < r1_string.length(); i++)
    {
        int aux = r1_string[i];

        if (aux == 49)
            r1_vector.push_back(1);
        else
        {
            r1_vector.push_back(0);
        }
    }

    cout << endl;
    for (int i = 0; i < r2_string.length(); i++)
    {
        int aux = r2_string[i];

        if (aux == 49)
            r2_vector.push_back(1);
        else
        {
            r2_vector.push_back(0);
        }
    }

    cout << endl;
    for (int i = 0; i < r3_string.length(); i++)
    {
        int aux = r3_string[i];

        if (aux == 49)
            r3_vector.push_back(1);
        else
        {
            r3_vector.push_back(0);
        }
    }

    for (int i = 0; i < r4_string.length(); i++)
    {
        int aux = r4_string[i];

        if (aux == 49)
            r4_vector.push_back(1);
        else
        {
            r4_vector.push_back(0);
        }
    }

    for (int i = 0; i < r5_string.length(); i++)
    {
        int aux = r5_string[i];

        if (aux == 49)
            r5_vector.push_back(1);
        else
        {
            r5_vector.push_back(0);
        }
    }

    for (int i = 0; i < r1_aux_string.length(); i++)
    {
        int aux = r1_aux_string[i];

        if (aux == 49)
        {
            r2_aux_vector.push_back(1);
            r1_aux_vector.push_back(1);
        }
        else
        {
            r2_aux_vector.push_back(0);
            r1_aux_vector.push_back(0);
        }
    }
}

// Método que realiza el desplazamiento y se encarga de actualizar los registros
void bluetooth::desplazamiento(string mensaje)
{
    cout << endl
         << " DESPLAZAMIENTO" << endl;
    for (int j = 0; j < (mensaje.length() * 8); j++)
    {
        cout << endl
             << endl
             << endl;

        // Número de unos
        contador = r1_vector[24] + r2_vector[30] + r3_vector[32] + r4_vector[38];
        // Xor entre los LSFR
        int suma_total = (r1_vector[24] ^ r2_vector[30] ^ r3_vector[32] ^ r4_vector[38]);
        write();

        // Calculando a quien introducir en el vector
        r1 = r1_vector[7] ^ r1_vector[11] ^ r1_vector[19] ^ r1_vector[24];
        r2 = r2_vector[11] ^ r2_vector[15] ^ r2_vector[23] ^ r2_vector[30];
        r3 = r3_vector[3] ^ r3_vector[23] ^ r3_vector[27] ^ r3_vector[32];
        r4 = r4_vector[3] ^ r4_vector[27] ^ r4_vector[35] ^ r4_vector[38];
        r5 = r5_vector[4] ^ r5_vector[9] ^ r5_vector[14] ^ r5_vector[24];

        // Moviendo los LSFR
        cout << endl
             << endl
             << " Moviendo el registro 1 y metiendo un " << r1 << endl;
        r1_vector.erase(r1_vector.begin() + r1_vector.size() - 1);
        r1_vector.insert(r1_vector.begin(), r1);

        cout << " Moviendo el registro 2 y metiendo un " << r2 << endl;
        r2_vector.erase(r2_vector.begin() + r2_vector.size() - 1);
        r2_vector.insert(r2_vector.begin(), r2);

        cout << " Moviendo el registro 3 y metiendo un " << r3 << endl;
        r3_vector.erase(r3_vector.begin() + r3_vector.size() - 1);
        r3_vector.insert(r3_vector.begin(), r3);

        cout << " Moviendo el registro 4 y metiendo un " << r4 << endl;
        r4_vector.erase(r4_vector.begin() + r4_vector.size() - 1);
        r4_vector.insert(r4_vector.begin(), r4);

        cout << " Moviendo el registro 5 y metiendo un " << r5 << endl;
        r5_vector.erase(r5_vector.begin() + r5_vector.size() - 1);
        r5_vector.insert(r5_vector.begin(), r5);

        // Procedimiento 1: Damos los valores a R1, R2, T1 y T2
        // Inversa de R1
        swap(r1_aux_vector[0], r1_aux_vector[1]);

        cout << endl
             << " R1 actual: ";
        cout << r1_aux_vector[0] << r1_aux_vector[1] << endl;

        cout << " R2 actual: ";
        cout << r2_aux_vector[0] << r2_aux_vector[1] << endl;

        // Damos valor a T1
        t1_vector.clear();
        for (int i = 0; i < r1_aux_vector.size(); i++)
        {
            t1_vector.push_back(r1_aux_vector[i]);
        }
        cout << " T1 actual: ";
        cout << t1_vector[0] << t1_vector[1] << endl;

        // Damos valor a T2
        t2_vector.clear();
        int c1 = r2_aux_vector[1];
        int c2 = c1 ^ r2_aux_vector[0];

        // Introducimos los valores calculados
        t2_vector.push_back(c1);
        t2_vector.push_back(c2);

        cout << " T2 actual: ";
        cout << t2_vector[0] << t2_vector[1] << endl;

        // Secuencia cifrante:
        int suma_total_2 = suma_total ^ r1_aux_vector[1] ^ r5_vector[38];
        sec_cifrante_vector.push_back(suma_total_2);

        // Paso a decimal el binario R1
        int num = 0;
        int expo = 0;
        for (int i = r1_aux_vector.size() - 1; i >= 0; i--)
        {
            num += (pow(2, (expo))) * r1_aux_vector[i];
            expo++;
        }

        // Suamamos R1 decimal con el número de unos
        int suma_decimal = num + contador;
        cout << endl
             << " La suma decimal es: " << suma_decimal;

        // Dividimos entre 2 el resultado
        int division = (suma_decimal / 2);
        cout << " y si dividimos: " << division << endl
             << endl;

        // Hay que pasar el resultado de la division a binario:
        bitset<2> aux;

        aux = bitset<2>(division);
        bitset<2> div_bitset_secundario;
        div_bitset_secundario = aux.to_ulong();

        div_vector.clear();

        // Introduzco el bitset a vector también
        for (int i = div_bitset_secundario.size() - 1; i >= 0; i--)
        {
            div_vector.push_back(div_bitset_secundario[i]);
        }

        cout
            << " División almacenada en vector: ";
        for (int i = 0; i < div_vector.size(); i++)
        {
            cout << div_vector[i];
        }

        // Introduzco lo del vector al bitset
        int k = 0;
        for (int i = 0; i < div_vector.size(); i++)
        {
            div_bitset.set(i, div_vector[k]);
            k++;
        }


        div_xor_t2.clear();

        // Tenemos que hacer un xor entre T2 y la division pasada a binaria:
        for (int i = 0; i < div_vector.size(); i++)
        {
            div_xor_t2.push_back(div_vector[i] ^ t2_vector[i]);
        }

        cout << endl
             << " T2 ^ div en vector: ";

        for (int i = 0; i < div_vector.size(); i++)
        {
            cout << div_xor_t2[i];
        }

        int q = 0;
        for (int i = 0; i < div_xor_t2.size(); i++)
        {
            div_xor_t2_bitset.set(i, div_xor_t2[q]);
            q++;
        }

        // Último xor para conocer el nuevo valor de R1:
        r1_aux_vector.clear();
        r2_aux_vector.clear();

        for (int i = 0; i < div_xor_t2.size(); i++)
        {
            int temp = div_xor_t2[i] ^ t1_vector[i];
            r1_aux_vector.push_back(temp);
            r2_aux_vector.push_back(temp);
        }

        cout << endl
             << " Actualizando R1 en vector: ";

        for (int i = 0; i < r1_aux_vector.size(); i++)
        {
            cout << r1_aux_vector[i];
        }
    }
    // Meto los resultados a un bitset para operar en el cifrado
    sec_cifrante_bitset = new bitset<8>[mensaje.length()];

    int k = 0;
    for (int j = 0; j < sec_cifrante_vector.size() / 8; j++)
    {
        for (int i = 7; i >= 0; i--)
        {
            sec_cifrante_bitset[j].set(i, sec_cifrante_vector[k]);
            k++;
        }
    }

}

void bluetooth::cifrado(string mensaje)
{
    cout << endl
         << endl;
    msg_binario_cifrado = new bitset<8>[mensaje.length()];
    for (int i = 0; i < mensaje.length(); i++)
    {
        msg_binario_cifrado[i] = msg_binario[i] ^ sec_cifrante_bitset[i];
    }
    cout << endl
         << " El cifrado es: ";
    for (int i = 0; i < mensaje.length(); i++)
    {
        cout << msg_binario_cifrado[i];
    }
    cout << endl;
}

void bluetooth::translate(string mensaje)
{
    for (int i = 0; i < mensaje.length(); i++)
    {

        msg_cifrado_ascii_temp += to_string((int)msg_binario_cifrado[i].to_ulong());
        msg_cifrado += msg_binario_cifrado[i].to_ulong();
    }
    cout << endl
         << " En string: " << msg_cifrado << endl;
}

void bluetooth::descifrado(string mensaje)
{
    cout << endl;
    msg_binario_descifrado = new bitset<8>[mensaje.length()];
    for (int i = 0; i < mensaje.length(); i++)
    {
        msg_binario_descifrado[i] = msg_binario_cifrado[i] ^ sec_cifrante_bitset[i];
    }
    cout << endl
         << " El descifrado es: ";
    for (int i = 0; i < mensaje.length(); i++)
    {
        cout << msg_binario_descifrado[i];
    }
    cout << endl;
}

void bluetooth::translate_des(string mensaje)
{
    for (int i = 0; i < mensaje.length(); i++)
    {

        msg_descifrado_ascii_temp += to_string((int)msg_binario_descifrado[i].to_ulong());
        msg_descifrado += msg_binario_descifrado[i].to_ulong();
    }
    cout << endl
         << " En string: " << msg_descifrado << endl;
}

void bluetooth::write()
{

    cout << endl
         << endl;
    for (int i = 0; i < r1_vector.size(); i++)
    {
        cout << r1_vector[i] << "|";
    }
    cout << endl;

    for (int i = 0; i < r2_vector.size(); i++)
    {
        cout << r2_vector[i] << "|";
    }

    cout << endl;

    for (int i = 0; i < r3_vector.size(); i++)
    {
        cout << r3_vector[i] << "|";
    }

    cout << endl;

    for (int i = 0; i < r4_vector.size(); i++)
    {
        cout << r4_vector[i] << "|";
    }
    cout << endl;

    for (int i = 0; i < r5_vector.size(); i++)
    {
        cout << r5_vector[i] << "|";
    }

    cout << endl
         << endl
         << "SECUENCIA CIFRANTE: ";
    for (int i = 0; i < sec_cifrante_vector.size(); i++)
    {
        cout << sec_cifrante_vector[i] << "|";
    }
}
