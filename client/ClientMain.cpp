
#include "../common/logging/LogHelper.h"
#include "meta/BuildInfo.h"
#include "monitor/device/MonitorDiscovererFactory.h"

#include <memory>
#include "message/TestEvent.h"
#include "message/TestSubscriber.h"
#include "message/SubscriberQueue.h"
#include "message/Broker.h"

int main() {
    spdlog::logger logger = LogHelper::logger(__FILE__);
    logger.info("Starting {} {} ({})", BuildInfo::projectName, BuildInfo::projectVersion, BuildInfo::buildType);

    MonitorDiscovererFactory factory;
    auto monitorDiscoverer = factory.getMonitorDiscoverer();

    monitorDiscoverer->discoverAll();

    auto event = std::make_shared<TestEvent>("", "");
    std::shared_ptr<Subscriber<Event>> testSubscriber = std::reinterpret_pointer_cast<Subscriber<Event>>(
            std::make_shared<TestSubscriber>());

    Broker broker = Broker::get();
    broker.subscribe(testSubscriber);
    broker.publish(event);

    return 0;
}
