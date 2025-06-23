INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
  )

SET (newborn_core_HEADERS
    NewbornAStar.hpp
    NewbornAlgorithm.hpp
    NewbornArray.hpp
    NewbornAssetPath.hpp
    NewbornAtomicSharedPtr.hpp
    NewbornAudio.hpp
    NewbornBTree.hpp
    NewbornBTreeDatabase.hpp
    NewbornBiMap.hpp
    NewbornBlockAllocator.hpp
    NewbornBuffer.hpp
    NewbornByteArray.hpp
    NewbornBytes.hpp
    NewbornCasting.hpp
    NewbornColor.hpp
    NewbornCompression.hpp
    NewbornConfig.hpp
    NewbornCurve25519.hpp
    NewbornDataStream.hpp
    NewbornDataStreamDevices.hpp
    NewbornDataStreamExtra.hpp
    NewbornDirectives.hpp
    NewbornDynamicLib.hpp
    NewbornEither.hpp
    NewbornEncode.hpp
    NewbornException.hpp
    NewbornFile.hpp
    NewbornFlatHashMap.hpp
    NewbornFlatHashSet.hpp
    NewbornFont.hpp
    NewbornFormat.hpp
    NewbornHash.hpp
    NewbornHostAddress.hpp
    NewbornIODevice.hpp
    NewbornIdMap.hpp
    NewbornImage.hpp
    NewbornImageProcessing.hpp
    NewbornImageScaling.hpp
    NewbornInputEvent.hpp
    NewbornInterpolation.hpp
    NewbornRefPtr.hpp
    NewbornIterator.hpp
    NewbornJson.hpp
    NewbornJsonBuilder.hpp
    NewbornJsonExtra.hpp
    NewbornJsonParser.hpp
    NewbornJsonPath.hpp
    NewbornJsonPatch.hpp
    NewbornJsonRpc.hpp
    NewbornFormattedJson.hpp
    NewbornLexicalCast.hpp
    NewbornLine.hpp
    NewbornList.hpp
    NewbornListener.hpp
    NewbornLockFile.hpp
    NewbornLogging.hpp
    NewbornLruCache.hpp
    NewbornLua.hpp
    NewbornLuaConverters.hpp
    NewbornMap.hpp
    NewbornMathCommon.hpp
    NewbornMatrix3.hpp
    NewbornMaybe.hpp
    NewbornMemory.hpp
    NewbornMultiArray.hpp
    NewbornMultiArrayInterpolator.hpp
    NewbornMultiTable.hpp
    NewbornNetCompatibility.hpp
    NewbornNetElement.hpp
    NewbornNetElementBasicFields.hpp
    NewbornNetElementContainers.hpp
    NewbornNetElementDynamicGroup.hpp
    NewbornNetElementExt.hpp
    NewbornNetElementFloatFields.hpp
    NewbornNetElementGroup.hpp
    NewbornNetElementSignal.hpp
    NewbornNetElementSyncGroup.hpp
    NewbornNetElementSystem.hpp
    NewbornNetElementTop.hpp
    NewbornNetImpl.hpp
    NewbornObserverStream.hpp
    NewbornOptionParser.hpp
    NewbornOrderedMap.hpp
    NewbornOrderedSet.hpp
    NewbornOutputProxy.hpp
    NewbornParametricFunction.hpp
    NewbornPch.hpp
    NewbornPeriodic.hpp
    NewbornPeriodicFunction.hpp
    NewbornPerlin.hpp
    NewbornPoly.hpp
    NewbornPythonic.hpp
    NewbornRandom.hpp
    NewbornRandomPoint.hpp
    NewbornRect.hpp
    NewbornRpcPromise.hpp
    NewbornRpcThreadPromise.hpp
    NewbornSectorArray2D.hpp
    NewbornSecureRandom.hpp
    NewbornSet.hpp
    NewbornSha256.hpp
    NewbornShellParser.hpp
    NewbornSignalHandler.hpp
    NewbornSocket.hpp
    NewbornSpatialHash2D.hpp
    NewbornSpline.hpp
    NewbornStaticRandom.hpp
    NewbornStaticVector.hpp
    NewbornString.hpp
    NewbornStringView.hpp
    NewbornStrongTypedef.hpp
    NewbornTcp.hpp
    NewbornText.hpp
    NewbornThread.hpp
    NewbornTickRateMonitor.hpp
    NewbornTime.hpp
    NewbornTtlCache.hpp
    NewbornUdp.hpp
    NewbornUnicode.hpp
    NewbornUuid.hpp
    NewbornVector.hpp
    NewbornVersion.hpp
    NewbornVlqEncoding.hpp
    NewbornWeightedPool.hpp
    NewbornWorkerPool.hpp
    NewbornXXHash.hpp
    NewbornZSTDCompression.hpp
    scripting/NewbornUtilityLuaBindings.hpp
  )

