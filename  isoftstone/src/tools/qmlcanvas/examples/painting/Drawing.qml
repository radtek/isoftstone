import "../../Canvas"
import Qt 4.7


Canvas {
    id:canvas
    color: "white"
    property int paintX
    property int paintY
    property int count: 0
    property int lineWidth: 2
    property variant drawColor: "black"
    property variant ctx: getContext("2d");

    MouseArea {
        id:mousearea
        hoverEnabled:true
        anchors.fill: parent
        onClicked: drawPoint();
        onPositionChanged:  {
            if (mousearea.pressed)
                drawLineSegment();
            paintX = mouseX;
            paintY = mouseY;
        }
    }

    function drawLineSegment() {
        ctx.beginPath();
        ctx.strokeStyle = drawColor
        ctx.lineWidth = lineWidth
        ctx.moveTo(paintX, paintY);
        ctx.lineTo(mousearea.mouseX, mousearea.mouseY);
        ctx.stroke();
        ctx.closePath();
    }

    function drawPoint() {
        ctx.lineWidth = lineWidth
        ctx.fillStyle = drawColor
        ctx.fillRect(mousearea.mouseX, mousearea.mouseY, 2, 2);
    }

    function clear() {
        ctx.clearRect(0, 0, width, height);
    }
}
