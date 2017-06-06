#ifndef FUNC_INFO_H // typo causes bugs: #ifdef ...., what a idiot
#define FUNC_INFO_H

#define Func_line_count Reader_func_line_count// should not append ";" !!!
#define Func_info_create Reader_func_info_create
#define Func_info_free Reader_func_info_free
//#define Func_have_tree_info_updated Reader_Func_have_tree_info_updated
#define Func_called_times           Reader_Func_called_times

typedef struct Func_info Func_info;

extern Func_info *Func_info_create(const char *type, const char *name);
extern unsigned int Func_line_count(Func_info *this);
//extern int Func_have_tree_info_updated(Func_info *this, Calltree tree);
extern unsigned int Func_called_times(Func_info *this); // update_times... the basic info... no need encapsulate??
extern void Func_info_free(Func_info *this);

#endif /* FUNC_INFO_H */
