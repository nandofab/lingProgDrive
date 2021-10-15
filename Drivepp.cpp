#include "Drivepp.h"

void Drivepp::receberComando(const string& nomeDaFuncao,vector<string>& argumentos ){
    CPyInstance instance;   
    CPyObject returnedValueFromPy;
    if(nomeDaFuncao.compare("criarPasta") == 0){
        if (argumentos.size() > 1)
            throw cArgsException();
        returnedValueFromPy = usePyDriveFunc("pyFuncs",nomeDaFuncao,argumentos);
        long resultado = PyLong_AsLong(returnedValueFromPy);
        if(resultado == 0)
            cout << "\nPasta criada com sucesso!"<<endl;
    } 
    else if(nomeDaFuncao.compare("listarDrive") == 0){
        if (argumentos.size() > 1)
            throw cArgsException();
        returnedValueFromPy = usePyDriveFunc("pyFuncs",nomeDaFuncao,argumentos);
        long resultado = PyLong_AsLong(returnedValueFromPy);
        if(resultado == 0)
            cout << "\nListagem completa da pasta feita com sucesso!"<<endl;
        else if (resultado == 1)
            throw DrivePathIsNotFolder(); 
    }
    else if(nomeDaFuncao.compare("downloadArquivo") == 0){
        if (argumentos.size() > 2)
            throw cArgsException();
        returnedValueFromPy = usePyDriveFunc("pyFuncs",nomeDaFuncao,argumentos);
        long resultado = PyLong_AsLong(returnedValueFromPy);
        if(resultado == 0)
            cout << "\nDownload concluído com sucesso!"<<endl;
        else if (resultado == 1)
            throw PathNotFound();  
    }
    else if(nomeDaFuncao.compare("uploadArquivo") == 0){
        if (argumentos.size() > 2)
            throw cArgsException();
        MimeTypes arquivo;
        argumentos.push_back(arquivo.getMimeType(argumentos[0]));
        returnedValueFromPy = usePyDriveFunc("pyFuncs",nomeDaFuncao,argumentos);
        long resultado = PyLong_AsLong(returnedValueFromPy);
        if(resultado == 0)
            cout << "\nUpload concluído com sucesso!"<<endl;
        else if (resultado == 1)
            throw FileNotFound();
        else if (resultado == 2)
            throw DrivePathIsNotFile();   
        else if (resultado == 3)
            throw UnknownError();    
    }
    else if(nomeDaFuncao.compare("moverArquivo") == 0){
        if (argumentos.size() >2)
            throw cArgsException();
        returnedValueFromPy = usePyDriveFunc("pyFuncs",nomeDaFuncao,argumentos);
        long resultado = PyLong_AsLong(returnedValueFromPy);
        if(resultado == 0)
            cout << "\nArquivo movido com sucesso!"<<endl;
    }
    else if(nomeDaFuncao.compare("help") == 0){
        cout << "\n\tBem-vindo ao Drivepp, interface C++ de interação com o Google Drive"<<endl;
        cout << "\nBy: Danilo Paes & Fernando Girão"<<endl;
        
        cout << "\n\tInformações gerais:"<<endl;
        cout << "\n\t\t Ao se referir a caminhos no Drive considere partindo da raiz do drive "<<endl;
        cout << "e para se referir a raiz escreva 'MeuDrive'. Não é necessário referenciá-la"<<endl;
        cout << "caso queira acessar outra pasta, uma pasta chamada teste na raiz do Drive pode ser"<<endl;
        cout << "referenciada simplesmente pelo caminho 'teste' ocultando a informação que essa pasta"<<endl;
        cout << "se encontra na raiz do drive"<<endl;
        
        cout << "\tComandos disponíveis:"<<endl;
        
        cout << "\n\t./Drivepp listarDrive caminhoNoDrive/nomeDaPasta"<<endl;
        cout << "\t\t Lista todos os arquivos e pastas em 'nomeDaPasta' localizada no Drive pelo 'caminhoNoDrive'."<<endl;
        cout << "Se quiser listar a pasta principal do seu Drive o caminho é 'MeuDrive'!"<<endl;
        
        cout << "\n\t./Drivepp criarPasta caminhoNoDrive/nomeDaPasta"<<endl;
        cout << "\t\t Cria uma pasta no 'caminhoNoDrive'. Se quiser criar uma pasta na raiz do Drive basta digitar" << endl;
        cout << "o nome da pasta desejada."<<endl;
        
        cout << "\n\t./Drivepp moverPasta caminhoDeOrigem/nomeDoArquivo.tipo caminhoDestino/pastaDestino"<<endl;
        cout << "\t\t Move o arquivo localizado no 'caminhoDeOrigem' para o 'caminhoDestino' dentro da 'pastaDestino."<<endl;
        cout << "Mover uma pasta a partir da raiz do drive, oculta-se o uso de 'MeuDrive'. Caso queira mover para a "<<endl;
        cout << "raiz do drive, basta escrever 'MeuDrive' no lugar de 'caminhoDestino/pastaDestino'."<< endl;

        cout << "\n\t./Drivepp downloadArquivo caminhoNoDrive/nomeDoArquivo.tipo caminhoDestinoNoPC/pastaDestinoNoPC"<<endl;
        cout << "\t\t Baixa o arquivo localizado no 'caminhoNoDrive' para a pasta local 'pastaDestinoNoPC' em "<<endl;
        cout << "'caminhoDestinoNoPC'.Baixar um arquivo a partir da raiz do drive, oculta-se o uso de 'MeuDrive'."<<endl;
        
        cout << "\n\t./Drivepp uploadArquivo caminhoOrigemNoPC/pastaOrigemNoPC caminhoDestinoNoDrive/pastaDestinoNoDrive "<<endl;
        cout << "\t\t Faz upload do arquivo localizado no 'caminhoOrigemNoPC' para a pasta no drive 'pastaDestinoNoDrive' em "<<endl;
        cout << "'caminhoDestinoNoDrive'.Fazer upload de um arquivo para a raiz do drive, basta escrever 'MeuDrive' no lugar "<<endl;
        cout << "de 'caminhoDestinoNoDrive/pastaDestinoNoDrive'."<<endl;
    }
    else
        throw PyFunctionException();
    //returnedValueFromPy = usePyDriveFunc("pyFuncs",nomeDaFuncao,argumentos);   // executa a função desejada em python retornando um CPyObject
    //return returnedValueFromPy;
}

CPyObject Drivepp::usePyDriveFunc(const string& fileName,const string& functionName,const  vector <string>& args){
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
                        case 3:
                            pyFunctionArgs = PyTuple_Pack(
                                args.size(),                   // Quantidade de argumentos  
                                PyUnicode_FromString(args[0].c_str()), // primeiro argumento
                                PyUnicode_FromString(args[1].c_str()), // segundo argumento
                                PyUnicode_FromString(args[2].c_str())  // terceiro argumento
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
