#ifndef CALLTREE_H // typo causes bugs: #ifdef ...., what a idiot
#define CALLTREE_H

#define Calltree_generate Reader_Calltree_generate
#define Calltree_create Reader_calltree_create
#define Calltree_free Reader_calltree_free
#define Calltree_update_func_info Reader_Calltree_update_func_info
#define Calltree_update_file_info           Reader_Calltree_update_file_info
#define Calltree_update_folder_info	Reader_Calltree_update_folder_info

#include "func_info.h"

typedef struct Calltree Calltree;

extern Calltree *Calltree_create(const char *type, const char *name);
extern unsigned int Calltree_generate(Calltree *this);
extern int Calltree_update_func_info(Calltree *this, Func_info func);
extern unsigned int Calltree_update_file_info(Calltree *this); // update_times... the basic info... no need encapsulate??
extern void Calltree_free(Calltree *this);
extern void Calltree_update_folder_info(Calltree *this);

#endif /* CALLTREE_H */
