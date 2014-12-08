/******************************************************************************
The MIT License(MIT)

Embedded Template Library.

Copyright(c) 2014 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <UnitTest++/UnitTest++.h>

#include <iterator>
#include <string>
#include <vector>
#include <stdint.h>

#include "../checksum.h"
#include "../endian.h"

namespace
{		
  SUITE(test_checksum)
  {
    //*************************************************************************
    TEST(test_checksum_constructor)
    {
      std::string data("123456789");

      uint8_t sum = etl::checksum<uint8_t>(data.begin(), data.end());

      CHECK_EQUAL(221, int(sum));
    }

    //*************************************************************************
    TEST(test_checksum_add_values)
    {
      std::string data("123456789");

      etl::checksum<uint8_t> checksum_calculator;

      for (size_t i = 0; i < data.size(); ++i)
      {
        checksum_calculator += data[i];
      }
      
      uint8_t sum = checksum_calculator;

      CHECK_EQUAL(221, int(sum));
    }

    //*************************************************************************
    TEST(test_checksum_add_range)
    {
      std::string data("123456789");

      etl::checksum<uint8_t> checksum_calculator;

      checksum_calculator.add(data.begin(), data.end());

      uint8_t sum = checksum_calculator.value();

      CHECK_EQUAL(221, int(sum));
    }

    //*************************************************************************
    TEST(test_checksum_add_range_sum32)
    {
      std::string data("123456789");

      etl::checksum<uint32_t> checksum_calculator;

      checksum_calculator.add(data.begin(), data.end());

      uint32_t sum = checksum_calculator.value();

      CHECK_EQUAL(477, int(sum));
    }

    //*************************************************************************
    TEST(test_checksum_add_range_endian)
    {
      std::vector<uint8_t>  data1 = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
      std::vector<uint32_t> data2 = { 0x04030201, 0x08070605 };
      std::vector<uint32_t> data3 = { 0x01020304, 0x05060708 };

      uint8_t sum1 = etl::checksum<uint8_t, etl::endian::little>(data1.begin(), data1.end());
      uint8_t sum2 = etl::checksum<uint8_t, etl::endian::little>(data2.begin(), data2.end());
      CHECK_EQUAL(int(sum1), int(sum2));

      uint8_t sum3 = etl::checksum<uint8_t, etl::endian::big>(data3.begin(), data3.end());
      CHECK_EQUAL(int(sum1), int(sum3));
    }
  };
}

