
#ifndef CELLSINTERLINKED_STRINGUTIL_H
#define CELLSINTERLINKED_STRINGUTIL_H

#include <string>
#include <sstream>
#include <iomanip>

/**
 * Utility methods for strings.
 */
class StringUtil {
public:
    /**
     * Joins the provided iterable with the passed in separator and converter. For example, this might join an array of
     * @code
     * {1,2,3}
     * @endcode
     * into "1, 2, 3".
     *
     * @tparam It an iterable type
     * @tparam Converter a string converter for the elements of the iterable
     * @param begin the start of the iterable
     * @param end the end of the iterable
     * @param delim the separator to join adjacent elements with
     * @param converter the converter to use for converting the elements to string
     * @return a string of the joined elements
     */
    template<typename It, typename Converter>
    static std::string join(
            It begin,
            It end,
            const std::string &delim = ", ",
            Converter converter = [](const std::string &string) { return string; }) {
        std::ostringstream ss;

        if (begin != end) {
            ss << converter(*begin++);
        }

        while (begin != end) {
            ss << delim;
            ss << converter(*begin++);
        }

        return ss.str();
    }

    /**
     * Performs a JSON escape on the given string
     * @param string the string to escape
     * @return the escaped string
     */
    static std::string escape(const std::string &string) {
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
};

#endif //CELLSINTERLINKED_STRINGUTIL_H
