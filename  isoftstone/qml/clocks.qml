
import QtQuick 1.0
import "content"
Rectangle {
    width: 320; height: 480
    color: "#646464"

    Column {
        anchors.centerIn: parent
        Clock { city: "New York"; shift: -4 }
        Clock { city: "Mumbai"; shift: 5.5 }
    }
    QuitButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
    }
}
