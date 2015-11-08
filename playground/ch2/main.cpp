/*
 * main.cpp
 *
 *  Created on: 2015年11月6日
 *      Author: ctai
 */

#include "gmock/gmock.h"

int main(int argc, char** argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

