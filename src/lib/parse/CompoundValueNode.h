#ifndef ORION_COMPOUND_VALUE
#define ORION_COMPOUND_VALUE

/*
*
* Copyright 2014 Telefonica Investigacion y Desarrollo, S.A.U
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

#include "common/Format.h"



namespace orion
{

/* ****************************************************************************
*
* CompoundValueNode - 
*
* The class fields:
* -------------------------------------------------------------------------------
* o name         When parsing an XML payload, each node in the tree has a tag.
*                The name of the node is taken from the tag-name.
*                When parsing a JSON payload, not necessarily all nodes have a
*                tag, so 'name' can be empty.
*                Also, when creating the tree from mongo BSON, there will often
*                be no 'name', just like the case of JSON payload parsing.
*
* o type         There are only three types of nodes: Vectors, Structs and Leafs.
*                The root node is somehow special, but is always either Vector or Struct.
*
* o value        The value of a Leaf in the tree. Always stored as a string, as the
*                payload always comes in as a string.
*
* o childV       A vector of the children of a Vector or Struct.
*                Contains pointers to CompoundValueNode.
*
* o container    A pointer to the father of the node. The father is the Struct/Vector node
*                that owns this node.
*
* o rootP        A pointer to the owner of the entire tree
*
* o error        This string is used by the 'check' function to save any errors detected during
*                the 'check' phase.
*                FIXME P1: May be removed if the check function is modified.
*
* o root         This field is used only by the owner of the entire tree.
*                It contains the absolute path of the payload node that is the owner of the tree.
*                Note that this path is not the same if the payload comes in JSON instead of XML.
*                FIXME P5: To be removed, as ContextValue points directly to the root node.
*
* o path         Absolute path of the node in the tree.
*                Used for error messages, e.g. duplicated tag-name in a struct.
*
* o level        The depth or nesting level in which this node lives.
*                FIXME P1: this field is not used and can be removed.
*
* o siblingNo:   This field is used for rendering JSON. It tells us whether a comma should
*                be added after a field (a comma is added unless the sibling number is
*                equal to the number of siblings (the size of the containers child vector).
*/
class CompoundValueNode
{
public:
   enum Type
   {
      Leaf,
      Struct,
      Vector
   };

   // Tree fields
   std::string                        name;
   Type                               type;
   std::string                        value;
   std::vector<CompoundValueNode*>    childV;


   // Auxiliar fields for cretion of the tree
   CompoundValueNode*                 container;
   CompoundValueNode*                 rootP;
   std::string                        error;


   // Fields that may not be necessary
   // FIXME P4: when finally sure, remove the unnecessary fields
   std::string                        root;
   std::string                        path;
   int                                level;
   int                                siblingNo;


   // Constructors/Destructors
   CompoundValueNode(std::string _root = "");   // FIXME P10: 'root' will probably disapear at the end. To be fixed at the end during the cleanup phase on the feature/complex_value branch
   CompoundValueNode(CompoundValueNode* _container, std::string _path, std::string _name, std::string _value, int _siblingNo, Type _type, int _level = -1);
   ~CompoundValueNode();

   CompoundValueNode*  clone(void);
   CompoundValueNode*  add(CompoundValueNode* node);
   CompoundValueNode*  add(const Type _type, const std::string& _name, const std::string& _containerPath, const std::string& _value = "");
   void                check(void);
   std::string         finish(void);
   std::string         render(Format format, std::string indent);

   const char*         typeName(const Type _type);
   void                shortShow(std::string indent);
   void                show(std::string indent);
};

} // namespace orion

#endif
