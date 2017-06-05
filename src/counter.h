#ifndef COUNTER_H // typo causes bugs: #ifdef ...., what a idiot
#define COUNTER_H

typedef struct Counter Counter;

Counter *counter_create(const char *type, const char *name);
const char *counter_path(Counter *this);
const char *counter_type(Counter *this);
void counter_free(Counter *this);

#endif /* COUNTER_H */
