
#include <gtest/gtest.h>
#include <thread>
#include "message/Broker.h"

class FakeEvent : public Event {
public:
    FakeEvent() : Event("FakeEvent") {};
};

class FakeEvent2 : public Event {
public:
    FakeEvent2() : Event("FakeEvent2") {};
};

class FakeSubscriber : public Subscriber {
public:
    FakeSubscriber() : Subscriber("FakeSubscriber") {};
protected:
    std::shared_ptr<Event> castEvent(const std::shared_ptr<Event> &event) override {
        return std::dynamic_pointer_cast<FakeEvent>(event);
    }
};

class FakeSubscriber2 : public Subscriber {
public:
    FakeSubscriber2() : Subscriber("FakeSubscriber2") {};
protected:
    std::shared_ptr<Event> castEvent(const std::shared_ptr<Event> &event) override {
        return std::dynamic_pointer_cast<FakeEvent2>(event);
    }
};

TEST(BrokerTest, EnrollProducesQueue) {
    Broker broker;

    auto subscriber = std::make_shared<FakeSubscriber>();
    auto queue = broker.enroll(subscriber);

    ASSERT_TRUE(queue != nullptr);
}

TEST(BrokerTest, PublishAndPoll) {
    Broker broker;

    auto subscriber = std::make_shared<FakeSubscriber>();
    auto queue = broker.enroll(subscriber);
    auto publishedEvent = std::make_shared<FakeEvent>();
    broker.publish(publishedEvent);
    auto poppedEvent = queue->popEvent();

    ASSERT_TRUE(poppedEvent != nullptr);
    EXPECT_EQ(publishedEvent.get(), poppedEvent.get());
}

TEST(BrokerTest, PublishToCorrectQueue) {
    Broker broker;

    auto subscriber = std::make_shared<FakeSubscriber>();
    auto queue = broker.enroll(subscriber);
    auto subscriber2 = std::make_shared<FakeSubscriber2>();
    auto queue2 = broker.enroll(subscriber2);

    auto publishedEvent = std::make_shared<FakeEvent2>();
    broker.publish(publishedEvent);

    EXPECT_TRUE(queue->popEvent() == nullptr);
    EXPECT_TRUE(queue2->popEvent() != nullptr);
}

TEST(BrokerTest, BlockingPoll) {
    using namespace std::chrono;

    Broker broker;

    auto subscriber = std::make_shared<FakeSubscriber>();
    auto queue = broker.enroll(subscriber);

    std::thread publishThread([&broker]() {
        std::this_thread::sleep_for(milliseconds(10));
        broker.publish(std::make_shared<FakeEvent>());
    });

    auto event = queue->popEvent(true, milliseconds(3000));
    EXPECT_TRUE(event != nullptr);

    publishThread.join();
}

TEST(BrokerTest, BlockingPollTimeout) {
    using namespace std::chrono;

    Broker broker;

    auto subscriber = std::make_shared<FakeSubscriber>();
    auto queue = broker.enroll(subscriber);

    auto expectedTimeout = milliseconds(10);
    auto startTime = system_clock::now();
    auto event = queue->popEvent(true, expectedTimeout);
    auto endTime = system_clock::now();

    auto runTime = duration_cast<milliseconds>(endTime - startTime);

    EXPECT_TRUE(event == nullptr);
    EXPECT_GE(runTime.count(), expectedTimeout.count());
}

TEST(BrokerTest, PublishWithNoValidSubscriberError) {
    Broker broker;

    auto event = std::make_shared<Event>("Event");
    EXPECT_ANY_THROW(broker.publish(event));
}