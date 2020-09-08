
#ifndef CELLSINTERLINKED_SERIALIZATIONUTIL_H
#define CELLSINTERLINKED_SERIALIZATIONUTIL_H

#include <string>
#include <vector>

/**
 * A utility class for serialization of types into a byte buffer.
 */
class SerializationUtil {
public:
    /**
     * Appends the given string to the byte buffer.
     * @param buffer the buffer to append to
     * @param str the string to convert
     */
    static void convert(std::vector<unsigned char> &buffer, const std::string &str);

    /**
     * Appends the given bool to the byte buffer.
     * @param buffer the buffer to append to
     * @param _bool the bool to convert
     */
    static void convert(std::vector<unsigned char> &buffer, bool _bool);

    /**
     * Appends the given short to the byte buffer.
     * @param buffer the buffer to append to
     * @param _short the short to convert
     */
    static void convert(std::vector<unsigned char> &buffer, short _short);

    /**
     * Appends the given integer to the byte buffer.
     * @param buffer the buffer to append to
     * @param _int the integer to convert
     */
    static void convert(std::vector<unsigned char> &buffer, int _int);

    /**
     * Appends the given long long to the byte buffer.
     * @param buffer the buffer to append to
     * @param _longlong the long long to convert
     */
    static void convert(std::vector<unsigned char> &buffer, long long _longlong);

    /**
     * Appends the given float to the byte buffer.
     * @param buffer the buffer to append to
     * @param _float the float to convert
     */
    static void convert(std::vector<unsigned char> &buffer, float _float);

    /**
     * Appends the given double to the byte buffer.
     * @param buffer the buffer to append to
     * @param _double the double to convert
     */
    static void convert(std::vector<unsigned char> &buffer, double _double);

    /**
     * Appends the given type to the byte buffer.
     * @tparam T the type to convert
     * @param buffer the buffer to append to
     * @param t the value to convert
     */
    template<typename T>
    static void convert(std::vector<unsigned char> &buffer, T t);

    /**
     * Appends the given iterable to the byte buffer, serializing each element using the serializer. This is useful in
     * situations such as serializing a collection of instances.
     * @tparam It the iterator type
     * @tparam Serializer the serializer type for the individual elements
     * @param buffer the buffer to append to
     * @param begin a pointer to the beginning of the elements to serialize
     * @param end a pointer to the end of the elements to serialize
     * @param serializer the serializer for which to run individual elements through to convert to a byte array
     */
    template<typename It, typename Serializer>
    static void convert(std::vector<unsigned char> &buffer, It begin, It end, Serializer serializer);
};

#endif //CELLSINTERLINKED_SERIALIZATIONUTIL_H
