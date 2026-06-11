#include "interface.h"
#include <cstring>
#include <cstdio>

// Фиксируем структуру, которую ожидает Source SDK
class IGModWebBrowser001 {
public:
    virtual ~IGModWebBrowser001() {} // 0
    virtual void Init() = 0;         // 1
    virtual void Shutdown() = 0;     // 2
    virtual void SetSize(int w, int h) = 0; // 3
    virtual void LoadURL(const char* url) = 0; // 4
    virtual void OnMouseMove(int x, int y) = 0; // 5
    virtual void OnMouseClick(int button, bool down) = 0; // 6
    virtual void Update() = 0;       // 7
};

class CGModWebBrowser : public IGModWebBrowser001 {
public:
    void Init() override { printf("WebBrowser: Init\n"); }
    void Shutdown() override { printf("WebBrowser: Shutdown\n"); }
    void SetSize(int w, int h) override { printf("WebBrowser: SetSize %d %d\n", w, h); }
    void LoadURL(const char* url) override { printf("WebBrowser: LoadURL %s\n", url); }
    void OnMouseMove(int x, int y) override {}
    void OnMouseClick(int button, bool down) override {}
    void Update() override {}
};

extern "C" __attribute__((visibility("default"))) void* CreateInterface(const char* pName, int* pReturnCode) {
    if (std::strcmp(pName, "IGModWebBrowser001") == 0) {
        if (pReturnCode) *pReturnCode = 0;
        return new CGModWebBrowser();
    }
    if (pReturnCode) *pReturnCode = 1;
    return nullptr;
}
