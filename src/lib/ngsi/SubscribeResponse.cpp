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

#include "common/globals.h"
#include "common/tag.h"
#include "common/Format.h"
#include "ngsi/SubscribeResponse.h"



/* ****************************************************************************
*
* SubscribeResponse::SubscribeResponse - 
*/ 
SubscribeResponse::SubscribeResponse()
{
}



/* ****************************************************************************
*
* SubscribeResponse::render - 
*/
std::string SubscribeResponse::render(Format format, std::string indent, bool comma)
{
  std::string  out                 = "";
  std::string  tag                 = "subscribeResponse";
  bool         durationRendered    = !duration.isEmpty();
  bool         throttlingRendered  = !throttling.isEmpty();

  out += startTag(indent, tag, format);
  out += subscriptionId.render(RtSubscribeResponse, format, indent + "  ", durationRendered || throttlingRendered);
  out += duration.render(format, indent + "  ", throttlingRendered);
  out += throttling.render(format, indent + "  ", false);
  out += endTag(indent, tag, format, comma);

  return out;
}
