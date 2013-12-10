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
#include "gtest/gtest.h"

#include "logMsg/logMsg.h"

#include "serviceRoutines/postIndividualContextEntityAttributes.h"
#include "serviceRoutines/getAttributeValueInstance.h"
#include "serviceRoutines/putAttributeValueInstance.h"
#include "serviceRoutines/deleteAttributeValueInstance.h"
#include "serviceRoutines/badVerbGetPutDeleteOnly.h"
#include "serviceRoutines/badRequest.h"
#include "rest/RestService.h"

#include "testDataFromFile.h"
#include "unittest.h"



/* ****************************************************************************
*
* rs - 
*/
static RestService rs[] = 
{
  { "POST",   IndividualContextEntityAttributes, 4, { "ngsi10", "contextEntities", "*", "attributes"           }, "appendContextElementRequest",   postIndividualContextEntityAttributes },
  { "GET",    AttributeValueInstance,            6, { "ngsi10", "contextEntities", "*", "attributes", "*", "*" }, "",                              getAttributeValueInstance             },
  { "PUT",    AttributeValueInstance,            6, { "ngsi10", "contextEntities", "*", "attributes", "*", "*" }, "updateContextAttributeRequest", putAttributeValueInstance             },
  { "DELETE", AttributeValueInstance,            6, { "ngsi10", "contextEntities", "*", "attributes", "*", "*" }, "",                              deleteAttributeValueInstance          },
  { "*",      AttributeValueInstance,            6, { "ngsi10", "contextEntities", "*", "attributes", "*", "*" }, "",                              badVerbGetPutDeleteOnly               },
  { "*",      InvalidRequest,                    0, { "*", "*", "*", "*", "*", "*"                             }, "",                              badRequest                            },
  { "",       InvalidRequest,                    0, {                                                          }, "",                              NULL                                  }
};



/* ****************************************************************************
*
* notFound - 
*/
TEST(putAttributeValueInstance, notFound)
{
  ConnectionInfo ci1("/ngsi10/contextEntities/E1/attributes/A1/left",  "PUT", "1.1");
  ConnectionInfo ci2("/ngsi10/contextEntities/E1/attributes/A1/right",  "PUT", "1.1");
  ConnectionInfo ci3("/ngsi10/contextEntities/E1/attributes/A1/left",  "PUT", "1.1");
  std::string    expected1   = "<statusCode>\n  <code>404</code>\n  <reasonPhrase>Entity Not Found</reasonPhrase>\n  <details>E1</details>\n</statusCode>\n";
  std::string    expected2  = "<statusCode>\n  <code>400</code>\n  <reasonPhrase>unmatching metadata ID value URI/payload</reasonPhrase>\n  <details>right vs left</details>\n</statusCode>\n";
  std::string    expected3  = "<statusCode>\n  <code>404</code>\n  <reasonPhrase>Entity Not Found</reasonPhrase>\n  <details>E1</details>\n</statusCode>\n";
  const char*    fileName   = "ngsi10.putAttributeValueInstance.A1-left.ok.postponed.xml";
  const char*    fileName2  = "ngsi10.putAttributeValueInstance.noIdMetadata.postponed.xml";
  std::string    out;

  utInit();
  
  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";
  ci1.outFormat    = XML;
  ci1.inFormat     = XML;
  ci1.payload      = testBuf;
  ci1.payloadSize  = strlen(testBuf);
  out             = restService(&ci1, rs);
  EXPECT_EQ(expected1, out);

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";
  ci2.outFormat    = XML;
  ci2.inFormat     = XML;
  ci2.payload      = testBuf;
  ci2.payloadSize  = strlen(testBuf);
  out             = restService(&ci2, rs);
  EXPECT_EQ(expected2, out);

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName2)) << "Error getting test data from '" << fileName2 << "'";
  ci3.outFormat    = XML;
  ci3.inFormat     = XML;
  ci3.payload      = testBuf;
  ci3.payloadSize  = strlen(testBuf);
  out             = restService(&ci3, rs);
  EXPECT_EQ(expected3, out);

  utExit();
}



/* ****************************************************************************
*
* found - 
*/
TEST(putAttributeValueInstance, found)
{
  ConnectionInfo ci1("/ngsi10/contextEntities/E1/attributes",          "POST", "1.1");
  ConnectionInfo ci2("/ngsi10/contextEntities/E1/attributes/A1/left",  "PUT", "1.1");
  std::string    expected1    = "<appendContextElementResponse>\n  <contextResponseList>\n    <contextAttributeResponse>\n      <contextAttributeList>\n        <contextAttribute>\n          <name>A1</name>\n          <type></type>\n          <contextValue></contextValue>\n          <metadata>\n            <contextMetadata>\n              <name>ID</name>\n              <type>string</type>\n              <value>left</value>\n            </contextMetadata>\n          </metadata>\n        </contextAttribute>\n      </contextAttributeList>\n      <statusCode>\n        <code>200</code>\n        <reasonPhrase>OK</reasonPhrase>\n      </statusCode>\n    </contextAttributeResponse>\n  </contextResponseList>\n</appendContextElementResponse>\n";
  std::string    expected2    = "<statusCode>\n  <code>200</code>\n  <reasonPhrase>OK</reasonPhrase>\n</statusCode>\n";
  const char*    fileName1    = "ngsi10.IndividualContextEntityAttributes.A1-left.postponed.xml";
  const char*    fileName2    = "ngsi10.putAttributeValueInstance.A1-left.ok.postponed.xml";
  std::string    out;

  utInit();

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName1)) << "Error getting test data from '" << fileName1 << "'";
  ci1.outFormat    = XML;
  ci1.inFormat     = XML;
  ci1.payload      = testBuf;
  ci1.payloadSize  = strlen(testBuf);
  out              = restService(&ci1, rs);
  EXPECT_EQ(expected1, out);

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName2)) << "Error getting test data from '" << fileName2 << "'";
  ci2.outFormat    = XML;
  ci2.inFormat     = XML;
  ci2.payload      = testBuf;
  ci2.payloadSize  = strlen(testBuf);
  out              = restService(&ci2, rs);
  EXPECT_EQ(expected2, out);

  utExit();
}
