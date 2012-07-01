
import QtQuick 1.0
Image {
    source: "../pics/quit.png"
    scale: quitMouse.pressed ? 0.8 : 1.0
    smooth: quitMouse.pressed
    MouseArea {
        id: quitMouse
        anchors.fill: parent
        anchors.margins: -10
        onClicked: Qt.quit()
    }
}
