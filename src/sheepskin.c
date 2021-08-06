#include <stdint.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "module.h"

int	sheep_item_timeout;

int	zbx_module_api_version(void)
{
	return ZBX_MODULE_API_VERSION;
}

void	zbx_module_item_timeout(int timeout)
{
	sheep_item_timeout = timeout;
}

int	zbx_module_init(void)
{
	int		ret = ZBX_MODULE_OK;

	printf("Initializing \"sheepskin\" module...\n");

	/* TODO */

	if (ZBX_MODULE_OK == ret)
		printf("Module \"sheepskin\" has been successfully initialized.\n");

	return ret;
}

int	zbx_module_uninit(void)
{
	printf("Uninitializing \"sheepskin\" module...\n");

	/* TODO */

	printf("Module \"sheepskin\" has been successfully uninitialized.\n");

	return ZBX_MODULE_OK;
}

static int	sheep_web_certificate_get(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	/* TODO */
	SET_MSG_RESULT(result, NULL);
	return SYSINFO_RET_FAIL;
}

ZBX_METRIC	*zbx_module_item_list(void)
{
	static ZBX_METRIC	keys[] =
	/*	KEY			FLAG		FUNCTION			TEST PARAMETERS */
	{
		{"web.certificate.get",	CF_HAVEPARAMS,	sheep_web_certificate_get,	"https://www.zabbix.com"},
		{NULL}
	};

	return keys;
}