SET (newborn_core_SOURCES
    NewbornAudio.cpp
    NewbornAssetPath.cpp
    NewbornBTreeDatabase.cpp
    NewbornBuffer.cpp
    NewbornByteArray.cpp
    NewbornColor.cpp
    NewbornCompression.cpp
    NewbornCurve25519.cpp
    NewbornDataStream.cpp
    NewbornDataStreamDevices.cpp
    NewbornDirectives.cpp
    NewbornEncode.cpp
    NewbornFile.cpp
    NewbornFont.cpp
    NewbornHostAddress.cpp
    NewbornIODevice.cpp
    NewbornImage.cpp
    NewbornImageProcessing.cpp
    NewbornImageScaling.cpp
    NewbornInputEvent.cpp
    NewbornJson.cpp
    NewbornJsonBuilder.cpp
    NewbornJsonExtra.cpp
    NewbornJsonPath.cpp
    NewbornJsonPatch.cpp
    NewbornJsonRpc.cpp
    NewbornFormattedJson.cpp
    NewbornLexicalCast.cpp
    NewbornListener.cpp
    NewbornLogging.cpp
    NewbornLua.cpp
    NewbornLuaConverters.cpp
    NewbornMemory.cpp
    NewbornNetCompatibility.cpp
    NewbornNetElement.cpp
    NewbornNetElementBasicFields.cpp
    NewbornNetElementGroup.cpp
    NewbornNetElementSyncGroup.cpp
    NewbornOptionParser.cpp
    NewbornPerlin.cpp
    NewbornRandom.cpp
    NewbornSha256.cpp
    NewbornShellParser.cpp
    NewbornSocket.cpp
    NewbornString.cpp
    NewbornStringView.cpp
    NewbornTcp.cpp
    NewbornText.cpp
    NewbornThread.cpp
    NewbornTime.cpp
    NewbornTickRateMonitor.cpp
    NewbornUdp.cpp
    NewbornUnicode.cpp
    NewbornUuid.cpp
    NewbornWorkerPool.cpp
    NewbornZSTDCompression.cpp
    scripting/NewbornUtilityLuaBindings.cpp
  )

IF (NEWBORN_SYSTEM_FAMILY_UNIX)
  SET (newborn_core_SOURCES ${newborn_core_SOURCES}
      NewbornDynamicLib_unix.cpp
      NewbornException_unix.cpp
      NewbornFile_unix.cpp
      NewbornLockFile_unix.cpp
      NewbornSecureRandom_unix.cpp
      NewbornSignalHandler_unix.cpp
      NewbornThread_unix.cpp
      NewbornTime_unix.cpp
    )
ELSEIF (NEWBORN_SYSTEM_FAMILY_WINDOWS)
  SET (newborn_core_HEADERS ${newborn_core_HEADERS}
      NewbornString_windows.hpp
    )

  SET (newborn_core_SOURCES ${newborn_core_SOURCES}
      NewbornDynamicLib_windows.cpp
      NewbornFile_windows.cpp
      NewbornLockFile_windows.cpp
      NewbornSignalHandler_windows.cpp
      NewbornString_windows.cpp
      NewbornThread_windows.cpp
      NewbornTime_windows.cpp
      NewbornException_windows.cpp
      NewbornSecureRandom_windows.cpp
    )

ENDIF ()

CONFIGURE_FILE (NewbornVersion.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/NewbornVersion.cpp)
ADD_LIBRARY (newborn_core OBJECT ${newborn_core_SOURCES} ${newborn_core_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/NewbornVersion.cpp)

IF(NEWBORN_PRECOMPILED_HEADERS)
  TARGET_PRECOMPILE_HEADERS (newborn_core PUBLIC NewbornPch.hpp)
ENDIF()
IF(NEWBORN_COMPILER STREQUAL "gnu")
  SET_SOURCE_FILES_PROPERTIES(NewbornImageScaling.cpp PROPERTIES COMPILE_FLAGS "-O2")
ENDIF()
IF(NEWBORN_USE_JEMALLOC AND JEMALLOC_IS_PREFIXED)
  SET_SOURCE_FILES_PROPERTIES(NewbornMemory.cpp PROPERTIES
          COMPILE_DEFINITIONS NEWBORN_JEMALLOC_IS_PREFIXED
          )
ENDIF()