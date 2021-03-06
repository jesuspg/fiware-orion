# Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
#
# This file is part of Orion Context Broker.
#
# Orion Context Broker is free software: you can redistribute it and/or
# modify it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# Orion Context Broker is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
# General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
#
# For those usages not covered by this license please contact with
# fermin at tid dot es

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (SOURCES
versionTreat.cpp
exitTreat.cpp
leakTreat.cpp
logVerboseTreat.cpp
logTraceTreat.cpp
postRegisterContext.cpp
postDiscoverContextAvailability.cpp
getContextEntitiesByEntityId.cpp
postUnsubscribeContextAvailability.cpp
postSubscribeContextAvailability.cpp
postUpdateContextAvailabilitySubscription.cpp
postUpdateContext.cpp
postQueryContext.cpp
postSubscribeContext.cpp
postUpdateContextSubscription.cpp
postUnsubscribeContext.cpp
postContextEntitiesByEntityId.cpp
getContextEntityAttributes.cpp
postContextEntityAttributes.cpp
getEntityByIdAttributeByName.cpp
postEntityByIdAttributeByName.cpp
getContextEntityTypes.cpp
postContextEntityTypes.cpp
getContextEntityTypeAttribute.cpp
postContextEntityTypeAttribute.cpp
getIndividualContextEntity.cpp
putIndividualContextEntity.cpp
postIndividualContextEntity.cpp
getIndividualContextEntityAttributes.cpp
putIndividualContextEntityAttributes.cpp
putIndividualContextEntityAttribute.cpp
postIndividualContextEntityAttributes.cpp
deleteIndividualContextEntityAttributes.cpp
getIndividualContextEntityAttribute.cpp
postIndividualContextEntityAttribute.cpp
deleteIndividualContextEntityAttribute.cpp
deleteIndividualContextEntity.cpp
getNgsi10ContextEntityTypes.cpp
getNgsi10ContextEntityTypesAttribute.cpp
putSubscriptionConvOp.cpp
deleteSubscriptionConvOp.cpp
putAvailabilitySubscriptionConvOp.cpp
deleteAvailabilitySubscriptionConvOp.cpp
badVerbPostOnly.cpp
badVerbAllFour.cpp
badVerbGetPostOnly.cpp
badVerbGetPostDeleteOnly.cpp
badVerbGetOnly.cpp
badVerbGetDeleteOnly.cpp
badVerbPutDeleteOnly.cpp
badVerbGetPutDeleteOnly
badNgsi9Request.cpp
badNgsi10Request.cpp
badRequest.cpp
postNotifyContext.cpp
postNotifyContextAvailability.cpp
statisticsTreat.cpp
getAttributeValueInstance.cpp
putAttributeValueInstance.cpp
deleteAttributeValueInstance.cpp
)

SET (HEADERS
versionTreat.h
exitTreat.h
logVerboseTreat.h
logTraceTreat.h
postRegisterContext.h
postDiscoverContextAvailability.h
getContextEntitiesByEntityId.h
postUnsubscribeContextAvailability.h
postSubscribeContextAvailability.h
postUpdateContextAvailabilitySubscription.h
postUpdateContext.h
postQueryContext.h
postSubscribeContext.h
postUpdateContextSubscription.h
postUnsubscribeContext.h
postContextEntitiesByEntityId.h
getContextEntityAttributes.h
postContextEntityAttributes.h
getEntityByIdAttributeByName.h
postEntityByIdAttributeByName.h
getContextEntityTypes.h
postContextEntityTypes.h
getContextEntityTypeAttribute.h
postContextEntityTypeAttribute.h
getIndividualContextEntity.h
putIndividualContextEntity.h
postIndividualContextEntity.h
getIndividualContextEntityAttributes.h
putIndividualContextEntityAttributes.h
putIndividualContextEntityAttribute.h
postIndividualContextEntityAttributes.h
deleteIndividualContextEntityAttributes.h
getIndividualContextEntityAttribute.h
postIndividualContextEntityAttribute.h
deleteIndividualContextEntityAttribute.h
deleteIndividualContextEntity.h
getNgsi10ContextEntityTypes.h
badVerbPostOnly.h
badVerbAllFour.h
badVerbGetPostOnly.h
badVerbGetPostDeleteOnly.h
badVerbGetOnly.h
badVerbGetDeleteOnly.h
badVerbPutDeleteOnly.h
badNgsi9Request.h
badNgsi10Request.h
badRequest.h
postNotifyContext.h
postNotifyContextAvailability.h
statisticsTreat.h
)



# Include directories
# -----------------------------------------------------------------
include_directories("${PROJECT_SOURCE_DIR}/src/lib")
include_directories("${RAPIDXML_INCLUDE}")

# Library declaration
# -----------------------------------------------------------------
ADD_LIBRARY(serviceRoutines STATIC ${SOURCES} ${HEADERS})
