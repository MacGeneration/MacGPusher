//
// MMGTools.hpp
//
// Copyright (c) 2013 @Nyx0uf. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
// conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
// of conditions and the following disclaimer in the documentation and/or other materials
// provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//


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
