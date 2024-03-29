set(VERSION_MAJOR 1)
set(VERSION_MINOR 04)
set(VERSION_SUBMINOR 12)
set(REVISION_DATE 20210209)
set(SUBVERSION_REV "")

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(mashz-lastz VERSION 1.04.12)

set(CMAKE_C_FLAGS "-O3 -Wall -Wextra -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE \
                   -DVERSION_MAJOR=${VERSION_MAJOR} \
                   -DVERSION_MAJOR=${VERSION_MAJOR} \
                   -DVERSION_MINOR=${VERSION_MINOR} \
                   -DVERSION_SUBMINOR=${VERSION_SUBMINOR} \
                   -DREVISION_DATE=${REVISION_DATE} \
                   -DSUBVERSION_REV=${SUBVERSION_REV}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
  src/lastz.c
  src/infer_scores.c
  src/seeds.c
  src/pos_table.c
  src/quantum.c
  src/seed_search.c
  src/diag_hash.c
  src/chain.c
  src/gapped_extend.c
  src/tweener.c
  src/masking.c
  src/segment.c
  src/edit_script.c
  src/identity_dist.c
  src/coverage_dist.c
  src/continuity_dist.c
  src/output.c
  src/gfa.c
  src/lav.c
  src/axt.c
  src/maf.c
  src/cigar.c
  src/sam.c
  src/genpaf.c
  src/text_align.c
  src/align_diffs.c
  src/utilities.c
  src/dna_utilities.c
  src/sequences.c
  src/capsule.c)

add_executable(mashz-lastz ${SOURCES})
target_link_libraries(mashz-lastz m)
