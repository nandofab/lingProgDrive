#include <iostream>
#include <vector>
#include <string>
#include "Drivepp.h"

using namespace std;

int main(int argc, char *argv[]){
    Drivepp myDrive;
    vector <string> args;    
    try{
        if(argc <= 2)                                                        // Se n tiver o nome do programa + nome da funcao desejada n tem argumentos suficientes para executar a funcao
            throw cArgsException();
        char* nomeDafuncao = argv[1];
        for (int cArg=2;cArg < argc;cArg++)                                 // trabalhar com vectors é mais prático e argv vem com argumentos q n temos interesse para a funcao do python
            args.push_back(argv[cArg]);
        
        myDrive.receberComando(nomeDafuncao,args); // executa a função desejada em python retornando um CPyObject
    }   
    catch(PyModuleException& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(PyFunctionException& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(PyValueException& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(pyArgsException& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(cArgsException& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(pyFuncInexistenteException& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(MimeTypeFileException& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(MimeTypeFileNotFound & exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(PathNotFound& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(DrivePathIsNotFile& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(UnknownError& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }
    catch(FileNotFound& exception){
        cout << "************************************************ ERRO ************************************************" <<endl;
        cout << "\t" <<exception.what() <<endl;
        cout << "******************************************************************************************************" <<endl;
    }    
    return 0; 
}
