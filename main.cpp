#include "interface.h"
#include <cstring>

class CGModWebBrowser {
public:
    virtual ~CGModWebBrowser() {}
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void SetSize(int w, int h) = 0;
    virtual void LoadURL(const char* url) = 0;
    virtual void OnMouseMove(int x, int y) = 0;
    virtual void OnMouseClick(int button, bool down) = 0;
    virtual void Update() = 0;
};

class BrowserImpl : public CGModWebBrowser {
public:
    void Init() override {}
    void Shutdown() override {}
    void SetSize(int w, int h) override {}
    void LoadURL(const char* url) override {}
    void OnMouseMove(int x, int y) override {}
    void OnMouseClick(int button, bool down) override {}
    void Update() override {}
};

extern "C" __attribute__((visibility("default"))) void* CreateInterface(const char* pName, int* pReturnCode) {
    if (std::strcmp(pName, "IGModWebBrowser001") == 0) {
        if (pReturnCode) *pReturnCode = 0;
        return new BrowserImpl();
    }
    if (pReturnCode) *pReturnCode = 1;
    return nullptr;
}
