# sheepskin [![Build Status](https://app.travis-ci.com/i-ky/sheepskin.svg?branch=main)](https://app.travis-ci.com/i-ky/sheepskin) [![Gitpod ready-to-code](https://img.shields.io/badge/Gitpod-ready--to--code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/i-ky/sheepskin)

[Zabbix](http://www.zabbix.com)
[loadable module](https://www.zabbix.com/documentation/current/manual/config/items/loadablemodules)
for monitoring
website
[certificates](https://en.wikipedia.org/wiki/Public_key_certificate)

## summary

This module provides
[Zabbix agent 2 feature of monitoring certificates](https://support.zabbix.com/browse/ZBXNEXT-6708)
in the form compatible with Zabbix server / proxy
[as was originally requested](https://support.zabbix.com/browse/ZBXNEXT-5931).
Agent (the "old" one) is supported too.

Module uses some of Zabbix code completely unchanged,
so the behaviour should be identical to native `web.certificate.get` item and
[templates designed for agent 2](https://git.zabbix.com/projects/ZBX/repos/zabbix/browse/templates/app/certificate_agent2)
should require only minor modifications.

## compile

You will need an environment with working
[C](https://en.wikipedia.org/wiki/List_of_compilers#C_compilers)
and
[Go](https://golang.org/doc/install)
compilers.

1. [Download](https://www.zabbix.com/download_sources)
Zabbix source or check it out from
[Git repository](https://git.zabbix.com/):
```bash
git clone https://git.zabbix.com/scm/zbx/zabbix.git --depth 1 /path/to/zabbix/source
```
Note that you need to compile module using sources of the version you will be using it with!

2. Configure Zabbix sources:
```bash
cd /path/to/zabbix/source
./bootstrap.sh
./configure
```

3. Get module sources,
point them to Zabbix source directory
and run `make` to build,
it should produce `sheepskin.so` and `sheepskin-cgo.so` shared libraries.
```bash
cd /path/to/sheepskin/source
export ZABBIX_SOURCE=/path/to/zabbix/source
make
```

## install

Copy `sheepskin.so` and `sheepskin-cgo.so` to a desired location, set up necessary permissions.

## configure

Set `LoadModulePath` and `LoadModule` parameters in Zabbix
[agent](https://www.zabbix.com/documentation/current/manual/appendix/config/zabbix_agentd) /
[proxy](https://www.zabbix.com/documentation/current/manual/appendix/config/zabbix_proxy) /
[server](https://www.zabbix.com/documentation/current/manual/appendix/config/zabbix_server)
configuration file.
```
LoadModulePath=/path/to/modules/
LoadModule=sheepskin.so
```
or
```
LoadModulePath=/path/to/modules/sheepskin.so
```
Restart Zabbix agent / proxy / server.

Note that you _don't need_ to mention `sheepskin-cgo.so` in Zabbix configuration file.
It will be loaded in runtime using `dlopen("sheepskin-cgo.so", ...)`.

Please make sure that
[`dlopen()` can find](https://man7.org/linux/man-pages/man3/dlopen.3.html)
`sheepskin-cgo.so` (e.g. by setting `LD_LIBRARY_PATH` appropriately).

## use

Configure `web.certificate.get` checks:
* use item type
[_Simple check_](https://www.zabbix.com/documentation/current/manual/config/items/itemtypes/simple_checks)
if the module is loaded by server or proxy;
* use item type
[_Zabbix agent_ or _Zabbix agent (active)_](https://www.zabbix.com/documentation/current/manual/config/items/itemtypes/zabbix_agent)
if the module is loaded by agent.

Please refer to
[official documentation of `web.certificate.get`](https://www.zabbix.com/documentation/current/en/manual/config/items/itemtypes/zabbix_agent/zabbix_agent2#web-certificate)
for further details.
