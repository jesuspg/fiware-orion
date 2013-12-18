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
#include "logMsg/traceLevels.h"

#include "ngsi/ParseData.h"
#include "common/globals.h"
#include "jsonParse/jsonRequest.h"
#include "rest/ConnectionInfo.h"
#include "xmlParse/xmlRequest.h"

#include "unittest.h"



/* ****************************************************************************
*
* ok_xml - 
*/
TEST(NotifyContextAvailabilityRequest, ok_xml)
{
  ParseData       parseData;
  const char*     inFile  = "ngsi9.notifyContextAvailabilityRequest.ok.valid.xml";
  const char*     outFile = "ngsi9.notifyContextAvailabilityRequestRendered.ok.valid.xml";
  ConnectionInfo  ci("", "POST", "1.1");
  std::string     rendered;

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), inFile)) << "Error getting test data from '" << inFile << "'";
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outFile)) << "Error getting test data from '" << outFile << "'";

  lmTraceLevelSet(LmtDump, true);
  std::string result = xmlTreat(testBuf, &ci, &parseData, NotifyContextAvailability, "notifyContextAvailabilityRequest", NULL);
  EXPECT_EQ("OK", result);
  lmTraceLevelSet(LmtDump, false);

  NotifyContextAvailabilityRequest* ncarP = &parseData.ncar.res;

  rendered = ncarP->render(NotifyContext, XML, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  ncarP->release();
}



/* ****************************************************************************
*
* ok_json - 
*/
TEST(NotifyContextAvailabilityRequest, ok_json)
{
  ParseData       parseData;
  const char*     fileName = "notifyContextAvailabilityRequest_ok.json";
  ConnectionInfo  ci("", "POST", "1.1");

  ci.inFormat  = JSON;
  ci.outFormat = JSON;

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";

  lmTraceLevelSet(LmtDump, true);
  std::string result = jsonTreat(testBuf, &ci, &parseData, NotifyContextAvailability, "notifyContextAvailabilityRequest", NULL);
  EXPECT_EQ("OK", result);
  lmTraceLevelSet(LmtDump, false);

  NotifyContextAvailabilityRequest* ncarP = &parseData.ncar.res;

  std::string     rendered = ncarP->render(NotifyContext, JSON, "");
  std::string     expected = "{\n  \"subscriptionId\" : \"012345678901234567890123\",\n  \"contextRegistrationResponses\" : [\n    {\n      \"contextRegistration\" : {\n        \"entities\" : [\n          {\n            \"type\" : \"Room\",\n            \"isPattern\" : \"false\",\n            \"id\" : \"ConferenceRoom\"\n          },\n          {\n            \"type\" : \"Room\",\n            \"isPattern\" : \"false\",\n            \"id\" : \"OfficeRoom\"\n          }\n        ],\n        \"attributes\" : [\n          {\n            \"name\" : \"temperature\",\n            \"type\" : \"degree\",\n            \"isDomain\" : \"false\",\n            \"metadatas\" : [\n              {\n                \"name\" : \"ID\",\n                \"type\" : \"string\",\n                \"value\" : \"1110\"\n              }\n            ]\n          }\n        ],\n        \"metadatas\" : [\n          {\n            \"name\" : \"ID\",\n            \"type\" : \"string\",\n            \"value\" : \"2212\"\n          }\n        ],\n        \"providingApplication\" : \"http://192.168.100.1:70/application\"\n      }\n    }\n  ]\n}\n";

  EXPECT_EQ(expected, rendered);

  ncarP->release();
}



/* ****************************************************************************
*
* badEntityAttribute_xml - 
*/
TEST(NotifyContextAvailabilityRequest, badEntityAttribute_xml)
{
  ParseData       parseData;
  const char*     fileName = "ngsi9.notifyContextAvailabilityRequest.entityAttribute.invalid.xml";
  ConnectionInfo  ci("", "POST", "1.1");
  std::string     expected = "<notifyContextAvailabilityResponse>\n  <responseCode>\n    <code>400</code>\n    <reasonPhrase>unsupported attribute for EntityId</reasonPhrase>\n  </responseCode>\n</notifyContextAvailabilityResponse>\n";

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";

  std::string result = xmlTreat(testBuf, &ci, &parseData, NotifyContextAvailability, "notifyContextAvailabilityRequest", NULL);
  EXPECT_EQ(expected, result);
}



