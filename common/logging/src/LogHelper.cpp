
#include <regex>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>


#include "meta/BuildInfo.h"
#include "../LogHelper.h"

LogHelper::LogHelper() {
    auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    sinks.push_back(stdoutSink);

    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/log.txt", 1048576 * 5, 3);
    sinks.push_back(fileSink);

    for (const auto &sink : sinks) {
        sink->set_level(getDefaultLogLevel());
        sink->set_pattern(getDefaultPattern());
    }
}

spdlog::logger LogHelper::logger(const std::string &file) {
    return get().createLogger(file);
}

LogHelper &LogHelper::get() {
    static LogHelper instance;
    return instance;
}

spdlog::logger LogHelper::createLogger(const std::string &file) {
    std::string loggerName = getLoggerName(file);

    return spdlog::logger(loggerName, sinks.begin(), sinks.end());
}

std::string LogHelper::getDefaultPattern() const {
    return "[%Y-%m-%d %T.%e][%^%l%$][%t][%n] %v";
}

spdlog::level::level_enum LogHelper::getDefaultLogLevel() const {
    if (BuildInfo::isDebug()) {
        return spdlog::level::debug;
    }

    return spdlog::level::info;
}

std::string LogHelper::getLoggerName(const std::string &fileName) const {
    auto forwardSlashFileName = convertToForwardSlash(fileName);
    auto forwardSlashBaseDirectory = convertToForwardSlash(BuildInfo::baseDirectory);
    if (forwardSlashBaseDirectory.find_last_of('/') < forwardSlashBaseDirectory.size() - 1) {
        forwardSlashBaseDirectory += '/';
    }
    auto relativeFileName = std::regex_replace(forwardSlashFileName, std::regex(forwardSlashBaseDirectory), "");
    return std::regex_replace(relativeFileName, std::regex("(.cpp|.h)"), "");
}

std::string LogHelper::convertToForwardSlash(std::string string) const {
    std::replace(string.begin(), string.end(), '\\', '/');
    return string;
}
