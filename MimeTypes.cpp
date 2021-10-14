#include "MimeTypes.h"

MimeTypes::MimeTypes(){
    fstream arquivo;
    arquivo.open("mimetypes.txt",fstream::in);
    if (!arquivo.is_open()){    // Retorna um erro se n conseguir abrir o arquivo
        cout << "Erro ao abrir arquivo"<<endl;
        return;
    }
    bool vazio = arquivo.peek() == EOF;
    if (!vazio){
        while(arquivo.good()){
            string tipo;
            string mimeType;
            getline(arquivo, tipo, ',');
            getline(arquivo, mimeType);
            mimeTypes[tipo]=mimeType;
        } 
    }  
}

string MimeTypes::getMimeType(string caminho){
    fstream arquivo(caminho);
    if(!arquivo.good())
        throw cArgsException();        
    size_t pos = caminho.rfind(".");
    if (pos == string::npos)
        throw cArgsException();    
    string tipo = caminho.substr(pos);
    return mimeTypes[tipo];
}