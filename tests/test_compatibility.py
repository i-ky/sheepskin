from pytest import mark
from zabbix import get, agent, agent2

@mark.parametrize("key", [
    "agent.ping",
    "web.certificate.get",
    "web.certificate.get[1,2,3,4]",
    "web.certificate.get[zabbix.com]",
    "web.certificate.get[example.org]",
])
def test_compatibility(key):
    assert get(key, agent) == get(key, agent2)
