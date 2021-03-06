/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include "logMsg/logMsg.h"

#include "rest/OrionError.h"

#include "unittest.h"



/* ****************************************************************************
*
* all - 
*/
TEST(OrionError, all)
{
  StatusCode    sc(SccBadRequest, "no details 2");
  OrionError    e0;
  OrionError    e1(SccOk, "no details 3");
  OrionError    e3(sc);
  OrionError    e4(SccOk, "Good Request");
  std::string   out;
  const char*   outfile1 = "orion.orionError.all1.valid.xml";
  const char*   outfile2 = "orion.orionError.all1.valid.json";
  const char*   outfile5 = "orion.orionError.all3.valid.xml";
  const char*   outfile6 = "orion.orionError.all3.valid.json";
  const char*   outfile7 = "orion.orionError.all4.valid.xml";
  const char*   outfile8 = "orion.orionError.all4.valid.json";

  EXPECT_EQ(SccNone, e0.code);
  EXPECT_EQ("",      e0.reasonPhrase);
  EXPECT_EQ("",      e0.details);

  EXPECT_EQ(SccOk,          e1.code);
  EXPECT_EQ("OK",           e1.reasonPhrase);
  EXPECT_EQ("no details 3", e1.details);

  EXPECT_EQ(sc.code,         e3.code);
  EXPECT_EQ(sc.reasonPhrase, e3.reasonPhrase);
  EXPECT_EQ(sc.details,      e3.details);

  EXPECT_EQ(SccOk,          e4.code);
  EXPECT_EQ("OK",           e4.reasonPhrase);
  EXPECT_EQ("Good Request", e4.details);

  out = e1.render(XML, "");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile1)) << "Error getting test data from '" << outfile1 << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  out = e3.render(XML, "");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile5)) << "Error getting test data from '" << outfile5 << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  out = e4.render(XML, "");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile7)) << "Error getting test data from '" << outfile7 << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  out = e1.render(JSON, "");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  out = e3.render(JSON, "");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile6)) << "Error getting test data from '" << outfile6 << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  out = e4.render(JSON, "");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile8)) << "Error getting test data from '" << outfile8 << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());
}
