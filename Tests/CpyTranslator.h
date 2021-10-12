#ifndef CPY_TRANSLATOR_H
    #define CPY_TRANSLATOR_H

    #define PY_SSIZE_T_CLEAN
    #include <Python.h>
    #include <vector>
    #include "exceptions.h"

    class CPyInstance{
        public:
        CPyInstance(){
            Py_Initialize();
        }

        ~CPyInstance(){
            Py_Finalize();
        }
    };


    class CPyObject{
        private:
            PyObject *p;
        public:
            CPyObject() : p(NULL){}
            CPyObject(PyObject* _p) : p(_p){}
            
            ~CPyObject(){
                Release();
            }

            PyObject* getObject(){
                return p;
            }

            PyObject* setObject(PyObject* _p){
                return (p=_p);
            }

            PyObject* AddRef(){
                if(p)
                    Py_INCREF(p);
                return p;
            }

            void Release(){
                if(p)
                    Py_DECREF(p);
                p= NULL;
            }

            PyObject* operator ->(){
                return p;
            }

            bool is(){
                return p ? true : false;
            }

            operator PyObject*(){
                return p;
            }

            PyObject* operator = (PyObject* pp){
                p = pp;
                return p;
            }

            operator bool(){
                return p ? true : false;
            }
    };

    CPyObject usePyFunc(char* fileName,char* functionName, vector <char*> args){
        CPyInstance instance;

        CPyObject pyfileName, pyModule, pyFunctionName, pyFunctionArgs, pyValueReturned;     // Tudo que vem ou vai do python é um PyObject

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\".\")");                                        // faz com que o programa tenha como referência o diretório local
        pyfileName = PyUnicode_FromString(fileName);                                         // Transforma c string em objeto python
        pyModule = PyImport_Import(pyfileName);                                              // Prepara o módulo python a ser interpretado
            
        if(pyModule){                                                                        // Se o módulo não for NULL
            pyFunctionName = PyObject_GetAttrString(pyModule, functionName);                 // Prepara a função
            if(pyFunctionName && PyCallable_Check(pyFunctionName)){
                if(args.size() != 0){                                                        // Se eu tiver argumentos
                    switch (args.size())
                    {
                        case 1:
                            pyFunctionArgs = PyTuple_Pack(
                                args.size(), 
                                PyUnicode_FromString(args[0])
                            ); // PyTuple_Pack (numero de argumentos,argumentos convertidos para PyObject)
                            break;
                        case 2:
                            pyFunctionArgs = PyTuple_Pack(
                                args.size(),                   // Quantidade de argumentos  
                                PyUnicode_FromString(args[0]), // primeiro argumento
                                PyUnicode_FromString(args[1])  // segundo argumento
                            ); // PyTuple_Pack (numero de argumentos,argumentos convertidos para PyObject)
                            break;
                        case 3:
                            pyFunctionArgs = PyTuple_Pack(
                                args.size(),                   // Quantidade de argumentos 
                                PyUnicode_FromString(args[0]), // primeiro argumento
                                PyUnicode_FromString(args[1]), // segundo argumento
                                PyUnicode_FromString(args[2])  // terceiro argumento
                            ); // PyTuple_Pack (numero de argumentos,argumentos convertidos para PyObject)
                            break;
                        case 4:
                            pyFunctionArgs = PyTuple_Pack(
                                args.size(),                   // Quantidade de argumentos 
                                PyUnicode_FromString(args[0]), // primeiro argumento
                                PyUnicode_FromString(args[1]), // segundo argumento
                                PyUnicode_FromString(args[2]), // terceiro argumento
                                PyUnicode_FromString(args[3]) // quarto argumento
                            ); // PyTuple_Pack (numero de argumentos,argumentos convertidos para PyObject)
                            break;                
                        default:
                            throw pyArgsException();
                            break;
                    }                    
                }
                else{                                         // Se eu não tiver
                    pyFunctionArgs = NULL;
                }
                pyValueReturned =  PyObject_CallObject(pyFunctionName, pyFunctionArgs);
                
                if(!pyValueReturned){                    
                    PyErr_Print();  
                    throw PyValueException();                                                   
                }
            }
            else{
                PyErr_Print();                                                               
                throw PyFunctionException();                                                
            }    
        }
        else{                                                                                
            PyErr_Print();                                                               
            throw PyModuleException();                                                   
        }
        return pyValueReturned;  
    }
#endif