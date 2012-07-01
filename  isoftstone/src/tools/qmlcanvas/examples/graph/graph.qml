import "../../Canvas"
import Qt 4.7

Canvas {
    width:600
    height:400
    property int count:6

    Column {
        id:sliders
        y:30
        anchors.right: parent.right
        anchors.margins: 30
        spacing:12

        Slider { nodecolor: "#88aaaa" ; onValueChanged:{requestPaint()}}
        Slider { nodecolor: "#aa8888" ; onValueChanged:{requestPaint()}}
        Slider { nodecolor: "#4488aa" ; onValueChanged:{requestPaint()}}
        Slider { nodecolor: "#444499" ; onValueChanged:{requestPaint()}}
        Slider { nodecolor: "#aa4444" ; onValueChanged:{requestPaint()}}
        Slider { nodecolor: "#559966" ; onValueChanged:{requestPaint()}}
    }

    onPaint: {

        var ctx = getContext();        
        var graphPadding = 20;
        var cHeight = height;
        var cWidth = width;

        var grad = ctx.createLinearGradient(0, 0, 0, height);
        grad.addColorStop(0,   '#fff'); // red
        grad.addColorStop(1, '#ccc'); // yellow
        ctx.fillStyle = grad;

        ctx.fillRect(0, 0, width, height);
        ctx.strokeStyle = "rgb(150,150,150)";
        ctx.lineWidth = 2;
	// Draw Axis
	ctx.beginPath();
	ctx.moveTo(graphPadding, graphPadding);
	ctx.lineTo(graphPadding,cHeight - graphPadding);
	ctx.lineTo(cWidth - graphPadding, cHeight - graphPadding);
	ctx.stroke();
	ctx.closePath();

	// Display a point for each slider, spaced equally
        var availableSpace = cWidth - (graphPadding * count);
        var horizSpace = availableSpace / count;
        var vertSpace = cHeight - (graphPadding * count);

	// Create an array of y points
	var points = new Array();
        for(var i = 0;i < count;i++){
            // Get Ypos
            var yPercent  =  (sliders.children[i].value - 100) * -1;
            var yPos = (vertSpace * (yPercent / 100) + (graphPadding * 2));
            points.push(yPos);
	}

	// Draw Lines
	var xPos = graphPadding * 2;
	ctx.beginPath();
        for(i = 0;i < count;i++){
            if(i == 0)
                ctx.moveTo(xPos, points[i]);
            else
                ctx.lineTo(xPos, points[i]);
            xPos += horizSpace;
	}
	ctx.stroke();
	ctx.closePath();

        // Draw Dots
        var xPos = graphPadding * 2;
        for(i = 0;i < count;i++){
            drawCircle(ctx, xPos, points[i], count, sliders.children[i].nodecolor);
            xPos += horizSpace;
        }

	// Draw Axis

        ctx.lineWidth = 1;
        ctx.strokeStyle = "rgba(0, 0, 0, 0.05)"
        for (var y = 0; y < height - graphPadding; y += height/20) {
          ctx.moveTo(graphPadding, y);
          ctx.lineTo(width - graphPadding, y);
        }
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(graphPadding, graphPadding);
        ctx.lineTo(graphPadding,cHeight - graphPadding);
        ctx.lineTo(cWidth - graphPadding, cHeight - graphPadding);
	ctx.stroke();
	ctx.closePath();
    }

    function drawCircle(ctx, x, y, radius, colour){
        ctx.save();
        ctx.fillStyle = colour;
        ctx.beginPath();
        ctx.arc(x-1, y-1, radius,0,Math.PI*2,true); // Outer circle
        ctx.fill();
        ctx.restore();
    }
}
