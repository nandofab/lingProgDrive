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
                return "Quantidade de argumentos inválido!\n\tPara mais informações sobre funcionamento desse programa digite ./Drivepp help";
            }
    };

    class pyFuncInexistenteException : public exception{
        public:
            virtual const char* what() const throw() {
                return "pyFuncInexistenteException!";
            }
    };

    class MimeTypeFileException : public exception{
        public:
            virtual const char* what() const throw() {
                return "MimeTypeFileException!";
            }
    };  

    class MimeTypeFileNotFound : public exception{
        public:
            virtual const char* what() const throw() {
                return "Arquivo para uplaod não encontrado!\n\tPara mais informações sobre funcionamento desse programa digite ./Drivepp help";
            }
    }; 

    class PathNotFound : public exception{
        public:
            virtual const char* what() const throw() {
                return "PathNotFound!";
            }
    }; 
    class DrivePathIsNotFolder : public exception{
        public:
            virtual const char* what() const throw() {
                return "DrivePathIsNotFolder!";
            }
    };
    class DrivePathIsNotFile : public exception{
        public:
            virtual const char* what() const throw() {
                return "DrivePathIsNotFile!";
            }
    };
    class UnknownError : public exception{
        public:
            virtual const char* what() const throw() {
                return "UnknownError!";
            }
    };
    class FileNotFound : public exception{
        public:
            virtual const char* what() const throw() {
                return "FileNotFound!";
            }
    };  

    
    
    
#endif