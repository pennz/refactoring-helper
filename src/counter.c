#include <stdlib.h>
#include "counter.h"

struct Counter
{
	const char *type; // need changed to enum
	const char *path;
};

Counter *counter_create(const char *type, const char *name)
{
	Counter *c = malloc(sizeof(Counter));

	if (c == NULL)
	{
		return NULL;
	}

	c->type = type;
	c->path = name;

	return c;
}
const char *counter_path(Counter *this)
{
	return this->path;
}
void counter_free(Counter *this)
{
	free(this);
	return;
}
const char *counter_type(Counter *this)
{
	return this->type;
}
