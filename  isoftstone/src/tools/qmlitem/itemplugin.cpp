
#include <qdeclarative.h>

#include "itemplugin.h"
#include "qmlitem.h"


void CItemPlugin::registerTypes(const char *uri)
{
	qmlRegisterType<CQMLLine>(uri, 1, 0, "Line");
	qmlRegisterType<CQMLCircle>(uri, 1, 0, "Circle");
	qmlRegisterType<CQMLEllipse>(uri, 1, 0, "Ellipse");
	qmlRegisterType<CQMLCircleArc>(uri, 1, 0, "CircleArc");
	qmlRegisterType<CQMLEllipseArc>(uri, 1, 0, "EllipseArc");
	qmlRegisterType<CQMLDiamond>(uri, 1, 0, "Diamond");
	qmlRegisterType<CQMLTriangle>(uri, 1, 0, "Triangle");
	qmlRegisterType<CQMLPolygon>(uri, 1, 0, "Polygon");
	qmlRegisterType<CQMLPolyline>(uri, 1, 0, "Polyline");
}

Q_EXPORT_PLUGIN2(itemplugin, CItemPlugin);