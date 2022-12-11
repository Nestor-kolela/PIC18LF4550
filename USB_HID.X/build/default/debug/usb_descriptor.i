# 1 "usb_descriptor.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/kolel/.mchp_packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "usb_descriptor.c" 2
# 157 "usb_descriptor.c"
# 1 "./usb.h" 1
# 110 "./usb.h"
# 1 "./GenericTypeDefs.h" 1
# 63 "./GenericTypeDefs.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 2 3
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 122 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 132 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef int ptrdiff_t;
# 168 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stddef.h" 2 3
# 63 "./GenericTypeDefs.h" 2


typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
typedef enum _BIT { CLEAR = 0, SET } BIT;






typedef signed int INT;
typedef signed char INT8;
typedef signed short int INT16;
typedef signed long int INT32;



            typedef signed long long INT64;



typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned short int UINT16;




typedef unsigned long int UINT32;


            typedef unsigned long long UINT64;


typedef union
{
    UINT8 Val;
    struct
    {
                    UINT8 b0:1;
                    UINT8 b1:1;
                    UINT8 b2:1;
                    UINT8 b3:1;
                    UINT8 b4:1;
                    UINT8 b5:1;
                    UINT8 b6:1;
                    UINT8 b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union
{
    UINT16 Val;
    UINT8 v[2] ;
    struct
    {
        UINT8 LB;
        UINT8 HB;
    } byte;
    struct
    {
                    UINT8 b0:1;
                    UINT8 b1:1;
                    UINT8 b2:1;
                    UINT8 b3:1;
                    UINT8 b4:1;
                    UINT8 b5:1;
                    UINT8 b6:1;
                    UINT8 b7:1;
                    UINT8 b8:1;
                    UINT8 b9:1;
                    UINT8 b10:1;
                    UINT8 b11:1;
                    UINT8 b12:1;
                    UINT8 b13:1;
                    UINT8 b14:1;
                    UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;
# 185 "./GenericTypeDefs.h"
typedef union
{
    UINT32 Val;
    UINT16 w[2] ;
    UINT8 v[4] ;
    struct
    {
        UINT16 LW;
        UINT16 HW;
    } word;
    struct
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
        UINT8 MB;
    } byte;
    struct
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct
    {
                    UINT8 b0:1;
                    UINT8 b1:1;
                    UINT8 b2:1;
                    UINT8 b3:1;
                    UINT8 b4:1;
                    UINT8 b5:1;
                    UINT8 b6:1;
                    UINT8 b7:1;
                    UINT8 b8:1;
                    UINT8 b9:1;
                    UINT8 b10:1;
                    UINT8 b11:1;
                    UINT8 b12:1;
                    UINT8 b13:1;
                    UINT8 b14:1;
                    UINT8 b15:1;
                    UINT8 b16:1;
                    UINT8 b17:1;
                    UINT8 b18:1;
                    UINT8 b19:1;
                    UINT8 b20:1;
                    UINT8 b21:1;
                    UINT8 b22:1;
                    UINT8 b23:1;
                    UINT8 b24:1;
                    UINT8 b25:1;
                    UINT8 b26:1;
                    UINT8 b27:1;
                    UINT8 b28:1;
                    UINT8 b29:1;
                    UINT8 b30:1;
                    UINT8 b31:1;
    } bits;
} UINT32_VAL;



typedef union
{
    UINT64 Val;
    UINT32 d[2] ;
    UINT16 w[4] ;
    UINT8 v[8] ;
    struct
    {
        UINT32 LD;
        UINT32 HD;
    } dword;
    struct
    {
        UINT16 LW;
        UINT16 HW;
        UINT16 UW;
        UINT16 MW;
    } word;
    struct
    {
                    UINT8 b0:1;
                    UINT8 b1:1;
                    UINT8 b2:1;
                    UINT8 b3:1;
                    UINT8 b4:1;
                    UINT8 b5:1;
                    UINT8 b6:1;
                    UINT8 b7:1;
                    UINT8 b8:1;
                    UINT8 b9:1;
                    UINT8 b10:1;
                    UINT8 b11:1;
                    UINT8 b12:1;
                    UINT8 b13:1;
                    UINT8 b14:1;
                    UINT8 b15:1;
                    UINT8 b16:1;
                    UINT8 b17:1;
                    UINT8 b18:1;
                    UINT8 b19:1;
                    UINT8 b20:1;
                    UINT8 b21:1;
                    UINT8 b22:1;
                    UINT8 b23:1;
                    UINT8 b24:1;
                    UINT8 b25:1;
                    UINT8 b26:1;
                    UINT8 b27:1;
                    UINT8 b28:1;
                    UINT8 b29:1;
                    UINT8 b30:1;
                    UINT8 b31:1;
                    UINT8 b32:1;
                    UINT8 b33:1;
                    UINT8 b34:1;
                    UINT8 b35:1;
                    UINT8 b36:1;
                    UINT8 b37:1;
                    UINT8 b38:1;
                    UINT8 b39:1;
                    UINT8 b40:1;
                    UINT8 b41:1;
                    UINT8 b42:1;
                    UINT8 b43:1;
                    UINT8 b44:1;
                    UINT8 b45:1;
                    UINT8 b46:1;
                    UINT8 b47:1;
                    UINT8 b48:1;
                    UINT8 b49:1;
                    UINT8 b50:1;
                    UINT8 b51:1;
                    UINT8 b52:1;
                    UINT8 b53:1;
                    UINT8 b54:1;
                    UINT8 b55:1;
                    UINT8 b56:1;
                    UINT8 b57:1;
                    UINT8 b58:1;
                    UINT8 b59:1;
                    UINT8 b60:1;
                    UINT8 b61:1;
                    UINT8 b62:1;
                    UINT8 b63:1;
    } bits;
} UINT64_VAL;





typedef void VOID;

typedef char CHAR8;
typedef unsigned char UCHAR8;

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned long DWORD;


typedef unsigned long long QWORD;
typedef signed char CHAR;
typedef signed short int SHORT;
typedef signed long LONG;


typedef signed long long LONGLONG;
typedef union
{
    BYTE Val;
    struct
    {
                    BYTE b0:1;
                    BYTE b1:1;
                    BYTE b2:1;
                    BYTE b3:1;
                    BYTE b4:1;
                    BYTE b5:1;
                    BYTE b6:1;
                    BYTE b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    WORD Val;
    BYTE v[2] ;
    struct
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct
    {
                    BYTE b0:1;
                    BYTE b1:1;
                    BYTE b2:1;
                    BYTE b3:1;
                    BYTE b4:1;
                    BYTE b5:1;
                    BYTE b6:1;
                    BYTE b7:1;
                    BYTE b8:1;
                    BYTE b9:1;
                    BYTE b10:1;
                    BYTE b11:1;
                    BYTE b12:1;
                    BYTE b13:1;
                    BYTE b14:1;
                    BYTE b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union
{
    DWORD Val;
    WORD w[2] ;
    BYTE v[4] ;
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct
    {
                    BYTE b0:1;
                    BYTE b1:1;
                    BYTE b2:1;
                    BYTE b3:1;
                    BYTE b4:1;
                    BYTE b5:1;
                    BYTE b6:1;
                    BYTE b7:1;
                    BYTE b8:1;
                    BYTE b9:1;
                    BYTE b10:1;
                    BYTE b11:1;
                    BYTE b12:1;
                    BYTE b13:1;
                    BYTE b14:1;
                    BYTE b15:1;
                    BYTE b16:1;
                    BYTE b17:1;
                    BYTE b18:1;
                    BYTE b19:1;
                    BYTE b20:1;
                    BYTE b21:1;
                    BYTE b22:1;
                    BYTE b23:1;
                    BYTE b24:1;
                    BYTE b25:1;
                    BYTE b26:1;
                    BYTE b27:1;
                    BYTE b28:1;
                    BYTE b29:1;
                    BYTE b30:1;
                    BYTE b31:1;
    } bits;
} DWORD_VAL;


typedef union
{
    QWORD Val;
    DWORD d[2] ;
    WORD w[4] ;
    BYTE v[8] ;
    struct
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct
    {
                    BYTE b0:1;
                    BYTE b1:1;
                    BYTE b2:1;
                    BYTE b3:1;
                    BYTE b4:1;
                    BYTE b5:1;
                    BYTE b6:1;
                    BYTE b7:1;
                    BYTE b8:1;
                    BYTE b9:1;
                    BYTE b10:1;
                    BYTE b11:1;
                    BYTE b12:1;
                    BYTE b13:1;
                    BYTE b14:1;
                    BYTE b15:1;
                    BYTE b16:1;
                    BYTE b17:1;
                    BYTE b18:1;
                    BYTE b19:1;
                    BYTE b20:1;
                    BYTE b21:1;
                    BYTE b22:1;
                    BYTE b23:1;
                    BYTE b24:1;
                    BYTE b25:1;
                    BYTE b26:1;
                    BYTE b27:1;
                    BYTE b28:1;
                    BYTE b29:1;
                    BYTE b30:1;
                    BYTE b31:1;
                    BYTE b32:1;
                    BYTE b33:1;
                    BYTE b34:1;
                    BYTE b35:1;
                    BYTE b36:1;
                    BYTE b37:1;
                    BYTE b38:1;
                    BYTE b39:1;
                    BYTE b40:1;
                    BYTE b41:1;
                    BYTE b42:1;
                    BYTE b43:1;
                    BYTE b44:1;
                    BYTE b45:1;
                    BYTE b46:1;
                    BYTE b47:1;
                    BYTE b48:1;
                    BYTE b49:1;
                    BYTE b50:1;
                    BYTE b51:1;
                    BYTE b52:1;
                    BYTE b53:1;
                    BYTE b54:1;
                    BYTE b55:1;
                    BYTE b56:1;
                    BYTE b57:1;
                    BYTE b58:1;
                    BYTE b59:1;
                    BYTE b60:1;
                    BYTE b61:1;
                    BYTE b62:1;
                    BYTE b63:1;
    } bits;
} QWORD_VAL;
# 110 "./usb.h" 2



# 1 "./usb_config.h" 1
# 113 "./usb.h" 2


# 1 "./usb_common.h" 1
# 86 "./usb_common.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\limits.h" 1 3





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\features.h" 1 3
# 6 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\limits.h" 2 3




# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/limits.h" 1 3
# 10 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\limits.h" 2 3
# 86 "./usb_common.h" 2
# 170 "./usb_common.h"
typedef union
{
    BYTE bitmap;
    struct
    {
        BYTE ep_num: 4;
        BYTE zero_pkt: 1;
        BYTE dts: 1;
        BYTE force_dts: 1;
        BYTE direction: 1;
    }field;

} TRANSFER_FLAGS;
# 244 "./usb_common.h"
typedef enum
{

    EVENT_NONE = 0,

    EVENT_DEVICE_STACK_BASE = 1,

    EVENT_HOST_STACK_BASE = 100,


    EVENT_HUB_ATTACH,


    EVENT_STALL,


    EVENT_VBUS_SES_REQUEST,




    EVENT_VBUS_OVERCURRENT,





    EVENT_VBUS_REQUEST_POWER,




    EVENT_VBUS_RELEASE_POWER,
# 285 "./usb_common.h"
    EVENT_VBUS_POWER_AVAILABLE,



    EVENT_UNSUPPORTED_DEVICE,



    EVENT_CANNOT_ENUMERATE,



    EVENT_CLIENT_INIT_ERROR,





    EVENT_OUT_OF_MEMORY,


    EVENT_UNSPECIFIED_ERROR,



    EVENT_DETACH,




    EVENT_TRANSFER,



    EVENT_SOF,


    EVENT_RESUME,



    EVENT_SUSPEND,



    EVENT_RESET,





    EVENT_DATA_ISOC_READ,





    EVENT_DATA_ISOC_WRITE,
# 352 "./usb_common.h"
    EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION,







    EVENT_1MS,


    EVENT_GENERIC_BASE = 400,

    EVENT_MSD_BASE = 500,

    EVENT_HID_BASE = 600,

    EVENT_PRINTER_BASE = 700,

    EVENT_CDC_BASE = 800,

    EVENT_CHARGER_BASE = 900,

    EVENT_AUDIO_BASE = 1000,

 EVENT_USER_BASE = 10000,




    EVENT_BUS_ERROR = 0x7fff

} USB_EVENT;
# 396 "./usb_common.h"
typedef struct _transfer_event_data
{
    TRANSFER_FLAGS flags;
    UINT32 size;
    BYTE pid;

} USB_TRANSFER_EVENT_DATA;
# 413 "./usb_common.h"
typedef struct _vbus_power_data
{
    BYTE port;
    BYTE current;
} USB_VBUS_POWER_EVENT_DATA;
# 426 "./usb_common.h"
typedef struct _override_client_driver_data
{
    WORD idVendor;
    WORD idProduct;
    BYTE bDeviceClass;
    BYTE bDeviceSubClass;
    BYTE bDeviceProtocol;
} USB_OVERRIDE_CLIENT_DRIVER_EVENT_DATA;
# 488 "./usb_common.h"
typedef BOOL (*USB_EVENT_HANDLER) ( USB_EVENT event, void *data, unsigned int size );
# 115 "./usb.h" 2

# 1 "./usb_ch9.h" 1
# 114 "./usb_ch9.h"
typedef struct __attribute__ ((packed)) _USB_DEVICE_DESCRIPTOR
{
    BYTE bLength;
    BYTE bDescriptorType;
    WORD bcdUSB;
    BYTE bDeviceClass;
    BYTE bDeviceSubClass;
    BYTE bDeviceProtocol;
    BYTE bMaxPacketSize0;
    WORD idVendor;
    WORD idProduct;
    WORD bcdDevice;
    BYTE iManufacturer;
    BYTE iProduct;
    BYTE iSerialNumber;
    BYTE bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;
# 140 "./usb_ch9.h"
typedef struct __attribute__ ((packed)) _USB_CONFIGURATION_DESCRIPTOR
{
    BYTE bLength;
    BYTE bDescriptorType;
    WORD wTotalLength;
    BYTE bNumInterfaces;
    BYTE bConfigurationValue;
    BYTE iConfiguration;
    BYTE bmAttributes;
    BYTE bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR;
# 165 "./usb_ch9.h"
typedef struct __attribute__ ((packed)) _USB_INTERFACE_DESCRIPTOR
{
    BYTE bLength;
    BYTE bDescriptorType;
    BYTE bInterfaceNumber;
    BYTE bAlternateSetting;
    BYTE bNumEndpoints;
    BYTE bInterfaceClass;
    BYTE bInterfaceSubClass;
    BYTE bInterfaceProtocol;
    BYTE iInterface;
} USB_INTERFACE_DESCRIPTOR;
# 186 "./usb_ch9.h"
typedef struct __attribute__ ((packed)) _USB_ENDPOINT_DESCRIPTOR
{
    BYTE bLength;
    BYTE bDescriptorType;
    BYTE bEndpointAddress;
    BYTE bmAttributes;
    WORD wMaxPacketSize;
    BYTE bInterval;
} USB_ENDPOINT_DESCRIPTOR;
# 236 "./usb_ch9.h"
typedef struct
{
    BYTE index;
    BYTE type;
    UINT16 language_id;

} DESCRIPTOR_ID;
# 251 "./usb_ch9.h"
typedef struct __attribute__ ((packed)) _USB_OTG_DESCRIPTOR
{
    BYTE bLength;
    BYTE bDescriptorType;
    BYTE bmAttributes;
} USB_OTG_DESCRIPTOR;
# 275 "./usb_ch9.h"
typedef struct __attribute__ ((packed)) _USB_STRING_DSC
{
    BYTE bLength;
    BYTE bDescriptorType;

} USB_STRING_DESCRIPTOR;
# 294 "./usb_ch9.h"
typedef struct __attribute__ ((packed)) _USB_DEVICE_QUALIFIER_DESCRIPTOR
{
    BYTE bLength;
    BYTE bType;
    WORD bcdUSB;
    BYTE bDeviceClass;
    BYTE bDeviceSubClass;
    BYTE bDeviceProtocol;
    BYTE bMaxPacketSize0;
    BYTE bNumConfigurations;
    BYTE bReserved;

} USB_DEVICE_QUALIFIER_DESCRIPTOR;
# 317 "./usb_ch9.h"
typedef union __attribute__ ((packed))
{

    struct __attribute__ ((packed))
    {
        BYTE bmRequestType;
        BYTE bRequest;
        WORD wValue;
        WORD wIndex;
        WORD wLength;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        WORD_VAL W_Value;
        WORD_VAL W_Index;
        WORD_VAL W_Length;
    };
    struct __attribute__ ((packed))
    {
        unsigned Recipient:5;
        unsigned RequestType:2;
        unsigned DataDir:1;
        unsigned :8;
        BYTE bFeature;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        union
        {
            BYTE bmRequestType;
            struct
            {
                BYTE recipient: 5;
                BYTE type: 2;
                BYTE direction: 1;
            };
        }requestInfo;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        BYTE bDscIndex;
        BYTE bDescriptorType;
        WORD wLangID;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        BYTE_VAL bDevADR;
        BYTE bDevADRH;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        BYTE bConfigurationValue;
        BYTE bCfgRSD;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        BYTE bAltID;
        BYTE bAltID_H;
        BYTE bIntfID;
        BYTE bIntfID_H;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        BYTE bEPID;
        BYTE bEPID_H;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned EPNum:4;
        unsigned :3;
        unsigned EPDir:1;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };



} CTRL_TRF_SETUP, SETUP_PKT, *PSETUP_PKT;
# 116 "./usb.h" 2



# 1 "./usb_device.h" 1
# 140 "./usb_device.h"
typedef enum
{



    DETACHED_STATE
                            = 0x00 ,


    ATTACHED_STATE
                            = 0x01 ,


    POWERED_STATE
                            = 0x02 ,


    DEFAULT_STATE
                            = 0x04 ,





    ADR_PENDING_STATE
                            = 0x08 ,


    ADDRESS_STATE
                            = 0x10 ,





    CONFIGURED_STATE
                            = 0x20
} USB_DEVICE_STATE;



typedef enum
{

    EVENT_CONFIGURED
                            = EVENT_DEVICE_STACK_BASE ,


    EVENT_SET_DESCRIPTOR,





    EVENT_EP0_REQUEST,
# 223 "./usb_device.h"
    EVENT_ATTACH,




    EVENT_TRANSFER_TERMINATED

} USB_DEVICE_STACK_EVENTS;
# 262 "./usb_device.h"
void USBDeviceInit(void);
# 367 "./usb_device.h"
void USBDeviceTasks(void);
# 419 "./usb_device.h"
void USBEnableEndpoint(BYTE ep, BYTE options);
# 512 "./usb_device.h"
void* USBTransferOnePacket(BYTE ep,BYTE dir,BYTE* data,BYTE len);
# 537 "./usb_device.h"
void USBStallEndpoint(BYTE ep, BYTE dir);
# 561 "./usb_device.h"
void USBCancelIO(BYTE endpoint);
# 658 "./usb_device.h"
void USBDeviceDetach(void);
# 703 "./usb_device.h"
void USBDeviceAttach(void);
# 742 "./usb_device.h"
void USBCtrlEPAllowStatusStage(void);
# 772 "./usb_device.h"
void USBCtrlEPAllowDataStage(void);
# 848 "./usb_device.h"
void USBDeferOUTDataStage(void);
extern volatile BOOL USBDeferOUTDataStagePackets;
# 918 "./usb_device.h"
void USBDeferStatusStage(void);
extern volatile BOOL USBDeferStatusStagePacket;
# 970 "./usb_device.h"
BOOL USBOUTDataStageDeferred(void);
# 1053 "./usb_device.h"
void USBDeferINDataStage(void);
extern volatile BOOL USBDeferINDataStagePackets;
# 1107 "./usb_device.h"
BOOL USBINDataStageDeferred(void);
# 1177 "./usb_device.h"
BOOL USBGetRemoteWakeupStatus(void);
# 1234 "./usb_device.h"
USB_DEVICE_STATE USBGetDeviceState(void);
# 1290 "./usb_device.h"
BOOL USBGetSuspendState(void);
# 1325 "./usb_device.h"
BOOL USBIsDeviceSuspended(void);
# 1368 "./usb_device.h"
BOOL USBIsBusSuspended(void);
# 1394 "./usb_device.h"
void USBSoftDetach(void);
# 1432 "./usb_device.h"
BOOL USBHandleBusy(void* handle);
# 1466 "./usb_device.h"
WORD USBHandleGetLength(void* handle);
# 1498 "./usb_device.h"
WORD USBHandleGetAddr(void*);
# 1598 "./usb_device.h"
void* USBGetNextHandle(BYTE ep_num, BYTE ep_dir);
# 1631 "./usb_device.h"
void USBEP0Transmit(BYTE options);
# 1659 "./usb_device.h"
void USBEP0SendRAMPtr(BYTE* src, WORD size, BYTE Options);
# 1691 "./usb_device.h"
void USBEP0SendconstPtr(BYTE* src, WORD size, BYTE Options);
# 1719 "./usb_device.h"
void USBEP0Receive(BYTE* dest, WORD size, void (*function));
# 1754 "./usb_device.h"
void* USBTxOnePacket(BYTE ep, BYTE* data, WORD len);
# 1791 "./usb_device.h"
void* USBRxOnePacket(BYTE ep, BYTE* data, WORD len);
# 1823 "./usb_device.h"
BOOL USB_APPLICATION_EVENT_HANDLER(BYTE address, USB_EVENT event, void *pdata, WORD size);
# 1855 "./usb_device.h"
void *USBDeviceCBGetDescriptor ( UINT16 *length,
                                    UINT8 *ptr_type,
                                    DESCRIPTOR_ID *id);
# 1925 "./usb_device.h"
typedef struct __attribute__ ((packed))
{
    union __attribute__ ((packed))
    {


        BYTE *bRam;
        const BYTE *bRom;
        WORD *wRam;
        const WORD *wRom;
    }pSrc;
    union __attribute__ ((packed))
    {
        struct __attribute__ ((packed))
        {

            BYTE ctrl_trf_mem :1;
            BYTE reserved :5;


            BYTE includeZero :1;

            BYTE busy :1;
        }bits;
        BYTE Val;
    }info;
    WORD_VAL __attribute__((aligned)) wCount;
}IN_PIPE;

extern IN_PIPE inPipes[];

typedef struct __attribute__ ((packed))
{
    union __attribute__ ((packed))
    {


        BYTE *bRam;
        WORD *wRam;
    }pDst;
    union __attribute__ ((packed))
    {
        struct __attribute__ ((packed))
        {
            BYTE reserved :7;

            BYTE busy :1;
        }bits;
        BYTE Val;
    }info;
    WORD_VAL wCount;
    void (*pFunc)(void);
}OUT_PIPE;
# 1987 "./usb_device.h"
extern BOOL RemoteWakeup;
extern BOOL USBBusIsSuspended;
extern USB_DEVICE_STATE USBDeviceState;
extern BYTE USBActiveConfiguration;
# 119 "./usb.h" 2
# 130 "./usb.h"
# 1 "./usb_hal.h" 1
# 93 "./usb_hal.h"
# 1 "./usb_hal_pic18.h" 1
# 118 "./usb_hal_pic18.h"
# 1 "./Compiler.h" 1
# 118 "./usb_hal_pic18.h" 2


# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdio.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdio.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 1 3





typedef void * va_list[1];




typedef void * __isoc_va_list[1];
# 137 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long ssize_t;
# 246 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long off_t;
# 399 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdio.h" 2 3
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

__attribute__((__format__(__printf__, 1, 2)))
int printf(const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int fprintf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int sprintf(char *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 3, 4)))
int snprintf(char *restrict, size_t, const char *restrict, ...);

__attribute__((__format__(__printf__, 1, 0)))
int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 2, 0)))
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 3, 0)))
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

__attribute__((__format__(__scanf__, 1, 2)))
int scanf(const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int fscanf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int sscanf(const char *restrict, const char *restrict, ...);

__attribute__((__format__(__scanf__, 1, 0)))
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__scanf__, 2, 0)))
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 120 "./usb_hal_pic18.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 1 3
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 411 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 2 3


