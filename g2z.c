#include "g2z.h"

int	sheep_get_rparams_num(const AGENT_REQUEST *request)
{
	return get_rparams_num(request);
}

const char	*sheep_get_rparam(const AGENT_REQUEST *request, int num)
{
	return get_rparam(request, num);
}

void	sheep_SET_TEXT_RESULT(AGENT_RESULT *res, const char *val)
{
	SET_TEXT_RESULT(res, val);
}

void	sheep_SET_MSG_RESULT(AGENT_RESULT *res, const char *val)
{
	SET_MSG_RESULT(res, val);
}
