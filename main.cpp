#include "interface.h"
#include <cstring>
#include <cstdio>

// В движках NillerUSR интерфейсы часто наследуются от IBaseInterface,
// который в бинарном виде для Android имеет жесткое выравнивание.
class IGModWebBrowser001 {
public:
    virtual ~IGModWebBrowser001() {}                     // 0
    virtual void Init() = 0;                             // 1
    virtual void Shutdown() = 0;                         // 2
    virtual void SetSize(int w, int h) = 0;              // 3
    virtual void LoadURL(const char* url) = 0;           // 4
    virtual void OnMouseMove(int x, int y) = 0;          // 5
    virtual void OnMouseClick(int button, bool down) = 0;// 6
    virtual void Update() = 0;                           // 7
    // Добавляем специфичные для NillerUSR заглушки (padding)
    virtual void Unknown8() {} virtual void Unknown9() {}
    virtual void Unknown10() {} virtual void Unknown11() {}
};

class CGModWebBrowser : public IGModWebBrowser001 {
public:
    void Init() override { printf("[GModBrowser] Init called\n"); }
    void Shutdown() override { printf("[GModBrowser] Shutdown called\n"); }
    void SetSize(int w, int h) override { printf("[GModBrowser] SetSize %dx%d\n", w, h); }
    void LoadURL(const char* url) override { printf("[GModBrowser] LoadURL %s\n", url); }
    void OnMouseMove(int x, int y) override {}
    void OnMouseClick(int button, bool down) override {}
    void Update() override {}
};

// Фабрика интерфейсов
extern "C" __attribute__((visibility("default"))) void* CreateInterface(const char* pName, int* pReturnCode) {
    if (std::strcmp(pName, "IGModWebBrowser001") == 0) {
        if (pReturnCode) *pReturnCode = 0;
        static CGModWebBrowser s_Browser;
        return &s_Browser;
    }
    return nullptr;
}
