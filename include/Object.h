/**
 * @class Object
 * @brief Represents a basic object with an identifier and associated data.
 *
 * The Object class provides a simple interface for storing and retrieving
 * an integer ID and associated data. It includes a default constructor
 * that initializes these values and provides getter methods for access.
 */
#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
  Object() : id(1234534), data(123098) {}
  virtual ~Object() {};
  int getId() const;
  int getData() const;
  void setId(int newId) { id = newId; }
  void setData(int newData) { data = newData; }

private:
  int id;
  int data;
  char padding[4]; // Padding to ensure alignment
  // This padding is not strictly necessary but can help with alignment
  // and may be useful in some contexts, especially if the class is extended.
  // It ensures that the size of the class is a multiple of the alignment requirement.
  // This is a common practice in C++ to ensure that objects of this class
  // are properly aligned in memory, which can be important for performance
  // and compatibility with certain hardware architectures.
  // The padding size can be adjusted based on the alignment requirements of the platform.
  // Note: The padding is not used in any operations and is purely for alignment purposes.
};

#endif