//Simulador de Comercio Electrónico "Ecommerce"
//Autor:
//Pablo González (A01745096)
//02 / 12 / 2020

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unistd.h>
#include <iomanip>

using namespace std;

class Productos {

private:
    string _name;
    string _description;
    int _value;

public:

    Productos(string name, string description, int value)
    {
        _name = name;
        _description = description;
        _value = value;
    }

    string get_name()
    {
        return _name;
    }

    string get_description()
    {
        return _description;
    }

    int get_value()
    {
        return _value;
    }
};

class Carrito {

private:
    int _cant;
    string _nom;
    int _val;
    int _importe;

public:

    Carrito(int cant, string nom, int val, int importe)
    {
        _cant = cant;
        _nom = nom;
        _val = val;
        _importe = importe;
    }

    string get_nom()
    {
        return _nom;
    }

    int get_val()
    {
        return _val;
    }

    int get_cant()
    {
        return _cant;
    }
    int get_importe()
    {
        return _importe;
    }
};

class Comprador {

private:

    int _total;
    vector<Carrito> _carrito;

public:

    Comprador(int total)
    {
        _total = total;
    }

    int get_total()
    {
        return _total;
    }

    bool is_over()
    {
        _total = 0;
        return _total;
    }

    void comprar(Productos x)
    {
        int quantity;
        cout << "¿Cuántas unidades deseas adquirir? (-1 para cancelar) ";
        cin >> quantity;

        if (!(quantity == -1)) {
            int tot_compra = quantity*x.get_value();

            cout << quantity << " unidad(es) de " << x.get_name() << " a $";
            cout << x.get_value() << "c/u, importe = $" << tot_compra << endl;

            _carrito.push_back(Carrito {quantity, x.get_name(), x.get_value(), tot_compra});

            _total += tot_compra;
        }

    }
    void imprimir_carrito()
    {
        cout << endl;
        cout << left << setw(12) << "Cantidad" << setw(12) << left << "Producto" << setw(12);
        cout << "P. Unitario" << setw(21) << "Importe" << endl;
        cout << setfill ('-') << setw (50) << "\n" << endl;
        cout << setfill(' ');
        for (int i = 0; i < _carrito.size(); i++) {
            cout << left << setw(3) << " ";
            cout << left << setw(9) << _carrito[i].get_cant();
            cout << left << setw(12);
            cout <<_carrito[i].get_nom();
            cout << left << setw(1);
            cout << "$" << left << setw(11) << _carrito[i].get_val();
            cout << setw(0) << left;
            cout << "$" << _carrito[i].get_importe() << endl;
            }
    }

    void borrar_carrito()
    {
        _carrito.clear();
    }

};

class Ecommerce {

private:

    Comprador _comprador {0};
    vector<Productos> _productos;

public:

    Ecommerce()
    {
        _productos.push_back(Productos {"Manzana", "Fruta pomacea de forma redonda y sabor dulce.",            890});
        _productos.push_back(Productos {"Naranja", "Fruta citrica obtenida del naranjo dulce.",                615});
        _productos.push_back(Productos {"Platano", "Fruto rico en almidon cubierto con una cascara.",          950});
        _productos.push_back(Productos {"Melon",   "Baya peponide con forma desde esferica hasta elipsoidal.", 150});
        _productos.push_back(Productos {"Sandia",  "Fruto peponide, carnoso y jugoso, casi esferico.",         780});
        _productos.push_back(Productos {"Mango",   "Fruta jugosa, es redondo a oblongo.",                      100});

    }

    void run_shop()
    {
        cout << "Ecommerce.com\n";
        cout << "=============\n";
        cout <<"© 2020 por Pablo González (A01745096) y Lesly Guerrero (A01753039) \n";
        int option;
        do {
            cout <<endl;
            cout << "*** MENÚ PRINCIPAL ***\n" << endl;
            cout << "1) Seleccionar productos\n";
            cout << "2) Ver carrito de compras\n";
            cout << "3) Terminar compra\n";
            cout << "4) Salir\n";
            cout << "Selecciona opción: ";
            cin >> option;
            switch (option) {
            case 1:
                perform_comprar();
                break;
            case 2:
                show_comprador_carrito();
                break;
            case 3:
                terminar_compra();
                break;
            case 4:
                cout << "\nSaliendo...\n";
                sleep(2);
                break;
            }
        } while (!(option == 4));

        cout << "\nGracias por comprar con nosotros! \n";

    }

    void show_comprador_carrito()
    {

        cout <<"\n*** CARRITO DE COMPRAS ***\n";

        if (!(_comprador.get_total() == 0)) {

        _comprador.imprimir_carrito();
        cout << setfill ('-') << setw (50) << "\n" << endl;
        cout << setfill (' ') << right << setw (39) << "TOTAL: $";
        cout << _comprador.get_total() << endl;

        } else {
            cout << endl;
            cout << "El carrito de compras está vacío";
            cout << endl;
        }

    }

    void perform_comprar()
    {
        cout << endl;
        cout << "*** SELECCIONAR PRODUCTO ***" << "\n";
        cout << endl;
        cout << left << setw(12) << "  Producto" << left << setw(25) << "  Descripcion";
        cout << right << setw(40) << "P. Unitario" << "\n";
        cout << setfill ('-') << setw (88) << "\n";
        //cout << ;

        for (int i = 0; i < _productos.size(); i++) {
            cout << setfill(' ');
            cout << left << setw(0);
            cout << i+1 << ") " << left << setw(10) << left << _productos[i].get_name() << " ";
            cout << setw(57) << left;
            cout <<_productos[i].get_description();
            cout << setw(0) << left ;
            cout << "$" << _productos[i].get_value() << endl;
            //cout << setw(11);
        }

        int opcion;
        cout << endl << "¿Qué producto deseas comprar? (-1 para cancelar) ";
        cin >> opcion;
        if (!(opcion == -1)){
        Productos c = _productos[opcion-1];
        _comprador.comprar(c);
        } else {
            cout << endl;
            //run_shop();
        }

    }

     void terminar_compra()
    {
        cout << endl;
        cout << "El total de tu compra es: $" << _comprador.get_total() << endl;
        cout << "Gracias por comprar en Ecommerce.com!" << endl;

        _comprador.borrar_carrito();

        _comprador.is_over();
    }
};

int main()
{
    Ecommerce cliente;
    cliente.run_shop();
    return 0;
}