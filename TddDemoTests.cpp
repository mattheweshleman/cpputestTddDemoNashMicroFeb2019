/*
Copyright (c) <2019> <Matthew Eshleman - https://covemountainsoftware.com>

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <cstdint>

//Header for the Code Under Test
#include "TemperatureMonitor.h"

//various test parameters
static constexpr uint8_t ADC_VALUE_TOO_HOT = 201;
static constexpr uint8_t ADC_VALUE_OK = 200;

TEST_GROUP(TemperatureMonitorTests)
{
    void setup()
    {
        TemperatureMonitorInit();
    }

    void teardown()
    {
        mock().clear();
    }
};

TEST(TemperatureMonitorTests, OnFirstAndSecondReadWithHotAdcValueReturnsOk)
{
    mock().expectOneCall("ADC_GetSample").andReturnValue(ADC_VALUE_TOO_HOT);
    bool ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);
    mock().checkExpectations();

    mock().expectOneCall("ADC_GetSample").andReturnValue(ADC_VALUE_TOO_HOT);
    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);
    mock().checkExpectations();
}

TEST(TemperatureMonitorTests, OnThirdReadWithHotAdcValueReturnsNotOk)
{
    mock().expectNCalls(3, "ADC_GetSample").andReturnValue(ADC_VALUE_TOO_HOT);

    bool ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);

    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);

    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(false, ok);
    mock().checkExpectations();
}

TEST(TemperatureMonitorTests, IfInterimValueIsOkThenThirdCallStillReturnsOk)
{
    mock().expectOneCall("ADC_GetSample").andReturnValue(ADC_VALUE_TOO_HOT);
    bool ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);
    mock().checkExpectations();

    mock().expectOneCall("ADC_GetSample").andReturnValue(ADC_VALUE_OK);
    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);
    mock().checkExpectations();

    mock().expectOneCall("ADC_GetSample").andReturnValue(ADC_VALUE_TOO_HOT);
    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);
    mock().checkExpectations();
}

TEST(TemperatureMonitorTests, IfInterimValueIsOkThenNeedThreeSubsequentHotValuesBeforeReturnsNotOk)
{
    mock().expectOneCall("ADC_GetSample").andReturnValue(ADC_VALUE_TOO_HOT);
    bool ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);
    mock().checkExpectations();

    mock().expectOneCall("ADC_GetSample").andReturnValue(ADC_VALUE_OK);
    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);
    mock().checkExpectations();

    mock().expectNCalls(3, "ADC_GetSample").andReturnValue(ADC_VALUE_TOO_HOT);
    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);

    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(true, ok);

    //third call should now return false
    ok = TemperatureMonitorIsOk();
    CHECK_EQUAL(false, ok);
    mock().checkExpectations();
}
