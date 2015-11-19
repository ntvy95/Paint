/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*COLLECTION: Exception.
*DESCRIPTION: We stores our exceptions in this. Weak encapsulation, weak OOP
=> Weak exceptions. Do not be surprised.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include <exception>
using std::exception;
class InvalidArgument : public exception {

};