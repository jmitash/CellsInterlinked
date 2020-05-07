
#include <gtest/gtest.h>
#include <system_error>
#include "application/Module.h"

class IncrementModule : public Module {
public:
    explicit IncrementModule(long long maxIterations)
            : Module("IncrementModule"), mMaxIterations(maxIterations) {}

    long long mIterations = 0;
protected:
    bool executeIteration() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        return ++mIterations >= mMaxIterations;
    }

private:
    const long long mMaxIterations;
};

class ErrorModule : public Module {
public:
    ErrorModule() : Module("ErrorModule") {};
    long long mIterations = 0;
protected:
    bool executeIteration() override {
        mIterations++;
        throw std::runtime_error("Simulated error");
    }
};


TEST(ModuleTest, StartExecutesIteration) {
    auto module = IncrementModule(1);

    // there's a race condition here, but it's extremely unlikely to pop up
    module.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    module.shutdown();

    EXPECT_EQ(module.mIterations, 1);
}

TEST(ModuleTest, ExceptionStopsModule) {
    auto module = ErrorModule();

    module.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    module.shutdown();

    EXPECT_EQ(module.isRunning(), false);
    EXPECT_EQ(module.isErrorState(), true);
    EXPECT_EQ(module.mIterations, 1);
}

TEST(ModuleTest, RestartErroredModule) {
    auto module = ErrorModule();

    module.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    module.shutdown();
    module.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    module.shutdown();
    module.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    module.shutdown();

    EXPECT_EQ(module.isRunning(), false);
    EXPECT_EQ(module.isErrorState(), true);
    EXPECT_EQ(module.mIterations, 3);
}

TEST(ModuleTest, ShutdownStopsModules) {
    auto module = IncrementModule(-1);

    module.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    module.shutdown();

    EXPECT_EQ(module.isRunning(), false);
    EXPECT_EQ(module.isErrorState(), false);
}

TEST(ModuleTest, CantStartRunningModule) {
    auto module = IncrementModule(-1);

    module.start();
    EXPECT_ANY_THROW(module.start());
    module.shutdown();
}

TEST(ModuleTest, ShutdownNotRunning) {
    auto module = IncrementModule(1);

    module.shutdown();
}
