#include <public/ccledmng_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCLEDMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCLEDMng &act,
	 TEDROOMUInt8 & EDROOMpVarVLEDPos,
	 TEDROOMBool & EDROOMpVarVShiftDirection,
	 TEDROOMUInt32 & EDROOMpVarVShiftPeriodMicrosecs,
	 Pr_Time & EDROOMpVarVTimeRef ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	LEDMngCtrl(EDROOMcomponent.LEDMngCtrl),
	Timer(EDROOMcomponent.Timer),
	CMaxShiftPeriodMicrosecs(900000),
	CMinShiftPeriodMicrosecs(100000),
	VLEDPos(EDROOMpVarVLEDPos),
	VShiftDirection(EDROOMpVarVShiftDirection),
	VShiftPeriodMicrosecs(EDROOMpVarVShiftPeriodMicrosecs),
	VTimeRef(EDROOMpVarVTimeRef)
{
}

CCLEDMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	LEDMngCtrl(context.LEDMngCtrl),
	Timer(context.Timer),
	CMaxShiftPeriodMicrosecs(900000),
	CMinShiftPeriodMicrosecs(100000),
	VLEDPos(context.VLEDPos),
	VShiftDirection(context.VShiftDirection),
	VShiftPeriodMicrosecs(context.VShiftPeriodMicrosecs),
	VTimeRef(context.VTimeRef)
{

}

	// EDROOMSearchContextTrans********************************************

bool CCLEDMng::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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

void	CCLEDMng::EDROOM_CTX_Top_0::FGetShiftPeriod()

{
   //Handle Msg->data
  TEDROOMUInt8 & varSLEDStart = *(TEDROOMUInt8 *)Msg->data;
 
 
// Data access
 
VShiftPeriodMicrosecs=varSLEDStart*100000;
 
//Limit Period
 
if(VShiftPeriodMicrosecs > CMaxShiftPeriodMicrosecs)
	VShiftPeriodMicrosecs=CMaxShiftPeriodMicrosecs;
else if (varSLEDStart < CMinShiftPeriodMicrosecs)
	VShiftPeriodMicrosecs=CMinShiftPeriodMicrosecs;
 
//Get Time reference
 
VTimeRef.GetTime();

}



void	CCLEDMng::EDROOM_CTX_Top_0::FProgShift()

{
   //Define absolute time
  Pr_Time time;
 
	 
 VTimeRef+=Pr_Time(0,VShiftPeriodMicrosecs); // interval of X sec + Y microsec	 
  
 time= VTimeRef;
   //Program absolute timer 
   Timer.InformAt( time ); 
}



void	CCLEDMng::EDROOM_CTX_Top_0::FReplyLEDShiftToggled()

{

VShiftDirection=!VShiftDirection;
   //Reply synchronous communication
   Msg->reply(SLEDShiftToggled); 
}



void	CCLEDMng::EDROOM_CTX_Top_0::FSendLEDReady()

{

   //Send message 
   LEDMngCtrl.send(SLEDReady); 
}



void	CCLEDMng::EDROOM_CTX_Top_0::FShiftLEDs()

{

nexys_srg_gpio_turn_off_led(VLEDPos);
 
if(VShiftDirection){
 
	VLEDPos=(VLEDPos + 1)%10;
}else{
	if(VLEDPos){
		VLEDPos--;
	}else{
		VLEDPos=9;
	}
}
 
nexys_srg_gpio_turn_on_led(VLEDPos);

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCLEDMng::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCLEDMng&act):
		EDROOM_CTX_Top_0(act,
			VLEDPos,
			VShiftDirection,
			VShiftPeriodMicrosecs,
			VTimeRef),
		VLEDPos(0),
		VShiftDirection(0),
		VShiftPeriodMicrosecs(100000)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCLEDMng::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Transicion0
			case (Transicion0):
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Start
			case (Start):
				//Msg->Data Handling 
				FGetShiftPeriod();
				//Execute Action 
				FProgShift();
				//Send Asynchronous Message 
				FSendLEDReady();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is ShiftTimeout
			case (ShiftTimeout):
				//Execute Actions 
				FShiftLEDs();
				FProgShift();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is ToggleShift
			case (ToggleShift):
				//Reply Synchronous Message 
				FReplyLEDShiftToggled();
				//Next State is Ready
				edroomNextState = Ready;
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

				//Go to the state Idle
			case (Idle):
				//Arrival to state Idle
				edroomCurrentTrans=EDROOMIdleArrival();
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

void CCLEDMng::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCLEDMng::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Transicion0
	edroomCurrentTrans.localId = Transicion0;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CCLEDMng::EDROOM_SUB_Top_0::EDROOMIdleArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SLEDStart): 

				 if (*Msg->GetPInterface() == LEDMngCtrl)
				{

					//Next transition is  Start
					edroomCurrentTrans.localId= Start;
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

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCLEDMng::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  ShiftTimeout
					edroomCurrentTrans.localId= ShiftTimeout;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (SToggleLEDShift): 

				 {
					//Next transition is  ToggleShift
					edroomCurrentTrans.localId= ToggleShift;
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



