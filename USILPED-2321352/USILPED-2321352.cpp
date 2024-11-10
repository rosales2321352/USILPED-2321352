// USILPED-2321352.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Colors.h"
#include "HashTable.h"
#include "Structure.h"
#include "UserRepository.h"
#include "BookingRepository.h"
#include "BookRepository.h"


user_repository::UserRepository userRepository = user_repository::UserRepository("users002.dat");
book_repository::BookRepository bookRepository = book_repository::BookRepository("books002.dat");
booking_repository::BookingRepository bookingRepository = booking_repository::BookingRepository("reservations002.dat");

void initData()
{
    structure::User user1(1, "Juam3", "juan@email.com", "982822646", "Av.example", true);
    structure::User user2(2, "Juam4", "jua2n@email.com", "982822646", "Av.example", false);

    userRepository.saveUser(user1);
    userRepository.saveUser(user2);

    structure::Book book1(1, "Larabel: Curso Practico Avanzado", "Lopes QuijadoJose", "Programacion", 2021, true);
    structure::Book book2(2, "Aprende a Programar", "Hammer Joshua", "Programacion", 2017, false);

    bookRepository.saveBook(book1);
    bookRepository.saveBook(book2);

    structure::Booking booking1(1, 1, 1, "2024-11-10", "2024-11-20", false);
    structure::Booking booking2(2, 2, 1, "2024-11-21", "2024-11-22", false);
    structure::Booking booking3(3, 1, 1, "2024-11-25", "2024-11-30", false);
    structure::Booking booking4(4, 2, 1, "2024-12-01", "2024-12-10", false);
    structure::Booking booking5(5, 1, 1, "2024-12-11", "2024-12-31", false);

    bookingRepository.saveBooking(booking1);
    bookingRepository.saveBooking(booking2);
    bookingRepository.saveBooking(booking3);
    bookingRepository.saveBooking(booking4);
    bookingRepository.saveBooking(booking5);
       
}

int main()
{
    cout << YELLOW << "Inicializar Datos" << RESET << endl;
    //initData();

    

    /*if (auto userOpt = userRepository.getUser(2))
    {
        User user = *userOpt;
        User original = user;
        user.name = "Juan7";
        userRepository.updateUser(original,user);
    }
    else {
        std::cout << "Usuario no encontrado." << std::endl;
    }


    userRepository.print();*/
    
    return 0;
}


