//
// MMGTools.hpp
//
// Copyright (c) 2013 MacGeneration. All rights reserved.
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
	/**
	 * @brief Convert a std::string to an integer
	 * @param str [in] : String to convert
	 * @returns the string as an integer
	 */
	static int StringToInteger(const std::string& str);

	/**
	 * @brief Convert a std::string to an unsigned integer
	 * @param str [in] : String to convert
	 * @returns the string as an unsigned integer
	 */
	static unsigned int StringToUnsignedInteger(const std::string& str);

	/**
	 * @brief Convert an integer to a std::string, Taken from : http://opensource.apple.com/source/groff/groff-10/groff/libgroff/itoa.c
	 * @param i [in] : Integer to convert
	 * @returns The integer as a std::string
	 */
	static const std::string IntegerToString(int i);

	/**
	 * @brief Convert an unsigned integer to a std::string, Taken from : http://opensource.apple.com/source/groff/groff-10/groff/libgroff/itoa.c
	 * @param i [in] : Unsigned integer to convert
	 * @returns The unsigned integer as a std::string
	 */
	static const std::string UnsignedIntegerToString(unsigned int i);

	/**
	 * @brief Convert a float to a std::string
	 * @param f [in] : Float to convert
	 * @returns The float as a std::string
	 */
	static const std::string FloatToString(const float f);

	/**
	 * @brief Split a std::string into a std::vector<std::string>
	 * @param str [in] : String to split
	 * @param vec [out] : Vector where to split the string
	 * @param sep [in] : String separator
	 */
	static void StringToVector(const std::string& str, std::vector<std::string>& vec, const char* sep);

	/**
	 * @brief Replace a part of a std::string with another
	 * @param str [out] : String
	 * @param from [in] : String to search
	 * @param to [in] : String to replace
	 * @returns true if success, false otherwise
	 */
	static bool StringReplace(std::string& str, const std::string& from, const std::string& to);

	/**
	 * @brief Replace all occurences of a std::string with another
	 * @param str [out] : String
	 * @param search [in] : String to search
	 * @param replace [in] : String to replace
	 */
	static void StringReplaceAll(std::string& str, const std::string& search, const std::string& replace);

	/**
	 * @brief Decode a base64 encoded std::string
	 * @param encoded_string [in] : Base64 encoded string
	 * @returns decoded std::string
	 */
	static const std::string Base64Decode(const std::string& encoded_string);
};

#endif /* __MMGTOOLS_H__ */
