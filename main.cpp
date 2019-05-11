// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            complain() << "-" << char (optopt) << ": invalid option"
                       << endl;
            break;
      }
   }
}


int main (int argc, char** argv) {
   sys_info::execname (argv[0]);
   scan_options (argc, argv);

   str_str_map test;
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      str_str_pair pair (*argp, to_string<int> (argp - argv));
      cout << "Before insert: " << pair << endl;
      test.insert (pair);
   }
   cout << endl;

   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = test.begin();
   itor = test.erase (itor);

    for (str_str_map::iterator itor = test.begin();
         itor != test.end(); ++itor) {
        cout << "During iteration: " << *itor << endl;
    }

    cout << endl << *test.find("one") << endl;


    for (str_str_map::iterator itor = test.begin();
         itor != test.end(); ++itor) {
        cout << "During iteration: " << *itor << endl;
    }

    cout << *itor<< " 1: " << endl;
    ++itor;
    cout << *itor<< " 2: " << endl;
    itor = test.erase(itor);
    cout << *itor<< " 3: " << endl ;

    cout << endl;
    for (str_str_map::iterator itor = test.begin();
         itor != test.end(); ++itor) {
        cout << "During iteration: " << *itor << endl;
    }
    cout << endl;
    for (str_str_map::iterator itor = test.begin();
         itor != test.end(); ++itor) {
        cout << "During iteration: " << *itor << endl;
    }
    cout <<endl;
    str_str_pair pair1 ("three", "3");
    str_str_pair pair2 ("for", "4");
    test.insert(pair1);
    test.insert(pair2);

    --itor;
    itor = test.erase(itor);
    ++itor;
    ++itor;
    itor = test.erase(itor);

    cout << endl;
    cout << *itor<< endl;
    for (str_str_map::iterator itor = test.begin();
         itor != test.end(); ++itor) {
        cout << "During iteration: " << *itor << endl;
    }


    cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

