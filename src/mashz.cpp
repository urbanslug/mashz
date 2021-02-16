#include <iostream>
using namespace std;

/*
  Both these attempts at including lastz functions
  fail with the rrror commented out below
 */

// #include "lastz/src/lastz.h"
// extern "C" {
// #include "lastz/src/lastz.h"
// }


int main() {
  cout << "lastz!" << endl;
  return 0;
}

/*
[ 50%] Building CXX object CMakeFiles/mashz.dir/src/mashz.cpp.o
In file included from /home/njagi/src/mashz/src/lastz/src/lastz.h:12,
                 from /home/njagi/src/mashz/src/mashz.cpp:8:
/home/njagi/src/mashz/src/lastz/src/dna_utilities.h:296:46: error: expected ‘,’ or ‘...’ before ‘template’
  296 | scoreset*   new_dna_score_set         (score template[4][4],
      |                                              ^~~~~~~~
In file included from /home/njagi/src/mashz/src/lastz/src/pos_table.h:14,
                 from /home/njagi/src/mashz/src/lastz/src/lastz.h:14,
                 from /home/njagi/src/mashz/src/mashz.cpp:8:
/home/njagi/src/mashz/src/lastz/src/sequences.h:481:7: error: declaration of ‘hsx seq::hsx’ changes meaning of ‘hsx’ [-fpermissive]
  481 |  hsx  hsx;    //     additional info for hsx files (only
      |       ^~~
/home/njagi/src/mashz/src/lastz/src/sequences.h:369:4: note: ‘hsx’ declared here as ‘typedef struct hsx hsx’
  369 |  } hsx;
      |    ^~~
/home/njagi/src/mashz/src/lastz/src/sequences.h:513:8: error: declaration of ‘chore seq::chore’ changes meaning of ‘chore’ [-fpermissive]
  513 |  chore chore;    //     the current alignment chore (valid only
      |        ^~~~~
/home/njagi/src/mashz/src/lastz/src/sequences.h:228:4: note: ‘chore’ declared here as ‘typedef struct chore chore’
  228 |  } chore;
      |    ^~~~~
In file included from /home/njagi/src/mashz/src/lastz/src/lastz.h:18,
                 from /home/njagi/src/mashz/src/mashz.cpp:8:
/home/njagi/src/mashz/src/lastz/src/masking.h:56:7: error: declaration of ‘seq* pmiInfo::seq’ changes meaning of ‘seq’ [-fpermissive]
   56 |  seq* seq;   // the sequence that has been masked
      |       ^~~
In file included from /home/njagi/src/mashz/src/lastz/src/pos_table.h:14,
                 from /home/njagi/src/mashz/src/lastz/src/lastz.h:14,
                 from /home/njagi/src/mashz/src/mashz.cpp:8:
/home/njagi/src/mashz/src/lastz/src/sequences.h:579:4: note: ‘seq’ declared here as ‘typedef struct seq seq’
  579 |  } seq;
      |    ^~~

 */
