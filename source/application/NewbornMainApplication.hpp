#pragma once

#include "NewbornApplication.hpp"
#include "NewbornApplicationController.hpp"
#include "NewbornRenderer.hpp"

namespace Newborn {
    int runMainApplication(ApplicationUPtr application, StringList cmdLineArgs);
}

#if defined NEWBORN_SYSTEM_WINDOWS

#include <Windows.h>

#define NEWBORN_MAIN_APPLICATION(ApplicationClass)                                          \
    int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {                               \
        int nArgs;                                                                          \
        LPWSTR* argsList = CommandLineToArgvW(GetCommandLineW(), &nArgs);                   \
        Newborn::StringList args;                                                           \
        for (int i = 0; i < nArgs; ++i) args.append(Newborn::String(argsList[i]));          \
        return Newborn::runMainApplication(Newborn::make_unique<ApplicationClass>(), args); \
    }

#else

#define NEWBORN_MAIN_APPLICATION(ApplicationClass)                                                                  \
    int main(int argc, char** argv) {                                                                               \
        return Newborn::runMainApplication(Newborn::make_unique<ApplicationClass>(), Newborn::StringList(argc, argv)); \
    }

#endif