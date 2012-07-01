
import QtQuick 1.0

Item {
    id: root

    property alias background: background.source
    property int currentIndex: 0
    default property alias content: visualModel.children

    Image {
        id: background
        fillMode: Image.TileHorizontally
        x: -list.contentX / 2
        width: Math.max(list.contentWidth, parent.width)
    }

    ListView {
        id: list
        anchors.fill: parent

        currentIndex: root.currentIndex
        onCurrentIndexChanged: root.currentIndex = currentIndex

        orientation: Qt.Horizontal
        boundsBehavior: Flickable.DragOverBounds
        model: VisualItemModel { id: visualModel }

        highlightRangeMode: ListView.StrictlyEnforceRange
        snapMode: ListView.SnapOneItem
    }

    ListView {
        id: selector

        height: 50
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: Math.min(count * 50, parent.width - 20)
        interactive: width == parent.width - 20
        orientation: Qt.Horizontal

        currentIndex: root.currentIndex
        onCurrentIndexChanged: root.currentIndex = currentIndex

        model: visualModel.children
        delegate: Item {
            width: 50; height: 50
            id: delegateRoot

            Image {
                id: image
                source: modelData.icon
                smooth: true
                scale: 0.8
            }

            MouseArea {
                anchors.fill: parent
                onClicked: { root.currentIndex = index }
            }

            states: State {
                name: "Selected"
                when: delegateRoot.ListView.isCurrentItem == true
                PropertyChanges {
                    target: image
                    scale: 1
                    y: -5
                }
            }
            transitions: Transition {
                NumberAnimation { properties: "scale,y" }
            }
        }

        Rectangle {
            color: "#60FFFFFF"
            x: -10; y: -10; z: -1
            width: parent.width + 20; height: parent.height + 20
            radius: 10
        }
    }
}
