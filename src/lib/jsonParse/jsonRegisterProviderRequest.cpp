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
#include "convenience/RegisterProviderRequest.h"
#include "jsonParse/jsonParse.h"
#include "jsonParse/jsonRegisterProviderRequest.h"
#include "jsonParse/JsonNode.h"
#include "jsonParse/jsonNullTreat.h"
#include "ngsi/Request.h"
#include "rest/ConnectionInfo.h"



/* ****************************************************************************
*
* contextMetadata - 
*/
static std::string contextMetadata(std::string path, std::string value, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata"));
   reqData->rpr.metadataP = new Metadata();
   reqData->rpr.res.metadataVector.push_back(reqData->rpr.metadataP);
   return "OK";
 }




/* ****************************************************************************
*
* contextMetadataName - 
*/
static std::string contextMetadataName(std::string path, std::string value, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata name '%s'", value.c_str()));
   reqData->rpr.metadataP->name = value;
   return "OK";
}



/* ****************************************************************************
*
* contextMetadataType - 
*/
static std::string contextMetadataType(std::string path, std::string value, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata type '%s'", value.c_str()));
   reqData->rpr.metadataP->type = value;
   return "OK";
}




/* ****************************************************************************
*
* contextMetadataValue - 
*/
static std::string contextMetadataValue(std::string path, std::string value, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a metadata value '%s'", value.c_str()));
   reqData->rpr.metadataP->value = value;
   return "OK";
}



/* ****************************************************************************
*
* duration - 
*/
static std::string duration(std::string path, std::string value, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a duration '%s'", value.c_str()));
   reqData->rpr.res.duration.set(value);
   return "OK";
}



/* ****************************************************************************
*
* providingApplication - 
*/
static std::string providingApplication(std::string path, std::string value, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a providingApplication '%s'", value.c_str()));
   reqData->rpr.res.providingApplication.set(value);
   return "OK";
}



/* ****************************************************************************
*
* registrationId - 
*/
static std::string registrationId(std::string path, std::string value, ParseData* reqData)
{
   LM_T(LmtParse, ("Got a registrationId '%s'", value.c_str()));
   reqData->rpr.res.registrationId.set(value);
   return "OK";
}


/* ****************************************************************************
*
* jsonRprParseVector -
*/
JsonNode jsonRprParseVector[] =
{
   { "/metadatas",                                               jsonNullTreat         },
   { "/metadatas/metadata",                                      contextMetadata       },
   { "/metadatas/metadata/name",                                 contextMetadataName   },
   { "/metadatas/metadata/type",                                 contextMetadataType   },
   { "/metadatas/metadata/value",                                contextMetadataValue  },

   { "/duration",                        duration              },
   { "/providingApplication",            providingApplication  },
   { "/registrationId",                  registrationId        },

   { "LAST", NULL }
};



/* ****************************************************************************
*
* jsonRprInit -
*/
void jsonRprInit(ParseData* reqData)
{
   reqData->rpr.res.registrationId.set("");
   reqData->rpr.res.providingApplication.set("");
   reqData->rpr.res.duration.set("");

   reqData->rpr.metadataP = NULL;
}



/* ****************************************************************************
*
* jsonRprRelease -
*/
void jsonRprRelease(ParseData* reqData)
{
   reqData->rpr.res.release();
}


/* ****************************************************************************
*
* jsonRprCheck -
*/
std::string jsonRprCheck(ParseData* reqData, ConnectionInfo* ciP)
{
  return reqData->rpr.res.check(ContextEntitiesByEntityId, ciP->outFormat, "", reqData->errorString, 0);
}


/* ****************************************************************************
*
* jsonRprPresent -
*/
void jsonRprPresent(ParseData* reqData)
{
   reqData->rpr.res.present("");
}
