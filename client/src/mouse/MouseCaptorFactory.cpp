
#include "mouse/MouseCaptorFactory.h"
#include "meta/BuildInfo.h"
#include "mouse/WindowsMouseCaptor.h"

std::unique_ptr<MouseCaptor> MouseCaptorFactory::getMouseCaptor() {
    BuildInfo::assertSupportedPlatform();

    if constexpr (BuildInfo::isWindows()) {
        return std::make_unique<WindowsMouseCaptor>();
    } else {
        return std::unique_ptr<MouseCaptor>(nullptr);
    }
}
