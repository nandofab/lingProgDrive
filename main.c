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

   if (argc < 4)
   {
        fprintf(stderr,"Uso: ArquivoPyhton + nomeDaFuncao +  argumentos\n");
       return 1;
   }

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");
    pName = PyUnicode_DecodeFSDefault(argv[1]);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
       
	  pFunc = PyObject_GetAttrString(pModule, argv[2]);
          if (pFunc ==NULL)
	  {
	  	cout <<" A funcao "<< argv[2] <<" nao existe"<<endl;
		return 1;
	  }
	 
	  /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(argc - 3);
         pArgs = PyTuple_Pack(1, PyUnicode_FromString(argv[3]));
	     // for (i = 0; i < argc - 3; ++i) {
               // pValue = PyLong_FromLong(1,);
               // if (!pValue) {
                //    Py_DECREF(pArgs);
                 //   Py_DECREF(pModule);
                  //  fprintf(stderr, "Cannot convert argument\n");
                   // return 1;
           	    //}
	}

	 else {
		Py_DECREF(pFunc);
		Py_DECREF(pModule);
		PyErr_Print();
		cout<<"A funcao "<< argv[2] << " nao existe"<<endl;
		return 1;	
	 }
	//	fprintf(stderr,"Call failed\n");
										            
                /* pValue reference stolen here: */
               // PyTuple_SetItem(pArgs, i, pValue);
           // }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
           if (pValue != NULL) 
	   {
		auto result = _PyUnicode_AsString(pValue);   
		cout<<result<<endl;
		Py_DECREF(pValue);
	   }					               
//	   auto result = _PyUnicode_AsString(pValue);
	   
               // printf("Result of call: %ld\n", PyLong_AsLong(pValue));
   //             cout<< result <<endl;
		


	       //	Py_DECREF(pValue);
	}

	else {
	     if (PyErr_Occurred())
		 PyErr_Print();
	    	cout <<"Impossivel encontrar a funcao "<< argv[1]<<endl;    
	    // fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);	    
	}
	
return 0;

	    
	    
	}
