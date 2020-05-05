
#include <regex>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "logging/LogHelper.h"
#include "meta/BuildInfo.h"

LogHelper::LogHelper() {
    auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    stdoutSink->set_level(getDefaultStdoutLogLevel());
    mSinks.push_back(stdoutSink);

    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/log.txt", 1048576 * 5, 3);
    fileSink->set_level(getDefaultFileLogLevel());
    mSinks.push_back(fileSink);

    for (const auto &sink : mSinks) {
        sink->set_pattern(getDefaultPattern());
    }
}

std::shared_ptr<LogHelper> LogHelper::get() {
    std::unique_lock<std::mutex> lock(mutex);

    if (instance == nullptr) {
        instance = std::shared_ptr<LogHelper>(new LogHelper());
    }

    return instance;
}

spdlog::logger LogHelper::logger(const std::string &file) {
    return get()->createLogger(file);
}

spdlog::logger LogHelper::createLogger(const std::string &file) {
    auto loggerName = getLoggerName(file);
    auto logger = spdlog::logger(loggerName, mSinks.begin(), mSinks.end());

    std::vector<spdlog::level::level_enum> loggerLevels;
    loggerLevels.push_back(getDefaultStdoutLogLevel());
    loggerLevels.push_back(getDefaultFileLogLevel());

    spdlog::level::level_enum lowestLevel = *std::min_element(loggerLevels.begin(), loggerLevels.end());
    logger.set_level(lowestLevel);

    return logger;
}

std::string LogHelper::getDefaultPattern() const {
    return "[%Y-%m-%d %T.%e][%^%l%$][%t][%n] %v";
}

spdlog::level::level_enum LogHelper::getDefaultStdoutLogLevel() const {
    if (BuildInfo::isDebug()) {
        return spdlog::level::debug;
    }

    return spdlog::level::info;
}

spdlog::level::level_enum LogHelper::getDefaultFileLogLevel() const {
    return spdlog::level::trace;
}

std::string LogHelper::getLoggerName(const std::string &fileName) const {
    auto forwardSlashFileName = convertToForwardSlash(fileName);
    auto forwardSlashBaseDirectory = std::string("");//convertToForwardSlash(BuildInfo::baseDirectory);
    if (forwardSlashBaseDirectory.find_last_of('/') < forwardSlashBaseDirectory.size() - 1) {
        forwardSlashBaseDirectory += '/';
    }
    auto relativeFileName = std::regex_replace(forwardSlashFileName, std::regex(forwardSlashBaseDirectory), "");
    std::string relativeFileNameNoExt = std::regex_replace(relativeFileName, std::regex("(.cpp|.h)"), "");

    auto lastSlashIdx = relativeFileNameNoExt.find_last_of('/');
    if (lastSlashIdx == -1) {
        return relativeFileNameNoExt;
    }

    return relativeFileNameNoExt.substr(lastSlashIdx + 1);
}

std::string LogHelper::convertToForwardSlash(std::string string) const {
    std::replace(string.begin(), string.end(), '\\', '/');
    return string;
}
