/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * TDA Lista
 * 
 * En este archivo se implementan las operaciones básicas de un TDA de lista
 * basada en un arreglo.
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

// Las clases para representar las excepciones.
struct error_lista_vacia
{
};
struct error_lista_llena
{
};
struct error_sin_sucesor
{
};
struct error_sin_antecesor
{
};

class Lista
{
public:
  /**
   * Constructor de la lista.
   * 
   * @param _maximo la máxima cantidad de elementos que puede tener la lista.
   */
  Lista(int _maximo) : maximo{_maximo}
  {
    cantidad = 0;
    valores = new int[_maximo];
  }

  /**
   * El destructor de la lista, para liberar la memoria.
   */
  ~Lista()
  {
    // Sólo debe borrar el arreglo que se generó en el constructor.
    delete valores;
  }

  /**
   * Regresa true si no hay elementos en la lista
   */
  bool estaVacia() noexcept
  {
    return cantidad == 0;
  }

  /**
   * Regresa true si la lista está en el máximo de su capacidad.
   */
  bool estaLlena() noexcept
  {
    return cantidad == maximo;
  }

  /**
   * Inserta en el índice dado el valor proporcionado. 
   * Lanza una excepción error_lista_llena si la lista ya está al máximo de su capacidad.
   * 
   * @param indice el indice basado en 0 de donde insertar el valor.
   * @param valor el valor a insertar.
   */
  void insertar(int indice, int valor)
  {
    if (estaLlena() || indice < 0 || indice >= maximo)
    {
      throw error_lista_llena();
    }
    else
    {
      // Recorrer elementos a la derecha
      for (int i = cantidad; i > indice; i--)
      {
        valores[i] = valores[i - 1];
      }
      valores[indice] = valor;
      cantidad += 1;
    }
  }

  /**
   * Elimina el elemento en el índice dado. Lanza una excepción error_lista_vacia
   * si la lista no contiene elementos.
   * 
   * @param indice el índice basado en 0 del elemento a borrar.
   */
  void eliminar(int indice)
  {
    if (estaVacia() || indice < 0 || indice >= maximo)
    {
      throw error_lista_vacia();
    }
    else
    {
      // Recorrer elementos a la izquierda
      for (int i = indice; i < cantidad; i++)
      {
        valores[i] = valores[i + 1];
      }
      cantidad -= 1;
    }
  }

  /**
   * Busca el elemento dado en la lista y obtiene su índice basado en 0.
   * Si no lo encuentra, regresa -1.
   * 
   * @param valor el valor a buscar en la lista.
   */
  int buscar(int valor) noexcept
  {
    for (int i = 0; i < cantidad; i++)
    {
      if (valores[i] == valor)
      {
        return i;
      }
    }
    return -1;
  }

  /**
   * Obtiene el sucesor del primer elemento con el valor dado.
   * Lanza una excepcion error_sin_sucesor si el elemento es el último
   * o si no se encontró en la lista. 
   * 
   * @param valor el valor a buscar en la lista.
   */
  int sucesor(int valor)
  {
    int indice = buscar(valor);
    if (indice == -1 || indice == cantidad - 1)
    {
      throw error_sin_sucesor();
    }
    else
    {
      return valores[indice + 1];
    }
  }

  /**
   * Obtiene el antecesor del primer elemento con el valor dado.
   * Lanza una excepcion error_sin_antecesor si el elemento es el primero
   * o si no se encontró en la lista. 
   * 
   * @param valor el valor a buscar en la lista.
   */
  int predecesor(int valor)
  {
    int indice = buscar(valor);
    if (indice == -1 || indice == 0)
    {
      throw error_sin_antecesor();
    }
    else
    {
      return valores[indice - 1];
    }
  }

  /** 
   * Elimina los duplicados de la lista, de izquierda a derecha.
   */
  void eliminarDuplicados() noexcept
  {
    if (cantidad >= 2)
    {
      int i = 1;

      while (i < cantidad)
      {
        bool eliminado = false;
        int j = 0;

        while (j < i && !eliminado)
        {
          if (valores[j] == valores[i])
          {
            eliminar(i);
            eliminado = true;
          }
          j += 1;
        }

        if (!eliminado)
        {
          i += 1;
        }
      }
    }
  }

  /**
   * Obtiene la longitud de la lista.
   */
  int length()
  {
    return cantidad;
  }

private:
  int maximo;
  int cantidad;
  int *valores;

  // Esta declaración es necesaria para permitir a la siguiente función
  // permitir acceder a los miembros privados de la clase.
  friend std::ostream &operator<<(std::ostream &, const Lista &);
};

// El toString() de la clase.
std::ostream &operator<<(std::ostream &o, const Lista &lista)
{
  o << '[';

  for (int i = 0; i < lista.cantidad; i++)
  {
    o << lista.valores[i];

    if (i + 1 < lista.cantidad)
    {
      o << ", ";
    }
  }

  o << ']';
}