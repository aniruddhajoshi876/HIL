#ifndef SG_TARGET_H
#define SG_TARGET_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "sg_common.h"
#include <stdint.h>

// Writes the mac address of the host link ethernet controller to outMac.
// outMac should be a byte array with 6 bytes in it.
// The functions returns 0 on success and -1 on failure.
int sg_target_getHostLinkMac(unsigned char* outMac);

//Reads the temperature on the CPU die
//For processors who don't support this, read the temperature of a random CPU core
//(Just the one that is currently running the thread)
int32_t sg_getCpuTemperature();

typedef enum {
	CL630,
	SD631,
	Xeon,
	Baseline,
	Baseline_TopLayer, // Special Baseline with only the top layer (light version)
	MobileV2,
	SBC,
	Unit,
	Corvalent,
	MobileAEG,
	Education2,
	PT631,
	MobileV3,
	Apollo,
	Stelli,
	Marmot,
	Nigora,
	NonSpeedgoat
	} sg_TargetType;
sg_TargetType sg_getTargetType();

#ifdef __QNX__
int sg_getHostLinkInterface();
#endif
int sg_getSerialNumber();
int sg_getSerialNumberInternal();
int sg_getSerialNumberSupplier();

///////////////////////////////////////////////////////////////////////////////////////////////
// PCI & IRQ specific
///////////////////////////////////////////////////////////////////////////////////////////////

//An element in the PCI bus hierarchy  (e.g. an endpoint, a switch, ...)
typedef struct _sg_topo_node{
	uint32_t bus;
	uint32_t slot;
	uint32_t func;
	uint32_t VID;
	uint32_t DID;
	uint32_t SubVID;
	uint32_t SubDID;
	uint32_t classcode;
	char* interfaceType;
	bool MF; 				//Multi-function device
	uint32_t headerType; 	//00h Standard Header - 01h PCI-to-PCI Bridge - 02h CardBus Bridge
	uintptr_t customData;
	struct _sg_topo_node *parent;
} sg_topo_node;

//If the element afrom above is a bridge (switches also go in that category),
//it's customData pointer contains a sg_topo_bridge object, with more infor about the
//underlying bus segments
typedef struct _sg_topo_bridge{
	uint32_t prim;			//Is always 0 in the bridges, I don't know what this is meant for
	uint32_t sec;
	uint32_t sub;
	uint32_t nChildren;
	struct _sg_topo_node *children;
} sg_topo_bridge;

//Returns the IRQ number assigned to the INTA of a device
int32_t sg_getIrqNumber(sg_PCIDevice* device);

//Returns a structure containing the full PCI bus hierarchy as rooted tree from the root complex
int32_t sg_getPciTopology(sg_topo_node** rootComplex);
int32_t sg_getPciTopologyAtBus(sg_topo_node** rootComplex, uint32_t bus);
//Print the structure (or a subbranch)
void sg_printPciTopology(sg_topo_node* branch, uint32_t nElements);

int sg_translateEthernetInterfaces(void);

const char * sg_getTargetMarketingName(void);

#ifdef __linux__

int sg_configureEthercat(unsigned int absIndex);

int sg_teardownEthercat(unsigned int absIndex);

// Writes the name of the serial device node into 'outStr' that matches the specified port number.
// E.g. searching for port 0x220 might return "/dev/ttyS0".
// 'maxLength' is the length of the 'outStr' buffer.
int sg_findSerialDeviceByPort(uint32_t addr, char *outStr, size_t maxLength);

// Writes the name of the serial device node into 'outStr' that matches the specified PCI device.
// Some I/O modules provide multiple serial ports, so you also need to specify the port number.
// E.g. searching for the IO503 on PCI bus 7 slot 4 port 2 might return "/dev/ttySTDRV002_2".
// 'maxLength' is the length of the 'outStr' buffer.
int sg_findSerialDeviceByPci(sg_PCIDevice *pciInfo, int port, char *outStr, size_t maxLength);

#endif // __linux__

#ifdef __cplusplus
}
#endif

#endif // #ifndef SG_TARGET_H
