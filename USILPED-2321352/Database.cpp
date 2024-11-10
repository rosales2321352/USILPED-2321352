#include <iostream>
#include <fstream>
#include <string>
#include "Database.h"
#include "File.h"


database::Database::Database()
{
}

database::Database::Database(std::string filename)
{
	this->filename = filename;
}

database::Database::~Database()
{
}

void database::Database::setFileName(std::string filename)
{
	this->filename = filename;
}

bool database::Database::openDatabase(std::fstream& stream) {
    // Intentamos abrir el archivo en modo lectura y escritura binaria
    stream.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::app);

    // Si el archivo no existe (stream no se ha abierto correctamente)
    if (!stream.is_open()) {
        // Creamos el archivo si no existe
        std::ofstream createFile(filename, std::fstream::out | std::fstream::binary);

        if (createFile.is_open()) {
            std::cout << "El archivo se ha creado correctamente." << std::endl;
            createFile.close();  // Cerramos después de crear el archivo
        }
        else {
            std::cerr << "No se pudo crear el archivo." << std::endl;
            return false;
        }

        // Ahora intentamos abrir el archivo nuevamente en modo lectura y escritura binaria
        stream.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary);
    }

    // Devolvemos si se pudo abrir correctamente el archivo
    return stream.is_open();
}

bool database::Database::closeDatabase(std::fstream& stream)
{
	if (stream.is_open())
	{
		stream.close();
		return true;
	}

	return false;
}


