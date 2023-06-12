### Quiz_301 – Blynk with Node-RED
##### • ทดสอบควบคุม 4 LED ด้วย Raspberry Pi ผ่าน Node-RED
##### • เพิ่มเติมให้ส่งข้อมูล Temperature ไปแสดงที่ Gauge บน Blynk

#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q301/Blynk%20with%20Node-RED/w03-w04-Quiz_301_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q301/Blynk%20with%20Node-RED/w03-w04-Quiz_301_0102.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "dffb1502c3eaef6c",
        "type": "tab",
        "label": "Q301-0101",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "e76f6e2313c72d81",
        "type": "blynk-iot-in-write",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "0",
        "pin_all": false,
        "client": "ab1d4c09e1839ba9",
        "x": 230,
        "y": 140,
        "wires": [
            [
                "23ded503dec1d0d4"
            ]
        ]
    },
    {
        "id": "2aaf67f44c16e9f0",
        "type": "blynk-iot-in-write",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "1",
        "pin_all": 0,
        "client": "ab1d4c09e1839ba9",
        "x": 230,
        "y": 200,
        "wires": [
            [
                "98eb1b7fc15cac1b"
            ]
        ]
    },
    {
        "id": "b0d1341f3399701c",
        "type": "blynk-iot-in-write",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "2",
        "pin_all": 0,
        "client": "ab1d4c09e1839ba9",
        "x": 230,
        "y": 260,
        "wires": [
            [
                "9aa1f7f09a97fbe0"
            ]
        ]
    },
    {
        "id": "8f8fe54a60f8704f",
        "type": "blynk-iot-in-write",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "3",
        "pin_all": 0,
        "client": "ab1d4c09e1839ba9",
        "x": 230,
        "y": 320,
        "wires": [
            [
                "a98d8b1201ddb4fc"
            ]
        ]
    },
    {
        "id": "cebb6018060d7824",
        "type": "debug",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 910,
        "y": 380,
        "wires": []
    },
    {
        "id": "2267963996589c42",
        "type": "blynk-iot-out-write",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "4",
        "pinmode": 0,
        "client": "ab1d4c09e1839ba9",
        "x": 740,
        "y": 600,
        "wires": []
    },
    {
        "id": "94700921cadc1a81",
        "type": "rpi-dht22",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "topic": "rpi-dht22",
        "dht": 22,
        "pintype": "0",
        "pin": "4",
        "x": 300,
        "y": 480,
        "wires": [
            [
                "2267963996589c42",
                "7f368d2ad74d89d4",
                "dda967c453255a84"
            ]
        ]
    },
    {
        "id": "d2e24577f9ae5d91",
        "type": "inject",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "10",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "",
        "payloadType": "date",
        "x": 150,
        "y": 480,
        "wires": [
            [
                "94700921cadc1a81"
            ]
        ]
    },
    {
        "id": "50906e1c5b229ab0",
        "type": "blynk-iot-out-write",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "5",
        "pinmode": 0,
        "client": "ab1d4c09e1839ba9",
        "x": 740,
        "y": 540,
        "wires": []
    },
    {
        "id": "7f368d2ad74d89d4",
        "type": "change",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "rules": [
            {
                "t": "set",
                "p": "payload",
                "pt": "msg",
                "to": "humidity",
                "tot": "msg"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 520,
        "y": 480,
        "wires": [
            [
                "50906e1c5b229ab0",
                "d91e02b8f04b7ec3"
            ]
        ]
    },
    {
        "id": "dda967c453255a84",
        "type": "function",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "func": "var   data = {}\ndata.Tempp = msg.payload;\n\nmsg.payload = data\n\nreturn   msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 720,
        "y": 380,
        "wires": [
            [
                "cebb6018060d7824"
            ]
        ]
    },
    {
        "id": "d91e02b8f04b7ec3",
        "type": "function",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "func": "var   data = {}\ndata.Humid = msg.payload;\n\nmsg.payload = data\n\nreturn   msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 720,
        "y": 420,
        "wires": [
            [
                "cebb6018060d7824"
            ]
        ]
    },
    {
        "id": "23ded503dec1d0d4",
        "type": "rpi-gpio out",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "26",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 520,
        "y": 140,
        "wires": []
    },
    {
        "id": "98eb1b7fc15cac1b",
        "type": "rpi-gpio out",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "19",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 520,
        "y": 200,
        "wires": []
    },
    {
        "id": "9aa1f7f09a97fbe0",
        "type": "rpi-gpio out",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "16",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 520,
        "y": 260,
        "wires": []
    },
    {
        "id": "a98d8b1201ddb4fc",
        "type": "rpi-gpio out",
        "z": "dffb1502c3eaef6c",
        "name": "",
        "pin": "20",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 520,
        "y": 320,
        "wires": []
    },
    {
        "id": "ab1d4c09e1839ba9",
        "type": "blynk-iot-client",
        "name": "",
        "path": "blynk.cloud",
        "key": "1Bq5LDdI8r_G-XbkXv44o_ht0E2iqDH0",
        "tmpl": "TMPL6mzpuFkns",
        "dbg_all": false,
        "dbg_log": false,
        "dbg_prop": false,
        "dbg_sync": false,
        "dbg_low": false,
        "dbg_pins": "",
        "multi_cmd": false,
        "enabled": true
    }
]
```

#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q301/Blynk%20with%20Node-RED/w03-w04-Quiz_301_0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q301/Blynk%20with%20Node-RED/w03-w04-Quiz_301_0104.png" />

### Quiz_302 – MQTT Client with Node-RED
##### • ทดสอบควบคุม 4 LED ด้วย Raspberry Pi ผ่าน Node-RED
##### • เพิ่มเติมให้ส่งข้อมูล Temperature ไปแสดงที่ บน Server
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q302/MQTT%20Client%20with%20Node-RED/w03-w04-Quiz_302_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q302/MQTT%20Client%20with%20Node-RED/w03-w04-Quiz_302_0102.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "51676f5ae1675c99",
        "type": "tab",
        "label": "Q302-0101",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "ede8af72fbce249f",
        "type": "debug",
        "z": "51676f5ae1675c99",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 750,
        "y": 40,
        "wires": []
    },
    {
        "id": "250656607fc84a6b",
        "type": "change",
        "z": "51676f5ae1675c99",
        "name": "Change:   LED1",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF1",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON1",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 460,
        "y": 120,
        "wires": [
            [
                "9f24efe46f80ece3"
            ]
        ]
    },
    {
        "id": "3ef021806c6b9745",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "ON1",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON1",
        "payloadType": "str",
        "x": 230,
        "y": 300,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "ebb6f203af356f41",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "OFF1",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF1",
        "payloadType": "str",
        "x": 230,
        "y": 340,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "660c806e35360b3a",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "ON2",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON2",
        "payloadType": "str",
        "x": 230,
        "y": 400,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "b120aaa6f163009a",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "OFF2",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF2",
        "payloadType": "str",
        "x": 230,
        "y": 440,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "affad71055d20fc9",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "ON3",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON3",
        "payloadType": "str",
        "x": 230,
        "y": 500,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "53898654fded8848",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "OFF3",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF3",
        "payloadType": "str",
        "x": 230,
        "y": 540,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "cb65d8fe58a56115",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "ON4",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON4",
        "payloadType": "str",
        "x": 230,
        "y": 600,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "90648d0de7b7d03c",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "OFF4",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF4",
        "payloadType": "str",
        "x": 230,
        "y": 640,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "fc71a41e06c42f96",
        "type": "change",
        "z": "51676f5ae1675c99",
        "name": "Change:   LED2",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF2",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON2",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 460,
        "y": 160,
        "wires": [
            [
                "73c248834cd70d73"
            ]
        ]
    },
    {
        "id": "b33943e6fd663555",
        "type": "change",
        "z": "51676f5ae1675c99",
        "name": "Change:   LED3",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF3",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON3",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 460,
        "y": 200,
        "wires": [
            [
                "a7be2b60ab8da531"
            ]
        ]
    },
    {
        "id": "b01f6765bf25358a",
        "type": "change",
        "z": "51676f5ae1675c99",
        "name": "Change:   LED4",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF4",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON4",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 460,
        "y": 240,
        "wires": [
            [
                "f72f99cf183ec4fb"
            ]
        ]
    },
    {
        "id": "c82886c94c3c8693",
        "type": "inject",
        "z": "51676f5ae1675c99",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "60",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "",
        "payloadType": "date",
        "x": 210,
        "y": 720,
        "wires": [
            [
                "31a5cb37583fb4c3"
            ]
        ]
    },
    {
        "id": "31a5cb37583fb4c3",
        "type": "rpi-dht22",
        "z": "51676f5ae1675c99",
        "name": "",
        "topic": "rpi-dht22",
        "dht": 22,
        "pintype": "0",
        "pin": "4",
        "x": 380,
        "y": 720,
        "wires": [
            [
                "891f6a710fa6a730"
            ]
        ]
    },
    {
        "id": "891f6a710fa6a730",
        "type": "function",
        "z": "51676f5ae1675c99",
        "name": "",
        "func": "var   data = {};\ndata.Tempp = msg.payload;\ndata.Humid = msg.humidity;\nmsg.payload   = data;\nreturn   msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 540,
        "y": 720,
        "wires": [
            [
                "4f81208d4aa232bb"
            ]
        ]
    },
    {
        "id": "d25587a16e46fe2c",
        "type": "mqtt in",
        "z": "51676f5ae1675c99",
        "name": "",
        "topic": "control/leds",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "f87103da3a72f890",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 150,
        "y": 40,
        "wires": [
            [
                "ede8af72fbce249f",
                "250656607fc84a6b",
                "fc71a41e06c42f96",
                "b33943e6fd663555",
                "b01f6765bf25358a"
            ]
        ]
    },
    {
        "id": "4f81208d4aa232bb",
        "type": "mqtt out",
        "z": "51676f5ae1675c99",
        "name": "",
        "topic": "control/leds",
        "qos": "0",
        "retain": "true",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "f87103da3a72f890",
        "x": 750,
        "y": 460,
        "wires": []
    },
    {
        "id": "9f24efe46f80ece3",
        "type": "rpi-gpio out",
        "z": "51676f5ae1675c99",
        "name": "",
        "pin": "26",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 740,
        "y": 120,
        "wires": []
    },
    {
        "id": "73c248834cd70d73",
        "type": "rpi-gpio out",
        "z": "51676f5ae1675c99",
        "name": "",
        "pin": "19",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 740,
        "y": 160,
        "wires": []
    },
    {
        "id": "a7be2b60ab8da531",
        "type": "rpi-gpio out",
        "z": "51676f5ae1675c99",
        "name": "",
        "pin": "16",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 740,
        "y": 200,
        "wires": []
    },
    {
        "id": "f72f99cf183ec4fb",
        "type": "rpi-gpio out",
        "z": "51676f5ae1675c99",
        "name": "",
        "pin": "20",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 740,
        "y": 240,
        "wires": []
    },
    {
        "id": "f87103da3a72f890",
        "type": "mqtt-broker",
        "name": "MQTT",
        "broker": "mqtt.eclipseprojects.io",
        "port": "1883",
        "clientid": "",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": "4",
        "keepalive": "60",
        "cleansession": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthRetain": "false",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closeQos": "0",
        "closeRetain": "false",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willRetain": "false",
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": "",
        "credentials": {}
    }
]
```
#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q302/MQTT%20Client%20with%20Node-RED/w03-w04-Quiz_302_0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q302/MQTT%20Client%20with%20Node-RED/w03-w04-Quiz_302_0104.png" />

### Quiz_303 – MQTT Server on Raspberry Pi
##### • ทดสอบควบคุม 4 LED ด้วย Raspberry Pi ผ่าน Node-RED ไปยัง private server
##### • เพิ่มเติมให้ส่งข้อมูล Temperature ไปแสดงที่ บน private Server
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q303/MQTT%20Server%20on%20Raspberry%20Pi/w03-w04-Quiz_303_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q303/MQTT%20Server%20on%20Raspberry%20Pi/w03-w04-Quiz_303_0102.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q303/MQTT%20Server%20on%20Raspberry%20Pi/w03-w04-Quiz_303_0103.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "eef2bbac8a4507be",
        "type": "tab",
        "label": "Q303-0101",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "ea52a05d201ce705",
        "type": "debug",
        "z": "eef2bbac8a4507be",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 790,
        "y": 60,
        "wires": []
    },
    {
        "id": "283086ae86caffa6",
        "type": "change",
        "z": "eef2bbac8a4507be",
        "name": "Change:   LED1",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF1",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON1",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 500,
        "y": 140,
        "wires": [
            [
                "76e9951c0da7bc9a"
            ]
        ]
    },
    {
        "id": "3ad45448f51a0a40",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "ON1",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON1",
        "payloadType": "str",
        "x": 270,
        "y": 320,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "2ccb6038299738a7",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "OFF1",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF1",
        "payloadType": "str",
        "x": 270,
        "y": 360,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "e2241713227ab3a3",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "ON2",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON2",
        "payloadType": "str",
        "x": 270,
        "y": 420,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "727bd3731b5edcaa",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "OFF2",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF2",
        "payloadType": "str",
        "x": 270,
        "y": 460,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "34c2c5c450c56fbe",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "ON3",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON3",
        "payloadType": "str",
        "x": 270,
        "y": 520,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "6148a2ab65660bec",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "OFF3",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF3",
        "payloadType": "str",
        "x": 270,
        "y": 560,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "c6153781b381a3c5",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "ON4",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "ON4",
        "payloadType": "str",
        "x": 270,
        "y": 620,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "afc54f7f1c716ffa",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "OFF4",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "OFF4",
        "payloadType": "str",
        "x": 270,
        "y": 660,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "087b593bb31ef221",
        "type": "change",
        "z": "eef2bbac8a4507be",
        "name": "Change:   LED2",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF2",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON2",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 500,
        "y": 180,
        "wires": [
            [
                "2ecf642895a282fe"
            ]
        ]
    },
    {
        "id": "f8605a6fdc41e284",
        "type": "change",
        "z": "eef2bbac8a4507be",
        "name": "Change:   LED3",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF3",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON3",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 500,
        "y": 220,
        "wires": [
            [
                "e8443c213eef1979"
            ]
        ]
    },
    {
        "id": "d712379ad2cf230a",
        "type": "change",
        "z": "eef2bbac8a4507be",
        "name": "Change:   LED4",
        "rules": [
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "OFF4",
                "fromt": "str",
                "to": "false",
                "tot": "bool"
            },
            {
                "t": "change",
                "p": "payload",
                "pt": "msg",
                "from": "ON4",
                "fromt": "str",
                "to": "true",
                "tot": "bool"
            }
        ],
        "action": "",
        "property": "",
        "from": "",
        "to": "",
        "reg": false,
        "x": 500,
        "y": 260,
        "wires": [
            [
                "dbb2c637d2f51363"
            ]
        ]
    },
    {
        "id": "13f6975c4d50bead",
        "type": "inject",
        "z": "eef2bbac8a4507be",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "60",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "",
        "payloadType": "date",
        "x": 250,
        "y": 740,
        "wires": [
            [
                "ec0983869a6e7bcc"
            ]
        ]
    },
    {
        "id": "ec0983869a6e7bcc",
        "type": "rpi-dht22",
        "z": "eef2bbac8a4507be",
        "name": "",
        "topic": "rpi-dht22",
        "dht": 22,
        "pintype": "0",
        "pin": "4",
        "x": 420,
        "y": 740,
        "wires": [
            [
                "61c33804fb90a694"
            ]
        ]
    },
    {
        "id": "61c33804fb90a694",
        "type": "function",
        "z": "eef2bbac8a4507be",
        "name": "",
        "func": "var   data = {};\ndata.Tempp = msg.payload;\ndata.Humid = msg.humidity;\nmsg.payload   = data;\nreturn   msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 580,
        "y": 740,
        "wires": [
            [
                "4e92a17d85cefb2a"
            ]
        ]
    },
    {
        "id": "5a6d8fff7e791f26",
        "type": "mqtt in",
        "z": "eef2bbac8a4507be",
        "name": "",
        "topic": "control/leds",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "f87103da3a72f890",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 190,
        "y": 60,
        "wires": [
            [
                "ea52a05d201ce705",
                "283086ae86caffa6",
                "087b593bb31ef221",
                "f8605a6fdc41e284",
                "d712379ad2cf230a"
            ]
        ]
    },
    {
        "id": "4e92a17d85cefb2a",
        "type": "mqtt out",
        "z": "eef2bbac8a4507be",
        "name": "",
        "topic": "control/leds",
        "qos": "0",
        "retain": "true",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "f87103da3a72f890",
        "x": 790,
        "y": 480,
        "wires": []
    },
    {
        "id": "76e9951c0da7bc9a",
        "type": "rpi-gpio out",
        "z": "eef2bbac8a4507be",
        "name": "",
        "pin": "26",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 780,
        "y": 140,
        "wires": []
    },
    {
        "id": "2ecf642895a282fe",
        "type": "rpi-gpio out",
        "z": "eef2bbac8a4507be",
        "name": "",
        "pin": "19",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 780,
        "y": 180,
        "wires": []
    },
    {
        "id": "e8443c213eef1979",
        "type": "rpi-gpio out",
        "z": "eef2bbac8a4507be",
        "name": "",
        "pin": "16",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 780,
        "y": 220,
        "wires": []
    },
    {
        "id": "dbb2c637d2f51363",
        "type": "rpi-gpio out",
        "z": "eef2bbac8a4507be",
        "name": "",
        "pin": "20",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 780,
        "y": 260,
        "wires": []
    },
    {
        "id": "f87103da3a72f890",
        "type": "mqtt-broker",
        "name": "MQTT",
        "broker": "192.168.0.31",
        "port": "1883",
        "clientid": "",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": "4",
        "keepalive": "60",
        "cleansession": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthRetain": "false",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closeQos": "0",
        "closeRetain": "false",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willRetain": "false",
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": ""
    }
]
```
#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q303/MQTT%20Server%20on%20Raspberry%20Pi/w03-w04-Quiz_303_0104.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q303/MQTT%20Server%20on%20Raspberry%20Pi/w03-w04-Quiz_303_0105.png" />
