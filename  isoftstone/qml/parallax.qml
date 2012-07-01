
import QtQuick 1.0
import "content"  // for loading the Clock element

Rectangle {
    width: 320; height: 480

    ParallaxView {
        id: parallax
        anchors.fill: parent
        background: "pics/background.jpg"

        Item {
            property url icon: "pics/yast-wol.png"
            width: 320; height: 480
            Clock { anchors.centerIn: parent }
        }

        Item {
            property url icon: "pics/home-page.svg"
            width: 320; height: 480
            Smiley { }
        }

        Item {
            property url icon: "pics/yast-joystick.png"
            width: 320; height: 480

            Loader {
                anchors { top: parent.top; topMargin: 0; horizontalCenter: parent.horizontalCenter }
                width: 320; height: 480
                clip: true; 
                source: "clocks.qml"
                Component.onCompleted: item.inAnotherDemo = true;
            }
        }
    }
}
