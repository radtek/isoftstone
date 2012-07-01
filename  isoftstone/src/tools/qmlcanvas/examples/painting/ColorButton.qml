import Qt 4.7
Rectangle {
    id:picker
    width:22
    height:22

    MouseArea {
        id:mousearea
        hoverEnabled:true
        anchors.fill: parent
        onClicked: {
            canvas.drawColor = picker.color;
            picker.focus = true
        }
    }
    border.color: focus ? "#eee" : "#444"
    border.width: 1

    Rectangle {
        visible: !focus
        x:3
        y:3
        z:-1
        width:parent.width
        height:parent.height
        color:"#222"
    }

    states: [
        State { name: "focus" ;
                when: focus
                PropertyChanges { target: picker.border; color:"#eee"}
        },
        State {
                name:  "hover";
                when: mousearea.containsMouse && !focus;
                PropertyChanges { target: picker; scale:1.2}
        }
    ]
    transitions: Transition {
        ColorAnimation { target: picker.border; property: "color"; duration: 200 }
        NumberAnimation { target: picker; property: "scale"; duration: 100 }
    }
}

