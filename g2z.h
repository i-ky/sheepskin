#include <stdint.h>
#include <stdlib.h>

#include "module.h"

int		sheep_get_rparams_num(const AGENT_REQUEST *request);
const char	*sheep_get_rparam(const AGENT_REQUEST *request, int num);
void		sheep_SET_TEXT_RESULT(AGENT_RESULT *res, const char *val);
void		sheep_SET_MSG_RESULT(AGENT_RESULT *res, const char *val);
