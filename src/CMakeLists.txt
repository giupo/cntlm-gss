set(SRCDIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB MAIN CONFIGURE_DEPENDES  ${SRCDIR}/*.*)
option(WITH_KERBEROS "Compile with Kerberos Support" OFF)

if(WITH_KERBEROS)
  message("Kerberos support ON")
  add_definitions(-DENABLE_KERBEROS)
else()
  message("Kerberos support OFF")
  list(REMOVE_ITEM MAIN ${SRCDIR}/kerberos.c)
endif()

list(REMOVE_ITEM MAIN kerberos.c)

source_group(cntlm FILES ${MAIN})

add_executable (cntlm ${MAIN})
set_property(TARGET cntlm PROPERTY C_STANDARD 99)

target_include_directories(cntlm PRIVATE $CMAKE_SOURCE_DIR/src)
find_package(Threads REQUIRED)

target_link_libraries(cntlm PRIVATE Threads::Threads)
target_link_libraries(cntlm PRIVATE zf_log)

if (WITH_KERBEROS)
  target_link_libraries(cntlm PRIVATE "gssapi_krb5")
endif()


