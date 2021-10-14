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
        
<<<<<<< HEAD:Tests/main.cpp
        CPyObject pyResultado = usePyFunc("pyFuncs",nomeDafuncao,args); // executa a função desejada em python retornando um CPyObject
//	auto cResultado = _PyUnicode_AsString(pyResultado);                 // converte o resultado de CPyObject para o desejado em C
  //     	cout<<cResultado<<endl;                                             // printa esse resultado
=======
        myDrive.receberComando(nomeDafuncao,args);
>>>>>>> 10103987b0f49941ab6c6c1dc15ed9e70298519e:main.cpp
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
