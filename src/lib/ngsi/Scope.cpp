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

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/Scope.h"
#include "common/Format.h"



/* ****************************************************************************
*
* Scope::Scope - 
*/
Scope::Scope()
{
  type     = "";
  value    = "";
  areaType = AreaNone;
}



/* ****************************************************************************
*
* Scope::Scope - 
*/
Scope::Scope(std::string _type, std::string _value)
{
  type  = _type;
  value = _value;
}



/* ****************************************************************************
*
* Scope::render - 
*/
std::string Scope::render(Format format, std::string indent, bool notLastInVector)
{
  std::string out      = "";
  std::string tag      = "operationScope";
  const char* tTag     = (format == XML)? "scopeType" : "type";
  const char* vTag     = (format == XML)? "scopeValue" : "value";

  out += startTag(indent, tag, tag, format, false, false);
  out += valueTag(indent + "  ", tTag, type, format, true);
  out += valueTag(indent + "  ", vTag, value, format);
  out += endTag(indent, tag, format, notLastInVector);

  return out;
}



/* ****************************************************************************
*
* Scope::check - 
*/
std::string Scope::check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
{
  if (type == "FIWARE_Location")
  {
    if (areaType == AreaCircle)
    {
      if (circle.radius == "0")
        return "Radius zero for a circle area";
      else if (circle.radius == "")
        return "Missing radius for circle area";
      else if (circle.inverted != "")
      {
        if (!isTrue(circle.inverted) && !isFalse(circle.inverted))
          return "bad value for circle/inverted: '" + circle.inverted + "'";
      }
      else if (circle.center.latitude == "")
        return "Missing latitude for circle center";
      else if (circle.center.longitude == "")
        return "Missing longitude for circle center";
    }
    else if (areaType == AreaPolygon)
    {
      if (polygon.vertexList.size() < 3)
        return "too few vertices for a polygon";
      else if (polygon.inverted != "")
      {
        if (!isTrue(polygon.inverted) && !isFalse(polygon.inverted))
          return "bad value for polygon/inverted: '" + polygon.inverted + "'";
      }

      for (unsigned int ix = 0; ix < polygon.vertexList.size(); ++ix)
      {
        if (polygon.vertexList[ix]->latitude == "")
          return std::string("missing latitude value for polygon vertex");
        if (polygon.vertexList[ix]->longitude == "")
          return std::string("missing longitude value for polygon vertex");
      }
    }
  }
  else
  {
    if ((type == "") || (type == "not in use"))
      return "Empty type in restriction scope";

    if ((value == "") || (value == "not in use"))
      return "Empty value in restriction scope";
  }

  return "OK";
}



/* ****************************************************************************
*
* Scope::present - 
*/
void Scope::present(std::string indent, int ix)
{
  if (ix == -1)
    PRINTF("%sScope:\n",       indent.c_str());
  else
    PRINTF("%sScope %d:\n",    indent.c_str(), ix);

  PRINTF("%s  Type:     %s\n", indent.c_str(), type.c_str());

  if (areaType == AreaNone)
    PRINTF("%s  Value:    %s\n", indent.c_str(), value.c_str());
  else if (areaType == AreaCircle)
  {
    PRINTF("%s  FI-WARE Circle Area:\n", indent.c_str());
    PRINTF("%s    Radius:     %s\n", indent.c_str(), circle.radius.c_str());
    PRINTF("%s    Longitude:  %s\n", indent.c_str(), circle.center.longitude.c_str());
    PRINTF("%s    Latitude:   %s\n", indent.c_str(), circle.center.latitude.c_str());
    PRINTF("%s    Inverted:   %s\n", indent.c_str(), circle.inverted.c_str());
  }
  else if (areaType == AreaPolygon)
  {
    PRINTF("%s  FI-WARE Polygon Area (%lu vertices):\n", indent.c_str(), polygon.vertexList.size());

    PRINTF("%s    Inverted:   %s\n", indent.c_str(), polygon.inverted.c_str());
    for (unsigned int ix = 0; ix < polygon.vertexList.size(); ++ix)
    {
      PRINTF("%s    Vertex %d\n", indent.c_str(), ix);
      PRINTF("%s      Longitude:  %s\n", indent.c_str(), polygon.vertexList[ix]->longitude.c_str());
      PRINTF("%s      Latitude:   %s\n", indent.c_str(), polygon.vertexList[ix]->latitude.c_str());
    }
  }
}



/* ****************************************************************************
*
* release - 
*/
void Scope::release(void)
{
   /* This method is included for the sake of homogeneity */
}
