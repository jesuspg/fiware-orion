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
* Author: Fermin Galan
*/
#include "NotifyContextRequest.h"

#include <string>

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi10/NotifyContextRequest.h"
#include "ngsi10/NotifyContextResponse.h"


/* ****************************************************************************
*
* NotifyContextRequest::render -
*/
std::string NotifyContextRequest::render(RequestType requestType, Format format, std::string indent)
{
  std::string  out                                  = "";
  std::string  tag                                  = "notifyContextRequest";
  bool         contextElementResponseVectorRendered = contextElementResponseVector.size() != 0;

  //
  // Note on JSON commas:
  //   subscriptionId and originator are MANDATORY.
  //   The only doubt here if whether originator should end in a comma.
  //   This doubt is taken care of by the variable 'contextElementResponseVectorRendered'
  //
  out += startTag(indent, tag, format, false);
  out += subscriptionId.render(NotifyContext, format, indent + "  ", true);
  out += originator.render(format, indent  + "  ", contextElementResponseVectorRendered);
  out += contextElementResponseVector.render(NotifyContext, format, indent  + "  ", false);
  out += endTag(indent, tag, format);

  return out;
}


/* ****************************************************************************
*
* NotifyContextRequest::check
*/
std::string NotifyContextRequest::check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
{
  std::string            res;
  NotifyContextResponse  response;
   
  if (predetectedError != "")
  {
    response.responseCode.fill(SccBadRequest, predetectedError);
  }
  else if (((res = subscriptionId.check(QueryContext, format, indent, predetectedError, 0))               != "OK") ||
           ((res = originator.check(QueryContext, format, indent, predetectedError, 0))                   != "OK") ||
           ((res = contextElementResponseVector.check(QueryContext, format, indent, predetectedError, 0)) != "OK"))
  {
    response.responseCode.fill(SccBadRequest, res);
  }
  else
    return "OK";

  return response.render(NotifyContext, format, indent);
}


/* ****************************************************************************
*
* NotifyContextRequest::present -
*/
void NotifyContextRequest::present(std::string indent)
{
  subscriptionId.present(indent);
  originator.present(indent);
  contextElementResponseVector.present(indent);
}



/* ****************************************************************************
*
* NotifyContextRequest::release -
*/
void NotifyContextRequest::release(void)
{
  contextElementResponseVector.release();
}
