#ifndef MIMETYPES_H_
    #define MIMETYPES_H_
#include <string.h>

class MimeTypes {
  public:
    static const char* getType(const char * path);
    static const char* getExtension(const char * type, int skip = 0);

  private:
    static MimeTypes::entry types[347];

};

#endif