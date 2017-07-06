#ifndef COUNTER_H // typo causes bugs: #ifdef ...., what a idiot
#define COUNTER_H

#define counter_path Reader_counter_path// should not append ";" !!!
#define counter_type Reader_counter_type
#define counter_create Reader_counter_create
#define counter_free Reader_counter_free

typedef struct Counter Counter;

extern Counter *counter_create(const char *type, const char *name);
extern const char *counter_path(Counter *this);
extern const char *counter_type(Counter *this);
extern void counter_free(Counter *this);

#endif /* COUNTER_H */
