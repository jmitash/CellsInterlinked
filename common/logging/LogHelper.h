
#ifndef CELLSINTERLINKED_LOGHELPER_H
#define CELLSINTERLINKED_LOGHELPER_H

#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

class LogHelper {
public:
    /**
     * Gets a singleton log helper instance. Creates the instance if not already created.
     * @return the singleton log helper instance
     */
    static LogHelper *get();

    /**
     * Creates a logger for the given file name using the default configuration.
     * @param file the name of the file to log for
     */
    static spdlog::logger logger(const std::string &file);

    /**
     * Creates a logger for the given file name using the default configuration.
     * @param file the name of the file to log for
     */
    spdlog::logger createLogger(const std::string &file);

private:
    /**
     * Creates a log helper with the default sinks.
     */
    LogHelper();

    /**
     * Gets the default logging pattern.
     * @return the default logging pattern
     */
    std::string getDefaultPattern() const;

    /**
     * Gets the default STDOUT log level. This is driven by the environment and build type.
     * @return the default STDOUT log level
     */
    spdlog::level::level_enum getDefaultStdoutLogLevel() const;

    /**
     * Gets the default file log level. This is driven by the environment and build type.
     * @return the default file log level
     */
    spdlog::level::level_enum getDefaultFileLogLevel() const;

    /**
     * Gets a logger friendly name to use from the file name.
     * @param fileName the name of the file that the logger is for
     * @return a logger friendly name
     */
    std::string getLoggerName(const std::string &fileName) const;

    /**
     * Converts any backslashes in a string to forward slashes.
     * @param string the string to convert
     * @return the string with backslashes replaced with forward slashes
     */
    std::string convertToForwardSlash(std::string string) const;

    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks;
};

#endif //CELLSINTERLINKED_LOGHELPER_H
