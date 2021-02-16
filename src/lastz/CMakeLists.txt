set(VERSION_MAJOR 1)
set(VERSION_MINOR 04)
set(VERSION_SUBMINOR 12)
set(REVISION_DATE 20210209)
set(SUBVERSION_REV "")

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(lastz VERSION 1.04.12)

# set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "-O3 -Wall -Wextra -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE \
                   -DVERSION_MAJOR=${VERSION_MAJOR} \
                   -DVERSION_MAJOR=${VERSION_MAJOR} \
                   -DVERSION_MINOR=${VERSION_MINOR} \
                   -DVERSION_SUBMINOR=${VERSION_SUBMINOR} \
                   -DREVISION_DATE=${REVISION_DATE} \
                   -DSUBVERSION_REV=${SUBVERSION_REV}")

# set(ENV{LASTZ_INSTALL} ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(LASTZ_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/lastz/src)
# set(LASTZ_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(SOURCES
  ${LASTZ_SOURCE_DIR}/lastz.c
  ${LASTZ_SOURCE_DIR}/infer_scores.c
  ${LASTZ_SOURCE_DIR}/seeds.c
  ${LASTZ_SOURCE_DIR}/pos_table.c
  ${LASTZ_SOURCE_DIR}/quantum.c
  ${LASTZ_SOURCE_DIR}/seed_search.c
  ${LASTZ_SOURCE_DIR}/diag_hash.c
  ${LASTZ_SOURCE_DIR}/chain.c
  ${LASTZ_SOURCE_DIR}/gapped_extend.c
  ${LASTZ_SOURCE_DIR}/tweener.c
  ${LASTZ_SOURCE_DIR}/masking.c
  ${LASTZ_SOURCE_DIR}/segment.c
  ${LASTZ_SOURCE_DIR}/edit_script.c
  ${LASTZ_SOURCE_DIR}/identity_dist.c
  ${LASTZ_SOURCE_DIR}/coverage_dist.c
  ${LASTZ_SOURCE_DIR}/continuity_dist.c
  ${LASTZ_SOURCE_DIR}/output.c
  ${LASTZ_SOURCE_DIR}/gfa.c
  ${LASTZ_SOURCE_DIR}/lav.c
  ${LASTZ_SOURCE_DIR}/axt.c
  ${LASTZ_SOURCE_DIR}/maf.c
  ${LASTZ_SOURCE_DIR}/cigar.c
  ${LASTZ_SOURCE_DIR}/sam.c
  ${LASTZ_SOURCE_DIR}/genpaf.c
  ${LASTZ_SOURCE_DIR}/text_align.c
  ${LASTZ_SOURCE_DIR}/align_diffs.c
  ${LASTZ_SOURCE_DIR}/utilities.c
  ${LASTZ_SOURCE_DIR}/dna_utilities.c
  ${LASTZ_SOURCE_DIR}/sequences.c
  ${LASTZ_SOURCE_DIR}/capsule.c)


add_executable(lastz ${SOURCES})
# set(CMAKE_C_FLAGS "-c ${CMAKE_C_FLAGS}")

add_library(lastz_lib ${SOURCES})
set_target_properties(lastz_lib PROPERTIES OUTPUT_NAME "lastz")

# execute_process (COMMAND make)
# execute_process (COMMAND make install)
