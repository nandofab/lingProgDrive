#ifndef DRIVEPP_H
    #define DRIVEPP_H

    #include "CPyTranslator.h"
    #include <iostream>
    #include <vector>
    #include <string>
    #include <string.h>
    #include "exceptions.h"
    #include "MimeTypes.h"
    
    using namespace std;

    class Drivepp{
        public:
            CPyObject receberComando(const string&,vector<string>&);
        private:            
            CPyObject usePyDriveFunc(const string& ,const string& ,const vector <string>& );
    };

#endif