void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);
# 65 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c99\\string.h" 3
char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 121 "./usb_hal_pic18.h" 2
# 284 "./usb_hal_pic18.h"
typedef union _BD_STAT
{
    BYTE Val;
    struct{

        unsigned BC8:1;
        unsigned BC9:1;
        unsigned BSTALL:1;
        unsigned DTSEN:1;
        unsigned INCDIS:1;
        unsigned KEN:1;
        unsigned DTS:1;
        unsigned UOWN:1;
    };
    struct{


        unsigned :2;
        unsigned PID0:1;
        unsigned PID1:1;
        unsigned PID2:1;
        unsigned PID3:1;
        unsigned :1;
    };
    struct{
        unsigned :2;
        unsigned PID:4;
        unsigned :2;
    };
} BD_STAT;


typedef union __BDT
{
    struct
    {
        BD_STAT STAT;
        BYTE CNT;
        BYTE ADRL;
        BYTE ADRH;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        WORD ADR;
    };
    DWORD Val;
    BYTE v[4];
} BDT_ENTRY;


typedef union __USTAT
{
    struct
    {
        unsigned char filler1:1;
        unsigned char ping_pong:1;
        unsigned char direction:1;
        unsigned char endpoint_number:4;
    };
    BYTE Val;
} USTAT_FIELDS;







