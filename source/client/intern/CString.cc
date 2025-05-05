#include "CString.h"

#include <string>

const char *StdString_CStr(const void *StdString) {
	return reinterpret_cast<const std::string *>(StdString)->c_str();
}
