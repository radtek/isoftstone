import "../../Canvas"
import "blobsallad.js" as Blob
import Qt 4.7

Canvas {
    width:500
    height:500

    property color color: "#ffeeaa"

    Timer {
        id: heartbeat;
        interval: 25;
        repeat: true
        running:true
        triggeredOnStart: true;
        onTriggered: {
            var ctx = getContext();
            ctx.clearRect(0, 0, width, height);
            Blob.update();
            Blob.draw(ctx);
        }
    }
    MouseArea {
        id:mousearea
        hoverEnabled:true
        anchors.fill: parent
        onPressed: { Blob.mousePressed(mouseX, mouseY) }         
        onReleased: { Blob.mouseReleased(mouseX, mouseY) }         
        onPositionChanged: { Blob.mouseMoved(mouseX, mouseY) }         
    }

    Button {
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        anchors.margins:16
        id:join
        text: "Split"
        onClicked: Blob.blobColl.split(); 
    }
    Button {
        anchors.bottom:parent.bottom
        anchors.horizontalCenter:parent.horizontalCenter
        anchors.margins:16
        text: "Join"
        onClicked: Blob.blobColl.join(); 
    }
    Button {
        anchors.bottom:parent.bottom
        anchors.right:parent.right
        anchors.margins:16
        text: "Gravity"
        onClicked: Blob.toggleGravity(); 
    }

    Component.onCompleted: Blob.init()
}

