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
#include <string>
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "ngsi/EntityId.h"
#include "ngsi9/SubscribeContextAvailabilityRequest.h"
#include "jsonParse/jsonNullTreat.h"
#include "jsonParse/JsonNode.h"
#include "jsonParse/jsonSubscribeContextAvailabilityRequest.h"
#include "parse/nullTreat.h"



/* ****************************************************************************
*
* entityId - 
*/
static std::string entityId(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("%s: %s", path.c_str(), value.c_str()));

  reqDataP->scar.entityIdP = new EntityId();

  LM_T(LmtNew, ("New entityId at %p", reqDataP->scar.entityIdP));
  reqDataP->scar.entityIdP->id        = "";
  reqDataP->scar.entityIdP->type      = "";
  reqDataP->scar.entityIdP->isPattern = "false";

  reqDataP->scar.res.entityIdVector.push_back(reqDataP->scar.entityIdP);
  LM_T(LmtNew, ("After push_back"));

  return "OK";
}



/* ****************************************************************************
*
* entityIdId - 
*/
static std::string entityIdId(std::string path, std::string value, ParseData* reqDataP)
{
   reqDataP->scar.entityIdP->id = value;
   LM_T(LmtParse, ("Set 'id' to '%s' for an entity", reqDataP->scar.entityIdP->id.c_str()));

   return "OK";
}



/* ****************************************************************************
*
* entityIdType - 
*/
static std::string entityIdType(std::string path, std::string value, ParseData* reqDataP)
{
   reqDataP->scar.entityIdP->type = value;
   LM_T(LmtParse, ("Set 'type' to '%s' for an entity", reqDataP->scar.entityIdP->type.c_str()));

   return "OK";
}



/* ****************************************************************************
*
* entityIdIsPattern - 
*/
static std::string entityIdIsPattern(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got an entityId:isPattern: '%s'", value.c_str()));

  if (!isTrue(value) && !isFalse(value))
    return "invalid isPattern (boolean) value for entity: '" + value + "'";

  reqDataP->scar.entityIdP->isPattern = value;

  return "OK";
}



/* ****************************************************************************
*
* attribute - 
*/
static std::string attribute(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got an attribute: '%s'", value.c_str()));

  reqDataP->scar.res.attributeList.push_back(value);

  return "OK";
}



/* ****************************************************************************
*
* reference - 
*/
static std::string reference(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a reference: '%s'", value.c_str()));

  reqDataP->scar.res.reference.set(value);

  return "OK";
}



/* ****************************************************************************
*
* duration - 
*/
static std::string duration(std::string path, std::string value, ParseData* reqDataP)
{
  std::string s;

  LM_T(LmtParse, ("Got a duration: '%s'", value.c_str()));

  reqDataP->scar.res.duration.set(value);

  if ((s = reqDataP->scar.res.duration.check(SubscribeContextAvailability, JSON, "", "", 0)) != "OK")
     LM_RE(s, ("error parsing duration '%s': %s", reqDataP->scar.res.duration.get().c_str(), s.c_str()));

  return "OK";
}



/* ****************************************************************************
*
* restriction - 
*/
static std::string restriction(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a restriction"));

  ++reqDataP->scar.res.restrictions;

  return "OK";
}



/* ****************************************************************************
*
* attributeExpression - 
*/
static std::string attributeExpression(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got an attributeExpression: '%s'", value.c_str()));

  reqDataP->scar.res.restriction.attributeExpression.set(value);

  return "OK";
}



/* ****************************************************************************
*
* scope - 
*/
static std::string scope(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a scope"));

  reqDataP->scar.scopeP = new Scope();
  reqDataP->scar.res.restriction.scopeVector.push_back(reqDataP->scar.scopeP);

  return "OK";
}



/* ****************************************************************************
*
* scopeType - 
*/
static std::string scopeType(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a scope type: '%s'", value.c_str()));
  reqDataP->scar.scopeP->type = value;
  return "OK";
}



/* ****************************************************************************
*
* scopeValue - 
*/
static std::string scopeValue(std::string path, std::string value, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a scope value: '%s'", value.c_str()));
  reqDataP->scar.scopeP->value = value;
  return "OK";
}



/* ****************************************************************************
*
* jsonScarParseVector -
*/
JsonNode jsonScarParseVector[] =
{
  { "/entities",                           jsonNullTreat        },
  { "/entities/entity",                    entityId             },
  { "/entities/entity/id",                 entityIdId           },
  { "/entities/entity/type",               entityIdType         },
  { "/entities/entity/isPattern",          entityIdIsPattern    },
  { "/attributes",                         jsonNullTreat        },
  { "/attributes/attribute",               attribute            },
  { "/reference",                          reference            },
  { "/duration",                           duration             },
  { "/restriction",                        restriction          },
  { "/restriction/attributeExpression",    attributeExpression  },
  { "/restriction/scopes",                 jsonNullTreat        },
  { "/restriction/scopes/scope",           scope,               },
  { "/restriction/scopes/scope/type",      scopeType            },
  { "/restriction/scopes/scope/value",     scopeValue           },
  { "LAST", NULL }
};



/* ****************************************************************************
*
* jsonScarInit - 
*/
void jsonScarInit(ParseData* reqDataP)
{
  jsonScarRelease(reqDataP);

  reqDataP->scar.entityIdP             = NULL;
  reqDataP->scar.scopeP                = NULL;
  reqDataP->errorString                = "";

  reqDataP->scar.res.restrictions      = 0;
  reqDataP->scar.res.restriction.attributeExpression.set("");
}



/* ****************************************************************************
*
* jsonScarRelease - 
*/
void jsonScarRelease(ParseData* reqDataP)
{
  reqDataP->scar.res.release();
}



/* ****************************************************************************
*
* jsonScarCheck - 
*/
std::string jsonScarCheck(ParseData* reqData, ConnectionInfo* ciP)
{
   std::string s;
   s = reqData->scar.res.check(SubscribeContextAvailability, ciP->outFormat, "", reqData->errorString, 0);
   return s;
}



/* ****************************************************************************
*
* jsonScarPresent - 
*/
void jsonScarPresent(ParseData* reqDataP)
{
  printf("jsonScarPresent\n");

  if (!lmTraceIsSet(LmtDump))
    return;

  reqDataP->scar.res.present("");
}
