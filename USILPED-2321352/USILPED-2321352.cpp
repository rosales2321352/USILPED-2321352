// USILPED-2321352.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HashTable.h"
#include "Structure.h"
#include "UserRepository.h"


int main()
{

    user_repository::UserRepository userRepository = user_repository::UserRepository("users001.dat");
    

    /*structure::User user1(1, "Juam3", "juan@email.com", "982822646", "Av.example", false);
    structure::User user2(2, "Juam4", "jua2n@email.com", "982822646", "Av.example", false);

    userRepository.saveUser(user1);
    userRepository.saveUser(user2);
    */
    
    userRepository.print();

    if (auto userOpt = userRepository.getUser(2))
    {
        User user = *userOpt;
        User original = user;
        user.name = "Juan7";
        userRepository.updateUser(original,user);
    }
    else {
        std::cout << "Usuario no encontrado." << std::endl;
    }


    userRepository.print();
    


    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
