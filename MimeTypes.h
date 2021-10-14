#ifndef MIMETYPES_H_
    #define MIMETYPES_H_
	#include <iostream>
	#include <string.h>
	#include <map>
	#include <fstream>
	#include "exceptions.h"

	using namespace std;

	class MimeTypes {
		public:
			MimeTypes();
			string getMimeType(string caminho);
		private:
			map <string,string> mimeTypes;
	};
#endif