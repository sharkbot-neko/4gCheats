#include "Utils/Service.hpp"
#include "Utils/String.hpp"
#include "Function.hpp"

// #include "Utils/String.hpp"
// int count = countTextLen("gsp::Gpu");
// GetServiceHandle(0x01038674, "gsp::Gpu", count, 0);
uint32_t Service::GetServiceHandle(uint32_t *outHandle, const char* serviceName, int serviceNameLen, int param_4) {
    return Function<uint32_t>(0x0010a234)(outHandle, serviceName, serviceNameLen, param_4);
}

uint32_t Service::GetHidServiceHandle() {
    uint32_t outHandle;
    const char* string = "hid:USER";
    
    String string_class;
    int count = string_class.countTextLen(const_cast<char*>(string));

    GetServiceHandle(&outHandle, string, count, 0);

    return outHandle;
}