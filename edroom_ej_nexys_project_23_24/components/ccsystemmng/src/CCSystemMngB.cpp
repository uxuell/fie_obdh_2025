#include <public/ccsystemmng_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCSystemMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCSystemMng &act,
	 TEDROOMByte & EDROOMpVarVCommand,
	 CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	DisplaysMngCtrl(EDROOMcomponent.DisplaysMngCtrl),
	LEDMngCtrl(EDROOMcomponent.LEDMngCtrl),
	SerialCommand(EDROOMcomponent.SerialCommand),
	CLEDPeriod100Ms(1),
	VCommand(EDROOMpVarVCommand),
	EDROOMPoolTEDROOMUInt8(EDROOMpPoolTEDROOMUInt8)
{
}

CCSystemMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	DisplaysMngCtrl(context.DisplaysMngCtrl),
	LEDMngCtrl(context.LEDMngCtrl),
	SerialCommand(context.SerialCommand),
	CLEDPeriod100Ms(1),
	VCommand(context.VCommand),
	EDROOMPoolTEDROOMUInt8(context.EDROOMPoolTEDROOMUInt8 )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCSystemMng::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCSystemMng::EDROOM_CTX_Top_0::FGetCommand()

{
   //Handle Msg->data
  TEDROOMByte & varEDROOMIRQsignal = *(TEDROOMByte *)Msg->data;
	
		// Data access
	
	VCommand=varEDROOMIRQsignal;

}



void	CCSystemMng::EDROOM_CTX_Top_0::FInit()

{

SerialCommand.MaskIRQ();
 
SerialCommand.InstallHandler();
 
leon3_uart_ctrl_rx_irq_enable();
leon3_uart_ctrl_rx_enable();
 
SerialCommand.UnMaskIRQ();
 
nexys_srg_gpio_init_buttons_switches();
 
nexys_srg_gpio_init_leds_7segs_displays();

}



void	CCSystemMng::EDROOM_CTX_Top_0::FSendIncreaseDisplays()

{

   //Send message 
   DisplaysMngCtrl.send(SIncreaseDisplays); 
}



bool	CCSystemMng::EDROOM_CTX_Top_0::GCmdIsIncreaseDisplays()

{

return (('i'==VCommand) || ('I'==VCommand));

}



bool	CCSystemMng::EDROOM_CTX_Top_0::GCmdIsToggleLEDShift()

{

return (('t'==VCommand) || ('T'==VCommand));

}



void	CCSystemMng::EDROOM_CTX_Top_0::FInvokeToogleLEDShift()

{

   //Invoke synchronous communication 
   MsgBack=LEDMngCtrl.invoke(SToggleLEDShift); 
}



// ***********************************************************************

// class EDROOM_CTX_StartUp_1

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCSystemMng::EDROOM_CTX_StartUp_1::EDROOM_CTX_StartUp_1(EDROOM_CTX_Top_0 &context):
	EDROOM_CTX_Top_0(context)
{

}

CCSystemMng::EDROOM_CTX_StartUp_1::EDROOM_CTX_StartUp_1(
	EDROOM_CTX_StartUp_1 &context ):
		EDROOM_CTX_Top_0(context)
{

}

	// EDROOMSearchContextTrans********************************************

bool CCSystemMng::EDROOM_CTX_StartUp_1::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg = false; 

	if (false == edroomValidMsg)
	{

		 edroomValidMsg = 
			EDROOM_CTX_Top_0::EDROOMSearchContextTrans(edroomCurrentTrans);
		 if (edroomValidMsg)
		 {
			edroomCurrentTrans.distanceToContext++;
		 }

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCSystemMng::EDROOM_CTX_StartUp_1::FSendDisplaysStart()

{

   //Send message 
   DisplaysMngCtrl.send(SDisplaysStart); 
}



void	CCSystemMng::EDROOM_CTX_StartUp_1::FSendLEDStart()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSLEDStart_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSLEDStart_Data=CLEDPeriod100Ms;
   //Send message 
   LEDMngCtrl.send(SLEDStart,pSLEDStart_Data,&EDROOMPoolTEDROOMUInt8); 
}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CCSystemMng::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(
			TEDROOMUInt32 elemCount,TEDROOMUInt8* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(TEDROOMUInt8))
{
}

