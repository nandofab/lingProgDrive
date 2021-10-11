#ifndef EXCEPTION_H
    #define EXCEPTION_H
    
    #include <iostream>
    #include <exception>

    using namespace std;

    class PyModuleException : public exception{
        public:
            virtual const char* what() const throw() {
                return "PyModuleException!";
            }
    };


    class PyFunctionException : public exception{
        public:
            virtual const char* what() const throw() {
                return "PyFunctionException!";
            }
    };

    class PyValueException: public exception{
        public:
            virtual const char* what() const throw() {
                return "PyValueException!";
            }
    };


    class pyArgsException : public exception{
        public:
            virtual const char* what() const throw() {
                return "pyArgsException!";
            }
    };

    class cArgsException : public exception{
        public:
            virtual const char* what() const throw() {
                return "cArgsException!";
            }
    };

    class pyFuncInexistenteException : public exception{
        public:
            virtual const char* what() const throw() {
                return "pyFuncInexistenteException!";
            }
    };

    
#endif