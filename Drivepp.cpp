#include "Drivepp.h"

CPyObject Drivepp::receberComando(const string& nomeDaFuncao,const vector<string>& argumentos ){   
    CPyObject returnedValueFromPy;
    if(nomeDaFuncao.compare("criarPasta") == 0){
        if (argumentos.size() > 1)
            throw cArgsException();
    } 
    else if(nomeDaFuncao.compare("listarDrive") == 0){
        if (argumentos.size() > 1)
            throw cArgsException();        
    }
    else if(nomeDaFuncao.compare("downloadArquivo") == 0){
        if (argumentos.size() > 2)
            throw cArgsException();   
    }
    else if(nomeDaFuncao.compare("uploadArquivo") == 0){
        if (argumentos.size() > 2)
            throw cArgsException();
    }
    else if(nomeDaFuncao.compare("moverArquivo") == 0){
        if (argumentos.size() >2)
            throw cArgsException();
    }
    else
        throw PyFunctionException();
    returnedValueFromPy = usePyDriveFunc("pyFuncs",nomeDaFuncao,argumentos);   // executa a função desejada em python retornando um CPyObject
    return returnedValueFromPy;
}

CPyObject Drivepp::usePyDriveFunc(const string& fileName,const string& functionName,const  vector <string>& args){
        CPyInstance instance;

        CPyObject pyfileName, pyModule, pyFunctionName, pyFunctionArgs, pyValueReturned;     // Tudo que vem ou vai do python é um PyObject

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\".\")");                                        // faz com que o programa tenha como referência o diretório local
        pyfileName = PyUnicode_FromString(fileName.c_str());                                         // Transforma c string em objeto python
        pyModule = PyImport_Import(pyfileName);                                              // Prepara o módulo python a ser interpretado
            
        if(pyModule){                                                                        // Se o módulo não for NULL
            pyFunctionName = PyObject_GetAttrString(pyModule, functionName.c_str());                 // Prepara a função
            if(pyFunctionName && PyCallable_Check(pyFunctionName)){
                if(args.size() != 0){                                                        // Se eu tiver argumentos
                    switch (args.size())
                    {
                        case 1:
                            pyFunctionArgs = PyTuple_Pack(
                                args.size(), 
                                PyUnicode_FromString(args[0].c_str())
                            ); // PyTuple_Pack (numero de argumentos,argumentos convertidos para PyObject)
                            break;
                        case 2:
                            pyFunctionArgs = PyTuple_Pack(
                                args.size(),                   // Quantidade de argumentos  
                                PyUnicode_FromString(args[0].c_str()), // primeiro argumento
                                PyUnicode_FromString(args[1].c_str())  // segundo argumento
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
