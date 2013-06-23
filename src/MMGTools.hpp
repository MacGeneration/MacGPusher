#ifndef __MMGTOOLS_H__
#define __MMGTOOLS_H__

#include <string>
#include <vector>


class MMGTools
{
public:
	/* Ctors/Dtors */
	MMGTools(void) {}
	~MMGTools(void) {}
	/// Convert a std::string to an integer
	static const int StringToInteger(const std::string&);
	/// Convert a std::string to an unsigned integer
	static const unsigned int StringToUnsignedInteger(const std::string&);
	/// Convert an integer to a std::string
	static const std::string IntegerToString(int);
	/// Convert an unsigned integer to a std::string
	static const std::string UnsignedIntegerToString(unsigned int);
	/// Convert a float to a std::string
	static const std::string FloatToString(const float);
	/// Split a string into a vector
	static void StringToVector(const std::string&, std::vector<std::string>&, const char*);
	/// String replace
	static const bool StringReplace(std::string&, const std::string&, const std::string&);
	/// Base64 decode
	static const std::string Base64Decode(const std::string&);
};

#endif /* __MMGTOOLS_H__ */
