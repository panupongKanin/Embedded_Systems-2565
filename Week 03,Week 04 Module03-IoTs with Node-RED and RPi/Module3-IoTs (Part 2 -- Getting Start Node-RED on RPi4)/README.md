### Quiz_201 – Node-RED UI
##### • แสดงข้อมูลที่ได้ทำการทดสอบ

#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q201/Node-RED%20UI/w03-w04-Quiz_201_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%202%20--%20Getting%20Start%20Node-RED%20on%20RPi4)/Q201/Node-RED%20UI/w03-w04-Quiz_201_0102.png" />

#### code ที่ใช้
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

### Quiz_302 – MQTT Client with Node-RED
##### • ทดสอบควบคุม 4 LED ด้วย Raspberry Pi ผ่าน Node-RED
##### • เพิ่มเติมให้ส่งข้อมูล Temperature ไปแสดงที่ บน Server

### Quiz_303 – MQTT Server on Raspberry Pi
##### • ทดสอบควบคุม 4 LED ด้วย Raspberry Pi ผ่าน Node-RED ไปยัง private server
##### • เพิ่มเติมให้ส่งข้อมูล Temperature ไปแสดงที่ บน private Server
