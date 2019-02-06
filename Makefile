# Copyright (c) <2019> <Matthew Eshleman - https://covemountainsoftware.com>
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the Software
# is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CPPUTEST_OBJS_DIR = objs/
CPPUTEST_USE_EXTENSIONS = Y

ifndef CPPUTEST_HOME
    CPPUTEST_HOME = ~/opt/cpputest-3.8
endif

COMPONENT_NAME = TddDemo

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

INCLUDE_DIRS += $(CPPUTEST_HOME)/include

SRC_FILES = TemperatureMonitor.c

# supporting source code (mocks, test runner, etc)
TEST_SRC_FILES += \
  TddDemoTests.cpp \
  RunAllTestsMain.cpp \
  MockADC.cpp

include DefaultCompilerFlags.mk
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
