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

# ---------------------------------------------------------
# External dependency checks
# ---------------------------------------------------------

FIND_LIBRARY (HAVE_GTEST gtest PATHS /usr/lib /usr/lib64 /usr/local/lib64 /usr/local/lib)
if (HAVE_GTEST)
    MESSAGE("Using ${HAVE_GTEST} for Google Test")
else (HAVE_GTEST)
    MESSAGE("Not using the Google Test library")
endif (HAVE_GTEST)

find_library(GTESTMAIN_LIBRARY gtest_main
             PATHS /usr/lib64 /usr/local/lib64 /usr/local/lib)


find_path(GTEST_INCLUDE_DIR gtest/gtest.h
          PATHS /usr/includes 
          PATH_SUFFIXES gtest)

FIND_LIBRARY (HAVE_GMOCK gmock PATHS /usr/lib /usr/lib64 /usr/local/lib64 /usr/local/lib)
if (HAVE_GMOCK)
    MESSAGE("Using ${HAVE_GMOCK} for Google Mock")
else (HAVE_GMOCK)
    MESSAGE("Not using the Google Mock library")
endif (HAVE_GMOCK)

find_library(GMOCKMAIN_LIBRARY gmock_main
             PATHS /usr/lib64 /usr/local/lib64 /usr/local/lib)

find_path(GMOCK_INCLUDE_DIR gmock/gmock.h
          PATHS /usr/includes
          PATH_SUFFIXES gmock)

