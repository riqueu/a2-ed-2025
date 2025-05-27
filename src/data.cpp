#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "data.h"

using namespace DocReading;
using namespace std;

namespace DocReading {
    Doc* createDoc(int id) {
        Doc* newDoc = new Doc;

        newDoc->docID = id;
        newDoc->content = new vector<string>;
        
        return newDoc;
    };
}