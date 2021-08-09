from subprocess import check_output
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

    return check_output(
        ["docker-compose", "exec", "-T", service(), "zabbix_get", "-s", "localhost", "-k", key],
        cwd = dirname(abspath(__file__))
    ).decode("utf8")
