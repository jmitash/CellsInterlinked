
#include "application/Module.h"


Module::~Module() {
    if (mThreadRunning || mKeepRunning) {
        shutdown();
    }

    // this should cover any race conditions in which the above shutdown() doesn't work out timing wise
    if (mThread.joinable()) {
        mThread.join();
    }
}

void Module::start() {
    std::unique_lock<std::mutex> lock(mThreadControlMutex);

    if (mThreadRunning) {
        throw std::runtime_error(fmt::format("Cannot start module '{}' when it's already running", mName));
    }
    if (mErrorState && mFailCount != mMaxFailCount) {
        logger.warn("Module '{}' start was called while in an error state. Clearing error state and continuing", mName);
        mErrorState = false;
    } else if (mErrorState && mFailCount == mMaxFailCount) {
        throw std::runtime_error(
                fmt::format("Cannot start module '{}'- it's failed too many times ({})", mName, mFailCount));
    }

    logger.info("Starting module '{}'", mName);

    mKeepRunning = true;
    mThread = std::thread(&Module::executionLoop, this);

    while (!mThreadRunning && mKeepRunning && !mErrorState) {
        mThreadStartedVariable.wait(lock);
    }
}

void Module::shutdown() {
    std::unique_lock<std::mutex> lock(mThreadControlMutex);

    if (!mThreadRunning) {
        logger.warn("Attempted to shutdown module '{}' when it wasn't running", mName);
    } else if (!mKeepRunning) {
        logger.warn("Attempted to shutdown module '{}', but it was already in the process of shutting down", mName);
    } else {
        spdlog::info("Shutting down module '{}'", mName);
        mKeepRunning = false;
    }

    lock.unlock();
    if (mThread.joinable()) {
        mThread.join();
    }
}

std::string Module::getName() const {
    return mName;
}

bool Module::isRunning() const {
    return mThreadRunning;
}

bool Module::isErrorState() const {
    return mErrorState;
}

void Module::executionLoop() {
    std::unique_lock<std::mutex> lock(mThreadControlMutex);
    mThreadRunning = true;
    mThreadStartedVariable.notify_all();
    lock.unlock();

    spdlog::debug("'{}' module thread started", mName);

    try {
        doExecutionLoop();
    } catch (...) {
        lock.lock();
        spdlog::error("'{}' module thread threw an error- shutting down", mName);
        mErrorState = true;
        mFailCount++;
        mKeepRunning = false;
        mThreadRunning = false;
        return;
    }

    lock.lock();
    spdlog::info("'{}' module thread shutting down. Iteration count: {}", mName, iterationCount);
    mKeepRunning = false;
    mThreadRunning = false;
}

void Module::doExecutionLoop() {
    while (mKeepRunning) {
        iterationCount++;
        bool stop = executeIteration();

        if (stop) {
            mKeepRunning = false;
            spdlog::debug("Received quit command from execution iteration for '{}' module thread", mName);
        }
    }
}

