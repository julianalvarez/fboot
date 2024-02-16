

#ifndef J1939_H
#define J1939_H

/* Include ********************************************************************/
#include <types32.h>
#include <typedef.h>
/* Enums **********************************************************************/
typedef enum { 
               ADDRESS_CLAIM_TX, 
               ADDRESS_CLAIM_RX
             } ADDRESS_CLAIM_E;

/* Defines ********************************************************************/
#define EXTENDED_FRAME_J1939                0x80U

/* ECU Address */
#define J1939_ADDRESS_JOYSTICK              208U
#define J1939_ADDRESS_GAC                   210U
#define J1939_ADDRESS_OCU                   215U
#define J1939_ADDRESS_UCU                   216U
#define J1939_ADDRESS_HCU                   217U
#define J1939_ADDRESS_UMU                   218U
#define J1939_ADDRESS_HCU2                  219U
#define J1939_ADDRESS_SHU                   220U
#define J1939_ADDRESS_ROCU                  221U
#define J1939_ADDRESS_CANSIP                223U
#define J1939_ADDRESS_CANSTEER              230U
#define J1939_ADDRESS_DD                    232U
#define J1939_ADDRESS_LIGHTBAR              233U
#define J1939_ADDRESS_CANGPRS               234U
#define J1939_ADDRESS_CANGPS                235U
#define J1939_ADDRESS_CANYIELD              236U
#define J1939_ADDRESS_CANKEY                238U
#define J1939_ADDRESS_HUB                   240U
#define J1939_ADDRESS_SBOX                  244U
#define J1939_ADDRESS_VDU                   245U
#define J1939_ADDRESS_AIOU                  246U
#define J1939_ADDRESS_EOS                   J1939_ADDRESS_AIOU
#define J1939_ADDRESS_FBOOT                 251U
#define J1939_ADDRESS_NULL                  254U
#define J1939_ADDRESS_GLOBAL                255U


/* PUT IT IN 1 ERROR GENERAL MODULE */
/* Function Return Codes */
#define RC_QUEUEEMPTY                       1
#define RC_QUEUEFULL                        1
#define RC_CANNOTRECEIVE                    2
#define RC_CANNOTTRANSMIT                   2
#define RC_PARAMERROR                       3
#define RC_NOMORE                           3
#define RC_FINISH  							4
#define RC_SIZEERROR						5	
#define RC_TXBUFFERFULL                     6
        
/* J1939 Default Priorities */
#define J1939_BOOTLOADER_PRIORITY		    1U
#define J1939_CONTROL_PRIORITY              3U
#define J1939_INFO_PRIORITY                 6U
#define J1939_PROPRIETARY_PRIORITY          6U
#define J1939_REQUEST_PRIORITY              6U
#define J1939_ACK_PRIORITY                  6U
#define J1939_TP_CM_PRIORITY                7U
#define J1939_TP_DT_PRIORITY                7U

/* J1939 PDU Formats, Control Bytes, and PGN's */
#define J1939_PF_ADDRESS_CLAIMED            0xEEU	/* With global address */
#define J1939_PF_CANNOT_CLAIM_ADDRESS       0xEEU	/* With null address */
#define J1939_PF_PROPRIETARY_A              0xEFU
#define J1939_PF_PROPRIETARY_B              0xFFU
#define J1939_PF_REQUEST                    0xEAU
#define J1939_PF_ACKNOWLEDGMENT             0xE8U
#define J1939_PF_DM14						0xD9U
#define J1939_PF_DM15						0xD8U
#define J1939_PF_DM16						0xD7U
#define J1939_PF_TPCM                       0xECU
#define J1939_PF_TPDT                       0xEBU
#define J1939_PF_REQUEST2                   0xC9U
#define J1939_PF_TRANSFER                   0xCAU
#define J1939_PF_VTTOECU                    0xE6U
#define J1939_PF_ECUTOVT                    0xE7U
#define J1939_PF_BOOTLOADER					0x01U
#define J1939_PF_RESET_ECU					0x02U

#define J1939_PGN_COMMANDED_ADDRESS         0xFED8U 
#define J1939_PGN_REQUEST                   0xEA00U
#define J1939_PGN_ACKNOWLEDGMENT            0xEE00U
#define J1939_PGN_BOOTLOADER				0x0100U
#define J1939_PGN_RESET_ECU 				0x0200U

#define J1939_MSG_LENGTH                    5U
#define J1939_DATA_LENGTH                   8U

#define GroupExtension                      PDUSpecific
#define DestinationAddress                  PDUSpecific

