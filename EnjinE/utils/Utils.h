#pragma once

#include <string>

#define to_ancii(x) Utils::encoding::to_utf8(x).c_str()
#define to_wide(x) Utils::encoding::to_multibytes(x).c_str()
#define delp(x) Utils::pointers::deleten(x); // Delete pointer and sets NULLPTR

namespace Utils
{
	namespace pointers {
		template<typename T>
		void deleten(T*& ptr) {
			delete ptr;
			ptr = nullptr;
		}
	}
	namespace encoding {
		std::string		to_utf8(const std::wstring& str);
		std::wstring	to_multibytes(const std::string& str);
	}
	namespace hashing {
		std::wstring	sha256(std::wstring text);
		std::string		sha256(std::string text);
	}
	namespace string {
		std::string		replace(std::string s, char c1, char c2);
		std::wstring	replace(std::wstring s, char c1, char c2);
	}
};

