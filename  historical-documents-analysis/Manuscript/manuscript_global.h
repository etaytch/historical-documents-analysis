#ifndef MANUSCRIPT_GLOBAL_H
#define MANUSCRIPT_GLOBAL_H


#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )

#ifdef MANUSCRIPT_LIB
# define MANUSCRIPT_EXPORT DllExport
#else
# define MANUSCRIPT_EXPORT DllImport
#endif

#endif // MANUSCRIPT_GLOBAL_H
