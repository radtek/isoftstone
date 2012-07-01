#ifndef GFILE_ENUM_H
#define GFILE_ENUM_H

#include <QGraphicsItem>

enum GEnum
{
	EUserType = QGraphicsItem::Type + 1,
	EACLine,
	EACLineEnd,
	EBar,
	EBay,
	EBus,
	ECBreaker,
	ECT,
	ECapacitor,
	ECapacitor_P,
	ECapacitor_S,
	EClock,
	EConnectLine,
	ECurve,
	EDText,
	EDcDot,
	EDcLine,
	EDial,
	EDisconnector,
	EDollyBreaker,
	EDynamic,
	EEnergyConsumer,
	EEntity,
	EField,
	EGenerator,
	EGrid,
	EGroundDisconnector,
	EHisTable,
	EInterfaceLine,
	ELayer,
	ELegend,
	EMerge,
	EOther,
	EPie,
	EPowerFlow,
	EProtect,
	EReactor,
	EReactor_P,
	EReactor_S,
	ERectifierInverter,
	ESensitive,
	EState,
	EStatus,
	ETable,
	ETerminal,
	EText,
	ETransformer2,
	ETransformer3,
	EX_axis,
	EY_axis,
	EZxddd,
	ECircle,
	ECirclearc,
	EDiamond,
	EEllipse,
	EHandline,
	EImage,
	ELine,
	EPoke,
	EPolygon,
	EPolyline,
	ERect,
	ERoundrect,
	ETriangle,
	EUiContext,
};


inline char* toString(GEnum eType)
{
	switch(eType)
	{
	case EACLine:		return "EACLine";
	case EACLineEnd:	return "EACLineEnd";
	case EBar:			return "EBar";
	case EBay:			return "EBay";
	case EBus:			return "EBus";
	case ECBreaker:		return "ECBreaker";
	case ECT:			return "ECT";
	case ECapacitor:	return "ECapacitor";
	case ECapacitor_P:	return "ECapacitor_P";
	case ECapacitor_S:	return "ECapacitor_S";
	case EClock:		return "EClock";
	case EConnectLine:	return "EConnectLine";
	case ECurve:		return "ECurve";
	case EDText:		return "EDText";
	case EDcDot:		return "EDcDot";
	case EDcLine:		return "EDcLine";
	case EDial:			return "EDial";
	case EDisconnector:	return "EDisconnector";
	case EDollyBreaker:	return "EDollyBreaker";
	case EDynamic:		return "EDynamic";
	case EEnergyConsumer:	return "EEnergyConsumer";
	case EEntity:		return "EEntity";
	case EField:		return "EField";
	case EGenerator:	return "EGenerator";
	case EGrid:			return "EGrid";
	case EGroundDisconnector:	return "EGroundDisconnector";
	case EHisTable:		return "EHisTable";
	case EInterfaceLine:	return "EInterfaceLine";
	case ELayer:		return "ELayer";
	case ELegend:		return "ELegend";
	case EMerge:		return "EMerge";
	case EOther:		return "EOther";
	case EPie:			return "EPie";
	case EPowerFlow:	return "EPowerFlow";
	case EProtect:		return "EProtect";
	case EReactor:		return "EReactor";
	case EReactor_P:	return "EReactor_P";
	case EReactor_S:	return "EReactor_S";
	case ERectifierInverter:	return "ERectifierInverter";
	case ESensitive:	return "ESensitive";
	case EState:		return "EState";
	case EStatus:		return "EStatus";
	case ETable:		return "ETable";
	case ETerminal:		return "ETerminal";
	case EText:			return "EText";
	case ETransformer2:	return "ETransformer2";
	case ETransformer3:	return "ETransformer3";
	case EX_axis:		return "EX_axis";
	case EY_axis:		return "EY_axis";
	case EZxddd:		return "EZxddd";
	case ECircle:		return "ECircle";
	case ECirclearc:	return "ECirclearc";
	case EDiamond:		return "EDiamond";
	case EEllipse:		return "EEllipse";
	case EHandline:		return "EHandline";
	case EImage:		return "EImage";
	case ELine:			return "ELine";
	case EPoke:			return "EPoke";
	case EPolygon:		return "EPolygon";
	case EPolyline:		return "EPolyline";
	case ERect:			return "ERect";
	case ERoundrect:	return "ERoundrect";
	case ETriangle:		return "ETriangle";
	case EUiContext:	return "EUiContext";
	default:			return "UnKnown";
	}
}
#endif
