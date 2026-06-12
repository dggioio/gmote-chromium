#ifndef INTERFACE_H
#define INTERFACE_H

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

class IBaseInterface {
public:
    virtual ~IBaseInterface() {}
};

#define EXPORT_FUNCTION extern "C" __attribute__((visibility("default")))

#endif // INTERFACE_H
