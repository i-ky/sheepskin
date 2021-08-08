from pytest import mark
from zabbix import get, agent, agent2

@mark.parametrize("key", [
    "agent.ping",
    "web.certificate.get",
])
def test_compatibility(key):
    assert get(key, agent) == get(key, agent2)