/* Put all the Transport Protocol in another Module */
#define TP_MAX_PACKETS                      255U
#define TP_MAX_BYTES	                    (TP_MAX_PACKETS * 7U)

/* Max Limit */
#define MAX_VALUE_U8_J1939                  0xFAU
#define MAX_VALUE_U16_J1939                 0xFAFFU
#define MAX_VALUE_U32_J1939                 0xFAFFFFFFUL

/* General VTSIG */
#define VTSIG_SI_U8							0xFBU
#define VTSIG_SI_U16						0xFB00U
#define VTSIG_NA_U2                         0x03U
#define VTSIG_NA_U3                         0x07U
#define VTSIG_NA_U4                         0x0FU
#define VTSIG_NA_U5                         0x1FU
#define VTSIG_NA_U8                         0xFFU
#define VTSIG_NA_U16			            0xFFFFU
#define VTSIG_NA_U32			            0xFFFFFFFFUL

#define VTSIG_OFF							0x00U	
#define VTSIG_ON							0x01U
    
#define VTSIG_ERROR_U2 			   			0x02U
#define VTSIG_ERROR_U3 			   			0x06U
#define VTSIG_ERROR_U4	  			   		0x0EU
#define VTSIG_ERROR_U8	  			   		0xFEU

#define VTSIG_REVERSED 						VTSIG_OFF
#define VTSIG_FORWARD						VTSIG_ON

#define VTSIG_NOT_PRESSED					VTSIG_OFF
#define VTSIG_PRESSED						VTSIG_ON

/* Vehicles Systems */
#define VS_NON_SPECIFIC_SYSTEM_MSG			0U
#define VS_TRACTOR_MSG						1U
#define VS_TILLAGE_MSG						2U
#define VS_SECONDARY_TILLAGE_MSG			3U
#define VS_PLANTERS_SEEDERS_MSG	 			4U
#define VS_FERTILIERS_MSG					5U
#define VS_SPRAYERS_MSG						6U
#define VS_COMBINES_HARVESTERS_MSG			7U
#define VS_ROOT_HARVESTERS_MSG				8U
#define VS_FORAGE_MSG						9U
#define VS_IRRIGATION_MSG					10U

/* Typedefs *******************************************************************/
typedef struct J1939FLAG
{
  unsigned int CannotClaimAddress                :1;
  unsigned int WaitingForAddressClaimContention  :1;
  unsigned int GettingCommandedAddress           :1;
  unsigned int GotFirstDataPacket                :1;
  unsigned int ReceivedMessagesDropped           :1;
} J1939FLAG_T;

#if defined (__GNUC__)
#pragma pack(1)
#endif
typedef struct
{
  U8 Byte[J1939_DATA_LENGTH];   /* CAN DATA LENGTH */
} DATA_T;

/* FIXME: TO ARM */
#if defined (__GNUC__)
#pragma pack(1)
#endif
typedef struct tagJ1939MESSAGE
{
  unsigned int DataLength :4;
  unsigned int Rvd  	  :2;				
  unsigned int bfRTR	  :1;
  unsigned int bfEFF	  :1;

  unsigned int DataPage   :1;
  unsigned int Rvd3 	  :1;
  unsigned int Priority   :3;
  unsigned int Rvd2 	  :3;		

  U8 PDUFormat;			
  U8 PDUSpecific;
  U8 SourceAddress;
  DATA_T Data;
} J1939MESSAGE_T;

/* Externs ********************************************************************/
extern U8				J1939_SrcAddress;
extern U8				J1939_DstAddress;

/* Prototypes *****************************************************************/
#if defined(__cplusplus)
extern "C" 
{
#endif

/* Public: */
void                    txBL_J1939 (U8* pData, U32 Size);
S32                     rxBL_J1939 (U8* pData, U32 Size, U32 Timeout);
void                    PutCmdBL_J1939 (U8 Cmd, U32 Address, U32 Size);
S32                     GetCmdBL_J1939 (U8* Cmd, U32* Address, U32* Size, U32 Timeout);
void					TransmitMessage_J1939 (U16 Pgn, 
                                               U8  Prio, 
											   U8* pData, 
											   U32 Size); 
S32						ReceiveMessages_J1939 (J1939MESSAGE_T* pOneMessage);

/* Private: */
void					mmemcpy (U8* pSrc, U8* pDst, U8 Size);

#if defined(__cplusplus)
}
#endif

#endif /* J1939_H */

/* End of $Workfile: j1939.h$ */



