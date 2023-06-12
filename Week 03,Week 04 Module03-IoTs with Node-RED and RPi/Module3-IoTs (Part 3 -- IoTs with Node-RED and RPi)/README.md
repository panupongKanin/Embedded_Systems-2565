### Quiz_301 – Blynk with Node-RED
##### • ทดสอบควบคุม 4 LED ด้วย Raspberry Pi ผ่าน Node-RED
##### • เพิ่มเติมให้ส่งข้อมูล Temperature ไปแสดงที่ Gauge บน Blynk

#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q301/Blynk%20with%20Node-RED/w03-w04-Quiz_301_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%203%20--%20IoTs%20with%20Node-RED%20and%20RPi)/Q301/Blynk%20with%20Node-RED/w03-w04-Quiz_301_0102.png" />

#### code ที่ใช้
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

### Quiz_303 – MQTT Server on Raspberry Pi
##### • ทดสอบควบคุม 4 LED ด้วย Raspberry Pi ผ่าน Node-RED ไปยัง private server
##### • เพิ่มเติมให้ส่งข้อมูล Temperature ไปแสดงที่ บน private Server