SET (SOURCES
    main_UnitTest.cpp
    testDataFromFile.cpp
    testInit.cpp
    unittest.cpp

    serviceRoutines/badVerbGetOnly_test.cpp
    serviceRoutines/badVerbPostOnly_test.cpp
    serviceRoutines/badVerbAllFour_test.cpp
    serviceRoutines/badVerbGetPostOnly_test.cpp
    serviceRoutines/badVerbGetPostDeleteOnly_test.cpp
    serviceRoutines/badVerbGetDeleteOnly_test.cpp
    serviceRoutines/badVerbGetPutDeleteOnly_test.cpp
    serviceRoutines/deleteIndividualContextEntity_test.cpp
    serviceRoutines/deleteIndividualContextEntityAttribute_test.cpp
    serviceRoutines/deleteIndividualContextEntityAttributes_test.cpp
    serviceRoutines/getContextEntitiesByEntityId_test.cpp
    serviceRoutines/getEntityByIdAttributeByName_test.cpp
    serviceRoutines/getContextEntityTypes_test.cpp
    serviceRoutines/postContextEntityTypes_test.cpp
    serviceRoutines/getContextEntityTypeAttributeContainer_test.cpp
    serviceRoutines/postContextEntityTypeAttributeContainer_test.cpp
    serviceRoutines/getContextEntityTypeAttribute_test.cpp
    serviceRoutines/postContextEntityTypeAttribute_test.cpp
    serviceRoutines/getIndividualContextEntity_test.cpp
    serviceRoutines/getContextEntityAttributes_test.cpp
    serviceRoutines/getIndividualContextEntityAttribute_test.cpp
    serviceRoutines/getIndividualContextEntityAttributes_test.cpp
    serviceRoutines/postContextEntitiesByEntityId_test.cpp
    serviceRoutines/postContextEntityAttributes_test.cpp
    serviceRoutines/postDiscoverContextAvailability_test.cpp
    serviceRoutines/postEntityByIdAttributeByName_test.cpp
    serviceRoutines/postIndividualContextEntity_test.cpp
    serviceRoutines/postIndividualContextEntityAttribute_test.cpp
    serviceRoutines/postIndividualContextEntityAttributes_test.cpp
    serviceRoutines/logTraceTreat_test.cpp
    serviceRoutines/logVerboseTreat_test.cpp
    serviceRoutines/postRegisterContext_test.cpp
    serviceRoutines/postSubscribeContext_test.cpp
    serviceRoutines/postSubscribeContextAvailability_test.cpp
    serviceRoutines/postUnsubscribeContext_test.cpp
    serviceRoutines/postUnsubscribeContextAvailability_test.cpp
    serviceRoutines/postUpdateContext_test.cpp
    serviceRoutines/postUpdateContextAvailabilitySubscription_test.cpp
    serviceRoutines/postUpdateContextSubscription_test.cpp
    serviceRoutines/putIndividualContextEntity_test.cpp
    serviceRoutines/putIndividualContextEntityAttributes_test.cpp
    serviceRoutines/putIndividualContextEntityAttribute_test.cpp
    serviceRoutines/postQueryContext_test.cpp
    serviceRoutines/getNgsi10ContextEntityTypes_test.cpp
    serviceRoutines/getNgsi10ContextEntityTypesAttribute_test.cpp
    serviceRoutines/putSubscriptionConvOp_test.cpp
    serviceRoutines/badNgsi10Request_test.cpp
    serviceRoutines/badNgsi9Request_test.cpp
    serviceRoutines/badRequest_test.cpp
    serviceRoutines/versionTreat_test.cpp
    serviceRoutines/exitTreat_test.cpp
    serviceRoutines/leakTreat_test.cpp
    serviceRoutines/statisticsTreat_test.cpp
    serviceRoutines/putAvailabilitySubscriptionConvOp_test.cpp
    serviceRoutines/deleteAttributeValueInstance_test.cpp
    serviceRoutines/putAttributeValueInstance_test.cpp
    serviceRoutines/getAttributeValueInstance_test.cpp

    convenience/Convenience_test.cpp
    convenienceMap/mapDeleteIndividualContextEntity_test.cpp
    convenienceMap/mapGetIndividualContextEntity_test.cpp
    convenienceMap/mapPostIndividualContextEntity_test.cpp
    convenienceMap/mapPutIndividualContextEntity_test.cpp

    convenienceMap/mapGetIndividualContextEntityAttribute_test.cpp
    convenienceMap/mapPostIndividualContextEntityAttribute_test.cpp

    convenienceMap/mapDeleteIndividualContextEntityAttributes_test.cpp
    convenienceMap/mapGetIndividualContextEntityAttributes_test.cpp
    convenienceMap/mapPostIndividualContextEntityAttributes_test.cpp
    convenienceMap/mapDeleteIndividualContextEntityAttribute_test.cpp

    convenience/AppendContextElementRequest_test.cpp
    convenience/AppendContextElementResponse_test.cpp
    convenience/ContextAttributeResponse_test.cpp
    convenience/ContextAttributeResponseVector_test.cpp
    convenience/UpdateContextAttributeRequest_test.cpp
    convenience/UpdateContextElementRequest_test.cpp
    convenience/UpdateContextElementResponse_test.cpp
    convenience/RegisterProviderRequest_test.cpp
    common/commonFormat_test.cpp
    common/commonGlobals_test.cpp
    common/commonString_test.cpp
    common/commonTag_test.cpp
    common/commonSem_test.cpp
    common/commonStatistics_test.cpp
    common/commonWsStrip_test.cpp

    ngsi9/RegisterContextRequest_test.cpp
    ngsi9/RegisterContextResponse_test.cpp
    ngsi9/DiscoverContextAvailabilityRequest_test.cpp
    ngsi9/DiscoverContextAvailabilityResponse_test.cpp
    ngsi9/SubscribeAvailabilityRequest_test.cpp
    ngsi9/SubscribeContextAvailabilityResponse_test.cpp
    ngsi9/NotifyContextAvailabilityRequest_test.cpp
    ngsi9/NotifyContextAvailabilityResponse_test.cpp
    ngsi9/UnsubscribeContextAvailabilityRequest_test.cpp
    ngsi9/UnsubscribeContextAvailabilityResponse_test.cpp
    ngsi9/UpdateContextAvailabilitySubscriptionRequest_test.cpp
    ngsi9/UpdateContextAvailabilitySubscriptionResponse_test.cpp

    ngsi10/QueryContextRequest_test.cpp
    ngsi10/QueryContextResponse_test.cpp
    ngsi10/NotifyContextRequest_test.cpp
    ngsi10/SubscribeContextRequest_test.cpp
    ngsi10/SubscribeContextResponse_test.cpp
    ngsi10/UnsubscribeContextRequest_test.cpp
    ngsi10/UnsubscribeContextResponse_test.cpp
    ngsi10/UpdateContextRequest_test.cpp
    ngsi10/UpdateContextResponse_test.cpp
    ngsi10/UpdateContextSubscriptionRequest_test.cpp
    ngsi10/UpdateContextSubscriptionResponse_test.cpp

    ngsi/ContextAttribute_test.cpp
    ngsi/ContextElement_test.cpp
    ngsi/NotifyCondition_test.cpp
    ngsi/AttributeAssociation_test.cpp
    ngsi/Association_test.cpp
    ngsi/AttributeAssociationList_test.cpp
    ngsi/AttributeDomainName_test.cpp
    ngsi/AttributeList_test.cpp
    ngsi/ConditionValueList_test.cpp
    ngsi/ContextAttributeVector_test.cpp
    ngsi/ContextElementResponse_test.cpp
    ngsi/ContextElementResponseVector_test.cpp
    ngsi/ContextRegistrationAttribute_test.cpp
    ngsi/ContextRegistrationAttributeVector_test.cpp
    ngsi/ContextRegistrationVector_test.cpp
    ngsi/ProvidingApplication_test.cpp
    ngsi/Duration_test.cpp
    ngsi/AttributeExpression_test.cpp
    ngsi/ContextElementVector_test.cpp
    ngsi/ContextRegistration_test.cpp
    ngsi/ContextRegistrationResponse_test.cpp
    ngsi/ContextRegistrationResponseVector_test.cpp
    ngsi/EntityId_test.cpp
    ngsi/Metadata_test.cpp
    ngsi/MetadataVector_test.cpp
    ngsi/NotifyConditionVector_test.cpp
    ngsi/Originator_test.cpp
    ngsi/Reference_test.cpp
    ngsi/Restriction_test.cpp
    ngsi/Request_test.cpp
    ngsi/RestrictionString_test.cpp
    ngsi/Scope_test.cpp
    ngsi/ScopeVector_test.cpp
    ngsi/StatusCode_test.cpp
    ngsi/SubscribeError_test.cpp
    ngsi/SubscriptionId_test.cpp
    ngsi/Throttling_test.cpp
    ngsi/UpdateActionType_test.cpp

    mongoBackend/mongoConfManOperations_test.cpp
    mongoBackend/mongoDiscoverContextAvailability_test.cpp
    mongoBackend/mongoOntimeintervalOperations_test.cpp
    mongoBackend/mongoQueryContext_test.cpp
    mongoBackend/mongoQueryContextCompoundValues_test.cpp
    mongoBackend/mongoQueryContextGeo_test.cpp
    mongoBackend/mongoRegisterContext_test.cpp
    mongoBackend/mongoRegisterContext_update_test.cpp
    mongoBackend/mongoSubscribeContextAvailability_test.cpp
    mongoBackend/mongoSubscribeContext_test.cpp
    mongoBackend/mongoUnsubscribeContextAvailability_test.cpp
    mongoBackend/mongoUnsubscribeContext_test.cpp
    mongoBackend/mongoUpdateContextAvailabilitySubscription_test.cpp
    mongoBackend/mongoUpdateContextSubscription_test.cpp
    mongoBackend/mongoUpdateContext_test.cpp
    mongoBackend/mongoUpdateContextGeo_test.cpp
    mongoBackend/mongoUpdateContext_withOnchangeSubscriptions_test.cpp
    mongoBackend/mongoUpdateContextCompoundValues_test.cpp
    mongoBackend/mongoNotifyContext_test.cpp
    mongoBackend/mongoNotifyContextAvailability_test.cpp

    parse/CompoundValueNode_test.cpp
    parse/compoundValue_test.cpp
    parse/nullTreat_test.cpp
    jsonParse/jsonRequest_test.cpp

    xmlParse/xmlAppendContextElementRequest_test.cpp
    xmlParse/xmlRegisterContextRequest_test.cpp
    xmlParse/xmlRegisterContextResponse_test.cpp
    xmlParse/xmlRequest_test.cpp
    xmlParse/xmlUpdateContextElementRequest_test.cpp
    xmlParse/xmlUpdateContextRequest_test.cpp

    rest/OrionError_test.cpp
    rest/Verb_test.cpp
    rest/restReply_test.cpp
    rest/RestService_test.cpp
)

