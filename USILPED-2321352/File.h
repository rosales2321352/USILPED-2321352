#pragma once

#include<iostream>
#include<fstream>

namespace file {
    template<typename T>
    void write(const T& value, std::fstream& stream);
    template<typename T>
    void read(T& value, std::fstream& stream);

    template<typename T>
    void write(const T& value, std::fstream& stream)
    {
        // Handling integers and floating-point numbers
        if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value)
        {
            // Cast integer, float or double to const char pointer.
            stream.write(reinterpret_cast<const char*>(&value), sizeof value);
        }
        // Handling char arrays (C-style strings)
        else if constexpr (std::is_same<T, const char*>::value || std::is_same<T, char*>::value)
        {
            size_t length = 0;
            const char* ptr = value;
            mbstate_t state = mbstate_t(); // Initialize multibyte state
            while (*ptr != '\0')
            {
                size_t char_size = mbrlen(ptr, MB_CUR_MAX, &state);
                if (char_size == static_cast<size_t>(-1))
                {
                    std::cerr << "Error in multibyte character sequence." << std::endl;
                    return;
                }
                length += char_size;
                ptr += char_size;
            }
            stream.write(reinterpret_cast<const char*>(&length), sizeof length); // Write the length
            stream.write(value, length);                                          // Write the string data
        }
        // Handling std::string
        else if constexpr (std::is_same<T, std::string>::value)
        {
            size_t length = value.size();
            stream.write(reinterpret_cast<const char*>(&length), sizeof length); // Write the length first
            stream.write(value.c_str(), length);                                  // Write the string data
        }
        else
        {
            stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
    }

    template<typename T>
    void read(T& value, std::fstream& stream)
    {
        // Handling integers and floating-point numbers
        if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value)
        {
            // Leer directamente el valor del archivo y asignarlo a 'value'
            stream.read(reinterpret_cast<char*>(&value), sizeof value);
        }
        // Handling char arrays (C-style strings)
        else if constexpr (std::is_same<T, const char*>::value || std::is_same<T, char*>::value)
        {
            size_t length = 0;
            stream.read(reinterpret_cast<char*>(&length), sizeof length); // Leer la longitud primero

            char* buffer = new char[length + 1];  // Reservar espacio para la cadena
            stream.read(buffer, length);          // Leer la cadena de datos
            buffer[length] = '\0';                // Terminar con un carácter nulo

            value = buffer;                       // Asignar el buffer a 'value'
            delete[] buffer;                      // Liberar el buffer después de la asignación
        }
        // Handling std::string
        else if constexpr (std::is_same<T, std::string>::value)
        {
            size_t length = 0;
            stream.read(reinterpret_cast<char*>(&length), sizeof length); // Leer la longitud primero

            char* buffer = new char[length + 1];  // Reservar espacio para la cadena
            stream.read(buffer, length);          // Leer la cadena de datos
            buffer[length] = '\0';                // Terminar con un carácter nulo

            value.assign(buffer, length);         // Asignar la cadena a 'value'
            delete[] buffer;                      // Liberar el buffer después de la asignación
        }
        else
        {
            stream.read(reinterpret_cast<char*>(&value), sizeof (value));
        }
    }
}