typedef union _POINTER
{
    struct
    {
        BYTE bLow;
        BYTE bHigh;

    };
    WORD _word;



    BYTE* bRam;

    WORD* wRam;


    const BYTE* bRom;
    const WORD* wRom;




} POINTER;
# 593 "./usb_hal_pic18.h"
    extern BYTE USBActiveConfiguration;
    extern IN_PIPE inPipes[1];
    extern OUT_PIPE outPipes[1];


extern volatile BDT_ENTRY* pBDTEntryOut[1 +1];
extern volatile BDT_ENTRY* pBDTEntryIn[1 +1];
# 93 "./usb_hal.h" 2
# 136 "./usb_hal.h"
void OTGCORE_SetDeviceAddr( BYTE addr );
# 175 "./usb_hal.h"
    void OTGCORE_ControlUsbResistors( BYTE flags );
# 219 "./usb_hal.h"
BOOL USBHALSessionIsValid( void );
# 245 "./usb_hal.h"
BOOL USBHALControlBusPower( BYTE cmd );
# 286 "./usb_hal.h"
unsigned long USBHALGetLastError( void );
# 332 "./usb_hal.h"
void USBHALHandleBusEvent ( void );
# 373 "./usb_hal.h"
BOOL OTGCORE_StallPipe( TRANSFER_FLAGS pipe );
# 410 "./usb_hal.h"
BOOL OTGCORE_UnstallPipe( TRANSFER_FLAGS pipe );
# 444 "./usb_hal.h"
UINT16 OTGCORE_GetStalledEndpoints ( void );
# 481 "./usb_hal.h"
BOOL USBHALFlushPipe( TRANSFER_FLAGS pipe );
# 541 "./usb_hal.h"
BOOL USBHALTransferData ( TRANSFER_FLAGS flags,
                          void *buffer,
                          unsigned int size );
