/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * TDA Lista
 * 
 * En este programa se implementa una interfaz de usuario en consola para
 * operar el TDA de lista.
 * 
 * Fecha: 21/01/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */

#include <iostream>
#include <cstdlib>

#include "TDA-Lista.h"

using namespace std;

/**
 * Solicita presionar enter al usuario para continuar.
 */
void esperar_enter()
{
  cout << "Presione enter para continuar...";

  cin.get();
  cin.get();
}

// La cantidad máxima de elementos que pude tener la lista.
constexpr int maximo = 8;

int main()
{
  Lista lista{maximo};
  int opc = -1, valor;

  do
  {
// Limpiar terminal
#ifdef __unix__
    system("tput reset");
#elif defined(_WIN32)
    system("cls")
#endif

    // Menú principal
    cout << "Tamaño: " << maximo << '\n';
    cout << "Lista: " << lista << "\n\n";

    cout << "1. Insertar al inicio.\n";
    cout << "2. Insertar al final.\n";
    cout << "3. Suprimir al inicio.\n";
    cout << "4. Suprimir al final.\n";
    cout << "5. Eliminar duplicados.\n";
    cout << "6. Obtener sucesor.\n";
    cout << "7. Obtener predecesor.\n";
    cout << "0. Salir.\n\n";
    cout << "Opción: ";
    cin >> opc;

    int tamano_anterior;
    switch (opc)
    {
    case 1:
      cout << "\nValor: ";
      cin >> valor;
      try
      {
        // Para insertar al inicio se utiliza el índice 0.
        lista.insertar(0, valor);
      }
      catch (error_lista_llena &error)
      {
        cerr << "Error, no se pueden insertar mas elementos.\n";
        esperar_enter();
      }
      break;
    case 2:
      cout << "\nValor: ";
      cin >> valor;
      try
      {
        // Para insertar al final se utiliza la longitud de la lista.
        lista.insertar(lista.length(), valor);
      }
      catch (error_lista_llena &error)
      {
        cerr << "Error, no se pueden insertar mas elementos.\n";
        esperar_enter();
      }
      break;
    case 3:
      try
      {
        // Para eliminar al inicio se utiliza el índice 0.
        lista.eliminar(0);
      }
      catch (error_lista_vacia &error)
      {
        cerr << "No se pudo eliminar, la lista esta vacia.\n";
        esperar_enter();
      }
      break;
    case 4:
      try
      {
        // Para eliminar al final se utiliza el índice del tamaño de la lista.
        lista.eliminar(lista.length());
      }
      catch (error_lista_vacia &error)
      {
        cerr << "No se pudo eliminar, la lista esta vacia.\n";
        esperar_enter();
      }
      break;
    case 5:
      // Si hay duplicados, la lista cambia de longitud.
      tamano_anterior = lista.length();
      lista.eliminarDuplicados();

      if (lista.length() < tamano_anterior)
      {
        cout << "Se eliminaron los duplicados." << endl;
      }
      else
      {
        cout << "No hay duplicados en la lista." << endl;
      }
      esperar_enter();
      break;
    case 6:
      cout << "Valor:\n";
      cin >> valor;
      try
      {
        cout << "El sucesor de " << valor << " es " << lista.sucesor(valor) << endl;
        esperar_enter();
      }
      catch (error_sin_sucesor &error)
      {
        cerr << "Error, no hay suficientes elementos en el arreglo.\n";
        esperar_enter();
      }
      break;
    case 7:
      cout << "Valor:\n";
      cin >> valor;
      try
      {
        cout << "El predecesor de " << valor << " es " << lista.predecesor(valor) << endl;
        esperar_enter();
      }
      catch (error_sin_antecesor &error)
      {
        cerr << "Error, no hay suficientes elementos en el arreglo.\n";
        esperar_enter();
      }
      break;
    }
  } while (opc != 0);

  return 0;
}