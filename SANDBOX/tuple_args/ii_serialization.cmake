#========================================================================================
#========================================================================================


#========================================================================================

if ( NOT  V_II_TTT_INCLUDED )
    set ( V_II_TTT_INCLUDED TRUE )

    message( "Include TTTTTTTTTTt..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/c++11/c++11.cmake" )
    include( "${VLIBS_DIR}/vcat/vcat.cmake" )
    include( "${VLIBS_DIR}/vstring/vstring.cmake" )
    include( "${VLIBS_DIR}/vcrc/vcrc.cmake" )
    include( "${VLIBS_DIR}/vrandom/vrandom.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${TEST_II_DIR}")

    
    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/vserializable.h")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/serialization/serialization_type_traits.h")
    set(V_SOURCES ${V_SOURCES} "${TEST_II_DIR}/serialization/serialization_type_traits.cpp")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/serialization/serialization_writebuffer.h")
    set(V_SOURCES ${V_SOURCES} "${TEST_II_DIR}/serialization/serialization_writebuffer.cpp")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/serialization/serialization_encoder.h")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/serialization/serialization_readbuffer.h")
    set(V_SOURCES ${V_SOURCES} "${TEST_II_DIR}/serialization/serialization_readbuffer.cpp")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/serialization/serialization_decoder.h")
    set(V_SOURCES ${V_SOURCES} "${TEST_II_DIR}/serialization/serialization_decoder.cpp")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/serialization/serialization_hash.h")
    set(V_SOURCES ${V_SOURCES} "${TEST_II_DIR}/serialization/serialization_hash.cpp")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/ii_udp_packets.h")
    set(V_SOURCES ${V_SOURCES} "${TEST_II_DIR}/ii_udp_packets.cpp")

    set(V_HEADERS ${V_HEADERS} "${TEST_II_DIR}/ii_udp_packets_unmerge.h")
    set(V_SOURCES ${V_SOURCES} "${TEST_II_DIR}/ii_udp_packets_unmerge.cpp")

    set(V_HEADERS ${V_HEADERS}
        "${TEST_II_DIR}/serialization/serialization_type_signature.h")
    set(V_SOURCES ${V_SOURCES}
        "${TEST_II_DIR}/serialization/serialization_type_signature.cpp")

    set(V_HEADERS ${V_HEADERS}
        "${TEST_II_DIR}/serialization/serialization_type_compare.h")
    set(V_SOURCES ${V_SOURCES}
        "${TEST_II_DIR}/serialization/serialization_type_compare.cpp")

    set(V_HEADERS ${V_HEADERS}
        "${TEST_II_DIR}/serialization/serialization_serializable_code_generator.h")
    set(V_SOURCES ${V_SOURCES}
        "${TEST_II_DIR}/serialization/serialization_serializable_code_generator.cpp")

    set(V_HEADERS ${V_HEADERS}
        "${TEST_II_DIR}/decodertransmitter.h")
    set(V_SOURCES ${V_SOURCES}
        "${TEST_II_DIR}/decodertransmitter.cpp")

    set(V_HEADERS ${V_HEADERS}
        "${TEST_II_DIR}/transmitterbychannels.h")
    set(V_SOURCES ${V_SOURCES}
        "${TEST_II_DIR}/transmitterbychannels.cpp")

    set(V_HEADERS ${V_HEADERS}
        "${TEST_II_DIR}/serialization/channels_udp_receiver.h")
    set(V_SOURCES ${V_SOURCES}
        "${TEST_II_DIR}/serialization/channels_udp_receiver.cpp")


    message( "TEST included" )

endif()
# vcat.cmake
#========================================================================================
