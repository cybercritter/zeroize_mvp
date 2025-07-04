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
};

#endif