# 581 "./usb_hal.h"
BOOL USBHALSetEpConfiguration ( BYTE ep_num, UINT16 max_pkt_size, UINT16 flags );
# 631 "./usb_hal.h"
BOOL USBHALInitialize ( unsigned long flags );
# 130 "./usb.h" 2
# 157 "usb_descriptor.c" 2


# 1 "./usb_function_hid.h" 1
# 174 "./usb_function_hid.h"
void USBCheckHIDRequest(void);
# 356 "./usb_function_hid.h"
typedef struct _USB_HID_DSC_HEADER
{
    BYTE bDescriptorType;
    WORD wDscLength;
} USB_HID_DSC_HEADER;



typedef struct _USB_HID_DSC
{
    BYTE bLength;
 BYTE bDescriptorType;
 WORD bcdHID;
    BYTE bCountryCode;
 BYTE bNumDsc;





} USB_HID_DSC;


extern volatile CTRL_TRF_SETUP SetupPkt;
extern const BYTE configDescriptor1[];
extern volatile BYTE CtrlTrfData[8];
# 159 "usb_descriptor.c" 2








const USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,
    0x01,
    0x0200,
    0x00,
    0x00,
    0x00,
    8,
    0x04D8,
    0x005E,
    0x0002,
    0x01,
    0x02,
    0x00,
    0x01
};


