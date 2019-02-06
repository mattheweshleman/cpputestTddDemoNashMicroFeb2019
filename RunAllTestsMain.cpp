#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"



int main(int ac, char** av)
{
    MockSupportPlugin mockPlugin;
    
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);
    
    return RUN_ALL_TESTS(ac, av);
}

