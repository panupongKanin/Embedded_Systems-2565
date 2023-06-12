### Quiz_201 – Node-RED UI
##### • แสดงข้อมูลที่ได้ทำการทดสอบ

#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q201/Node-RED%20UI/w03-w04-Quiz_201_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q201/Node-RED%20UI/w03-w04-Quiz_201_0102.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "d6af899f9daf2c4b",
        "type": "tab",
        "label": "Q201-0101",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "b2848cd6.ca5c7",
        "type": "ui_slider",
        "z": "d6af899f9daf2c4b",
        "tab": "5969fd52.22b424",
        "name": "Slider",
        "topic": "",
        "group": "Control LED",
        "order": "2",
        "min": "0",
        "max": "100",
        "x": 270,
        "y": 160,
        "wires": [
            [
                "1cca457a.60fb5b",
                "732721f2.32913",
                "3c7de1d6.58b99e",
                "869c189f.bbbd18"
            ]
        ]
    },
    {
        "id": "1cca457a.60fb5b",
        "type": "ui_gauge",
        "z": "d6af899f9daf2c4b",
        "tab": "5969fd52.22b424",
        "name": "Gauge",
        "group": "Control LED",
        "order": "3",
        "format": "{{value}}",
        "min": 0,
        "max": "1",
        "x": 670,
        "y": 160,
        "wires": []
    },
    {
        "id": "732721f2.32913",
        "type": "ui_chart",
        "z": "d6af899f9daf2c4b",
        "tab": "5969fd52.22b424",
        "name": "",
        "group": "Control LED",
        "order": "4",
        "interpolate": "linear",
        "nodata": "No Data",
        "removeOlder": 1,
        "removeOlderUnit": "86400",
        "x": 670,
        "y": 220,
        "wires": [
            [],
            []
        ]
    },
    {
        "id": "3c7de1d6.58b99e",
        "type": "rpi-gpio out",
        "z": "d6af899f9daf2c4b",
        "name": "LED",
        "pin": "26",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "pwm",
        "bcm": true,
        "x": 670,
        "y": 100,
        "wires": []
    },
    {
        "id": "828cc789.3d3b08",
        "type": "function",
        "z": "d6af899f9daf2c4b",
        "name": "Function",
        "func": "if(msg.payload == \"true\"){\n    msg.payload = 1;\n}\nelse{\n    msg.payload = 0;\n}    \nreturn msg;",
        "outputs": "1",
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 480,
        "y": 380,
        "wires": [
            [
                "b2848cd6.ca5c7"
            ]
        ]
    },
    {
        "id": "58638633.9de238",
        "type": "ui_switch",
        "z": "d6af899f9daf2c4b",
        "tab": "5969fd52.22b424",
        "name": "Switch",
        "topic": "",
        "group": "Control LED",
        "order": 1,
        "onvalue": "true",
        "offvalue": "false",
        "x": 270,
        "y": 380,
        "wires": [
            [
                "828cc789.3d3b08"
            ]
        ]
    },
    {
        "id": "869c189f.bbbd18",
        "type": "function",
        "z": "d6af899f9daf2c4b",
        "name": "SetSwitch",
        "func": "if(msg.payload > 0)\n    msg.payload = 1;\nelse \n    msg.payload = 0;\n    \nreturn msg;\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 290,
        "y": 280,
        "wires": [
            [
                "58638633.9de238"
            ]
        ]
    },
    {
        "id": "5969fd52.22b424",
        "type": "ui_tab",
        "name": "Q201-0101",
        "icon": "dashboard",
        "order": "1"
    }
]
```

#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q201/Node-RED%20UI/w03-w04-Quiz_201_0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q201/Node-RED%20UI/w03-w04-Quiz_201_0104.png" />

### Quiz_202 – Node-RED to LINE notify
##### • แสดงข้อมูลที่ได้ทำการทดสอบ

#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q202/Node-RED%20to%20LINE%20notify/w03-w04-Quiz_202_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q202/Node-RED%20to%20LINE%20notify/w03-w04-Quiz_202_0102.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "bf05387658e4fc4c",
        "type": "tab",
        "label": "Q202-0101",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "8cb66889.d96b28",
        "type": "http request",
        "z": "bf05387658e4fc4c",
        "name": "",
        "method": "POST",
        "ret": "txt",
        "paytoqs": "ignore",
        "url": "https://notify-api.line.me/api/notify",
        "tls": "",
        "persist": false,
        "proxy": "",
        "insecureHTTPParser": false,
        "authType": "",
        "senderr": false,
        "headers": [],
        "x": 550,
        "y": 260,
        "wires": [
            [
                "6d47b0ce.054b2"
            ]
        ]
    },
    {
        "id": "6d47b0ce.054b2",
        "type": "debug",
        "z": "bf05387658e4fc4c",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 730,
        "y": 260,
        "wires": []
    },
    {
        "id": "51ef834a.3d95ec",
        "type": "function",
        "z": "bf05387658e4fc4c",
        "name": "Message",
        "func": "msg.token = 'Your Token';\nmsg.message = \"Hello World\";\nmsg.stickerPackageId = 11537;\nmsg.stickerId = 52002734;\n\nmsg.headers = {\n \"content-type\":\"application/x-www-form-urlencoded\",\n \"Authorization\":\"Bearer \" + msg.token\n};\nmsg.payload = {\n \"message\": msg.message,\n \"stickerPackageId\":msg.stickerPackageId,\n \"stickerId\":msg.stickerId\n};\nreturn msg;\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 380,
        "y": 260,
        "wires": [
            [
                "8cb66889.d96b28"
            ]
        ]
    },
    {
        "id": "75e765f7.d089fc",
        "type": "inject",
        "z": "bf05387658e4fc4c",
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
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "",
        "payloadType": "date",
        "x": 200,
        "y": 260,
        "wires": [
            [
                "51ef834a.3d95ec"
            ]
        ]
    }
]
```

