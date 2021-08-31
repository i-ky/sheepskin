package main

/*
#include "g2z.h"
*/
import "C"

import (
	"zabbix.com/pkg/plugin"
	webcertificate "zabbix.com/plugins/web/certificate"
)

var impl webcertificate.Plugin

//export sheep_set_timeout
func sheep_set_timeout(timeout C.int) {
	var options plugin.GlobalOptions
	options.Timeout = int(timeout)
	impl.Configure(&options, nil)
}

//export sheep_check_item
func sheep_check_item(request *C.AGENT_REQUEST, result *C.AGENT_RESULT) C.int {
	var params = make([]string, C.sheep_get_rparams_num(request))

	for i := 0; i < len(params); i++ {
		params[i] = C.GoString(C.sheep_get_rparam(request, C.int(i)))
	}

	if text, err := impl.Export("web.certificate.get", params, nil); err != nil {
		C.sheep_SET_MSG_RESULT(result, C.CString(err.Error()))
		return C.SYSINFO_RET_FAIL
	} else {
		C.sheep_SET_TEXT_RESULT(result, C.CString(text.(string)))
		return C.SYSINFO_RET_OK
	}
}

func main() {
	panic("This should never happen.")
}
