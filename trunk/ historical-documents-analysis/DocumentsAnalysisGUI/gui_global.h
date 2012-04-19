#ifndef GUI_GLOBAL_H
#define GUI_GLOBAL_H

#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )

#ifdef GUI_LIB
# define GUI_EXPORT DllExport
#else
# define GUI_EXPORT DllImport
#endif

#endif // GUI_GLOBAL_H
