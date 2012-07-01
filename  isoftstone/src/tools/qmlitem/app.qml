
import QmlItem 1.0
import QtQuick 1.0

Item
{
	width: 36
	height: 36

	Circle
	{
		cx: 17
		cy: 17
		radius: 16
		color: Qt.rgba(255,0,0,255)
		width: 1
	}
	Text
	{
		x: 5
		y: 11
		color: Qt.rgba(255,0,0,255)
		font.pointSize: 13
		text: "热备"
		transform
		{
			Rotation {angle:0}
			Scale {xScale:1; yScale:1.30769}
		}
	}
}
