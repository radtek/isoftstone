
import Qt 4.7

Rectangle {
    id: frame
    width: 800
    height: 480

    Image {
        id: image1
        x: 0
        y: 0
        width: 800
        height: 480
        source: "heart-run.png"

        Text {
            id: l_rate
            x: 163
            y: 163
            width: 64
            height: 27
            text: pmap.l_rate
            font.family: "Modern No. 20"
            font.strikeout: false
            font.underline: false
            font.italic: false
            font.bold: true
            style: Text.Normal
            font.pixelSize: 30
            smooth: false
        }

        Text {
            id: r_rate
            x: 582
            y: 163
            width: 64
            height: 27
            text: pmap.r_rate
            smooth: false
            font.pixelSize: 30
            style: Text.Normal
            font.underline: false
            font.strikeout: false
            font.italic: false
            font.bold: true
            font.family: "Modern No. 20"
        }

        Text {
            id: l_in_press
            x: 163
            y: 227
            width: 64
            height: 27
            text: pmap.l_in_press
            smooth: false
            font.pixelSize: 30
            style: Text.Normal
            font.underline: false
            font.strikeout: false
            font.italic: false
            font.bold: true
            font.family: "Modern No. 20"
        }

        Text {
            id: l_out_press
            x: 163
            y: 303
            width: 68
            height: 27
            text: pmap.l_out_press
            smooth: false
            font.pixelSize: 30
            style: Text.Normal
            font.underline: false
            font.strikeout: false
            font.italic: false
            font.family: "Modern No. 20"
            font.bold: true
        }

        Text {
            id: l_shrink
            x: 163
            y: 379
            width: 68
            height: 27
            text: pmap.l_shrink
            smooth: false
            font.pixelSize: 30
            style: Text.Normal
            font.underline: false
            font.strikeout: false
            font.italic: false
            font.bold: true
            font.family: "Modern No. 20"
        }

        Text {
            id: r_in_press
            x: 582
            y: 227
            width: 64
            height: 27
            text: pmap.r_in_press
            smooth: false
            font.pixelSize: 30
            style: Text.Normal
            font.underline: false
            font.strikeout: false
            font.italic: false
            font.family: "Modern No. 20"
            font.bold: true
        }

        Text {
            id: r_out_press
            x: 582
            y: 303
            width: 64
            height: 27
            text: pmap.r_out_press
            smooth: false
            font.pixelSize: 30
            style: Text.Normal
            font.underline: false
            font.strikeout: false
            font.italic: false
            font.family: "Modern No. 20"
            font.bold: true
        }

        Text {
            id: r_shrink
            x: 582
            y: 374
            width: 64
            height: 27
            text: pmap.r_shrink
            smooth: false
            font.pixelSize: 30
            style: Text.Normal
            font.underline: false
            font.strikeout: false
            font.italic: false
            font.bold: true
            font.family: "Modern No. 20"
        }
    }
}
