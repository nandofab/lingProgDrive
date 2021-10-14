#ifndef DRIVEPP_H
    #define DRIVEPP_H

    #include "CPyTranslator.h"
    #include <iostream>
    #include <vector>
    #include <string>
    #include <string.h>
    #include "exceptions.h"
    
    using namespace std;

    class Drivepp{
        public:
            void receberComando(const string&,const vector<string>&);
        private:            
            CPyObject usePyDriveFunc(const string& ,const string& ,const vector <string>& );
    };

#endif