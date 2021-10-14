#include <iostream>
#include <vector>
#include <string>
#include "Drivepp.h"

using namespace std;

int main(int argc, char *argv[])
{
    Drivepp myDrive;
    vector <string> args;    
    try{
        if(argc < 2)                                                        // Se n tiver o nome do programa + nome da funcao desejada n tem argumentos suficientes para executar a funcao
            throw cArgsException();
        char* nomeDafuncao = argv[1];
        for (int cArg=2;cArg < argc;cArg++)                                 // trabalhar com vectors é mais prático e argv vem com argumentos q n temos interesse para a funcao do python
            args.push_back(argv[cArg]);
        
        myDrive.receberComando(nomeDafuncao,args);
    }   
    catch(PyModuleException& exception){
        cout << "***** Erro: " << exception.what() << " *****" <<endl;
    }
    catch(PyFunctionException& exception){
        cout << "\n***** Erro: " << exception.what() << " *****" <<endl;
    }
    catch(PyValueException& exception){
        cout << "\n***** Erro: " << exception.what() << " *****" <<endl;
    }
    catch(pyArgsException& exception){
        cout << "\n***** Erro: " << exception.what() << " *****" <<endl;
    }
    catch(cArgsException& exception){
        cout << "\n***** Erro: " << exception.what() << " *****" <<endl;
    }
    catch(pyFuncInexistenteException& exception){
        cout << "\n***** Erro: " << exception.what() << " *****" <<endl;
    }
    return 0; 
}
