// Adopted from code found at http://www.anxioussilence.co.uk
// Original author can be contacted at bob@anxioussilence.co.uk

var tId;
var cHeight = 0;
var cWidth = 0;
var numBalls = 100;
var balls = new Array();

function Ball(){
    this.xPos = 0;
    this.yPos = 0;
    this.vx = 0;
    this.vy = 0;
    this.radius = 5;
    this.colour;
    this.wind;
    this.gravity;
    this.sizeWobble;

    this.reset = function() {
        this.xPos = cWidth / 2;
        this.yPos = cHeight / 2;
        this.vx = Math.random() * 10 - 5;
        this.vy = Math.random() * 10 - 5;
        this.colour = randomColour();
        this.wind = Math.random() * 2 - 1;
        this.gravity = Math.random() * 2 - 1;
        this.radius = Math.random() * 20 + 5;
        this.sizeWobble = Math.random() * 2 - 1;
    }
}

function init(w, h) {

    // Set canvas values
    cHeight = w
    cWidth = h;

    // Generate balls
    for(var i = 0;i < numBalls;i++){
        balls.push(new Ball());
        balls[i].reset();
    }
}

function drawBalls(){
    var ctx = getContext();
    for(var i = 0;i < numBalls;i++){
        drawCircle(balls[i].xPos, balls[i].yPos, balls[i].radius, balls[i].colour);
        balls[i].vy += balls[i].gravity;
        balls[i].vx += balls[i].wind;
        balls[i].xPos += balls[i].vx;
        balls[i].yPos += balls[i].vy;
        if(balls[i].radius > 2){
            balls[i].radius += balls[i].sizeWobble;
        }

        if(
                balls[i].xPos - balls[i].radius > cWidth||
                balls[i].xPos + balls[i].radius < 0||
                balls[i].yPos - balls[i].radius > cHeight||
                balls[i].yPos + balls[i].radius < 0
                ){
            balls[i].reset();
        }
    }
}

function randomColour(){
    var red = Math.round(Math.random() * 255);
    var green = Math.round(Math.random() * 255);
    var blue = Math.round(Math.random() * 255);
    return "rgb(" + red + ", " + green + ", " + blue + ")";
}

function drawCircle(cx, cy, radius, colour){
    var ctx = getContext();    
    ctx.fillStyle = colour;
    ctx.strokeStyle = "rgb(60, 80, 50)";
    ctx.beginPath();
    ctx.arc(cx,cy,radius,0,Math.PI*2,true); // Outer circle
    ctx.fill();
    ctx.stroke();
}
