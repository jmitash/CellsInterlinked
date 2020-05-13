
#ifndef CELLSINTERLINKED_STRINGUTIL_H
#define CELLSINTERLINKED_STRINGUTIL_H

#include <string>
#include <sstream>

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
     * @tparam Cnvrt a string converter for the elements of the iterable
     * @param begin the start of the iterable
     * @param end the end of the iterable
     * @param converter the converter to use for converting the elements to string
     * @param delim the separator to join adjacent elements with
     * @return a string of the joined elements
     */
    template<typename It, typename Cnvrt>
    static std::string join(
            It begin,
            It end,
            Cnvrt converter = [](const std::string &string) { return string; },
            const std::string &delim = ", ") {
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
     * Converts the given collection into a string form (surrounded by square brackets, comma-space separated).
     * @tparam Collection the type of the collection to convert (must be iterable)
     * @tparam Cnvrt the conversion function to use for converting the individual elements to a string
     * @param collection the collection to convert
     * @param converter the converter to use to convert the elements
     * @return the string form of the collection
     */
    template<typename Collection, typename Cnvrt>
    static std::string toString(
            Collection collection,
            Cnvrt converter = [](const std::string &string) { return string; }) {
        std::ostringstream ss;

        ss << "[" << join(collection.begin(), collection.end(), converter) << "]";
        return ss.str();
    }

    /**
     * Performs a JSON escape on the given string
     * @param string the string to escape
     * @return the escaped string
     */
    static std::string escape(const std::string &string);
};

#endif //CELLSINTERLINKED_STRINGUTIL_H
