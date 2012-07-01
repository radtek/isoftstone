import "../../Canvas"
import Qt 4.7

import "balls.js" as Balls

Canvas {
    id: clock
    width:500
    height:400
    
    Timer {
        interval: 50; running: true; repeat: true
        onTriggered: draw();
    }

    function draw() {
        var ctx = getContext();
        ctx.clearRect(0, 0, width, height);
        Balls.drawBalls(ctx);
    }

    Component.onCompleted: Balls.init(width, height)
}


