#pragma once
#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <string>
#include <vector>
#include <iostream>

class Service {
public:
    uint32_t GetServiceHandle(uint32_t *outHandle, const char* serviceName, int serviceNameLen, int param_4);
    uint32_t GetHidServiceHandle();
};

#endif