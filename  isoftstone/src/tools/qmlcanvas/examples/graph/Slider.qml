import Qt 4.7

Rectangle {
    id: slider;
    width: 100; height: 15;
    property int value: Math.round(handle.x*100/(slider.width-handle.width))
    property color nodecolor: "black"
    color: "#aaaaaa"
    border.color: "#777777"
    border.width: 1
    radius: 2
    opacity:0.6

    MouseArea {
        id:baseMouse
        hoverEnabled: true
        anchors.fill: parent
    }

    Rectangle {
        smooth:true
        id: handle; width: 20; height: 16
        x:Math.random()*40
        color: nodecolor
        border.color: "#333333"
        border.width: 0
        MouseArea {
            id: handleMouse
            hoverEnabled: true
            anchors.fill: parent
            drag.target: parent; drag.axis: "XAxis"
            drag.minimumX: 0; drag.maximumX: slider.width - handle.width
        }
    }

    transitions: [
        Transition {
            PropertyAnimation { properties: "opacity"; duration: 120}
        }
    ]

    states: [
        State {
            name: "hover"
            when: handleMouse.containsMouse || baseMouse.containsMouse
                PropertyChanges { target: slider; opacity:1}
        }
    ]
}
