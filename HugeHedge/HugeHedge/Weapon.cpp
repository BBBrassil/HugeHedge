//	Weapon.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#include "Weapon.h"

#include "IOManager.h"
#include "ObjectReader.h"
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
	Reads data from a file, storing it in the item's fields.

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
Weapon::Weapon(const std::string& fn) {
	std::unique_ptr<ObjectReader<Weapon>> reader(new ObjectReader<Weapon>(fn));
	attack = 0;
	damage = 0;

	try {
		reader->read(*this);
	}
	catch( ... ) {
		throw;
	}
}
////////////////////////////////////////////////////////////////////////////////
/*	toString()
	Shows the weapon name, description, and stats.
*/
////////////////////////////////////////////////////////////////////////////////
std::string Weapon::toString() const {
	std::stringstream ss;
	ss
		<< name << '\n'
		<< "  " << description << '\n'
		<< "  Attack: " << attack << '\n'
		<< "  Damage: " << damage << '\n';

	return ss.str();
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads data from an input stream, storing it in the item's fields.

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, Weapon& w) {
	std::string line, data;

	try {
		// name
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		w.name = data;

		// description
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		w.description = data;

		// attack
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		w.attack = stoi(data);

		// damage
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		w.damage = stoi(data);
	}
	catch( ... ) {
		throw;
	}
	return ns;
}