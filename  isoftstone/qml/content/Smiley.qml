
import QtQuick 1.0

Item {
    id: window
    width: 320; height: 480

    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        y: smiley.minHeight + 58
        source: "../pics/shadow.png"

        scale: smiley.y * 0.5 / (smiley.minHeight - smiley.maxHeight)
    }

    Image {
        id: smiley
        property int maxHeight: window.height / 3
        property int minHeight: 2 * window.height / 3

        anchors.horizontalCenter: parent.horizontalCenter
        y: minHeight
        source: "../pics/face-smile.png"

        SequentialAnimation on y {
            loops: Animation.Infinite

            NumberAnimation {
                from: smiley.minHeight; to: smiley.maxHeight
                easing.type: Easing.OutExpo; duration: 300
            }

            NumberAnimation {
                from: smiley.maxHeight; to: smiley.minHeight
                easing.type: Easing.OutBounce; duration: 1000
            }

            PauseAnimation { duration: 500 }
        }
    }
}

