import "../../Canvas"
import Qt 4.7

Rectangle {
    id:root
    width:500
    height:300
    color:"#333"
    anchors.margins: 4

    Rectangle {
        width:300
        height:260
        color:"#222"
        x:8
        y:8

        Drawing {
            id:canvas
            width:parent.width
            height:parent.height
            anchors.margins:-2
            x:-3
            y:-3
        }
    }

    ListModel {
        id:model
    }

    Rectangle {
        color:"#222"
        anchors.right: parent.right
        height:parent.height
        width:180
        ListView {
            id:view
            anchors.fill: parent
            delegate: idelegate
            model: model
        }
    }

    Component {
        id:idelegate
        Item {
            id:root
            width:120
            height:142
            anchors.horizontalCenter: parent.horizontalCenter
            Canvas {
                width: 140
                height: 140
                canvasWidth:width
                canvasHeight:height
                color: "#222"
                smooth:true
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                onInit: {
                    var ctx = getContext("2d");
                    // Here we copy contents from drawing and apply drop shaddow
                    var img = image;
                    ctx.shadowOffsetX = 1;
                    ctx.shadowOffsetY = 1;
                    ctx.shadowBlur    = 14;
                    ctx.shadowColor   = "black";
                    ctx.drawImage(img, 25, 25, width-50, height-50);
                }
            }
            ListView.onAdd:NumberAnimation{target: root; property: "opacity" ; from:0; to:1; duration:500}
        }
    }

    FocusScope {
        id: colorpicker
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 8
        width:200
        height:22
        focus:true
        Row {
            id:row
            anchors.fill: parent
            spacing: 8
            Repeater {
                model: ["black","firebrick", "orange", "gold", "purple", "steelblue", "seagreen"]
                ColorButton { color: modelData }
            }
        }
    }

    Rectangle {
        id:savebutton
        width:80
        height:22
        color:"gray"
        radius: 4
        border.color: "#222"
        anchors.bottom: parent.bottom
        anchors.right: clearbutton.left
        anchors.leftMargin: 32
        anchors.margins: 8
        Text { text: "Save" ; anchors.centerIn: parent}
        MouseArea {
            anchors.fill:parent
            onClicked: {
                model.append({image:canvas});
                view.currentIndex = model.count-1
            }
        }
    }

    Rectangle {
        id:clearbutton
        width:80
        height:22
        color:"gray"
        border.color: "#222"
        radius: 4
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 8
        Text { text: "Clear" ; anchors.centerIn: parent}
        MouseArea {
            anchors.fill:parent
            onClicked: canvas.clear();
        }
    }
}
