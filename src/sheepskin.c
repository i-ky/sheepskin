#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "module.h"

/* NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables) */
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
	int	ret = ZBX_MODULE_OK;

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
	static void	*lib = NULL;
	static void	(*set_timeout)(int) = NULL;
	static int	(*check_item)(AGENT_REQUEST *, AGENT_RESULT *) = NULL;

	if (NULL == lib && NULL == (lib = dlopen("sheepskin-cgo.so", RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND)))
	{
		SET_MSG_RESULT(result, strdup(dlerror()));
		return SYSINFO_RET_FAIL;
	}

	if (NULL == set_timeout)
	{
		if (NULL == (set_timeout = dlsym(lib, "sheep_set_timeout")))
		{
			SET_MSG_RESULT(result, strdup(dlerror()));
			return SYSINFO_RET_FAIL;
		}

		set_timeout(sheep_item_timeout);
	}

	if (NULL == check_item && NULL == (check_item = dlsym(lib, "sheep_check_item")))
	{
		SET_MSG_RESULT(result, strdup(dlerror()));
		return SYSINFO_RET_FAIL;
	}

	return check_item(request, result);
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