### Quiz_203 – Node-RED to Google Sheet
##### • แสดงข้อมูลที่ได้ทำการทดสอบ

#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q203/Node-RED%20to%20Google%20Sheet/w03-w04-Quiz_203_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q203/Node-RED%20to%20Google%20Sheet/w03-w04-Quiz_203_0102.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "bccf86285085930b",
        "type": "tab",
        "label": "Q203-0101",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "7d1e14812a855917",
        "type": "http request",
        "z": "bccf86285085930b",
        "name": "",
        "method": "GET",
        "ret": "txt",
        "paytoqs": "ignore",
        "url": "https://docs.google.com/forms/u/1/d/e/1FAIpQLSfZrXI2Jkf2fCOMY31jeSyHmBqLsJPYtGRpINk90Y6CxExlCA/formResponse?entry.252906820=1111&entry.786950774=1111&entry.1482600245=1111&entry.1894859910=1111",
        "tls": "",
        "persist": false,
        "proxy": "",
        "insecureHTTPParser": false,
        "authType": "",
        "senderr": false,
        "headers": [],
        "x": 550,
        "y": 300,
        "wires": [
            [
                "b9895985dc7e1f96"
            ]
        ]
    },
    {
        "id": "cb0745f72cc70fd3",
        "type": "inject",
        "z": "bccf86285085930b",
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
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "",
        "payloadType": "date",
        "x": 160,
        "y": 300,
        "wires": [
            [
                "09b1e9e81f8ff62a"
            ]
        ]
    },
    {
        "id": "b9895985dc7e1f96",
        "type": "debug",
        "z": "bccf86285085930b",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 750,
        "y": 300,
        "wires": []
    },
    {
        "id": "09b1e9e81f8ff62a",
        "type": "function",
        "z": "bccf86285085930b",
        "name": "function 1",
        "func": "var data = {}\ndata.Tempp = parseFloat((Math.random() * 20) + 20).toFixed(2);\ndata.Humid = parseFloat((Math.random() * 20) + 40).toFixed(2);\ndata.Light = parseFloat((Math.random() * 20) + 60).toFixed(2);\ndata.RSSI = parseFloat((Math.random() * 20) + 80).toFixed(2);\n\nmsg.payload = data\n\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 360,
        "y": 300,
        "wires": [
            [
                "7d1e14812a855917"
            ]
        ]
    }
]
```