SET (HEADERS
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_INCLUDE_DIR}
)

SET (STATIC_LIBS
    ${HAVE_GTEST}
    ${GTESTMAIN_LIBRARY}
    ${HAVE_GMOCK}
    ${GMOCKMAIN_LIBRARY}
    mongoBackend
    ngsiNotify
    jsonParse
    xmlParse
    parse
    convenience
    serviceRoutines
    convenienceMap
    rest
    ngsi9
    ngsi10
    ngsi
    common
    lm
    pa
    pthread
)

# Include directories
# ------------------------------------------------------------
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src/lib")
include_directories("${PROJECT_SOURCE_DIR}/src/app")
include_directories("${PROJECT_SOURCE_DIR}/test/unittests")
include_directories("${RAPIDXML_INCLUDE}")

# Lib directories
# ------------------------------------------------------------
link_directories("/usr/local/lib/")
link_directories("/usr/lib64/")


# flags
# ------------------------------------------------------------
add_definitions(-DUNIT_TEST)


# Executable declaration
# ------------------------------------------------------------

ADD_EXECUTABLE(unitTest ${SOURCES} ${HEADERS})

IF ((${DISTRO} STREQUAL "Ubuntu_13.04") OR (${DISTRO} STREQUAL "Ubuntu_12.04.1_LTS"))
  MESSAGE("Ubuntu DISTRO: '${DISTRO}'")
  TARGET_LINK_LIBRARIES(unitTest ${STATIC_LIBS} -lmicrohttpd -lmongoclient -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt -lpthread -lssl -lcrypto -lgnutls -lgcrypt)
ELSEIF(${DISTRO} STREQUAL "openSUSE_12.3")
  MESSAGE("openSUSE DISTRO: '${DISTRO}'")
  TARGET_LINK_LIBRARIES(unitTest ${STATIC_LIBS} -lmicrohttpd -lmongoclient -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt -lpthread -lssl -lcrypto)
ELSEIF(${DISTRO} STREQUAL "CentOS_6.3")
  MESSAGE("CentOS DISTRO: '${DISTRO}'")
  TARGET_LINK_LIBRARIES(unitTest ${STATIC_LIBS} -lmicrohttpd -lmongoclient -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt)
ELSE()
  MESSAGE("Other DISTRO: '${DISTRO}'")
  TARGET_LINK_LIBRARIES(unitTest ${STATIC_LIBS} -lmicrohttpd -lmongoclient -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt)
ENDIF()

