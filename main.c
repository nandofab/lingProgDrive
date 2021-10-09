#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
using namespace std;

int
main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

  //  if (argc < 3) {
    //    fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
      //  return 1;
   // }

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");
    pName = PyUnicode_DecodeFSDefault(argv[1]);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(argc - 3);
         pArgs = PyTuple_Pack(1, PyUnicode_FromString(argv[3]));
	    //  for (i = 0; i < argc - 3; ++i) {
               // pValue = PyLong_FromLong(1,);
               // if (!pValue) {
                 //   Py_DECREF(pArgs);
                   // Py_DECREF(pModule);
                   // fprintf(stderr, "Cannot convert argument\n");
             //       return 1;
           	    }
                /* pValue reference stolen here: */
               // PyTuple_SetItem(pArgs, i, pValue);
           // }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
           
	   auto result = _PyUnicode_AsString(pValue);
	   
               // printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                cout<< result <<endl;
		


	       //	Py_DECREF(pValue);
		}            
	       	 return 0;

	    
	    
	    
	    }
