from subprocess import run
from os.path import abspath, dirname

class agent:
    pass

class agent2:
    pass

def get(key, target):
    def service():
        if target is agent:
            return "agent"
        if target is agent2:
            return "agent2"

    ret = run(
        ["docker-compose", "exec", "-T", service(), "zabbix_get", "-s", "localhost", "-k", key],
        capture_output=True,
        cwd = dirname(abspath(__file__))
    )
    return ret.returncode, ret.stdout, ret.stderr
