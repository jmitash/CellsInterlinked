
#include <gtest/gtest.h>
#include "monitor/MonitorStateManager.h"
#include "monitor/MonitorStateChangeEvent.h"

class FakeMonitorStateChangeSubscriber : public Subscriber {
public:
    FakeMonitorStateChangeSubscriber() : Subscriber("FakeMonitorStateChangeSubscriber") {}

protected:
    std::shared_ptr<Event> castEvent(const std::shared_ptr<Event> &event) override {
        return std::dynamic_pointer_cast<MonitorStateChangeEvent>(event);
    }
};

TEST(MonitorStateManagerTest, DifferentState) {
    Broker broker;
    auto subscriber = std::make_shared<FakeMonitorStateChangeSubscriber>();
    auto queue = broker.enroll(subscriber);

    MonitorStateManager monitorStateManager(&broker);

    Monitor originalMonitor;
    originalMonitor.setName("original");

    // set the "beginning" state
    monitorStateManager.handleStateChange({originalMonitor});

    Monitor newMonitor;
    newMonitor.setName("new");

    EXPECT_TRUE(monitorStateManager.isDifferentState({newMonitor}));
}

TEST(MonitorStateManagerTest, SameState) {
    Broker broker;
    auto subscriber = std::make_shared<FakeMonitorStateChangeSubscriber>();
    auto queue = broker.enroll(subscriber);

    MonitorStateManager monitorStateManager(&broker);

    Monitor originalMonitor;
    originalMonitor.setName("original");

    // set the "beginning" state
    monitorStateManager.handleStateChange({originalMonitor});

    EXPECT_FALSE(monitorStateManager.isDifferentState({originalMonitor}));
}

TEST(MonitorStateManagerTest, HandleStateChange) {
    Broker broker;
    auto subscriber = std::make_shared<FakeMonitorStateChangeSubscriber>();
    auto queue = broker.enroll(subscriber);

    MonitorStateManager monitorStateManager(&broker);

    Monitor originalMonitor;
    originalMonitor.setName("original");

    // set the "beginning" state
    monitorStateManager.handleStateChange({originalMonitor});

    // discard the first event
    ASSERT_TRUE(queue->popEvent() != nullptr);

    Monitor newMonitor;
    newMonitor.setName("new");
    monitorStateManager.handleStateChange({newMonitor});

    auto event = queue->popEvent();
    ASSERT_TRUE(event != nullptr);

    auto changeEvent = std::dynamic_pointer_cast<MonitorStateChangeEvent>(event);
    ASSERT_TRUE(changeEvent != nullptr);

    auto monitors = changeEvent->getNewMonitors();

    ASSERT_EQ(monitors.size(), 1);
    EXPECT_EQ(monitors.begin()->getName(), "new");
}