// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string, string>;
using str_str_pair = str_str_map::value_type;

void scan_options(int argc, char **argv) {
    opterr = 0;
    for (;;) {
        int option = getopt(argc, argv, "@:");
        if (option == EOF) break;
        switch (option) {
            case '@':
                debugflags::setflags(optarg);
                break;
            default:
                complain() << "-" << char(optopt) << ": invalid option"
                           << endl;
                break;
        }
    }
}

void process_file(istream &s, string name) {
    string line;
    int i = 0;
    while (getline(s, line)) {
        cout << name << ": " << i++ << ": " << line << endl;
    }
}


int main(int argc, char **argv) {
    sys_info::execname(argv[0]);
    scan_options(argc, argv);

    if (argc == 1) {
        process_file(cin, "-");
    } else {
        for (char **argp = &argv[optind]; argp != &argv[argc]; ++argp) {
            ifstream myfile;
            myfile.open(*argp);

            if (myfile.fail()) {
                cerr << "Can't open file " << *argp << endl;
                continue;
            }

            istream &s = myfile;
            process_file(s, *argp);
            myfile.close();
        }
    }


    cout << "EXIT_SUCCESS" << endl;
    return EXIT_SUCCESS;
}

