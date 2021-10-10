#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Py_Initialize();                                                                     // Inicia uma instância do python
    
    PyObject* pyfileName, pyModule, pyFunctionName, pyFunctionArgs, pyValueReturned;     // Tudo que vem ou vai do python é um PyObject
	
	pyfileName = PyUnicode_FromString(argv[1]);                                          // O nome é o primeiro argumento dado na execução do programa
	pyModule = PyImport_Import(pyfileName);                                              // Prepara o módulo python a ser interpretado
	pyFunctionName = PyObject_GetAttrString(pyModule, argv[2]);                          // O nome da função é o segundo argumento dado na execução do programa, prepara a função
	pyFunctionArgs = PyTuple_Pack(argc -1/*quantidade de argumentos que não vão pro python*/, PyUnicode_FromString(argv[3])); // PyTuple_Pack (numero de argumentos,argumentos convertidos para PyObject), argumentos maiores que tres na execução são os parâmetros da função
	pValue = PyObject_CallObject(pyFunctionName, pArgs);                                 // Recebe o retorno da função do python como PyObject
	
	auto result = _PyUnicode_AsString(pValue);                                           // Converte o retorno em PyObjetct para o tipo desejado em C++
	std::cout << result << std::endl;

	Py_Finalize();                                                                       //Fecha a instância do python
    return 0;
}