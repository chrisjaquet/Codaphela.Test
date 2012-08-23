SET(APP_NAME TestBaseLib)
OPTION(${PROJECT_NAME}_BUILD_${APP_NAME} "Set this to ON to build ${APP_NAME}." ON)

IF(${${PROJECT_NAME}_BUILD_${APP_NAME}})
    SET(HEADER_FILES
                        TestArrayBit.h
                        TestArrayEmbedded.h
                        TestArrayInt.h
                        TestArrayInt2D.h
                        TestArrayLong.h
                        TestArrayPrimitiveTemplate.h
                        TestArrayTemplate.h
                        TestASCIITree.h
                        TestBufferedFile.h
                        TestChunkFile.h
                        TestCSVFileEditable.h
                        TestDate.h
                        TestDenseArrayTemplate.h
                        TestDiskFile.h
                        TestFileFinder.h
                        TestFileSystem.h
                        TestFileUtil.h
                        TestFreeList.h
                        TestIntegerHelper.h
                        TestLinkListAligned.h
                        TestLinkListTemplate.h
                        TestMapInt.h
                        TestMapPtr.h
                        TestMD5File.h
                        TestMemory.h
                        TestMemoryCache.h
                        TestMemoryFile.h
                        TestMemoryStack.h
                        TestNumbers.h
                        TestPackFile.h
                        TestScratchPad.h
                        TestSorting.h
                        TestSparseArrayTemplate.h
                        TestStringHelper.h
                        TestTreeTemplate.h
                    )

    SET(SOURCE_FILES 
                        TestArrayBit.cpp
                        TestArrayEmbedded.cpp
                        TestArrayInt.cpp
                        TestArrayInt2D.cpp
                        TestArrayLong.cpp
                        TestArrayPrimitiveTemplate.cpp
                        TestArrayTemplate.cpp
                        TestASCIITree.cpp
                        TestBaseLib.cpp
                        TestBufferedFile.cpp
                        TestChunkFile.cpp
                        TestCSVFileEditable.cpp
                        TestDate.cpp
                        TestDenseArrayTemplate.cpp
                        TestDiskFile.cpp
                        TestFileFinder.cpp
                        TestFileSystem.cpp
                        TestFileUtil.cpp
                        TestFreeList.cpp
                        TestIntegerHelper.cpp
                        TestLinkListAligned.cpp
                        TestLinkListTemplate.cpp
                        TestMapInt.cpp
                        TestMapPtr.cpp
                        TestMD5File.cpp
                        TestMemory.cpp
                        TestMemoryCache.cpp
                        TestMemoryFile.cpp
                        TestMemoryStack.cpp
                        TestNumbers.cpp
                        TestPackFile.cpp
                        TestScratchPad.cpp
                        TestSorting.cpp
                        TestSparseArrayTemplate.cpp
                        TestStringHelper.cpp
                        TestTreeTemplate.cpp
                    )
    SET(ASSET_FILES
                        Test.txt
                        Finder/Ants.rar
                        Finder/Ants.txt
                        Finder/Echo.rar
                        Finder/File.txt
                        Finder/Glenmark.wav
                        Finder/Last.txt
                        Finder/March.rar
                        Finder/Marching.txt
                        Finder/Ninja.txt
                        Finder/Lord/1.rar
                        Finder/Rising/2.rar
                        Finder/Storm/3.rar
                        InFile/Giana/Brothers.PAK
                        InFile/Giana/Sisters.PAK
                        InFile/Giana/Sisters/Document.txt
                        Input/Test.PAK
                        PackFile/Test.PAK
                    )

    IF(WIN32)
        ADD_EXECUTABLE(${APP_NAME} WIN32 ${SOURCE_FILES} ${HEADER_FILES})
    ELSE()
        ADD_EXECUTABLE(${APP_NAME} ${SOURCE_FILES} ${HEADER_FILES})
    ENDIF()

    # Library Dependency
    FIND_LIBRARY(BASELIB_LIB BaseLib ${CMAKE_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib64)
    FIND_LIBRARY(BASELIB_LIB_DEBUG BaseLibd ${CMAKE_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib64)
    FIND_PATH(CODAPHELA_INCLUDE_PATH BaseLib/Define.h ${CMAKE_INSTALL_PREFIX}/include ${CMAKE_INSTALL_PREFIX}/include/CodaphelaLibrary)
    IF(NOT CODAPHELA_INCLUDE_PATH)
        MESSAGE(FATAL_ERROR "Could Not find the Codaphela Library header folder")
    ELSE()
        INCLUDE_DIRECTORIES(${CODAPHELA_INCLUDE_PATH})
    ENDIF()
    IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
        IF(NOT BASELIB_LIB_DEBUG)
            MESSAGE(WARNING "Building in Debug mode but the path to the Codaphela BaseLib Debug library is not found")
            IF(NOT BASELIB_LIB)
                MESSAGE(FATAL_ERROR "Path to the Codaphela BaseLib library is necessary")
            ENDIF()
            TARGET_LINK_LIBRARIES(${APP_NAME} ${BASELIB_LIB})
        ELSE()
            TARGET_LINK_LIBRARIES(${APP_NAME} ${BASELIB_LIB_DEBUG})
        ENDIF()
    ELSE()
        IF(NOT BASELIB_LIB)
            MESSAGE(FATAL_ERROR "Path to the Codaphela BaseLib library is necessary")
        ENDIF()
        TARGET_LINK_LIBRARIES(${APP_NAME} ${BASELIB_LIB})
    ENDIF()   
    
    # Installation
    INSTALL(TARGETS ${APP_NAME}
            LIBRARY DESTINATION lib${LIB_ARCH}
            ARCHIVE DESTINATION lib${LIB_ARCH}
            RUNTIME DESTINATION bin)
    INSTALL(FILES ${ASSET_FILES}
            DESTINATION .)
ENDIF()

