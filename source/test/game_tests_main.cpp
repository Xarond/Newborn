#include "NewbornLogging.hpp"
#include "NewbornFile.hpp"

#include "gtest/gtest.h"

using namespace Newborn;

struct ErrorLogSink : public LogSink {
    ErrorLogSink() {
        setLevel(LogLevel::Error);
    }

    void log(char const* msg, LogLevel) override {
        ADD_FAILURE() << "Error was logged: " << msg;
    }
};

class TestEnvironment : public testing::Environment {
public:
    TestEnvironment() {}

    virtual void SetUp() {
        Logger::addSink(make_shared<ErrorLogSink>());

    }

    virtual void TearDown() {
    // Perform necessary cleanup tasks here
    }

    private:
    void clearUniverseFiles() {
        // Implement the logic to clear universe files
    }

    void clearPlayerFiles() {
        // Implement the logic to clear player files
    }
  };

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    
    // Add the test environment
    testing::AddGlobalTestEnvironment(new TestEnvironment());
    
    return RUN_ALL_TESTS();
}