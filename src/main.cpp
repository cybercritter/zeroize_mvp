#include <iostream>
#include <string>

#include <Object.h>
#include <zeroize.h>
using namespace std;

/**
 * @brief Entry point for the Zeroize MVP application.
 *
 * This function creates an Object instance, displays its ID and data,
 * then attempts to securely zeroize the object's memory using the zeroize function.
 * It verifies the zeroization with is_zeroized, and reports errors if either operation fails.
 * Finally, it prints a welcome message upon successful execution.
 *
 * @return int Returns 0 on success, or 1 if zeroization or verification fails.
 */
int main() {

    cout << "Welcome to Zeroize MVP!" << endl;
    cout << "This is a simple C++ application." << endl;

    cout << "It demonstrates the use of zeroization to securely erase sensitive data.\n";
    cout << "It also verifies that the data has been successfully zeroized.\n";
    cout << "###########################################################################################\n\n";


    cout << "----------------------------------------" << endl;
    cout << "Creating an object of class Object...\n";
    Object obj;

    // Display initial state of the object

    cout << "This is the state of the object before zeroization:" << endl;
    cout << "Object created." << endl;
    cout << "Object ID: " << obj.getId() << endl;
    cout << "Object Data: " << obj.getData() << endl;

    cout << "----------------------------------------" << endl;

    cout << "Zeroizing the object...\n";
    if(zeroize((void*)&obj, sizeof(obj)) != 0)    {
        cerr << "Error zeroizing object!" << endl;
        return 1;
    }

    if(!is_zeroized((void*)&obj, sizeof(obj)))
    {
        cerr << "Object is not zeroized!" << endl;
        return 1;
    }
    else if (is_zeroized((void*)&obj, sizeof(obj)))
    {
        cout << "Object is successfully zeroized!" << endl;
    }
    else
    {
        cerr << "Object zeroization verification failed!" << endl;
        return 1;
    }



    // Display state of the object after zeroization
    cout << "This is the state of the object after zeroization:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Object ID after zeroization: " << obj.getId() << endl;
    cout << "Object Data after zeroization: " << obj.getData() << endl;

    cout << "\n\nCreating a new object at the same memory location as the old version" << endl;
    new (&obj) Object(); // Reinitialize the object

    cout << "Object reinitialized." << endl;
    obj.setId(99887733); // Set new ID
    obj.setData(11223344); // Set new data
    cout << "Object ID after reinitialization: " << obj.getId() << endl;
    cout << "Object Data after reinitialization: " << obj.getData() << endl;
    cout << "Zeroization and verification completed successfully!" << endl;
    return 0;
}