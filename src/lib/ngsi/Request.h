#ifndef REQUEST_H
#define REQUEST_H

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

struct ConnectionInfo;



/* ****************************************************************************
*
* RequestType - 
*/
typedef enum RequestType
{
  RegisterContext = 1,
  DiscoverContextAvailability,
  SubscribeContextAvailability,
  RtSubscribeContextAvailabilityResponse,
  UpdateContextAvailabilitySubscription,
  RtUpdateContextAvailabilitySubscriptionResponse,
  UnsubscribeContextAvailability,
  RtUnsubscribeContextAvailabilityResponse,
  NotifyContextAvailability,

  QueryContext = 11,
  SubscribeContext,
  UpdateContextSubscription,
  UnsubscribeContext,
  RtUnsubscribeContextResponse,
  NotifyContext,
  UpdateContext,

  ContextEntitiesByEntityId = 21,
  ContextEntityAttributes,
  EntityByIdAttributeByName,
  ContextEntityTypes,
  ContextEntityTypeAttributeContainer,
  ContextEntityTypeAttribute,
  Ngsi9SubscriptionsConvOp,

  IndividualContextEntity                = 31,
  IndividualContextEntityAttributes,
  IndividualContextEntityAttribute,
  AttributeValueInstance,
  Ngsi10ContextEntityTypes,
  Ngsi10ContextEntityTypesAttributeContainer,
  Ngsi10ContextEntityTypesAttribute,
  Ngsi10SubscriptionsConvOp,

  UpdateContextElement = 41,
  AppendContextElement,
  UpdateContextAttribute,

  LogRequest = 51,
  VersionRequest,
  ExitRequest,
  LeakRequest,
  StatisticsRequest,

  RegisterResponse,
  RtSubscribeResponse,
  RtSubscribeError,
  InvalidRequest,
} RequestType;



/* ****************************************************************************
*
* Forward declarations
*/
struct ParseData;



/* ****************************************************************************
*
* requestType - 
*/
extern const char* requestType(RequestType rt);



/* ****************************************************************************
*
* RequestInit - 
*/
typedef void (*RequestInit)(ParseData* reqDataP);



/* ****************************************************************************
*
* RequestRelease - 
*/
typedef void (*RequestRelease)(ParseData* reqDataP);



/* ****************************************************************************
*
* RequestCheck - 
*/
typedef std::string (*RequestCheck)(ParseData* reqDataP, ConnectionInfo* ciP);



/* ****************************************************************************
*
* RequestPresent - 
*/
typedef void (*RequestPresent)(ParseData* reqDataP);

#endif
