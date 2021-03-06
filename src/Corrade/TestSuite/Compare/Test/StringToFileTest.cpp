/*
    This file is part of Corrade.

    Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <sstream>

#include "Corrade/TestSuite/Tester.h"
#include "Corrade/TestSuite/Compare/StringToFile.h"
#include "Corrade/Utility/Directory.h"

#include "configure.h"

using Corrade::Utility::Directory;

namespace Corrade { namespace TestSuite { namespace Compare { namespace Test {

class StringToFileTest: public Tester {
    public:
        StringToFileTest();

        void same();
        void empty();

        void notFound();

        void outputActualSmaller();
        void outputExpectedSmaller();
        void output();
};

StringToFileTest::StringToFileTest() {
    addTests({&StringToFileTest::same,
              &StringToFileTest::empty,
              &StringToFileTest::notFound,
              &StringToFileTest::outputActualSmaller,
              &StringToFileTest::outputExpectedSmaller,
              &StringToFileTest::output});
}

void StringToFileTest::same() {
    CORRADE_VERIFY(Comparator<Compare::StringToFile>()("Hello World!", Directory::join(FILETEST_DIR, "base.txt")));
}

void StringToFileTest::empty() {
    CORRADE_VERIFY(Comparator<Compare::StringToFile>()("", Directory::join(FILETEST_DIR, "empty.txt")));
}

void StringToFileTest::notFound() {
    std::stringstream out;

    {
        Error e(&out);
        Comparator<Compare::StringToFile> compare;
        CORRADE_VERIFY(!compare("Hello World!", "nonexistent.txt"));
        compare.printErrorMessage(e, "a", "file");
    }

    CORRADE_COMPARE(out.str(), "File file (nonexistent.txt) cannot be read.\n");
}

void StringToFileTest::outputActualSmaller() {
    std::stringstream out;

    {
        Error e(&out);
        Comparator<Compare::StringToFile> compare;
        CORRADE_VERIFY(!compare("Hello W", Directory::join(FILETEST_DIR, "base.txt")));
        compare.printErrorMessage(e, "a", "b");
    }

    CORRADE_COMPARE(out.str(), "Files a and b have different size, actual 7 but 12 expected. Expected has character o on position 7.\n");
}

void StringToFileTest::outputExpectedSmaller() {
    std::stringstream out;

    {
        Error e(&out);
        Comparator<Compare::StringToFile> compare;
        CORRADE_VERIFY(!compare("Hello World!", Directory::join(FILETEST_DIR, "smaller.txt")));
        compare.printErrorMessage(e, "a", "b");
    }

    CORRADE_COMPARE(out.str(), "Files a and b have different size, actual 12 but 7 expected. Actual has character o on position 7.\n");
}

void StringToFileTest::output() {
    std::stringstream out;

    {
        Error e(&out);
        Comparator<Compare::StringToFile> compare;
        CORRADE_VERIFY(!compare("Hello world?", Directory::join(FILETEST_DIR, "base.txt")));
        compare.printErrorMessage(e, "a", "b");
    }

    CORRADE_COMPARE(out.str(), "Files a and b have different contents. Actual character w but W expected on position 6.\n");
}

}}}}

CORRADE_TEST_MAIN(Corrade::TestSuite::Compare::Test::StringToFileTest)
