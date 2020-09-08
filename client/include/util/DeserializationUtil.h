
#ifndef CELLSINTERLINKED_DESERIALIZATIONUTIL_H
#define CELLSINTERLINKED_DESERIALIZATIONUTIL_H

#include <string>
#include <queue>

/**
 * A utility class for deserialization of types from a buffer.
 */
class DeserializationUtil {
public:
    /**
     * Deserializes a string from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the string that was next in the buffer
     */
    static std::string _string(std::queue<unsigned char> &buffer);

    /**
     * Deserializes a bool from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the bool that was next in the buffer
     */
    static bool _bool(std::queue<unsigned char> &buffer);

    /**
     * Deserializes a short from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the short that was next in the buffer
     */
    static short _short(std::queue<unsigned char> &buffer);

    /**
     * Deserializes an unsigned short from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the unsigned short that was next in the buffer
     */
    static unsigned short _ushort(std::queue<unsigned char> &buffer);

    /**
     * Deserializes an integer from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the integer that was next in the buffer
     */
    static int _int(std::queue<unsigned char> &buffer);

    /**
     * Deserializes an unsigned integer from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the unsigned integer that was next in the buffer
     */
    static unsigned int _uint(std::queue<unsigned char> &buffer);

    /**
     * Deserializes a long long from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the long long that was next in the buffer
     */
    static long long _longlong(std::queue<unsigned char> &buffer);

    /**
     * Deserializes an unsigned long long from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the unsigned long long that was next in the buffer
     */
    static unsigned long long _ulonglong(std::queue<unsigned char> &buffer);

    /**
     * Deserializes a float from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the float that was next in the buffer
     */
    static float _float(std::queue<unsigned char> &buffer);

    /**
     * Deserializes a double from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the double that was next in the buffer
     */
    static float _double(std::queue<unsigned char> &buffer);

    /**
     * Deserializes a type from a buffer.
     * @param buffer the buffer to deserialize from
     * @return the type that was next in the buffer
     * @tparam T the native type to retrieve from the buffer
     */
    template<typename T>
    static T convert(std::queue<unsigned char> &buffer);

    /**
     * Reads and pops the specified number of bytes from the buffer.
     * @param buffer the buffer to read and pop from
     * @param count the count of bytes to read
     * @param bytes an array of bytes to write to
     */
    static void readBytes(std::queue<unsigned char> &buffer, unsigned short count, unsigned char *bytes);
};

#endif //CELLSINTERLINKED_DESERIALIZATIONUTIL_H
