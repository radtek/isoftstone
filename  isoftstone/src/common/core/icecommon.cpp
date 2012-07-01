
#include "icecommon.h"
#include <Ice/Ice.h>
#include <IceSSL/IceSSL.h>

using namespace std;
using namespace Ice;


void CIceCommon::displayCurrent(const Ice::Current& curr)
{
	std::cout << curr;
}

Ice::Context CIceCommon::getEndpointInfoAsContext(const Ice::Current& c)
{
	ostringstream os;

	Ice::Context ctx;
	Ice::EndpointInfoPtr info = c.con->getEndpoint()->getInfo();
	os << info->timeout;
	ctx["timeout"] = os.str();
	ctx["compress"] = info->compress ? "true" : "false";
	ctx["datagram"] = info->datagram() ? "true" : "false";
	ctx["secure"] = info->datagram() ? "true" : "false";
	os.str("");
	os << info->type();
	ctx["type"] = os.str();

	Ice::IPEndpointInfoPtr ipinfo = Ice::IPEndpointInfoPtr::dynamicCast(info);

	ctx["host"] = ipinfo->host;
	os.str("");
	os << ipinfo->port;
	ctx["port"] = os.str();

	if(Ice::UDPEndpointInfoPtr::dynamicCast(ipinfo))
	{
		Ice::UDPEndpointInfoPtr udp = Ice::UDPEndpointInfoPtr::dynamicCast(ipinfo);
		ctx["protocolMajor"] = udp->protocolMajor;
		ctx["protocolMinor"] = udp->protocolMinor;
		ctx["encodingMajor"] = udp->encodingMajor;
		ctx["encodingMinor"] = udp->encodingMinor;
		ctx["mcastInterface"] = udp->mcastInterface;
		ctx["mcastTtl"] = udp->mcastTtl;
	}

	return ctx;
}

Ice::Context CIceCommon::getConnectionInfoAsContext(const Ice::Current& c)
{
	Ice::Context ctx;
	Ice::ConnectionInfoPtr info = c.con->getInfo();
	ctx["adapterName"] = info->adapterName;
	ctx["incoming"] = info->incoming ? "true" : "false";
	ostringstream os;

	Ice::IPConnectionInfoPtr ipinfo = Ice::IPConnectionInfoPtr::dynamicCast(info);
	ctx["localAddress"] = ipinfo->localAddress;
	os.str("");
	os << ipinfo->localPort;
	ctx["localPort"] = os.str();
	ctx["remoteAddress"] = ipinfo->remoteAddress;
	os.str("");
	os << ipinfo->remotePort;
	ctx["remotePort"] = os.str();

	return ctx;
}