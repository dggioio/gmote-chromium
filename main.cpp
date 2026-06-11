#include "interface.h"
#include <cstring>

class IHtmlChromium : public IBaseInterface {
public:
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void Update() = 0;
};

class CHtmlChromium : public IHtmlChromium {
public:
    void Init() override {}
    void Shutdown() override {}
    void Update() override {}
};

extern "C" __attribute__((visibility("default"))) void* CreateInterface(const char* pName, int* pReturnCode) {
    if (std::strcmp(pName, "IGModWebBrowser001") == 0) {
        if (pReturnCode) *pReturnCode = 0;
        return new CHtmlChromium();
    }
    if (pReturnCode) *pReturnCode = 1;
    return nullptr;
}
