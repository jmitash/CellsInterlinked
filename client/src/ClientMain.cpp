
#include "logging/LogHelper.h"
//#include "meta/BuildInfo.h"
#include "monitor/MonitorDiscovererFactory.h"

#include <memory>
#include "message/TestEvent.h"
#include "message/TestSubscriber.h"
#include "message/SubscriberQueue.h"
#include "message/Broker.h"

int main() {
    spdlog::logger logger = LogHelper::logger(__FILE__);
//    logger.info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion, BuildInfo::buildType);

    MonitorDiscovererFactory factory;
    auto monitorDiscoverer = factory.getMonitorDiscoverer();

    monitorDiscoverer->discoverAll();

    auto event = std::make_shared<TestEvent>();
    std::shared_ptr<Subscriber<Event>> testSubscriber = std::reinterpret_pointer_cast<Subscriber<Event>>(
            std::make_shared<TestSubscriber>());

    Broker *broker = Broker::get();
    auto pollableQueue = broker->enroll(testSubscriber);
    broker->publish(event);
    auto receivedEvent = pollableQueue->popEvent(false);

    Broker *broker1 = Broker::get();

    return 0;
}
