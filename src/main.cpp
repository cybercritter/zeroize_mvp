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

    Object obj;
    cout << "Object ID: " << obj.getId() << endl;
    cout << "Object Data: " << obj.getData() << endl;

    if(zeroize((void*)&obj, sizeof(obj))== -1)
    {
        cerr << "Error zeroizing object!" << endl;
        return 1;
    }

    if(!is_zeroized((void*)&obj, sizeof(obj)))
    {
        cerr << "Object is not zeroized!" << endl;
        return 1;
    }

    cout << endl;

    Object *obj1 = new Object();
    cout << "Object ID: " << obj1->getId() << endl;
    cout << "Object Data: " << obj1->getData() << endl;
    
    if (zeroize((void *)obj1, sizeof(Object)) == -1)
    {
        cerr << "Error zeroizing object1!" << endl;
        return 1;
    }

    if (!is_zeroized((void *)obj1, sizeof(Object)))
    {
        cerr << "Object1 is not zeroized!" << endl;
        return 1;
    }

    new (obj1) Object(); // Reinitialize the object
    cout << "Object1 reinitialized." << endl;
    obj1->setId(99887733); // Set new ID
    obj1->setData(11223344); // Set new data
    cout << "Object1 ID after reinitialization: " << obj1->getId() << endl;
    cout << "Object1 Data after reinitialization: " << obj1->getData() << endl;
    delete obj1; // Clean up dynamically allocated memory

    return 0;
}