
#ifndef CELLSINTERLINKED_MODULE_H
#define CELLSINTERLINKED_MODULE_H

#include <string>
#include <thread>
#include <mutex>
#include <utility>
#include <condition_variable>
#include "logging/LogHelper.h"

/**
 * Some module of the application. Encapsulates a thread which allows the module to run asynchronously.
 */
class Module {
public:
    /**
     * Creates the module with the given name. The name is mainly used for debug purposes.
     * @param name the name of the module
     */
    explicit Module(std::string name) : mName(std::move(name)) {}

    /**
     * Destructs the module by shutting down and/or joining the thread if able.
     */
    ~Module();

    /**
     * Starts the module by initializing data starting the module's thread. Calling this while it's already running will
     * throw an exception. Blocks until the module's thread has started.
     */
    void start();

    /**
     * Shuts down the module and the backing thread, if running. Blocks until the thread shuts down.
     */
    void shutdown();

    /**
     * Gets the name of this module.
     * @return the name of this module
     */
    [[nodiscard]] std::string getName() const;

    /**
     * Tells if this module is running (determined by the backing thread). Note that this may not be accurate due to concurrent data access.
     * @return whether this module is running or not
     */
    [[nodiscard]] bool isRunning() const;

    /**
     * Tells if this module is currently in an error state. Being in an error state indicates the module's thread encountered an unexpected error and quit early. Restarting the module (when allowed) will clear the error state.
     * @return true if this module is an error state, false otherwise
     */
    [[nodiscard]] bool isErrorState() const;

protected:
    /**
     * Contains the logic of this module to execute on an iterative basis. This is essentially the code the thread runs in a loop while the module is running.
     * @return true to stop execution and shut down the thread, false to continue executing
     */
    [[nodiscard]] virtual bool executeIteration() = 0;

    /**
     * Optionally yield at the end of an iteration. This is where something like a sleep, wait or yield would occur to not have the thread running 100% of the time. Overriders should be mindful of the latency the module requires and the CPU usage tradeoff.
     */
    virtual void yieldIteration();

private:
    /**
     * Executes ::doExecutionLoop() but captures any thrown exceptions to be able to track the thread failure.
     */
    void executionLoop();

    /**
     * Executes ::executeIteration() in a loop, stopping when the method indicates that execution should stop, or the module is shutdown.
     */
    void doExecutionLoop();

    /**
     * Attempts to resolve the message from a given exception pointer.
     * @param exceptionPtr a pointer to the exception to resolve the message of
     * @return the message of the exception, or empty string if not resolvable
     */
    [[nodiscard]] std::string resolveExceptionMessage(const std::exception_ptr &exceptionPtr);

    const std::string mName;
    std::thread mThread;
    bool mThreadRunning = false;
    bool mKeepRunning = false;
    bool mErrorState = false;
    int mFailCount = 0;
    int mMaxFailCount = -1;
    unsigned long long iterationCount = 0;
    std::mutex mThreadControlMutex;
    std::condition_variable mThreadStartedVariable;

    inline static spdlog::logger logger = LogHelper::logger(__FILE__);
};

#endif //CELLSINTERLINKED_MODULE_H
