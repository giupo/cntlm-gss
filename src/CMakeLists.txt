set(SRCDIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB MAIN CONFIGURE_DEPENDES  ${SRCDIR}/*.*)
source_group(cntlm FILES ${MAIN})

add_executable (cntlm ${MAIN})
set_property(TARGET cntlm PROPERTY C_STANDARD 99)

target_include_directories(cntlm PRIVATE $CMAKE_SOURCE_DIR/src)
find_package(Threads REQUIRED)

target_link_libraries(cntlm PRIVATE Threads::Threads)
# This is junk, but I dunno how to find_package for the following lib
target_link_libraries(cntlm PRIVATE "gssapi_krb5")