TEDROOMUInt8 *	CCSystemMng::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::AllocData()
{
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCSystemMng::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCSystemMng&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VCommand,
			EDROOMPoolTEDROOMUInt8),
		EDROOMStartUp(StartUp , *this),
		VCommand('z'),
		EDROOMPoolTEDROOMUInt8(
			2, pEDROOMMemory->poolTEDROOMUInt8,
			pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCSystemMng::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Init
			case (Init):
				//Execute Action 
				FInit();
				//Next State is StartUp
				edroomNextState = StartUp;
				break;
			//Next Transition is SybsysReady
			case (SybsysReady):
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//To Choice Point GetCommand
			case (GetCommand):

				//Msg->Data Handling 
				FGetCommand();
				//Evaluate Branch ToggleLEDShift
				if( GCmdIsToggleLEDShift() )
				{
					//Invoke Synchronous Message 
					FInvokeToogleLEDShift();

					//Branch taken is GetCommand_ToggleLEDShift
					edroomCurrentTrans.localId =
						GetCommand_ToggleLEDShift;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch IncreaseDisplays
				else if( GCmdIsIncreaseDisplays() )
				{
					//Send Asynchronous Message 
					FSendIncreaseDisplays();

					//Branch taken is GetCommand_IncreaseDisplays
					edroomCurrentTrans.localId =
						GetCommand_IncreaseDisplays;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Default Branch NotValidCommand
				else
				{

					//Branch taken is GetCommand_NotValidCommand
					edroomCurrentTrans.localId =
						GetCommand_NotValidCommand;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state I
			case (I):
				//Arrival to state I
				edroomCurrentTrans=EDROOMIArrival();
				break;

				//Go to the state StartUp
			case (StartUp):
				//Arrival to state StartUp
				edroomCurrentTrans=EDROOMStartUp.Arrival(
				(TEDROOMTransitionID) edroomCurrentTrans.localId);
				break;

				//Go to the state Ready
			case (Ready):
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCSystemMng::EDROOM_SUB_Top_0::EDROOMInit()
{

EDROOMStartUp.EDROOMInit();
edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCSystemMng::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCSystemMng::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMIRQsignal): 

				 if (*Msg->GetPInterface() == SerialCommand)
				{

					//Next transition is  GetCommand
					edroomCurrentTrans.localId = GetCommand;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



// ***********************************************************************

// class EDROOM_SUB_StartUp_1

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCSystemMng::EDROOM_SUB_StartUp_1::EDROOM_SUB_StartUp_1(
	EDROOM_CTX_Top_0::TEDROOMStateID stateID, 
	EDROOM_CTX_Top_0 &context):
		EDROOM_CTX_StartUp_1(context)
{
	edroomStateID =stateID; 
}

	// llegada**********************************************

TEDROOMTransId CCSystemMng::EDROOM_SUB_StartUp_1::Arrival(
	EDROOM_CTX_Top_0::TEDROOMTransitionID arrivingTrans)
{

	TEDROOMTransId edroomCurrentTrans;

	int edroomContextExit=0;

	//Transition at Context Entry
	switch (arrivingTrans)
	{

		//From entry point Init
		case (EDROOM_CTX_Top_0::Init):
			edroomCurrentTrans.localId= StartLED;
			edroomNextState = WaitLEDReady;
		//Send Asynchronous Message 
		FSendLEDStart();
			break;
		case (EDROOM_CTX_Top_0::EDROOMMemoryTrans):
			//Memory Entry added
			edroomCurrentTrans.localId = EDROOMMemoryTrans ;
			edroomNextState = edroomCurrentState;
			break;
		default:
			//Default is memory entry
			edroomCurrentTrans.localId = EDROOMMemoryTrans ;
			edroomNextState = edroomCurrentState;
			break;
	}

	do
	{

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state WaitLEDReady
			case (WaitLEDReady):
				//Arrival to state WaitLEDReady
				edroomCurrentTrans=EDROOMWaitLEDReadyArrival();
				break;

				//Go to the state WaitDisplaysReady
			case (WaitDisplaysReady):
				//Arrival to state WaitDisplaysReady
				edroomCurrentTrans=EDROOMWaitDisplaysReadyArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

		if (edroomCurrentTrans.distanceToContext == 0)
		{

			switch (edroomCurrentTrans.localId)
			{

				case (StartDisplays):
				//Send Asynchronous Message 
				FSendDisplaysStart();
					//Go to the state WaitDisplaysReady
					edroomNextState = WaitDisplaysReady;
					edroomContextExit=0;
					break;

				case (DisplaysReady):
					//Exit across the exit point SybsysReady
					edroomCurrentTrans.localId= 
						EDROOM_CTX_Top_0::SybsysReady;
					edroomCurrentTrans.distanceToContext= 1;
					edroomContextExit=1;
					break;

			}

		}else
		{
			edroomContextExit=1;
		}

	}while(0 == edroomContextExit);

	edroomCurrentTrans.distanceToContext--;

	return(edroomCurrentTrans);

}



	// Context Init**********************************************

void CCSystemMng::EDROOM_SUB_StartUp_1::EDROOMInit()
{

}



	// ***********************************************************************

	// Leaf SubState  WaitLEDReady

	// ***********************************************************************



TEDROOMTransId CCSystemMng::EDROOM_SUB_StartUp_1::EDROOMWaitLEDReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SLEDReady): 

				 if (*Msg->GetPInterface() == LEDMngCtrl)
				{

					//Next transition is  StartDisplays
					edroomCurrentTrans.localId= StartDisplays;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  WaitDisplaysReady

	// ***********************************************************************



TEDROOMTransId CCSystemMng::EDROOM_SUB_StartUp_1::EDROOMWaitDisplaysReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SDisplaysReady): 

				 if (*Msg->GetPInterface() == DisplaysMngCtrl)
				{

					//Next transition is  DisplaysReady
					edroomCurrentTrans.localId= DisplaysReady;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



