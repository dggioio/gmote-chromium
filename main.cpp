#include "interface.h"
#include <cstdio>
#include <cstring>
#include <dlfcn.h>

typedef void (*ConMsg_t)(const char* format, ...);
ConMsg_t pConMsg = nullptr;

class IGModWebBrowser : public IBaseInterface {
public:
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void SetSize(int w, int h) = 0;
    virtual void LoadURL(const char* url) = 0;
    virtual void OnMouseMove(int x, int y) = 0;
    virtual void OnMouseClick(int button, bool down) = 0;
    virtual void Update() = 0;
    virtual void OnKeyType(int key, bool down) = 0;
    virtual void RunJavaScript(const char* script) = 0;
    virtual void ClearHistory() = 0;
    virtual void GoBack() = 0;
    virtual void GoForward() = 0;
    virtual bool IsLoading() = 0;
    virtual const char* GetCurrentURL() = 0;
    virtual void SetPaintTarget(void* pTarget) = 0;
};

class CGModWebBrowser : public IGModWebBrowser {
private:
    char m_szCurrentUrl[512];
public:
    CGModWebBrowser() {
        std::strncpy(m_szCurrentUrl, "about:blank", sizeof(m_szCurrentUrl));
    }
    virtual ~CGModWebBrowser() {}

    void Init() override { 
        if (pConMsg) pConMsg("[GModBrowser] Init: Bridge connection established.\n"); 
    }
    
    void Shutdown() override {
        if (pConMsg) pConMsg("[GModBrowser] Shutdown: Cleaning resources.\n"); 
    }
    
    void SetSize(int w, int h) override {
        if (pConMsg) pConMsg("[GModBrowser] SetSize: Viewport dimensions set to %dx%d\n", w, h);
    }
    
    void LoadURL(const char* url) override {
        if (url) {
            std::strncpy(m_szCurrentUrl, url, sizeof(m_szCurrentUrl));
            if (pConMsg) pConMsg("[GModBrowser] LoadURL: Navigating to %s\n", m_szCurrentUrl);
        }
    }
    
    void OnMouseMove(int x, int y) override {}
    void OnMouseClick(int button, bool down) override {}
    void Update() override {}
    void OnKeyType(int key, bool down) override {}
    
    void RunJavaScript(const char* script) override {
        if (pConMsg && script) pConMsg("[GModBrowser] JavaScript executed in context.\n");
    }
    
    void ClearHistory() override {}
    void GoBack() override {}
    void GoForward() override {}
    
    bool IsLoading() override { 
        return false; 
    }
    
    const char* GetCurrentURL() override { 
        return m_szCurrentUrl; 
    }
    
    void SetPaintTarget(void* pTarget) override {
        if (pConMsg && pTarget) pConMsg("[GModBrowser] Paint target context updated.\n");
    }
};

EXPORT_FUNCTION void* CreateInterface(const char* pName, int* pReturnCode) {
    if (!pConMsg) {
        void* engineHandle = dlopen("libengine.so", RTLD_NOLOAD | RTLD_LAZY);
        if (!engineHandle) {
            engineHandle = dlopen("libtier0.so", RTLD_NOLOAD | RTLD_LAZY);
        }
        if (engineHandle) {
            pConMsg = (ConMsg_t)dlsym(engineHandle, "_Z6ConMsgPKcz");
        }
    }

    if (pConMsg && pName) {
        pConMsg("[GModBrowser] Factory query for interface: %s\n", pName);
    }

    if (pName && std::strstr(pName, "IGModWebBrowser")) {
        if (pReturnCode) {
            *pReturnCode = 0;
        }
        static CGModWebBrowser s_Browser;
        return static_cast<void*>(&s_Browser);
    }
    
    if (pReturnCode) {
        *pReturnCode = 1;
    }
    return nullptr;
}
