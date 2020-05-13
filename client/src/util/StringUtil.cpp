
#include <iomanip>
#include "util/StringUtil.h"

std::string StringUtil::escape(const std::string &string) {
    std::ostringstream o;
    for (char c : string) {
        if (c == '"' || c == '\\') {
            o << "\\" << c;
        } else if ('\x00' <= c && c <= '\x1f') {
            o << "\\u"
              << std::hex << std::setw(4) << std::setfill('0') << (int) c;
        } else {
            o << c;
        }
    }
    return o.str();
}