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

#include "ngsi10/QueryContextResponse.h"

#include "unittest.h"



/* ****************************************************************************
*
* ok_xml - 
*/
TEST(QueryContextResponse, ok_xml)
{
  ErrorCode*            ecP = new ErrorCode(SccOk, "Reason", "Detail");
  ErrorCode             ec(SccOk, "Reason2", "Detail2");
  QueryContextResponse  qcr1;
  QueryContextResponse  qcr2(ec);
  std::string           rendered;
  std::string           expected1 = "<queryContextResponse>\n  <errorCode>\n    <code>404</code>\n    <reasonPhrase>Query without hits</reasonPhrase>\n  </errorCode>\n</queryContextResponse>\n";
  std::string           expected2 = "<queryContextResponse>\n  <errorCode>\n    <code>404</code>\n    <reasonPhrase>Query without hits</reasonPhrase>\n  </errorCode>\n</queryContextResponse>\n";

  rendered = qcr1.render(QueryContext, XML, "");
  EXPECT_STREQ(expected1.c_str(), rendered.c_str());

  rendered = qcr2.render(QueryContext, XML, "");
  EXPECT_STREQ(expected2.c_str(), rendered.c_str());

  delete ecP;
}



/* ****************************************************************************
*
* json_render - 
*/
TEST(QueryContextResponse, json_render)
{
  const char*              filename1  = "ngsi10.queryContextResponse.jsonRender1.valid.json";
  const char*              filename2  = "ngsi10.queryContextResponse.jsonRender2.valid.json";
  const char*              filename3  = "ngsi10.queryContextResponse.jsonRender3.valid.json";
  const char*              filename4  = "ngsi10.queryContextResponse.jsonRender4.valid.json";
  const char*              filename5  = "ngsi10.queryContextResponse.jsonRender5.valid.json";
  const char*              filename6  = "ngsi10.queryContextResponse.jsonRender6.valid.json";
  const char*              filename7  = "ngsi10.queryContextResponse.jsonRender7.valid.json";
  const char*              filename8  = "ngsi10.queryContextResponse.jsonRender8.valid.json";
  const char*              filename9  = "ngsi10.queryContextResponse.jsonRender9.valid.json";
  const char*              filename10 = "ngsi10.queryContextResponse.jsonRender10.valid.json";
  const char*              filename11 = "ngsi10.queryContextResponse.jsonRender11.valid.json";
  const char*              filename12 = "ngsi10.queryContextResponse.jsonRender12.valid.json";
  const char*              filename13 = "ngsi10.queryContextResponse.jsonRender13.valid.json";
  QueryContextResponse*    qcrP;
  ContextElementResponse*  cerP;
  Metadata*                mdP;
  ContextAttribute*        caP;
  std::string              rendered;

  utInit();

  // Preparations
  qcrP = new QueryContextResponse();

  // 1. ContextElement: +entityId -attributeDomainName -contextAttributeVector -domainMetadataVector
  cerP = new ContextElementResponse();

  cerP->contextElement.entityId.fill("E01", "EType", "false");
  cerP->statusCode.fill(SccOk, "OK");
  qcrP->contextElementResponseVector.push_back(cerP);
  
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename1)) << "Error getting test data from '" << filename1 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());


  // 2. ContextElement: +entityId -attributeDomainName -contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md1", "string", "FIN");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename2)) << "Error getting test data from '" << filename2 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 3. ContextElement: +entityId -attributeDomainName +contextAttributeVector -domainMetadataVector
  cerP->contextElement.domainMetadataVector.release();
  caP = new ContextAttribute("ca", "string", "a context attribute");
  cerP->contextElement.contextAttributeVector.push_back(caP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename3)) << "Error getting test data from '" << filename3 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 4. ContextElement: +entityId -attributeDomainName +contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md1", "string", "FIN");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename4)) << "Error getting test data from '" << filename4 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 5. ContextElement: +entityId +attributeDomainName -contextAttributeVector -domainMetadataVector
  cerP->contextElement.domainMetadataVector.release();
  cerP->contextElement.contextAttributeVector.release();
  cerP->contextElement.attributeDomainName.set("AttrDomain");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename5)) << "Error getting test data from '" << filename5 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  // 6. ContextElement: +entityId +attributeDomainName -contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md6", "string", "FIN6");
  cerP->contextElement.domainMetadataVector.push_back(mdP);
  
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename6)) << "Error getting test data from '" << filename6 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 7. ContextElement: +entityId +attributeDomainName +contextAttributeVector -domainMetadataVector
  cerP->contextElement.domainMetadataVector.release();
  caP = new ContextAttribute("ca7", "string", "context attribute 7");
  cerP->contextElement.contextAttributeVector.push_back(caP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename7)) << "Error getting test data from '" << filename7 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 8. ContextElement: +entityId +attributeDomainName +contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md8", "string", "FIN8");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename8)) << "Error getting test data from '" << filename8 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());


  // 9. ContextElement: contextAttributeVector of two attributes
  caP = new ContextAttribute("ca9", "string", "context attribute 9");
  cerP->contextElement.contextAttributeVector.push_back(caP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename9)) << "Error getting test data from '" << filename9 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  // 10. ContextElement: domainMetadataVector of two metadatas
  mdP = new Metadata("md10", "string", "FIN10");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename10)) << "Error getting test data from '" << filename10 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());
  


  // 11. QueryContextResponse::contextElementResponseVector of TWO responses
  cerP = new ContextElementResponse();

  cerP->contextElement.entityId.fill("E02", "EType", "false");
  cerP->statusCode.fill(SccOk, "OK");
  qcrP->contextElementResponseVector.push_back(cerP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename11)) << "Error getting test data from '" << filename11 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 12  QueryContextResponse::errorCode OK and contextElementResponseVector filled id (no details)
  qcrP->errorCode.fill(SccOk, "OK");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename12)) << "Error getting test data from '" << filename12 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());


  // 13  QueryContextResponse::errorCode NOT OK and contextElementResponseVector filled id (with details)
  qcrP->errorCode.fill(SccBadRequest, "Bad Request", "no details");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename13)) << "Error getting test data from '" << filename13 << "'";
  rendered = qcrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  utExit();
}
