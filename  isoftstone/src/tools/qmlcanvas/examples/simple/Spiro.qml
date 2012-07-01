import "../../Canvas"
import Qt 4.7

// Spirograph

Canvas {
    width:200
    height:200

    property color color: "#ffee00"

    MouseArea {
        id:mousearea
        hoverEnabled:true
        anchors.fill: parent
        onPositionChanged: { requestPaint(); }
    }

    onPaint: { draw(); }

    function draw() {
        var ctx = getContext();
        ctx.save();
        ctx.fillStyle = "white"
        ctx.fillRect(0,0,width, height);
        ctx.strokeStyle = color;
        ctx.translate((width/2), (height/2));
        ctx.rotate(mousearea.mouseY/width)
        drawSpirograph(ctx,20*(2)/(1),-8*(3)/(1),mousearea.mouseX/2);
        ctx.globalAlpha = 0.5;
        drawSpirograph(ctx,20*(2)/(1),-8*(3)/(1),mousearea.mouseX/2 + 5);
        ctx.restore();
    }

    function drawSpirograph(ctx,R,r,O){
        var x1 = R-O;
        var y1 = 0;
        var i  = 1;
        ctx.beginPath();
        ctx.moveTo(x1,y1);
        do {
            if (i>20000) break;
            var fuzz = (i)*Math.PI/72;
            var x2 = (R+r)*Math.cos(fuzz) - (r+O)*Math.cos(((R+r)/r)*(fuzz))
            var y2 = (R+r)*Math.sin(fuzz) - (r+O)*Math.sin(((R+r)/r)*(fuzz))
            ctx.lineTo(x2,y2);
            x1 = x2;
            y1 = y2;
            i++;
        } while (x2 != R-O && y2 != 0 );
        ctx.stroke();
    }
}

