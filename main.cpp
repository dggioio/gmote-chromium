#include <cstdio>
#include <cstring>
#include <dlfcn.h>

// Function pointers for engine imports
typedef void (*ConMsg_t)(const char* format, ...);
ConMsg_t pConMsg = nullptr;

// Base interface mapping Source Engine ABI expectations
class IGModWebBrowser {
public:
    virtual ~IGModWebBrowser() {}
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void SetSize(int w, int h) = 0;
    virtual void LoadURL(const char* url) = 0;
    virtual void OnMouseMove(int x, int y) = 0;
    virtual void OnMouseClick(int button, bool down) = 0;
    virtual void Update() = 0;
    
    // Padding for unknown NillerUSR engine calls or extended ABI
    virtual void Padding0() = 0;
    virtual void Padding1() = 0;
    virtual void Padding2() = 0;
    virtual void Padding3() = 0;
};

// Implementation class
class CGModWebBrowser : public IGModWebBrowser {
public:
    CGModWebBrowser() {}
    virtual ~CGModWebBrowser() {}

    void Init() override { 
        if (pConMsg) pConMsg("[GModBrowser] Initialization routine executed.\n"); 
    }
    void Shutdown() override {
        if (pConMsg) pConMsg("[GModBrowser] Shutdown routine executed.\n"); 
    }
    void SetSize(int w, int h) override {}
    void LoadURL(const char* url) override {
        if (pConMsg && url) pConMsg("[GModBrowser] URL requested: %s\n", url);
    }
    void OnMouseMove(int x, int y) override {}
    void OnMouseClick(int button, bool down) override {}
    void Update() override {}
    
    void Padding0() override {}
    void Padding1() override {}
    void Padding2() override {}
    void Padding3() override {}
};

// Interface factory handling multiple version strings
extern "C" __attribute__((visibility("default"))) void* CreateInterface(const char* pName, int* pReturnCode) {
    // Dynamically resolve ConMsg to avoid strict linkage dependencies
    if (!pConMsg) {
        void* engineHandle = dlopen("libengine.so", RTLD_NOLOAD | RTLD_LAZY);
        if (!engineHandle) {
            engineHandle = dlopen("libtier0.so", RTLD_NOLOAD | RTLD_LAZY);
        }
        if (engineHandle) {
            pConMsg = (ConMsg_t)dlsym(engineHandle, "_Z6ConMsgPKcz");
        }
    }

    if (pConMsg) {
        pConMsg("[GModBrowser] CreateInterface called for: %s\n", pName);
    }

    // Match old and new interface version strings
    if (std::strcmp(pName, "IGModWebBrowser001") == 0 || 
        std::strcmp(pName, "IGModWebBrowser002") == 0 ||
        std::strcmp(pName, "IGModWebBrowser") == 0) {
        
        if (pReturnCode) *pReturnCode = 0;
        static CGModWebBrowser s_Browser;
        return (void*)&s_Browser;
    }
    
    if (pReturnCode) *pReturnCode = 1;
    return nullptr;
}