/* ****************************************************************************
*
* check - 
*/
TEST(NotifyContextAvailabilityRequest, check)
{
  NotifyContextAvailabilityRequest  ncr;
  std::string                       check;
  std::string                       expected1 = "OK";
  std::string                       expected2 = "<notifyContextAvailabilityResponse>\n  <responseCode>\n    <code>400</code>\n    <reasonPhrase>predetected error</reasonPhrase>\n  </responseCode>\n</notifyContextAvailabilityResponse>\n";
  std::string                       expected3 = "<notifyContextAvailabilityResponse>\n  <responseCode>\n    <code>400</code>\n    <reasonPhrase>bad length (24 chars expected)</reasonPhrase>\n  </responseCode>\n</notifyContextAvailabilityResponse>\n";

  // check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
  check = ncr.check(NotifyContextAvailability, XML, "", "", 0);
  EXPECT_EQ(expected1, check);

  check = ncr.check(NotifyContextAvailability, XML, "", "predetected error", 0);
  EXPECT_EQ(expected2, check);
 
  ncr.subscriptionId.set("12345");
  check = ncr.check(NotifyContextAvailability, XML, "", "", 0);
  EXPECT_EQ(expected3, check);
}



/* ****************************************************************************
*
* json_render - 
*/
TEST(NotifyContextAvailabilityRequest, json_render)
{
  const char*                          filename1  = "ngsi10.notifyContextAvailabilityRequest.jsonRender1.valid.json";
  const char*                          filename2  = "ngsi10.notifyContextAvailabilityRequest.jsonRender2.valid.json";
  NotifyContextAvailabilityRequest*    ncarP;
  std::string                          rendered;
  ContextRegistrationResponse*         crrP;
  EntityId*                            eidP  = new EntityId("E01", "EType", "false");

  utInit();

  //
  // Both subscriptionId and contextRegistrationResponseVector are MANDATORY.
  // Just two tests here:
  //  1. contextRegistrationResponseVector with ONE contextRegistrationResponse instance
  //  2. contextRegistrationResponseVector with TWO contextRegistrationResponse instances
  //



  // Preparation
  ncarP = new NotifyContextAvailabilityRequest();
  ncarP->subscriptionId.set("012345678901234567890123");

  crrP = new ContextRegistrationResponse();
  ncarP->contextRegistrationResponseVector.push_back(crrP);
  crrP->contextRegistration.entityIdVector.push_back(eidP);
  crrP->contextRegistration.providingApplication.set("http://www.tid.es/NotifyContextAvailabilityRequestTest");

  // Test 1. contextRegistrationResponseVector with ONE contextRegistrationResponse instance
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename1)) << "Error getting test data from '" << filename1 << "'";
  rendered = ncarP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());
  

  
  // Test 2. contextRegistrationResponseVector with TWO contextRegistrationResponse instances
  Metadata*                     mdP   = new Metadata("M01", "MType", "123");
  ContextRegistrationAttribute* craP  = new ContextRegistrationAttribute("CRA1", "CType", "false");

  eidP->fill("E02", "EType", "false");
  crrP = new ContextRegistrationResponse();
  ncarP->contextRegistrationResponseVector.push_back(crrP);

  crrP->contextRegistration.entityIdVector.push_back(eidP);
  crrP->contextRegistration.entityIdVectorPresent = true;
  crrP->contextRegistration.contextRegistrationAttributeVector.push_back(craP);
  crrP->contextRegistration.registrationMetadataVector.push_back(mdP);

  crrP->contextRegistration.providingApplication.set("http://www.tid.es/NotifyContextAvailabilityRequestTest2");
  
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename2)) << "Error getting test data from '" << filename2 << "'";
  rendered = ncarP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  
  utExit();
}