const BYTE configDescriptor1[]={

    0x09,
    0x02,
    0x29,0x00,
    1,
    1,
    0,
    (0x01<<7) | (0x01<<6),
    150,


    0x09,
    0x04,
    0,
    0,
    2,
    0x03,
    0,
    0,
    0,


    0x09,
    0x21,
    0x11,0x01,
    0x00,
    1,
    0x22,
    29,0x00,


    0x07,
    0x05,
    1 | 0x80,
    0x03,
    0x40,0x00,
    0x01,


    0x07,
    0x05,
    1 | 0x00,
    0x03,
    0x40,0x00,
    0x01
};



const struct{BYTE bLength;BYTE bDscType;WORD string[1];}sd000={
sizeof(sd000),0x03,{0x0409
}};


const struct{BYTE bLength;BYTE bDscType;WORD string[25];}sd001={
sizeof(sd001),0x03,
{'M','i','c','r','o','c','h','i','p',' ',
'T','e','c','h','n','o','l','o','g','y',' ','I','n','c','.'
}};


const struct{BYTE bLength;BYTE bDscType;WORD string[22];}sd002={
sizeof(sd002),0x03,
{'S','i','m','p','l','e',' ','H','I','D',' ',
'D','e','v','i','c','e',' ','D','e','m','o'
}};


const struct{BYTE report[29];}hid_rpt01={
{
    0x06, 0x00, 0xFF,
    0x09, 0x01,
    0xA1, 0x01,
    0x19, 0x01,
    0x29, 0x40,
    0x15, 0x00,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0x40,
    0x81, 0x02,
    0x19, 0x01,
    0x29, 0x40,
    0x91, 0x02,
    0xC0}
};


const BYTE *const USB_CD_Ptr[]=
{
    (const BYTE *const)&configDescriptor1
};


const BYTE *const USB_SD_Ptr[]=
{
    (const BYTE *const)&sd000,
    (const BYTE *const)&sd001,
    (const BYTE *const)&sd002
};
