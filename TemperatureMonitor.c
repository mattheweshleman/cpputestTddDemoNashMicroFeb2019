/* Copyright (c) <2019> <Matthew Eshleman - https://covemountainsoftware.com>

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

#include "TemperatureMonitor.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ADC.h"

#define MAX_EXCEED_COUNT                        (3U)
#define MAX_ALLOWED_ADC_VALUE_FROM_THERMISTOR   (200U)

static uint8_t s_ExceedCount = 0;

/*
 *    see TemperatureMonitor.h for details
 */
void TemperatureMonitorInit(void)
{
    s_ExceedCount = 0;
}

/*
 *    see TemperatureMonitor.h for details
 */
bool TemperatureMonitorIsOk()
{
    uint8_t value = ADC_GetSample();

    if (value > MAX_ALLOWED_ADC_VALUE_FROM_THERMISTOR)
    {
        s_ExceedCount++;
    }
    else
    {
        s_ExceedCount = 0;
    }

    bool isOk = false;
    if (s_ExceedCount < MAX_EXCEED_COUNT)
    {
        isOk = true;
    }

    return isOk;
}
