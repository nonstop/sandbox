#!/usr/bin/env python

import json
import httplib
conn = httplib.HTTPConnection('10.1.90.91:10500')

print conn

login = """{ "method": "login", "id": "lol", "params":             { "user": "nonstop", "password": "12345" } }"""
createScd = """{
    "id" : "qwert2",
    "method" : "resScheduleCreate",
    "params" : {
        "periods" : [
            {
                "flight" : {
                    "airline" : "AY",
                    "number" : 100
                },
                "period" : {
                    "d1" : "20120611",
                    "d2" : "20120621",
                    "freq" : "1234567"
                },
                "route" : {
                    "legs" : [
                        {
                            "aircraftConf" : "TU5C10Y200",
                            "aircraftType" : "TU5",
                            "arrTerm" : 1,
                            "depTerm" : 1,
                            "et" : false,
                            "section" : {
                                "arr" : "18:00",
                                "dep" : "14:00",
                                "from" : "MUC",
                                "to" : "HAM"
                            },
                            "subclOrder" : " C SYKLMN"
                        }
                    ]
                }
            },
            {
                "flight" : {
                    "airline" : "AY",
                    "number" : 100
                },
                "period" : {
                    "d1" : "20120612",
                    "d2" : "20120612",
                    "freq" : "1234567"
                },
                "route" : {
                    "legs" : [
                        {
                            "aircraftConf" : "TU5C10Y200",
                            "aircraftType" : "TU5",
                            "arrTerm" : 1,
                            "depTerm" : 1,
                            "et" : false,
                            "section" : {
                                "arr" : "18:00",
                                "dep" : "14:00",
                                "from" : "MUC",
                                "to" : "HAM"
                            },
                            "subclOrder" : " C SYKLMN"
                        }
                    ]
                },
                "adhoc": true
            },
            {
                "flight" : {
                    "airline" : "AY",
                    "number" : 200
                },
                "period" : {
                    "d1" : "20120611",
                    "d2" : "20120621",
                    "freq" : "1234567"
                },
                "route" : {
                    "legs" : [
                        {
                            "aircraftConf" : "TU5C10Y200",
                            "aircraftType" : "TU5",
                            "arrTerm" : 1,
                            "depTerm" : 1,
                            "et" : false,
                            "section" : {
                                "arr" : "27:40",
                                "dep" : "23:40",
                                "from" : "HAM",
                                "to" : "MUC"
                            },
                            "subclOrder" : " C SYKLMN"
                        }
                    ]
                }
            }
        ]
    }
}"""

deleteScd = """{
    "id" : "qwert2",
    "method" : "resScheduleDelete",
    "params" : {
    "flight" : {
        "airline" : "$(airline)",
        "number" : $(flight)
    },
    "period" : {
        "d1" : "20120612",
        "d2" : "20120621",
        "freq" : "1234567"
    }
    }
}"""

airlines = """{
    "method": "descAirlines", "id":"qwert2",
    "params": { "airlines": ["UT", "U6", "AY"] }
}"""

def call(conn, str):
    req = json.loads(str)
    str = json.dumps(req)
    print len(str), str
    headers = {"Content-type": "application/json", "Leon-Session": "12345"}
    conn.request("POST", "", str, headers)
    r1 = conn.getresponse()
    data = r1.read()
    print r1.status, r1.reason
    print data

searchScd = """{
    "method": "resScheduleSearch",
    "params": {
        "airline": "AY",
        "d1" : "20120611",
        "d2" : "20120621"
    },
    "id":"qwert3"
}"""

#call(conn, login)
#call(conn, createScd)
for i in range(1, 100):
    call(conn, searchScd)
#call(conn, deleteScd.replace("$(airline)", "AY").replace("$(flight)", "100"))
#call(conn, deleteScd.replace("$(airline)", "AY").replace("$(flight)", "100"))
#call(conn, deleteScd.replace("$(airline)", "AY").replace("$(flight)", "200"))
#call(conn, deleteScd.replace("$(airline)", "AY").replace("$(flight)", "300"))
#call(conn, searchScd)
#call(conn, airlines)

conn.close()
