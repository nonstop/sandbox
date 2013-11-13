#!/usr/bin/env python

import json
import httplib

#conn = httplib.HTTPConnection('0.0.0.0:8888')
#conn = httplib.HTTPConnection('10.4.130.33:8082')
conn = httplib.HTTPConnection('0.0.0.0:10500')

def call(conn, str):
    req = json.loads(str)
    str = json.dumps(req)
    print len(str), str
    headers = {"Content-type": "application/json"}
    conn.request("POST", "", str, headers)
    r1 = conn.getresponse()
    data = r1.read()
    print r1.status, r1.reason
    print data

call(conn, '{"method":"getSchedule", "params":[{"flight":{"airline":"UT", "number":200}}, {"d1":"20100420"}, {"d2":"20120430"}], "id":"qwert2"}')
call(conn, '{"method":"getSchedule", "params":[{"flight":{"airline":"VY", "number":101}}, {"d1":"20100420"}, {"d2":"20120430"}], "id":"qwert2"}')
#
#call(conn, '{"method":"getSchedule", "params":[{"flight":{"airline":"VY", "number":501, "suffix":1}}], "id":"qwert2"}')
#
#call(conn, '{"method":"getRaces", "params":[{"airline":"UT"}], "id":"qwert1"}')
#
#call(conn, '{"method":"getRaces", "params":[{"airline":"VY"}], "id":"qwert1"}')
#
#call(conn, '{"method":"getSchedule", "params":[{"d1":"20120420"}, {"d2":"20120430"}], "id":"qwert2"}')

#call(conn, '{"method":"getRaces", "params":[{"airline":"U6"}, {"airline":"UT"}], "id":"qwert3"}')

conn.close()
